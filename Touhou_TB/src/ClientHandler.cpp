

#include "ClientHandler.h"



ClientHandler::ClientHandler()
{
    pw = "DavaiMachi";
}

ClientHandler::~ClientHandler()
{

}

void ClientHandler::init(const std::string & serverIP, unsigned int port)
{
    std::cout << "Init Client \n";

    // pw = serverPW;

    m_client = RakNet::RakPeerInterface::GetInstance();

    m_serverIP = serverIP;
    m_port = port;
    
    m_client->AllowConnectionResponseIPMigration(false);


    m_socketDescriptor = RakNet::SocketDescriptor(m_port + 1, 0);
    m_socketDescriptor.socketFamily = AF_INET;
    m_client->Startup(8, &m_socketDescriptor, 1);
    m_client->SetOccasionalPing(true);

    m_isInited = true;

}

void ClientHandler::connect()
{
    if(m_isInited)
    {
        RakNet::ConnectionAttemptResult car = m_client->Connect(m_serverIP.c_str(), m_port, pw.c_str(), pw.size());
        RakAssert(car == RakNet::CONNECTION_ATTEMPT_STARTED);
    
        std::cout << "IP address: \n";
        for(int i = 0; i < m_client->GetNumberOfAddresses(); i++)
        {
            printf("%i. %s\n", i+1, m_client->GetLocalIP(i));
        }
        // std::cout << "init networking OK ! \n";
        std::cout << "GUID is : " << m_client->GetGuidFromSystemAddress (RakNet::UNASSIGNED_SYSTEM_ADDRESS).ToString() << "\n"; 
        // if(car != RakNet::CONNECTION_ATTEMPT_STARTED)
        // {
        //     m_isConnected = true;
        // }
        //m_isConnected = true;
        
    }
}

void ClientHandler::update(float deltaTime)
{
    for (m_currentPacket=m_client->Receive(); 
    m_currentPacket;
    m_client->DeallocatePacket(m_currentPacket),
    m_currentPacket=m_client->Receive())
		{
			// We got a packet, get the identifier with our handy function
			unsigned char packetIdentifier = GetPacketIdentifier(m_currentPacket);

			// Check if this is a network message packet
			switch (packetIdentifier)
			{
			case ID_DISCONNECTION_NOTIFICATION:
				// Connection lost normally
				printf("Disconnected !!!\n");
                m_isConnected = false;
                m_status = Status::Disconnected;
				break;
			case ID_ALREADY_CONNECTED:
				// Connection lost normally
				printf("already connected with guid %" PRINTF_64_BIT_MODIFIER "u\n", m_currentPacket->guid);
                m_isConnected = true;
                m_status = Status::Connected;
				break;
			case ID_INCOMPATIBLE_PROTOCOL_VERSION:
				printf("error code K2 D32\n");
                m_status = Status::Disconnected;
				break;
			case ID_REMOTE_DISCONNECTION_NOTIFICATION: // Server telling the clients of another client disconnecting gracefully.  You can manually broadcast this in a peer to peer enviroment if you want.
				printf("remote disconnect\n"); 
                m_status = Status::Disconnected;
                // m_isConnected = false;
				break;
			case ID_REMOTE_CONNECTION_LOST: // Server telling the clients of another client disconnecting forcefully.  You can manually broadcast this in a peer to peer enviroment if you want.
				printf("remove connection lost\n");
                m_status = Status::Disconnected;
                m_isConnected = false;
				break;
			case ID_REMOTE_NEW_INCOMING_CONNECTION: // Server telling the clients of another client connecting.  You can manually broadcast this in a peer to peer enviroment if you want.
				printf("remote new incoming\n");
				break;
			case ID_CONNECTION_BANNED: // Banned from this server
				printf("Banned\n");
                m_status = Status::Banned;
				break;			
			case ID_CONNECTION_ATTEMPT_FAILED:
				printf("Connection attempt failed\n");
                m_status = Status::FailedAttemp;
				break;
			case ID_NO_FREE_INCOMING_CONNECTIONS:
				// Sorry, the server is full.  I don't do anything here but
				// A real app should tell the user
                m_status = Status::IsFull;
				printf("Server is full\n");
				break;
			case ID_INVALID_PASSWORD:
                m_status = Status::WSPacket;
				printf("error code K2 D31\n");
				break;

			case ID_CONNECTION_LOST:
                m_status = Status::Disconnected;
				// Couldn't deliver a reliable packet - i.e. the other system was abnormally
				// terminated
				printf("Lost connection\n");
                m_isConnected = false;
				break;

			case ID_CONNECTION_REQUEST_ACCEPTED:
				// This tells the client they have connected
				printf("Able to connect to %s gennerated GUID %s\n", m_currentPacket->systemAddress.ToString(true), m_currentPacket->guid.ToString());
				printf("My external address is %s\n", m_client->GetExternalID(m_currentPacket->systemAddress).ToString(true));
                m_status = Status::Connected;
                m_isConnected = true;
				break;
			case ID_CONNECTED_PING:
			case ID_UNCONNECTED_PING:
				printf("Ping from %s\n", m_currentPacket->systemAddress.ToString(true));
				break;
			default:
				// It's a client, so just show the message
                {
                    std::string msg ((const char*)m_currentPacket->data);
                    std::cout << "server : " << msg << std::endl;
                    break;
                }
			}
                // m_client->DeallocatePacket(m_currentPacket);
                // m_currentPacket = nullptr;
                //std::flush(std::ostream&);
		}

}