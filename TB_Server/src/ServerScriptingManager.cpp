#include "ServerScriptingManager.h"


// MARK: lua section

static const std::string KEY_TABLE = "register_key_table";
static const std::string ACCOUNT_TABLE = "account_table";
static const std::string ACCOUNT_STATS_TABLE = "account_stats_table";
static const std::string CHARACTER_BASE_TABLE = "character_base_table";
static const std::string CHARACTER_EXISTANCE_TABLE = "character_existance_table";

static const std::string INSERT = "insert into";

static int serverScriptingCallback(void *NotUsed, int argc, char **argv, char **azColName)
{

    std::cout << "serverScriptingCallback \n";
	

    for(int i = 0 ; i < m_response.data.size() ; i++)
    {
        m_response.data[i].clear();
    }
    m_response.data.clear();

    for(int i = 0; i<m_response.columnNames.size(); i++)
    {
        m_response.columnNames[i].clear();
    }

	for(int i = 0; i<argc; i++) {
		//printf("%s : %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        // std::cout << "index i " << i << "\n";
        lua_getglobal(shared_luaState, "AddColData");
        if (lua_isfunction(shared_luaState, -1))
        {
            std::string colName = azColName[i];
            std::string value = "NULL";
            if (argv[i])
            {
                value = argv[i];
            }
            m_response.columnNames.push_back(colName);
            m_response.data.push_back(value);
            lua_pushstring(shared_luaState, colName.c_str());
            lua_pushstring(shared_luaState, value.c_str());
            if (!LuaManager::Instance()->checkLua(shared_luaState, lua_pcall(shared_luaState, 2, 1, 0)))
            {
                std::cout << "call AddColData failed \n";
            }
        }

	}
	m_response.recordCount = argc;
	printf("\n");
	return 0;
}

std::string genKey(int numberOfRandom)
{
    char a[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int size = sizeof(a) - 1;
    char p[numberOfRandom + 1];
    for (int i = 0; i < numberOfRandom; i++)
    {
        p[i] = a[rand() % size];
    }
    p[numberOfRandom] = '\0';

    return std::string(p);
}

int lua_GenKey(lua_State * L)
{
    if (lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_GenKey) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        int numberOfRandom = lua_tointeger(L, 1);
        std::string key = genKey(numberOfRandom);
        std::cout << "c++ side: key: " << key << "\n";
        lua_pushstring(L, key.c_str());
    }

    return 1;
}

int lua_GetQueryResults(lua_State * L)
{
    if (lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_GetQueryResults) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        ServerScriptingManager * host = static_cast<ServerScriptingManager*>(lua_touserdata(L, 1));
        int resultCode = m_response.rc;
        int recordCount = m_response.recordCount;

        
        lua_pushinteger(L, resultCode);
        lua_pushinteger(L, recordCount);
       // lua_pushstring(L, result.c_str());

    }
    return 3;
}

int lua_DoQuery(lua_State * L)
{
    if (lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_DoQuery) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        ServerScriptingManager * host = static_cast<ServerScriptingManager*>(lua_touserdata(L, 1));
        std::string queryCmd = lua_tostring(L, 2);

        host->doQuery(queryCmd);
        return 0;
    }

    return 0;
}

int lua_SendToClient(lua_State * L)
{
    // std::cout << "lua_SendToClient called \n";
    if (lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_SendToClient) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        ServerScriptingManager * host = static_cast<ServerScriptingManager*>(lua_touserdata(L, 1));
        RakNet::SystemAddress * clientId = static_cast<RakNet::SystemAddress*>(lua_touserdata(L, 2));
        std::string msg = lua_tostring(L, 3);
        //std::cout << "msg send is |" << msg << "|\n"; 
       // msg += "\0";
        host->sendData(*clientId, msg);
        // host->sendToClient(clientId, requestCode);
        return 0;
    }

    return 0;
}

int lua_Packet_getData(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_Packet_getData) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        RakNet::Packet * p = static_cast<RakNet::Packet*>(lua_touserdata(L, 1));
        std::string msg((const char *)p->data);

        lua_pushstring(L, msg.c_str());
        return 1;
    }
}

