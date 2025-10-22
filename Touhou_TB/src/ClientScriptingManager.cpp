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
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_SendData) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        ClientScriptingManager * host =   static_cast<ClientScriptingManager*>(lua_touserdata(L, 1));
        std::string requestCmd = lua_tostring(L, 2);
        uint8_t encryptIndex = lua_tointeger(L, 3);
        // std::cout << "client side send data:" << requestCmd << "\n";
        uint32_t result = host->sendData(requestCmd, encryptIndex);
        lua_pushnumber(L, result);
        return 1;
    }
    return -1;
}

int lua_SendWrapData(lua_State * L)
{
    // std::cout << "lua_SendWrapData called \n";
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_SendWrapData) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        ClientScriptingManager * host =   static_cast<ClientScriptingManager*>(lua_touserdata(L, 1));
        std::string requestCmd = lua_tostring(L, 2);

        // std::cout << "data : " << requestCmd << "\n";
        // std::cout << "client side send data:" << requestCmd << "\n";

        uint32_t result = host->sendWrapData(requestCmd);
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

int lua_GetClientGUID(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_GetClientGUID) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        ClientScriptingManager * host =   static_cast<ClientScriptingManager*>(lua_touserdata(L, 1));
        std::string result = host->getClientGUID();
        lua_pushstring(L, result.c_str());
        return 1;
    }
    return 0;
}

int lua_GetPingFromServer(lua_State * L)
{
    if(lua_gettop(L)  > 3)
    {
        std::cout << "gettop failed (lua_GetPingFromServer) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        RakNet::SystemAddress addr;
        
        ClientScriptingManager * host =   static_cast<ClientScriptingManager*>(lua_touserdata(L, 1));

        if (lua_gettop(L) == 1)
        {
            addr = host->getServerIPAddr();
        }
        else
        {
            addr = *(RakNet::SystemAddress*)lua_touserdata(L, 2);
        }
        uint32_t result = host->getPingFromServer(addr);
        lua_pushnumber(L, result);
        return 1;
    }
    return 0;
}



std::string ClientScriptingManager::getClientGUID()
{
    if(m_client)
    {
        return m_client->GetMyGUID().ToString();
    }
    return "Sike";
}

