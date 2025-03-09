#include "ClientMain.h"

// unsigned char GetPacketIdentifier(RakNet::Packet *p)
// {
// 	if (p==0)2
// 		return 255;

// 	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
// 	{
// 		RakAssert(p->length > sizeof(RakNet::MessageID) + sizeof(RakNet::Time));
// 		return (unsigned char) p->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time)];
// 	}
// 	else
// 		return (unsigned char) p->data[0];
// }


ClientMain::ClientMain()
{
    pw = "DavaiMachi";
    m_serverIP = "127.0.0.1";
    m_port = 1123;
}


ClientMain::~ClientMain()
{

}

void ClientMain::init(const std::string & serverIP,const std::string & pw,unsigned int port, unsigned int serverSize)
{
    std::cout << "Init Client \n";

    m_client = RakNet::RakPeerInterface::GetInstance();

    m_serverIP = serverIP;
    m_port = port;
    m_connectionSize = serverSize;

    m_client->AllowConnectionResponseIPMigration(false);


    m_socketDescriptor = RakNet::SocketDescriptor(m_port + 2, 0);
    m_socketDescriptor.socketFamily = AF_INET;
    m_client->Startup(8, &m_socketDescriptor, 1);
    m_client->SetOccasionalPing(true);

    // m_socketDescriptor[0].port = m_port;
    // m_socketDescriptor[0].socketFamily = AF_INET;
    // m_socketDescriptor[1].port = m_port;
    // m_socketDescriptor[1].socketFamily = AF_INET6;

    
    RakNet::ConnectionAttemptResult car = m_client->Connect(m_serverIP.c_str(), m_port, pw.c_str(), pw.size());

    RakAssert(car == RakNet::CONNECTION_ATTEMPT_STARTED);

    std::cout << "IP address: \n";

    for(int i = 0; i <m_client->GetNumberOfAddresses(); i++)
    {
        printf("%i. %s\n", i+1, m_client->GetLocalIP(i));
    }
    std::cout << "init networking OK ! \n";
    std::cout << "GUID is : " << m_client->GetGuidFromSystemAddress(RakNet::UNASSIGNED_SYSTEM_ADDRESS).ToString() << "\n"; 


    //m_scriptManager = new ClientScriptingManager();
    //m_scriptManager->init(m_client);

}


void ClientMain::run()
{
    while(m_clientOn)
    {
        // This sleep keeps RakNet responsive
#ifdef _WIN32
		Sleep(30);
#else
		usleep(30 * 1000);
#endif
        update(1.0f);
        handleInput();
    }

    m_client->Shutdown(300);
    RakNet::RakPeerInterface::DestroyInstance(m_client);
    std::cout << "Client shutdown \n"; 

}
void ClientMain::update(float deltaTime)
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
				printf("ID_DISCONNECTION_NOTIFICATION\n");
				break;
			case ID_ALREADY_CONNECTED:
				// Connection lost normally
				printf("ID_ALREADY_CONNECTED with guid %" PRINTF_64_BIT_MODIFIER "u\n", m_currentPacket->guid);
				break;
			case ID_INCOMPATIBLE_PROTOCOL_VERSION:
				printf("ID_INCOMPATIBLE_PROTOCOL_VERSION\n");
				break;
			case ID_REMOTE_DISCONNECTION_NOTIFICATION: // Server telling the clients of another client disconnecting gracefully.  You can manually broadcast this in a peer to peer enviroment if you want.
				printf("ID_REMOTE_DISCONNECTION_NOTIFICATION\n"); 
				break;
			case ID_REMOTE_CONNECTION_LOST: // Server telling the clients of another client disconnecting forcefully.  You can manually broadcast this in a peer to peer enviroment if you want.
				printf("ID_REMOTE_CONNECTION_LOST\n");
				break;
			case ID_REMOTE_NEW_INCOMING_CONNECTION: // Server telling the clients of another client connecting.  You can manually broadcast this in a peer to peer enviroment if you want.
				printf("ID_REMOTE_NEW_INCOMING_CONNECTION\n");
				break;
			case ID_CONNECTION_BANNED: // Banned from this server
				printf("We are banned from this server.\n");
				break;			
			case ID_CONNECTION_ATTEMPT_FAILED:
				printf("Connection attempt failed\n");
				break;
			case ID_NO_FREE_INCOMING_CONNECTIONS:
				// Sorry, the server is full.  I don't do anything here but
				// A real app should tell the user
				printf("ID_NO_FREE_INCOMING_CONNECTIONS\n");
				break;

			case ID_INVALID_PASSWORD:
				printf("ID_INVALID_PASSWORD\n");
				break;

			case ID_CONNECTION_LOST:
				// Couldn't deliver a reliable packet - i.e. the other system was abnormally
				// terminated
				printf("ID_CONNECTION_LOST\n");
				break;

			case ID_CONNECTION_REQUEST_ACCEPTED:
				// This tells the client they have connected
				printf("ID_CONNECTION_REQUEST_ACCEPTED to %s with GUID %s\n", m_currentPacket->systemAddress.ToString(true), m_currentPacket->guid.ToString());
				printf("My external address is %s\n", m_client->GetExternalID(m_currentPacket->systemAddress).ToString(true));
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
                m_client->DeallocatePacket(m_currentPacket);
                m_currentPacket = nullptr;
                //std::flush(std::ostream&);
		}

}