int lua_Packet_getIP(lua_State * L)
{

    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_Packet_getIP) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        RakNet::Packet * p = static_cast<RakNet::Packet*>(lua_touserdata(L, 1));
        RakNet::SystemAddress * clientId = &p->systemAddress;
        lua_pushlightuserdata(L,clientId);
        return 1;
    }
}

ServerScriptingManager::ServerScriptingManager()
{

}
ServerScriptingManager::~ServerScriptingManager()
{

}


void ServerScriptingManager::update(float deltaTime)
{

}


std::string ServerScriptingManager::getMegFromPackget(RakNet::Packet *p)
{
    //p->systemAddress
    //p->systemAddress
    return std::string((const char*)p->data);
}

uint32_t ServerScriptingManager::sendData(const RakNet::SystemAddress & target, const std::string & data)
{
    m_server->Send(data.c_str(), data.size() + 1, HIGH_PRIORITY, RELIABLE_SEQUENCED,12, target,false);
    return 0;
}

ClientRequestCode ServerScriptingManager::handleCommand(RakNet::Packet *p)
{
    PacketCode requestCode = getSpecialRequestCode(p);
    // send relay data to lua to process
    std::string msg = getMegFromPackget(p);

    lua_getglobal(m_script, "HandleMessage");
    if (lua_isfunction(m_script, -1))
    {
        lua_pushlightuserdata(m_script, this); // host

        //std::cout << "Issue next task pointer " << object << "\n";

        lua_pushlightuserdata(m_script, p);
        //lua_pushlightuserdata(m_script, m_guiHandler);

        lua_pushnumber(m_script, requestCode);

        // lua_pushlightuserdata(m_script, entity->getTargetSlot());

        if (!LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, 3, 1, 0)))
        {
            std::cout << "call HandleMessage failed \n";
        }
    }

    // switch (requestCode)
    // {
    //     case PacketCode::LOGIN:
    //     {
    //         std::cout << "Login request found !!!\n";
    //         // todo : verify login
    //         std::string cData((const char*) p->data);
            
    //         return ClientRequestCode::Login;
    //     }
    //     break;
    //     default :
    //         return ClientRequestCode::Client_Invalid;
    //     break;
    // }
    return ClientRequestCode::Client_Invalid;
}

bool ServerScriptingManager::doQuery(const std::string & queryCmd)
{
    char * zErrMsg = 0;
    m_response.rc = sqlite3_exec(m_dbh->getDatabase(), queryCmd.c_str(), serverScriptingCallback, (void*)m_response.rawData, &zErrMsg);

    if(m_response.rc != SQLITE_OK)
    {
        //std::cout << "ServerScriptingManager doQuery failed: " << zErrMsg << "\n";
        //std::cout << "The query tried to be: " << queryCmd << "\n";
        sqlite3_free(zErrMsg);
        return false;
    }
    else
    {
        //std::cout << "ServerScriptingManager doQuery OK! , check the response\n";
        return true;
    }
    return false;
}

void ServerScriptingManager::init(RakNet::RakPeerInterface * server,DataBaseHandler * dbh)
{
    std::cout << "|=========================================|\n";
    std::cout << "|     Init Server Scripting Manager       |\n";
    m_server = server;
    m_dbh = dbh;
    std::cout << "|     Init Server Scripting Manager OK    |\n";
    std::cout << "|=========================================|\n";

    m_script = luaL_newstate();

    luaL_openlibs(m_script);

    // register lua functions
    
    lua_register(m_script, "cppDoQuery", lua_DoQuery);
    lua_register(m_script, "cppGetQueryResults", lua_GetQueryResults);
    lua_register(m_script, "cppGenKey", lua_GenKey);
    lua_register(m_script, "cppSendToClient", lua_SendToClient);

    // extract data from packet
    lua_register(m_script, "cppPacket_getData", lua_Packet_getData);
    lua_register(m_script, "cppPacket_getIP", lua_Packet_getIP);


    if(LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, "../luaFiles/serverSideScript.lua")))
    {
        std::cout << "Run script OK \n";
    }

    lua_getglobal(m_script, "ServerSide_Init");
    if(lua_isfunction(m_script, -1))
    {
        lua_pushlightuserdata(m_script, this);
        const int argc = 1;
        const int returnCount = 0;
        if(LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, argc, returnCount, 0)))
        {
            std::cout << "Call ServerSide_Init from C++ OK \n";
        }
    }

    shared_luaState = m_script;
}

