
#include "ClientEPHandler.h"

int lua_ClientEPHandler_AddClientEP(lua_State * L)
{
    std::cout << " cpp_ClientEPHandler_AddClientEP called \n";
    if(lua_gettop(L) != 4)
    {
        std::cout << "gettop failed (lua_ClientEPHandler_AddClientEP) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        ClientEPHandler * host = static_cast<ClientEPHandler*>(lua_touserdata(L, 1));
        RakNet::SystemAddress *ip = static_cast<RakNet::SystemAddress*>(lua_touserdata(L, 2));
        std::string guid = lua_tostring(L, 3);
        std::string name = lua_tostring(L, 4);
        ClientEP *clientEP = new ClientEP();
        clientEP->init(ip, guid, name);
        host->addClientEP(clientEP, guid);

        std::cout << "lua added clientEP for guid " << guid << " OK \n";
        return 0;
    }
    return 0;
}


////////

ClientEPHandler::ClientEPHandler()
{

}

ClientEPHandler::~ClientEPHandler()
{

}

void ClientEPHandler::addClientEP(ClientEP *clientEP, const std::string &guid)
{
    if(m_clientEPTable.find(guid) == m_clientEPTable.end())
    {
        m_clientEPTable[guid] = clientEP;
        m_clientEPs.push_back(clientEP); // for iterating if needed
        std::cout << "added clientEP for guid " << guid << "\n";
    }
    else
    {
        std::cout << "guid " << guid << " already exists, this issue is huge, if you see this you are cooked (error K221) \n"; 
    }
}

void ClientEPHandler::init(lua_State * script)
{
    m_script = script;

    
    if(LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, "../luaFiles/clientHandling.lua")))
    {
        std::cout << "ClientEPHandler Run script clientHandling.lua OK \n";
    }

    lua_getglobal(m_script, "CH_Init");
    if(lua_isfunction(m_script, -1))
    {
        lua_pushlightuserdata(m_script, this);
        const int argc = 1;
        const int returnCount = 0;
        if(LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, argc, returnCount, 0)))
        {
            std::cout << "Call CH_Init from C++ OK \n";
        }
    }

    lua_register(m_script, "cpp_ClientEPHandler_AddClientEP", lua_ClientEPHandler_AddClientEP);

}