PacketCode ClientMain::getCommand(const std::string & command)
{
    // if command contains certain word
    if(command == "quit" || command == "exit")
    {
        return PacketCode::QUIT;
    }

    if(command.find("stats") != std::string::npos)
    {
        return PacketCode::STATS;
    }
    if(command == "connect")
    {
        return PacketCode::CONNECT;
    }
    if(command == "disconnect" || command == "dc")
    {
        return PacketCode::DISCONNECT;
    }
    if(command == "ping")
    {
        return PacketCode::PING;
    }
    if(command == "glp")
    {
        return PacketCode::GETLASTPING;
    }
    if(command == "startup")
    {
        return PacketCode::STARTUP;
    }
    if(command == "shutdown")
    {
        return PacketCode::SHUTDOWN;
    }
    if(command == "login")
    {
        return PacketCode::LOGIN;
    }
    if(command == "register")
    {
        return PacketCode::REGISTER;
    }
    if(command == "key" || command == "getkey")
    {
        return PacketCode::REQUEST_KEY;
    }

    return PacketCode::UNKNOWN;
}

void ClientMain::handleInput()
{
    if(kbhit())
    {
        Gets(messageBuffer,sizeof(messageBuffer));
        handleCommand(messageBuffer);
        
    }
}

void ClientMain::handleCommand(const std::string & command)
{
    PacketCode rc = getCommand(command);

    switch(rc)
    {

    case PacketCode::QUIT:
    {
        // dc before quit
        m_client->CloseConnection(m_client->GetSystemAddressFromIndex(0),false);
        m_clientOn = false;
        break;
    }

    case PacketCode::STATS:
    {
        m_statistics = m_client->GetStatistics(m_client->GetSystemAddressFromIndex(0));
        StatisticsToString(m_statistics, messageBuffer, 2);
        printf("%s", messageBuffer);
        printf("Ping %i\n", m_client->GetAveragePing(m_client->GetSystemAddressFromIndex(0)));
    }
        break;

    case PacketCode::CONNECT:
    {


        std::cout << "try to connect to server \n";
        bool connectResult = m_client->Connect(m_serverIP.c_str(), m_port, "TTKR",strlen("TTKR")) == RakNet::CONNECTION_ATTEMPT_STARTED;
        if(connectResult)
        {
            std::cout << "Atteming connection \n";
        }
        else
        {
            std::cout << "Connection failed \n";
        }
        break;
    }
    case PacketCode::DISCONNECT:
    {
        // printf("Enter index to disconnect: ");
        // char str[32];
        // Gets(str, sizeof(str));
        // if (str[0]==0)
        //     strcpy(str,"0");
        // int index = atoi(str);
        int index = 0;

        m_client->CloseConnection(m_client->GetSystemAddressFromIndex(index),false);
        printf("Disconnecting.\n");
        break;
    }

    case PacketCode::STARTUP:
    {
        bool b = m_client->Startup(8,&m_socketDescriptor, 1)==RakNet::RAKNET_STARTED;
        if (b)
        {
            printf("Started.\n");
        }
        else
        {
            printf("Startup failed.\n");
        }
    }

    case PacketCode::PING:
    {
        if (m_client->GetSystemAddressFromIndex(0)!=RakNet::UNASSIGNED_SYSTEM_ADDRESS)
        {
            m_client->Ping(m_client->GetSystemAddressFromIndex(0));
        }
    }
        break;

    case PacketCode::GETLASTPING:
    {
        if (m_client->GetSystemAddressFromIndex(0)!=RakNet::UNASSIGNED_SYSTEM_ADDRESS)
        {
            printf("Last ping is %i\n", m_client->GetLastPing(m_client->GetSystemAddressFromIndex(0)));
        }
		break;	
    }

    case PacketCode::LOGIN:
    {
        std::cout << "enter ID : \n";
        std::cin >> m_idStr;
        std::cout << "enter password : \n";
        std::cin >> m_pwStr;

        std::string packet = combine2Package("LOGIN",m_idStr, m_pwStr);
        m_client->Send(packet.c_str(), packet.length() +1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
        
        std::cout << "sent " << packet <<  "\n";
    }
    break;

    case PacketCode::REGISTER:
    {
        std::cout << "enter ID : \n";
        std::cin >> m_registerID;
        std::cout << "enter password : \n";
        std::cin >> m_registerPw;
        std::cout << "confirm password : \n";
        std::cin >> m_regiserPWConfirm;

        int retry = 0;
        while(retry < 4)
        {
            if (std::strcmp(m_registerPw.c_str(), m_regiserPWConfirm.c_str()) != 0)
            {
                std::cout << "Password does not match, try again \n";
                std::cout << "enter password : \n";
                std::cin >> m_registerPw;
                std::cout << "confirm password : \n";
                std::cin >> m_regiserPWConfirm;
                retry ++;
            }
            else if (std::strcmp(m_registerPw.c_str(), m_regiserPWConfirm.c_str()) == 0)
            {
                retry = 4;
                break;
            }
            else
            {
                std::cout << "end\n";
            }

        };
        
        std::cout << "enter key : \n";
        std::cin >> m_registerKey;

        std::string packet = combine3Package("REGISTER",m_registerID, m_registerPw,m_registerKey);
        m_client->Send(packet.c_str(), packet.length() +1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
        
    }
    break;

    case PacketCode::REQUEST_KEY:
    {
        std::cout << "enter ID : \n";
        std::cin >> m_idStr;
        std::cout << "enter password : \n";
        std::cin >> m_pwStr;
        std::string packet = combine2Package("REQUEST_KEY",m_idStr, m_pwStr);
        m_client->Send(packet.c_str(), packet.length() +1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
        
    }
    break;

    default:
    {
        m_client->Send(command.c_str(), command.length() +1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);

    }
        break;
    }


}