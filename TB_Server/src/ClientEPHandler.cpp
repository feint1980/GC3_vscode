
#include "ClientEPHandler.h"


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
        std::cout << "Run script OK \n";
    }

    

}