#include "ClientScriptingManager.h"

// MARK: lua section


int lua_SendData(lua_State *L)
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

        host->sendData(requestCmd);
        return 1;
    }


    return 0;
}


ClientScriptingManager::ClientScriptingManager()
{

}

ClientScriptingManager::~ClientScriptingManager()
{

}

void ClientScriptingManager::sendData(const std::string & data)
{

}

void ClientScriptingManager::init(RakNet::RakPeerInterface * client)
{
    std::cout << "|=========================================|\n";
    std::cout << "|     Init Client Scripting Manager       |\n";
    m_client = client;
    std::cout << "|     Init Client Scripting Manager OK    |\n";
    std::cout << "|=========================================|\n";

    m_script = luaL_newstate();

    luaL_openlibs(m_script);

    // register lua functions
    
    lua_register(m_script, "cppSendData", lua_SendData);
    //lua_register(m_script, "cppHandleCmd", lua_HandlingCmd);

}

void ClientScriptingManager::handleKeyboard(const std::string & data)
{
    
}
