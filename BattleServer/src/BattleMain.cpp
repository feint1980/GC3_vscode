#include "BattleMain.h"




int lua_BM_SendWrapData(lua_State *L)
{
    if(lua_gettop(L) != 4)
    {
        std::cout << "gettop failed (lua_BM_SendWrapData) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        BattleMain * host = static_cast<BattleMain*>(lua_touserdata(L, 1));
        RakNet::SystemAddress * addr = static_cast<RakNet::SystemAddress*>(lua_touserdata(L, 2));
        std::string guid = lua_tostring(L, 3);
        std::string data = lua_tostring(L, 4);

        uint32_t tResult = host->sendWrapData(*addr,guid, data);
        lua_pushinteger(L, tResult);
        return 1;
    }
    return 0;

}

int lua_Packet_getIP(lua_State *L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_Packet_getIP) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }

    RakNet::Packet * p = static_cast<RakNet::Packet*>(lua_touserdata(L, 1));
    RakNet::SystemAddress * addr = &p->systemAddress;

    lua_pushlightuserdata(L,addr);
    return 1;
}

int lua_Packet_getIPAsString(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_Packet_getIPAsString) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        RakNet::Packet * p = static_cast<RakNet::Packet*>(lua_touserdata(L, 1));
        RakNet::SystemAddress * clientId = &p->systemAddress;
        std::string ip = clientId->ToString(false);
        lua_pushstring(L, ip.c_str());
        return 1;
    }
    return 0;
}

int lua_handleIncomingConnection(lua_State *L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_handleIncomingConnection) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    BattleMain * bm = static_cast<BattleMain*>(lua_touserdata(L, 1));
    bm->handleConnections(static_cast<RakNet::Packet*>(lua_touserdata(L, 2)));

    return 0;
}


/// Lua section


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

void BattleMain::init(const std::string & password,const std::string & mainServerPassword, int port, unsigned int serverSize, const std::string & mainServerIP)
{
    std::cout << "|===============================================|\n";
    std::cout << "|            Init Server                        |\n";

    m_server = RakNet::RakPeerInterface::GetInstance();

    m_mainServerPassword = mainServerPassword;
    m_password = password;
    m_port = port;
    m_connectionSize = serverSize;
    m_mainServerIP = mainServerIP;
    m_server->AllowConnectionResponseIPMigration(false);
    m_server->SetIncomingPassword(m_password.c_str(), m_password.size());
    m_server->SetTimeoutTime(5000, RakNet::UNASSIGNED_SYSTEM_ADDRESS);
    m_server->SetMaximumIncomingConnections(m_connectionSize);

    // Just create *one* IPv4 socket descriptor for now
    RakNet::SocketDescriptor sd(m_port, "0.0.0.0");
    sd.socketFamily = AF_INET;

    RakNet::StartupResult res = m_server->Startup(m_connectionSize, &sd, 1);
    if (res != RakNet::RAKNET_STARTED) {
        std::cout << "Server failed to start: " << res << std::endl;
        exit(1);
    }

    std::cout << "Server started successfully on port " << m_port << std::endl;

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

    m_server->AllowConnectionResponseIPMigration(true);

    std::cout << "|            Init Lua component                 |\n";

    m_script = luaL_newstate();

    luaL_openlibs(m_script);

    // communication 
    lua_register(m_script, "cpp_BM_SendWrapData", lua_BM_SendWrapData);
    
    // handle packets
    lua_register(m_script, "cpp_handleIncomingConnection", lua_handleIncomingConnection);

    // get packet data
    lua_register(m_script, "cpp_getPacketIP", lua_Packet_getIP);
    lua_register(m_script, "cpp_getPacketIPAsString", lua_Packet_getIPAsString);


    if(LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, "../luaFiles/battleSideScript.lua")))
    {
        std::cout << "BattleMain Run script battleSideScript.lua OK \n";
    }

    lua_getglobal(m_script, "BattleSide_Init");
    if(lua_isfunction(m_script, -1))
    {
        lua_pushlightuserdata(m_script, this);
        const int argc = 1;
        const int returnCount = 0;
        if(LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, argc, returnCount, 0)))
        {
            std::cout << "Call BattleSide_Init from C++ OK \n";
        }
    }

    std::cout << "|===============================================|\n";
    std::cout << "| Attemp to connect to main server ...          |\n";


    RakNet::ConnectionAttemptResult car = m_server->Connect(m_mainServerIP.c_str(), 1123, m_mainServerPassword.c_str(), m_mainServerPassword.size());

    // std::cout << "connect to " << m_mainServerIP << " via port " << 1123 << " with password " << m_mainServerPassword << "\n";
    RakAssert(car == RakNet::CONNECTION_ATTEMPT_STARTED);

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
            float deltaTime = 0; //totalDeltaTime > 0.1f ? 0.1f : totalDeltaTime; // rewrite this in the more readable way 
            if (totalDeltaTime > 0.1f)
            {
                deltaTime = 0.1f;
            }
            else
            {
                deltaTime = totalDeltaTime;
            }
            update(deltaTime);
            totalDeltaTime -= deltaTime;
        }
    }
}

