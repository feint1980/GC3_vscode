#include "ClientScriptingManager.h"



int lua_GetPacketId(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_GetPacketId) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        RakNet::Packet * p = static_cast<RakNet::Packet*>(lua_touserdata(L, 1));
        if(p)
        {
            lua_pushnumber(L, GetPacketIdentifier(p));
            return 1;
        }

    }
    return 0;
}

int lua_SendData(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_SendRequest) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        ClientScriptingManager * host =   static_cast<ClientScriptingManager*>(lua_touserdata(L, 1));
        std::string requestCmd = lua_tostring(L, 2);
        uint32_t result = host->sendData(requestCmd);
        lua_pushnumber(L, result);
        return 1;

    }
    return -1;
}

int lua_Connect(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_Connect) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        ClientScriptingManager * host =   static_cast<ClientScriptingManager*>(lua_touserdata(L, 1));
        host->connect();
    }

    return 0;
}


uint32_t ClientScriptingManager::sendData(const std::string & data)
{
    return m_client->Send(data.c_str(), data.length() +1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

void ClientScriptingManager::init(const std::string & serverIP, unsigned int port,lua_State * script)
{
    std::cout << "|=========================================|\n";
    std::cout << "|     Init Client Scripting Manager       |\n";

    //m_client = client;
    std::cout << "|     Init Client RakNet Core ...         |\n";

    m_client = RakNet::RakPeerInterface::GetInstance();
    m_serverIP = serverIP;
    m_port = port;

    m_client->AllowConnectionResponseIPMigration(false);
    m_socketDescriptor = RakNet::SocketDescriptor(m_port + 1, 0);
    m_socketDescriptor.socketFamily = AF_INET;
    m_client->Startup(8, &m_socketDescriptor, 1);
    m_client->SetOccasionalPing(true);

    std::cout << "|     Init Client RakNet Core OK          |\n";
    m_RakNetCoreInitialized = true;

    m_script = script;
    // m_script = luaL_newstate();
    // luaL_openlibs(m_script);

    std::cout << "|     Init Client Scripting Manager OK    |\n";
    std::cout << "|=========================================|\n";

    // register lua functions

    lua_register(m_script, "cppSendData", lua_SendData);
    lua_register(m_script, "cppConnect", lua_Connect);
    lua_register(m_script, "cppGetPacketId", lua_GetPacketId);

    if(LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, "./Assets/Lua/system/Networking/clientSide.lua")))
    {
        std::cout << "Run script OK \n";
    }

    lua_getglobal(m_script, "ClientSide_Init");
    if(lua_isfunction(m_script, -1))
    {
        lua_pushlightuserdata(m_script, this);
        const int argc = 1;
        const int returnCount = 0;
        if(LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, argc, returnCount, 0)))
        {
            std::cout << "Call Init from C++ OK \n";
        }
    }

}

ClientScriptingManager::ClientScriptingManager()
{
    pw = "DavaiMachi";
}



ClientScriptingManager::~ClientScriptingManager()
{

}


void ClientScriptingManager::handleMessage(RakNet::Packet *p)
{

    // first gateway
    sendDataToLuaScripting(p);
    // firstGateWay(p);

    //PacketCode requestCode = getSpecialRequestCode(p);
}

void ClientScriptingManager::connect()
{
    if(m_RakNetCoreInitialized)
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
        
    }
}

void ClientScriptingManager::sendDataToLuaScripting(RakNet::Packet *p)
{
    if(m_script)
    {
        lua_getglobal(m_script, "Client_ReceiveData");
        if(lua_isfunction(m_script, -1))
        {
            lua_pushstring(m_script,(const char*)p->data);
            lua_pushlightuserdata(m_script, &p->systemAddress);
            lua_pushnumber(m_script, GetPacketIdentifier(p));
            const int argc = 3;
            const int returnCount = 0;
            if(LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, argc, returnCount, 0)))
            {
                //std::cout << "Pass Data OK \n";
            }
        }
    }
}

