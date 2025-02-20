#include "ClientScriptingManager.h"

ClientScriptingManager::ClientScriptingManager()
{

}



ClientScriptingManager::~ClientScriptingManager()
{

}

void ClientScriptingManager::init(RakNet::RakPeerInterface * client)
{
    std::cout << "|=========================================|\n";
    std::cout << "|     Init Client Scripting Manager       |\n";

    m_client = client;
    m_script = luaL_newstate();

    luaL_openlibs(m_script);

    std::cout << "|     Init Client Scripting Manager OK    |\n";
    std::cout << "|=========================================|\n";

    // register lua functions

    // lua_register(m_script, "cppSendData", lua_SendData);

}
