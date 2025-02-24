#include "ClientScriptingManager.h"

ClientScriptingManager::ClientScriptingManager()
{

}



ClientScriptingManager::~ClientScriptingManager()
{

}


void ClientScriptingManager::update(float deltaTime)
{
    PacketCode requestCode = getSpecialRequestCode(m_client->Receive());
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


uint32_t ClientScriptingManager::sendData(const std::string & data)
{
    return m_client->Send(data.c_str(), data.length() +1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
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

    lua_register(m_script, "cppSendData", lua_SendData);


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