void BattleMain::addCommonPacket(RakNet::Packet *p)
{
    RakNet::Packet* original = p;
    auto copy = new RakNet::Packet(*original); // shallow copy
    copy->data = new unsigned char[original->length];
    memcpy(copy->data, original->data, original->length);
    copy->length = original->length;

    m_commonPacketQueue.push(std::move(copy));
}

void BattleMain::update(float deltaTime)
{
    listen();
    handleCommonPacketQueue();
}

void BattleMain::handleCommonPacket(RakNet::Packet *p)
{
    lua_getglobal(m_script, "BattleMain_HandleCommon");
    if (lua_isfunction(m_script, -1))
    {
        lua_pushlightuserdata(m_script, this); // host

        lua_pushlightuserdata(m_script, p);

        auto packetID = GetPacketIdentifier(p);

        std::string data = std::string(reinterpret_cast<const char*>(p->data), p->length);

        lua_pushnumber(m_script, packetID);
        // lua_pushlightuserdata(m_script, entity->getTargetSlot());

        int arguments = 3;
        int returnCount = 1;
        if (!LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, arguments, returnCount, 0)))
        {
            std::cout << "call HandleCommon failed \n";
        }
    }
}

void BattleMain::handleCommonPacketQueue()
{
    while (!m_commonPacketQueue.empty())
    {
        RakNet::Packet *p = m_commonPacketQueue.front();
        handleCommonPacket(p);
        delete[] p->data;
        delete p;
        m_commonPacketQueue.pop();
    }
}

void BattleMain::listen()
{
    RakNet::Packet *p = nullptr;
    p = m_server->Receive();
    if(p)
    {
        unsigned char packetIdentifier = GetPacketIdentifier(p);
        switch(packetIdentifier)
        {
            case ID_DISCONNECTION_NOTIFICATION:
            case ID_NEW_INCOMING_CONNECTION:
            case ID_INCOMPATIBLE_PROTOCOL_VERSION:
            case ID_CONNECTED_PING:
            case ID_UNCONNECTED_PING:
            case ID_CONNECTION_LOST:
            case ID_CONNECTION_REQUEST_ACCEPTED:
            case ID_CONNECTION_ATTEMPT_FAILED:
                
                addCommonPacket(p);
            break;
            default :
            {
                std::cout << "uncommon packet " << packetIdentifier << "\n";
            }
            break;
        }
    }
    m_server->DeallocatePacket(p);
}


void BattleMain::handleConnections(RakNet::Packet *p)
{
    RakNet::SystemAddress addr = p->systemAddress;
    std::cout << "New connection from " << addr.ToString(true) << "\n";
    int port = addr.GetPort();
    std::cout << "port : " << port << "\n";

    if(port = 1123)
    {
        // connected to main server 
        std::cout << "connected to main server\n";
        // do request to register here
        std::cout << "init cryptor with main server";
        m_mainServerCryptor.init("BNML is real", p->guid.ToString()); 
        std::cout << "cryptor created\n";
    }
}

uint32_t BattleMain::sendWrapData( const RakNet::SystemAddress & target,const std::string & guid, const std::string & data)
{
    if (data.size() < 3) // headers
    {
        std::cout << "sendWrapData failed (data size < 2)\n";
        return ;
    }
    RakNet::MessageID id = static_cast<RakNet::MessageID>(data[0]); 
    uint8_t channel = static_cast<uint8_t>(data[1]);
    uint8_t request = static_cast<uint8_t>(data[2]);
    int payLoadIndex = 3;

    std::string payLoad(data.begin() + payLoadIndex, data.end());
    
    std::string tData = "";

    if (id == ID_TH_INTERNAL)
    {
        tData = m_mainServerCryptor.encrypt(payLoad);
    }
    else if (id == ID_TH_TB_BATTLE)
    {
        tData = m_cryptors[guid]->encrypt(payLoad);
    }
    else 
    {
        std::cout << "sendWrapData failed (invalid id) " << id << "\n";
        return 0;
    }

    // Build BitStream safely
    RakNet::BitStream bsOut;
    bsOut.Write(id);                              // custom message ID
    bsOut.Write(channel);                         // 1 byte
    bsOut.Write(request);                         // 1 byte
    bsOut.WriteAlignedBytes(
        reinterpret_cast<const unsigned char*>(tData.data()), 
        (const unsigned int)tData.size()
    );

    // Safe send (BitStream handles memory ownership)
    return m_server->Send(
        &bsOut, 
        HIGH_PRIORITY, 
        RELIABLE_ORDERED, 
        channel, 
        target, 
        false
    );


}