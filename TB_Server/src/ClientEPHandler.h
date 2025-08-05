#ifndef CLIENTEPHANDLER_H
#define CLIENTEPHANDLER_H

#include "ClientEP.h"


class ClientEPHandler
{
public:
    ClientEPHandler();
    ~ClientEPHandler();

private:
    std::unordered_map<std::string, ClientEP *> m_clientEPTable;

};


#endif // CLIENTEPHANDLER_H