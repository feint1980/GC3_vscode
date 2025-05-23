#include "ClientScriptingManager.h"

static void to_json(json& j, const CharacterStats& c) 
{
    j = json{
        {"strength", c.strength},
        {"vitality", c.vitality},
        {"dexterity", c.dexterity},
        {"agility", c.agility},
        {"intelligence", c.intelligence},
        {"wisdom", c.wisdom},
        {"animationPath", c.animationPath},
        {"portraitPath", c.portraitPath},
        {"panelPath",c.panelPath},
        {"action",c.action},
        {"hp",c.hp},
        {"mana",c.mana},
        {"sp",c.sp},
        {"spCap",c.spCap},
        {"physicDmg",c.physicDmg},
        {"physicDef",c.physicDef},
        {"magicDmg",c.magicDmg},
        {"magicDef",c.magicDef},
        {"accurate",c.accurate},
        {"evadeChance",c.evadeChance},
        {"critChance",c.critChance},
        {"hpScale",c.hpScale},
        {"manaScale",c.manaScale},
        {"physicDmgScale",c.physicDmgScale},
        {"magicDmgScale",c.magicDmgScale},
        {"physicDefScale",c.physicDefScale},
        {"magicDefScale",c.magicDefScale},
        {"accurateScale",c.accurateScale},
        {"evadeChanceScale",c.evadeChanceScale},
        {"deathDoorSurviveChance",c.deathDoorSurviveChance},
        {"name",c.name},
        {"lastName",c.lastName},
        {"title",c.title},
        {"side",c.side},
        {"level",c.level},
        {"xp", c.xp},
        {"price",c.price},
        {"ID",c.ID}
    };
}

// Convert JSON to struct
static void from_json(const json& j, CharacterStats& c) {
    j.at("strength").get_to(c.strength);
    j.at("vitality").get_to(c.vitality);
    j.at("dexterity").get_to(c.dexterity);
    j.at("agility").get_to(c.agility);
    j.at("intelligence").get_to(c.intelligence);
    j.at("wisdom").get_to(c.wisdom);
    j.at("animationPath").get_to(c.animationPath);
    j.at("portraitPath").get_to(c.portraitPath);
    j.at("panelPath").get_to(c.panelPath);
    j.at("action").get_to(c.action);
    j.at("hp").get_to(c.hp);
    j.at("mana").get_to(c.mana);
    j.at("sp").get_to(c.sp);
    j.at("spCap").get_to(c.spCap);
    j.at("physicDmg").get_to(c.physicDmg);
    j.at("physicDef").get_to(c.physicDef);
    j.at("magicDmg").get_to(c.magicDmg);
    j.at("magicDef").get_to(c.magicDef);
    j.at("accurate").get_to(c.accurate);
    j.at("evadeChance").get_to(c.evadeChance);
    j.at("critChance").get_to(c.critChance);
    j.at("hpScale").get_to(c.hpScale);  
    j.at("manaScale").get_to(c.manaScale);
    j.at("physicDmgScale").get_to(c.physicDmgScale);
    j.at("magicDmgScale").get_to(c.magicDmgScale);
    j.at("physicDefScale").get_to(c.physicDefScale);
    j.at("magicDefScale").get_to(c.magicDefScale);
    j.at("accurateScale").get_to(c.accurateScale);
    j.at("evadeChanceScale").get_to(c.evadeChanceScale);
    j.at("deathDoorSurviveChance").get_to(c.deathDoorSurviveChance);
    j.at("name").get_to(c.name);
    j.at("lastName").get_to(c.lastName);
    j.at("title").get_to(c.title);
    j.at("side").get_to(c.side);
    j.at("level").get_to(c.level);
    j.at("xp").get_to(c.xp);
    j.at("price").get_to(c.price);
    j.at("ID").get_to(c.ID);
}

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
        // std::cout << "client side send data:" << requestCmd << "\n";
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

int lua_ParseCharacterFromJson(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_ParseCharacterFromJson) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        ClientScriptingManager * host =   static_cast<ClientScriptingManager*>(lua_touserdata(L, 1));
        std::string jsonSrc = lua_tostring(L, 2);

        CharacterStats  *returnStats = new CharacterStats();
        *returnStats = host->parseFromStr(jsonSrc);

        // CharacterDesc des; 
        // des.setCharacterStats(returnStats);

        // std::cout << "check data ||||" << returnStats->name << "|||||||\n";
        lua_pushlightuserdata(L, returnStats);
        return 1;
    }
    return 0;
}

