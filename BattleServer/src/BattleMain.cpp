#include "BattleMain.h"


BattleMain::BattleMain()
{

}

BattleMain::~BattleMain()
{

}

uint64_t getTicks() {
    static const auto start = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - start
    ).count();
}

void BattleMain::init(const std::string & password, int port, unsigned int serverSize, const std::string & mainServerIP)
{
    std::cout << "|===============================================|\n";
    std::cout << "|            Init Server                        |\n";

    m_server = RakNet::RakPeerInterface::GetInstance();

    m_password = password;
    m_port = port;
    m_connectionSize = serverSize;
    m_mainServerIP = mainServerIP;

    m_server->SetIncomingPassword(m_password.c_str(), m_password.size());
    m_server->SetTimeoutTime(5000, RakNet::UNASSIGNED_SYSTEM_ADDRESS);
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

    m_server->AllowConnectionResponseIPMigration(false);

    std::cout << "|            Init Lua component                 |\n";

    m_script = luaL_newstate();

    luaL_openlibs(m_script);

    std::cout << "|===============================================|\n";

    m_serverOn = true;
}

void BattleMain::run()
{
    uint64_t prevTicks = getTicks();
    while(m_serverOn)
    {
        uint64_t newTicks = getTicks();
        uint64_t frameTime = newTicks - prevTicks;
        prevTicks = newTicks;

        float totalDeltaTime =  frameTime / (1000.0f  / 60.0f);

        while (totalDeltaTime > 0.0f)
        {
            float deltaTime = totalDeltaTime > 0.1f ? 0.1f : totalDeltaTime;
            update(deltaTime);
            totalDeltaTime -= deltaTime;
        }

    }
}