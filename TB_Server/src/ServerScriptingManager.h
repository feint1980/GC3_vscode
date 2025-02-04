#ifndef SERVERSCRIPTINGMANAGER_H
#define SERVERSCRIPTINGMANAGER_H

#include <RakNet/MessageIdentifiers.h>

#include <RakNet/RakPeerInterface.h>
#include <RakNet/RakNetStatistics.h>
#include <RakNet/RakNetTypes.h>
#include <RakNet/BitStream.h>
#include <RakNet/RakSleep.h>
#include <RakNet/PacketLogger.h>
#include <RakNet/Gets.h>
#include <RakNet/Kbhit.h>
#include <assert.h>
#include <cstdio>
#include <cstring>
#include <stdlib.h>

#include <stdio.h>
#include <string.h>
#include "NetworkPacket.h"
#include "DataBaseHandler.h"

#include "LuaManager.h"

#include <iostream>

#include "ServerMain.h"

class ServerScriptingManager
{
public:
    ServerScriptingManager();
    ~ServerScriptingManager();

    void init(RakNet::RakPeerInterface * server,DataBaseHandler * dbh)
    {
        std::cout << "|=========================================|\n";
        std::cout << "|     Init Server Scripting Manager       |\n";
        m_server = server;
        m_dbh = dbh;
        std::cout << "|    Init Server Scripting Manager OK     |\n";
        std::cout << "|=========================================|\n";
    }
    void update(float deltaTime);

    int handleCommand(RakNet::Packet *p);

    //void handleInput();

private:

    RakNet::RakPeerInterface * m_server;
    DataBaseHandler * m_dbh;


};




#endif // SERVERSCRIPTINGMANAGER_H