uint32_t ClientScriptingManager::sendData(const std::string & data)
{

    unsigned char iv[AES_IV_SIZE] = {};
    m_cryptor.generateRandomIV(iv);

    auto tData = m_cryptor.encrypt(data,iv);
    for(int i = 0 ; i < AES_IV_SIZE;i++)
    {
        tData.push_back(iv[i]);
    }
    std::string sendStr;
    for(int i = 0 ; i < tData.size() ; i++)
    {
        sendStr.push_back((tData[i]));
    } 
    return m_client->Send(sendStr.c_str(), sendStr.length() +1, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

CharacterStats ClientScriptingManager::parseFromStr(const std::string & str)
{
    CharacterStats result;
    json j = json::parse(str);
    result = j.get<CharacterStats>();
    return result;
}

void ClientScriptingManager::init(const std::string & serverIP, unsigned int port,  RakNet::RakPeerInterface * client, lua_State * script)
{
    std::cout << "|=========================================|\n";
    std::cout << "|     Init Client Scripting Manager       |\n";

    //m_client = client;
    std::cout << "|     Init Client RakNet Core ...         |\n";

    m_client = client;
    // m_client = RakNet::RakPeerInterface::GetInstance();
    m_serverIP = serverIP;
    m_port = port;
    // m_client->AllowConnectionResponseIPMigration(false);
    // m_socketDescriptor = RakNet::SocketDescriptor(m_port + 1, 0);
    // m_socketDescriptor.socketFamily = AF_INET;
    // m_client->Startup(8, &m_socketDescriptor, 1);
    // m_client->SetOccasionalPing(true);

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
    lua_register(m_script, "cppParseCharacterFromJson", lua_ParseCharacterFromJson);


    if(LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, "../../Lua/system/Networking/clientSide.lua")))
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
    // init key
    int t1[16] = {
        7, 12, 5, 7,
        8, 33, 51, 21,
        77, 71, 22, 43,
        12, 15, 99, 4
    };
    int t2[8] = {
        12, 6, 7, 2,
        9, 12, 91, 42
    } ;

    std::string tStr1;
    
    std::string tStr2;
    
    for(int i = 0 ; i < 16 ; i++)
    {
        tStr1.push_back(t1[i]);
    }

    for(int i = 0 ; i < 8 ; i++)
    {
        tStr2.push_back(t2[i]);
    }

    m_cryptor.init(tStr1, tStr2);   

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
    sendDataToLuaScripting(p);
}

void ClientScriptingManager::cleanUp()
{
    // for(int i = 0 ; i < 8 ; i++)
    // {
    //     m_client->DeallocatePacket(m_client->Receive());
    // }

    // RakNet::RakPeerInterface::DestroyInstance(m_client);
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
    std::cout << "sendDataToLuaScripting \n";
    if(m_script)
    {
        std::cout << "script is not null \n";
        lua_getglobal(m_script, "Client_ReceiveData");
        if(lua_isfunction(m_script, -1))
        {
            std::cout << "length of packet is " << p->length << "\n";
            std::cout << "attemp to call lua fuinction \n";
            bool selfPacket = false;
            if(p->length < 2)
            {
                selfPacket = true;

            }
            // std::cout << "tMsg check \n";
            // for(int i = 0 ;i < tMsg.size() ; i++)
            // {
            //     printf("%02x", tMsg[i]);
            // }   
            // std::cout << "\ndecrypt : \n";
            std::cout << "get packet identifier \n";
            unsigned char identifier = GetPacketIdentifier(p);
            // // std::cout << m_cryptor.decrypt(tMsg, iv) << "\n";
            std::cout << "got packet !!!!!!! " << identifier << "\n";

            if(!selfPacket)
            {
                unsigned char iv[AES_IV_SIZE];
                for(int i = 0 ; i < AES_IV_SIZE ; i++)
                {
                    iv[i] = p->data[(p->length -1) - (AES_IV_SIZE - i)]; 
                }
                // std::cout << "salt is :\n";
                // for(int i = 0 ; i < AES_IV_SIZE; i++)
                // {
                //     printf("%02x", iv[i]);
                // }  
                // std::cout << "\n";
                std::vector<unsigned char> tMsg;
                for(int i = 0 ;i < (p->length -1) - AES_IV_SIZE; i++)
                {
                    tMsg.push_back(p->data[i]);
                }
                lua_pushstring(m_script,m_cryptor.decrypt(tMsg, iv).c_str());
            }
            else
            {
                lua_pushstring(m_script, std::string((const char *) p->data).c_str());
            }
            lua_pushlightuserdata(m_script, &p->systemAddress);
            lua_pushnumber(m_script, identifier);
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