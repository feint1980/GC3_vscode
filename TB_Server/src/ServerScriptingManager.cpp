#include "ServerScriptingManager.h"


// MARK: lua section


static int serverScriptingCallback(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	for(i = 0; i<argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	m_response.recordCount = argc;
	printf("\n");
	return 0;
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
    }

    return 0;
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



ResponseCode ServerScriptingManager::handleCommand(RakNet::Packet *p)
{
    PacketCode requestCode = getSpecialRequestCode(p);
    switch (requestCode)
    {
        case PacketCode::LOGIN:
        {
            std::cout << "Login request found !!!\n";
            // todo : verify login
            std::string cData((const char*) p->data);
            
            return ResponseCode::Login;
        }
        break;
        default :
            return ResponseCode::Invalid;
        break;
    }
    return ResponseCode::Invalid;
}

bool ServerScriptingManager::doQuery(const std::string & queryCmd)
{
    char * zErrMsg = 0;
    m_response.rc = sqlite3_exec(m_dbh->getDatabase(), queryCmd.c_str(), serverScriptingCallback, (void*)m_response.data, &zErrMsg);

    if(m_response.rc != SQLITE_OK)
    {
        std::cout << "ServerScriptingManager doQuery failed: " << zErrMsg << "\n";
        std::cout << "The query tried to be: " << queryCmd << "\n";
        sqlite3_free(zErrMsg);
        return false;
    }
    else
    {
        std::cout << "ServerScriptingManager doQuery OK! , check the response\n";
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
    std::cout << "|    Init Server Scripting Manager OK     |\n";
    std::cout << "|=========================================|\n";

    m_script = luaL_newstate();

    luaL_openlibs(m_script);

    // register lua functions
    
    lua_register(m_script, "cppDoQuery", lua_DoQuery);


}

