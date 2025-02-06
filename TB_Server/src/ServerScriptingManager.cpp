#include "ServerScriptingManager.h"

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

std::string ServerScriptingManager::doQuery(const std::string & queryCmd)
{
    
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
    
    // lua_register(m_script, "cppSendQuery", lua_SendQuery);


}