uint32_t ClientScriptingManager::sendData(const std::string & data, uint8_t encryptIndex)
{
    // unsigned char iv[AES_IV_SIZE] = {};
    // m_cryptor.generateRandomIV(iv);
    // // std::string fData ;
    // // fData.push_back(ID_TH_TB);

    // std::string cData = std::string(data.begin() + encryptIndex, data.end());

    // auto tData = m_cryptor.encrypt(cData,iv);
    // for(int i = 0 ; i < AES_IV_SIZE;i++)
    // {
    //     tData.push_back(iv[i]);
    // }
    // std::string sendStr;
    // sendStr.push_back(ID_TH_TB);
    // for(int i = 0 ; i < tData.size() ; i++)
    // {
    //     sendStr.push_back((tData[i]));
    // } 
    return m_client->Send(data.c_str(), data.length() +1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

uint32_t ClientScriptingManager::sendWrapData(const std::string &data)
{
    if (data.size() < 2) // headers
    {
        std::cout << "sendWrapData failed (data size < 2)\n";
        return 0;
    }

    uint8_t channel = static_cast<uint8_t>(data[0]);
    uint8_t request = static_cast<uint8_t>(data[1]);
    int payLoadIndex = 2;

    std::string payLoad(data.begin() + payLoadIndex, data.end());
    std::string tData = m_cryptor->encrypt(payLoad);

    RakNet::BitStream bsOut;
    bsOut.Write((RakNet::MessageID)ID_TH_TB);
    bsOut.Write(channel);
    bsOut.Write(request);
    bsOut.WriteAlignedBytes(reinterpret_cast<const unsigned char*>(tData.data()), tData.size());

    // m_client->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, channel, m_serverIPAddr, false);
    unsigned int bits = bsOut.GetNumberOfBitsUsed();
    unsigned int bytes = bits / 8 + (bits % 8 ? 1 : 0);

    // Safe send (BitStream handles memory ownership)
    return m_client->Send(
        &bsOut, 
        HIGH_PRIORITY, 
        RELIABLE_ORDERED, 
        channel, 
        m_serverIPAddr, 
        false
    );
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
    // std::cout << "my GUID is : "<<  m_client->GetMyGUID().ToString() << "\n"; 
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
    lua_register(m_script, "cppSendWrapData", lua_SendWrapData);
    lua_register(m_script, "cppGetPingFromServer", lua_GetPingFromServer);
    //lua_register(m_script, "cppSendRequest", lua_SendRequest);
    lua_register(m_script, "cppConnect", lua_Connect);
    lua_register(m_script, "cppGetPacketId", lua_GetPacketId);
    lua_register(m_script, "cppParseCharacterFromJson", lua_ParseCharacterFromJson);
    lua_register(m_script, "cppGetClientGUID", lua_GetClientGUID);


    if(LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, "../../Lua/system/Networking/clientSide.lua")))
    {
        std::cout << "ClientScriptingManager Run script clientSide.lua OK \n";
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

    //m_cryptor.init(tStr1, tStr2); // old 
    // std::cout << "init cryptor for guid " << m_client->GetMyGUID().ToString() << "\n";
    m_cryptor = new Feintgine::F_Cryptor_sodium();
    m_cryptor->init("BNML is real", m_client->GetMyGUID().ToString());
}

ClientScriptingManager::ClientScriptingManager()
{
    pw = "DavaiMachi";
}

ClientScriptingManager::~ClientScriptingManager()
{

}

uint32_t ClientScriptingManager::handleWrapData(RakNet::Packet *p)
{
    // std::cout << "handleWrapData  called \n";
    if(p->length < 2 )
    {
        // std::cout << "Invalid Packet (data size < 2) \n";
        // self packet detected 
        handleMessage(p);
        return 0;
    }
    else
    {
        unsigned char packetIdentifier = GetPacketIdentifier(p);
        switch(packetIdentifier)
        {
            case ID_TH_TB:
            {
                lua_getglobal(m_script, "ClientHandlerWrapResponse");
                if(lua_isfunction(m_script, -1))
                {
                    RakNet::BitStream bsIn(p->data, p->length, false);

                    RakNet::MessageID msgId;
                    uint8_t channel;
                    uint8_t request;

                    bsIn.Read(msgId);
                    bsIn.Read(channel);
                    bsIn.Read(request);

                    unsigned int remainingBytes = bsIn.GetNumberOfUnreadBits() / 8;
                    std::string encData;
                    encData.resize(remainingBytes);
                    bsIn.ReadAlignedBytes(reinterpret_cast<unsigned char*>(&encData[0]), remainingBytes);

                    // std::string payLoad = m_cryptor->decrypt(encData);

                    std::string payLoad = getDecryptMessage(encData);

                    lua_pushlightuserdata(m_script, this);
                    lua_pushnumber(m_script, channel);
                    lua_pushnumber(m_script, request);
                    lua_pushstring(m_script, payLoad.c_str());
                    // lua_pushlightuserdata(m_script, &p->systemAddress);
                    lua_pushstring(m_script, p->guid.ToString());
                    // std::cout << "recieve guid check " << p->guid.ToString() << "\n";
                    const int argc = 5; // remember to modify this number when you change the number of arguments
                    const int returnCount = 1;
                    return LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, argc, returnCount, 0));
                }
                    break;
                default:
                {
                    handleMessage(p);
                    return 0;
                }
                break;
            }
        }
    }   
    return 0;
}

std::string ClientScriptingManager::getDecryptMessage(const std::string & data)
{

    return m_cryptor->decrypt(data);
}


void ClientScriptingManager::handleMessage(RakNet::Packet *p)
{
   // unsigned char packetIdentifier = GetPacketIdentifier(p);

        // bool handlingPacket = false;
        firstGateWay(p);
        sendDataToLuaScripting(p);
        // while(!handlingPacket)
        // {
        //     handlingPacket = sendDataToLuaScripting(p);
        // };
        // std::cout << "append " << GetPacketIdentifier(p) << "\n";
        // ResponseMSG msg(p, GetPacketIdentifier(p));
        // m_responseQueue.push(p);

    //sendDataToLuaScripting(p);
}

void ClientScriptingManager::handleData()
{
    if(!m_responseQueue.empty())
    {
        //Pacj
        RakNet::Packet *p = m_responseQueue.front();
        std::cout << "handling " << m_responseQueue.front() << "\n";
        sendDataToLuaScripting(p);
        m_responseQueue.pop();
    }
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
        // if(car == RakNet::CONNECTION_)
    
        std::cout << "IP address: \n";
        for(int i = 0; i < m_client->GetNumberOfAddresses(); i++)
        {
            printf("%i. %s\n", i+1, m_client->GetLocalIP(i));
        }

        // std::cout << "init networking OK ! \n";
        // std::cout << "GUID is : " << m_client->GetGuidFromSystemAddress (RakNet::UNASSIGNED_SYSTEM_ADDRESS).ToString() << "\n"; 
    }
}

