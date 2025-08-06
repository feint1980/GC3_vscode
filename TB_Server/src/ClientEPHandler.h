#ifndef CLIENTEPHANDLER_H
#define CLIENTEPHANDLER_H

#include "ClientEP.h"
#include "LuaManager.h"

class ClientEPHandler
{
public:
    ClientEPHandler();
    ~ClientEPHandler();


    void init(lua_State * script);

    void addClientEP(ClientEP *clientEP, const std::string &guid);
    
private:
    std::unordered_map<std::string, ClientEP *> m_clientEPTable; // dont know if should manage this key by using guid or name 
    std::vector<ClientEP *> m_clientEPs;

    lua_State * m_script = nullptr;

};


#endif // CLIENTEPHANDLER_H