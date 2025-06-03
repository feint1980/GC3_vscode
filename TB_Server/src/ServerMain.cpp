#include "ServerMain.h"

#include "ServerScriptingManager.h"

uint64_t getTicks() {
    static const auto start = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - start
    ).count();
}

ServerMain::ServerMain()
{
    m_password = "TTKR";
    m_port = 1123 ;
}

ServerMain::~ServerMain()
{

}

void ServerMain::init(const std::string & password, int port,unsigned int serverSize)
{
    std::cout << "|=========================================|\n";
	std::cout << "|            Init DataBase                |\n";
    m_dbh = new DataBaseHandler();
	m_dbh->loadDataBase("../data/t2.db");
	std::cout << "|=========================================|\n";
    std::cout << "|             Init Server                 |\n";

    m_server = RakNet::RakPeerInterface::GetInstance();

    m_password = password;
    m_port = port;
    m_connectionSize = serverSize;

    m_server->SetIncomingPassword(m_password.c_str(), m_password.size());
	m_server->SetTimeoutTime(5000,RakNet::UNASSIGNED_SYSTEM_ADDRESS);
    m_server->SetMaximumIncomingConnections(m_connectionSize);

    m_socketDescriptor[0] = RakNet::SocketDescriptor(m_port, "0.0.0.0");
    m_socketDescriptor[0].socketFamily = AF_INET;
    m_socketDescriptor[1] = RakNet::SocketDescriptor(m_port, "0.0.0.0");
    m_socketDescriptor[1].socketFamily = AF_INET6;

    bool init2IPVer = m_server->Startup(10, m_socketDescriptor,2) == RakNet::RAKNET_STARTED;
    if (!init2IPVer)
    {
        std::cout << "Failed to start dual IPV4 and IPV6 ports. Trying IPV4 only.\n";
        bool init1IPVer = m_server->Startup(m_connectionSize, m_socketDescriptor, 1) == RakNet::RAKNET_STARTED;

        if (!init1IPVer)
        {
            std::cout << "Server failed to start. Terminating.\n";
            exit(1);
        }
    }

    m_server->SetOccasionalPing(true);
	m_server->SetUnreliableTimeout(1000);
    m_server->AllowConnectionResponseIPMigration(false);

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

    m_scriptManager = new ServerScriptingManager();
    m_scriptManager->init(m_server,m_dbh);
}

void ServerMain::run()
{
    uint64_t prevTicks = getTicks();
    while(m_serverOn)
    {
        uint64_t newTicks = getTicks();
        uint64_t frameTime = newTicks - prevTicks;
        prevTicks = newTicks;

        float totalDeltaTime =  frameTime / (1000.0f  / 60.0f);

        // This sleep keeps RakNet responsive
        //RakSleep(10);
        // todo, think about delta time problem :
        while (totalDeltaTime > 0.0f)
        {
            float deltaTime = totalDeltaTime > 0.1f ? 0.1f : totalDeltaTime;
            update(deltaTime);
            totalDeltaTime -= deltaTime;
        }

        handleInput();
    }
    m_server->Shutdown(300);
    RakNet::RakPeerInterface::DestroyInstance(m_server);
    std::cout << "Server shutdown \n"; 

}

void ServerMain::update(float deltaTime)
{
    // check for packets
    for (m_currentPacket=m_server->Receive(); m_currentPacket; m_server->DeallocatePacket(m_currentPacket), m_currentPacket=m_server->Receive())
    {
        // We got a packet, get the identifier with our handy function
        unsigned char packetIdentifier = GetPacketIdentifier(m_currentPacket);
        // Check if this is a network message packet
        switch (packetIdentifier)
        {
        case ID_DISCONNECTION_NOTIFICATION:
        case ID_NEW_INCOMING_CONNECTION:
        case ID_INCOMPATIBLE_PROTOCOL_VERSION:
        case ID_CONNECTED_PING:
        case ID_UNCONNECTED_PING:
        case ID_CONNECTION_LOST:
            m_scriptManager->handleCommon(m_currentPacket);
        break;
        default:
            m_scriptManager->handleCommand(m_currentPacket);
            break;
        }
    }
    m_scriptManager->update(deltaTime);
}

PacketCode ServerMain::getCommand(const std::string & command)
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
    if(command == "ping")
    {
        return PacketCode::PING;
    }
    if(command == "pingip")
    {
        return PacketCode::PINGIP;
    }
    if(command == "ls" || command == "list")
    {
        return PacketCode::LIST;
    }
    if(command == "kick")
    {
        return PacketCode::KICK;
    }
    if(command == "ban")
    {
        return PacketCode::BAN;
    }
    std::string sample = "SVB ";
    std::string subStr = command.substr(0,sample.length());

    if(subStr == sample)
    {
        return PacketCode::BC;
    }
    return PacketCode::UNKNOWN;
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
    PacketCode sc = getCommand(command);
    switch(sc)
    {
    case PacketCode::QUIT:
    {
        m_serverOn = false;
        break;
    }
    case PacketCode::STATS:
    {
        m_statistics = m_server->GetStatistics(m_server->GetSystemAddressFromIndex(0));
        StatisticsToString(m_statistics, messageBuffer, 2);
        printf("%s", messageBuffer);
        printf("Ping %i\n", m_server->GetAveragePing(m_server->GetSystemAddressFromIndex(0)));
    }
        break;
    case PacketCode::PING:
    {
        m_server->Ping(m_clientID); // not sure what this line actually do 
        break;
    }
    case PacketCode::PINGIP:
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
    case PacketCode::KICK:
    {
        m_server->CloseConnection(m_clientID, true, 0);
        break;
    }
    case PacketCode::BAN:
    {
        printf("Enter IP to ban.  You can use * as a wildcard\n");
        Gets(messageBuffer,sizeof(messageBuffer));
        m_server->AddToBanList(messageBuffer, 0);
        break;
    }
    case PacketCode::LIST:
    {
        RakNet::SystemAddress systems[m_connectionSize];
        unsigned short numConnections=m_connectionSize;
        m_server->GetConnectionList((RakNet::SystemAddress*) &systems, &numConnections);
        std::cout << "Total connections : " << numConnections << "\n";
        for (int i=0; i < numConnections; i++)
        {
            printf("%i. %s\n", i+1, systems[i].ToString(true));
        }
        break;
    }
    case PacketCode::BC:
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