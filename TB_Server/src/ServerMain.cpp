#include "ServerMain.h"

unsigned char GetPacketIdentifier(RakNet::Packet *p)
{
	if (p==0)
		return 255;

	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
	{
		RakAssert(p->length > sizeof(RakNet::MessageID) + sizeof(RakNet::Time));
		return (unsigned char) p->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time)];
	}
	else
		return (unsigned char) p->data[0];
}


ServerMain::ServerMain()
{
    m_password = "TTKR";
    m_port = 1123 ;
}

int ServerMain::handleStep2Request(RakNet::Packet *p)
{
    RequestCode requestCode = getSpecialRequestCode(p);
    switch (requestCode)
    {
        case RequestCode::login:
        {
            std::cout << "Login request found !!!\n";
            // todo : verify login

            return 12;
        }
        break;
        default :
            return 0;
        break;
    }
    return -22;
}


ServerMain::~ServerMain()
{

}

void ServerMain::init(const std::string & password, int port,unsigned int serverSize)
{

    std::cout << "|=========================================|\n";
	std::cout << "|            Init DataBase                |\n";
	m_dbh.loadDataBase("../data/tData.db");
	std::cout << "|=========================================|\n";
    std::cout << "|             Init Server                 |\n";

    m_server = RakNet::RakPeerInterface::GetInstance();

    m_password = password;
    m_port = port;
    m_connectionSize = serverSize;

    m_server->SetIncomingPassword("TTKR", strlen("TTKR"));
	m_server->SetTimeoutTime(5000,RakNet::UNASSIGNED_SYSTEM_ADDRESS);
    m_server->SetMaximumIncomingConnections(m_connectionSize);


    m_socketDescriptor[0].port = m_port;
    m_socketDescriptor[0].socketFamily = AF_INET;
    m_socketDescriptor[1].port = m_port;
    m_socketDescriptor[1].socketFamily = AF_INET6;



    bool init2IPVer = m_server->Startup(10, m_socketDescriptor,2) == RakNet::RAKNET_STARTED;
    if (!init2IPVer)
    {
        std::cout << "Failed to start dual IPV4 and IPV6 ports. Trying IPV4 only.\n";
        bool init1IPVer = m_server->Startup(m_connectionSize, m_socketDescriptor, 1) == RakNet::RAKNET_STARTED;

        if (!init1IPVer)
        {
            std::cout << "Server failed to start.  Terminating.\n";
            exit(1);
        }
    }

    m_server->SetOccasionalPing(true);
	m_server->SetUnreliableTimeout(1000);

	DataStructures::List< RakNet::RakNetSocket2* > sockets;
	m_server->GetSockets(sockets);
    std::cout << "Socket addresses used by RakNet:\n";
	for (unsigned int i=0; i < sockets.Size(); i++)
	{
		printf("%i. %s\n", i+1, sockets[i]->GetBoundAddress().ToString(true));
	}

    std::cout << "\nServer's IP addresses:\n";
	for (unsigned int i=0; i < m_server->GetNumberOfAddresses(); i++)
	{
		RakNet::SystemAddress sa = m_server->GetInternalID(RakNet::UNASSIGNED_SYSTEM_ADDRESS, i);
		printf("%i. %s (LAN=%i)\n", i+1, sa.ToString(false), sa.IsLANAddress());
	}
    printf("\nGUID: %s\n", m_server->GetGuidFromSystemAddress(RakNet::UNASSIGNED_SYSTEM_ADDRESS).ToString());
    

}