void ClientScriptingManager::firstGateWay(RakNet::Packet *p)
{
    unsigned char packetIdentifier = GetPacketIdentifier(m_currentPacket);

    // Check if this is a network message packet
    switch (packetIdentifier)
    {
    case ID_DISCONNECTION_NOTIFICATION:
    {
        // Connection lost normally
        printf("Disconnected !!!\n");
        m_isConnected = false;
        m_status = ClientStatus::Disconnected;
    }
        break;
    case ID_ALREADY_CONNECTED:
    {
        // Connection lost normally
        printf("already connected with guid %" PRINTF_64_BIT_MODIFIER "u\n", m_currentPacket->guid);
        m_isConnected = true;
        m_status = ClientStatus::Connected;
    }
        break;
    case ID_INCOMPATIBLE_PROTOCOL_VERSION:
        printf("error code K2 D32\n");
        m_status = ClientStatus::Incompatible;
        break;
    case ID_REMOTE_DISCONNECTION_NOTIFICATION: // Server telling the clients of another client disconnecting gracefully.  You can manually broadcast this in a peer to peer enviroment if you want.
        printf("remote disconnect\n"); 
        // m_isConnected = false;
        break;
    case ID_REMOTE_CONNECTION_LOST: // Server telling the clients of another client disconnecting forcefully.  You can manually broadcast this in a peer to peer enviroment if you want.
        printf("remote connection lost\n");
        break;
    case ID_REMOTE_NEW_INCOMING_CONNECTION: // Server telling the clients of another client connecting.  You can manually broadcast this in a peer to peer enviroment if you want.
        printf("remote new incoming\n");
        break;
    case ID_CONNECTION_BANNED: // Banned from this server
        printf("Banned\n");
        m_status = ClientStatus::Banned;
        break;			
    case ID_CONNECTION_ATTEMPT_FAILED:
        printf("Connection attempt failed\n");
        m_status = ClientStatus::FailedAttemp;
        break;
    case ID_NO_FREE_INCOMING_CONNECTIONS:
        // Sorry, the server is full.  I don't do anything here but
        // A real app should tell the user
        m_status = ClientStatus::IsFull;
        printf("Server is full\n");
        break;
    case ID_INVALID_PASSWORD:
        m_status = ClientStatus::WSPacket;
        printf("error code K2 D31\n");
        break;

    case ID_CONNECTION_LOST:
        m_status = ClientStatus::Disconnected;
        // Couldn't deliver a reliable packet - i.e. the other system was abnormally
        // terminated
        printf("Lost connection\n");
        m_isConnected = false;
        break;

    case ID_CONNECTION_REQUEST_ACCEPTED:
        // This tells the client they have connected
        printf("Able to connect to %s gennerated GUID %s\n", m_currentPacket->systemAddress.ToString(true), m_currentPacket->guid.ToString());
        printf("My external address is %s\n", m_client->GetExternalID(m_currentPacket->systemAddress).ToString(true));
        m_status = ClientStatus::Connected;
        m_isConnected = true;
        break;
    case ID_CONNECTED_PING:
    case ID_UNCONNECTED_PING:
        printf("Ping from %s\n", m_currentPacket->systemAddress.ToString(true));
        break;
    default:
        // It's a client, so just show the message
        {
            secondGateWay(p);
            break;
        }
    }
}

void ClientScriptingManager::secondGateWay(RakNet::Packet *p)
{
    // todo 
}

void ClientScriptingManager::update(float deltaTime)
{

    if(m_RakNetCoreInitialized)
    {

        //PacketCode requestCode = getSpecialRequestCode(m_client->Receive());
        for (m_currentPacket=m_client->Receive(); 
        m_currentPacket;
        m_client->DeallocatePacket(m_currentPacket),
        m_currentPacket=m_client->Receive())
        {
            handleMessage(m_currentPacket);
        }
    }
    // m_client->DeallocatePacket(m_currentPacket);

}