bool ClientScriptingManager::sendDataToLuaScripting(RakNet::Packet *p)
{
   // std::cout << "sendDataToLuaScripting \n";
    if(m_script)
    {
        //std::cout << "script is not null \n";
        if(p != nullptr)
        {   
            lua_getglobal(m_script, "Client_ReceiveData");
            if(lua_isfunction(m_script, -1))
            {
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
                unsigned char identifier = GetPacketIdentifier(p);
                // // std::cout << m_cryptor.decrypt(tMsg, iv) << "\n";
                std::cout << "got packet !!!!!!! " << (int)identifier << "\n";

                if(!selfPacket)
                {

                    // std::cout << "salt is :\n";
                    // for(int i = 0 ; i < AES_IV_SIZE; i++)
                    // {
                    //     printf("%02x", iv[i]);
                    // }  
                    // std::cout << "\n";
                    std::string tMsg = std::string(reinterpret_cast<const char*>(p->data), p->length);
                    // 
                    lua_pushstring(m_script,m_cryptor->decrypt(tMsg).c_str());
                }
                else
                {
                    lua_pushstring(m_script, std::string((const char *) p->data).c_str());
                }
                lua_pushlightuserdata(m_script, &p->systemAddress);
                lua_pushnumber(m_script, identifier);
                const int argc = 3;
                const int returnCount = 0;
                return LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, argc, returnCount, 0));
            }
        }
    }
    return false;
}

void ClientScriptingManager::firstGateWay(RakNet::Packet *p)
{
    unsigned char packetIdentifier = GetPacketIdentifier(p);

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
        printf("already connected with guid %" PRINTF_64_BIT_MODIFIER "u\n", p->guid);
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
        printf("Able to connect to %s gennerated GUID %s\n", p->systemAddress.ToString(true), p->guid.ToString());
        // printf("My external address is %s\n", m_client->GetExternalID(p->systemAddress).ToString(true));
        m_status = ClientStatus::Connected;
        m_serverIPAddr = p->systemAddress;
        InfoHolder::getInstance()->saveServerIP(m_serverIPAddr);
        std::cout << "server ip : " << m_serverIPAddr.ToString(true) << "\n";

        m_isConnected = true;
        break;
    case ID_CONNECTED_PING:
    case ID_UNCONNECTED_PING:
        printf("Ping from %s\n", p->systemAddress.ToString(true));
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

void ClientScriptingManager::handleReceive()
{
        for(RakNet::Packet *p = m_client->Receive(); p; m_client->DeallocatePacket(p), p = m_client->Receive())
        {
            if(p->length < 2)
            {
                handleMessage(p);
            }
            else
            {
                m_responseQueue.push(p);
            }

        }
}

void ClientScriptingManager::update(float deltaTime)
{

    if(m_RakNetCoreInitialized)
    {

        // handleReceive();
        //PacketCode requestCode = getSpecialRequestCode(m_client->Receive());
        //RakNet::Packet *p = nullptr;
         for(RakNet::Packet *p = m_client->Receive(); p; m_client->DeallocatePacket(p), p = m_client->Receive())
        {
            // p = m_client->Receive();
            // if(p)
            // {
                // std::cout << "handle wrap data precalled " << (int)(GetPacketIdentifier(p)) << "\n";
                handleWrapData(p);
                // handleMessage(p);
                // m_client->DeallocatePacket(p);
        }

        // if (m_responseQueue.size() > 0)
        // {
        //     RakNet::Packet *p = m_responseQueue.front();
        //     std::cout << "m_responseQueue size " << m_responseQueue.size() << "\n";
            
        //     m_responseQueue.pop();
        //     handleWrapData(p);
        //     m_client->DeallocatePacket(p);

        // }
        updateScript(deltaTime);
            // }
        
        // if(m_responseQueue.size() > 0)
        // {
        //     std::cout << "m_responseQueue size " << m_responseQueue.size() << "\n";
        //     sendDataToLuaScripting(m_responseQueue.front().packet);
        //     m_responseQueue.pop();
        // }
       // 
    }
    //handleData();
    // m_client->DeallocatePacket(m_currentPacket);
    //handleData();
}

void ClientScriptingManager::updateScript(float delta)
{
    lua_getglobal(m_script, "UpdateRequests");
    if(lua_isfunction(m_script, -1))
    {
        
        lua_pushlightuserdata(m_script, this);
        const int argc = 1; // remember to modify this number when you change the number of arguments
        const int returnCount = 1;
        LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, argc, returnCount, 0));
    }
    
}


int ClientScriptingManager::getPingFromServer(const RakNet::SystemAddress & addr)
{
    return m_client->GetAveragePing(addr);
}