void ServerMain::run()
{
    while(m_serverOn)
    {

        // This sleep keeps RakNet responsive
        RakSleep(30);
        update(1.0f);

        handleInput();
    }
    m_server->Shutdown(300);
    RakNet::RakPeerInterface::DestroyInstance(m_server);
    std::cout << "Server shutdown \n"; 

}
void ServerMain::update(float deltaTime)
{
    for (m_currentPacket=m_server->Receive(); m_currentPacket; m_server->DeallocatePacket(m_currentPacket), m_currentPacket=m_server->Receive())
		{
			// We got a packet, get the identifier with our handy function
            unsigned char packetIdentifier = GetPacketIdentifier(m_currentPacket);

			// Check if this is a network message packet
			switch (packetIdentifier)
			{
			case ID_DISCONNECTION_NOTIFICATION:
				// Connection lost normally
				printf("ID_DISCONNECTION_NOTIFICATION from %s\n", m_currentPacket->systemAddress.ToString(true));;
				break;


			case ID_NEW_INCOMING_CONNECTION:
				// Somebody connected.  We have their IP now
				printf("ID_NEW_INCOMING_CONNECTION from %s with GUID %s\n", m_currentPacket->systemAddress.ToString(true), m_currentPacket->guid.ToString());
				m_clientID=m_currentPacket->systemAddress; // Record the player ID of the client

				printf("Remote internal IDs:\n");
				for (int index=0; index < MAXIMUM_NUMBER_OF_INTERNAL_IDS; index++)
				{
					RakNet::SystemAddress internalId = m_server->GetInternalID(m_currentPacket->systemAddress, index);
					if (internalId!=RakNet::UNASSIGNED_SYSTEM_ADDRESS)
					{
						printf("%i. %s\n", index+1, internalId.ToString(true));
					}
				}

				break;

			case ID_INCOMPATIBLE_PROTOCOL_VERSION:
				printf("ID_INCOMPATIBLE_PROTOCOL_VERSION\n");
				break;

			case ID_CONNECTED_PING:
			case ID_UNCONNECTED_PING:
				printf("Ping from %s\n", m_currentPacket->systemAddress.ToString(true));
				break;

			case ID_CONNECTION_LOST:
				// Couldn't deliver a reliable packet - i.e. the other system was abnormally
				// terminated
				printf("ID_CONNECTION_LOST from %s\n", m_currentPacket->systemAddress.ToString(true));;
				break;

			default:

                handleStep2Request(m_currentPacket);
				// The server knows the static data of all clients, so we can prefix the message
				// With the name data
				printf("%s\n", m_currentPacket->data);

				// Relay the message.  We prefix the name for other clients.  This demonstrates
				// That messages can be changed on the server before being broadcast
				// Sending is the same as before
                sprintf(messageBuffer, "Relay msg: %s", m_currentPacket->data);
				
				m_server->Send(messageBuffer, (const int) strlen(messageBuffer)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_currentPacket->systemAddress, true);

				break;
			}

		}

}

ServerCommand ServerMain::getCommand(const std::string & command)
{
    // if command contains certain word
    if(command == "quit" || command == "exit")
    {
        return ServerCommand::QUIT;
    }

    if(command.find("stats") != std::string::npos)
    {
        return ServerCommand::STATS;
    }
    if(command == "ping")
    {
        return ServerCommand::PING;
    }
    if(command == "pingip")
    {
        return ServerCommand::PINGIP;
    }
    if(command == "ls" || command == "list")
    {
        return ServerCommand::LIST;
    }
    if(command == "kick")
    {
        return ServerCommand::KICK;
    }
    if(command == "ban")
    {
        return ServerCommand::BAN;
    }
    std::string sample = "SVB ";
    std::string subStr = command.substr(0,sample.length());

    if(subStr == sample)
    {
        return ServerCommand::BC;
    }



    return ServerCommand::UNKNOWN;

}

void ServerMain::handleInput()
{
    if(kbhit())
    {
        Gets(messageBuffer,sizeof(messageBuffer));
        handleCommand(messageBuffer);
        
    }
}

void ServerMain::handleCommand(const std::string & command)
{
    ServerCommand sc = getCommand(command);

    switch(sc)
    {

    case ServerCommand::QUIT:
    {

    
        m_serverOn = false;
        break;
    }

    case ServerCommand::STATS:
    {
        m_statistics = m_server->GetStatistics(m_server->GetSystemAddressFromIndex(0));
        StatisticsToString(m_statistics, messageBuffer, 2);
        printf("%s", messageBuffer);
        printf("Ping %i\n", m_server->GetAveragePing(m_server->GetSystemAddressFromIndex(0)));
    }
        break;

    case ServerCommand::PING:
    {
        m_server->Ping(m_clientID); // not sure what this line actually do 
        break;

    }

    case ServerCommand::PINGIP:
    {
        printf("Enter IP: ");
        Gets(messageBuffer,sizeof(messageBuffer));
        char portstring[30];
        printf("Enter port: ");
        Gets(portstring,sizeof(portstring));
        if (portstring[0]==0)
            strcpy(portstring, "1919");
        m_server->Ping(messageBuffer, atoi(portstring), false);
        break;
    }

    case ServerCommand::KICK:
    {
        m_server->CloseConnection(m_clientID, true, 0);
        break;
    }

    case ServerCommand::BAN:
    {
        printf("Enter IP to ban.  You can use * as a wildcard\n");
        Gets(messageBuffer,sizeof(messageBuffer));
        m_server->AddToBanList(messageBuffer, 0);
        break;
    }
    case ServerCommand::LIST:
    {
        
			RakNet::SystemAddress systems[m_connectionSize];
			unsigned short numConnections=0;
			m_server->GetConnectionList((RakNet::SystemAddress*) &systems, &numConnections);
			for (int i=0; i < numConnections; i++)
			{
				printf("%i. %s\n", i+1, systems[i].ToString(true));
			}
			break;
    }

    case ServerCommand::BC:
    {
        serverBroadcast[0] = 0;
        const static char prefix[] = "SV_BROADCAST: ";
        strncpy(serverBroadcast, prefix, sizeof(serverBroadcast));
        // trim the SVB
        std::string msg = command.substr(strlen("SVB "), command.length());
        strcat(serverBroadcast, msg.c_str());
        
        m_server->Send(serverBroadcast, (int) strlen(serverBroadcast), HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
        break;
    }

    default:
        break;
    }


}