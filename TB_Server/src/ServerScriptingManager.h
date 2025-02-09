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

//#include "ServerMain.h"



struct SQLResponse
{
    int rc;
    void * data;
    int recordCount;
};

static SQLResponse m_response;

class ServerScriptingManager
{
public:
    ServerScriptingManager();
    ~ServerScriptingManager();

    void init(RakNet::RakPeerInterface * server,DataBaseHandler * dbh);
    void update(float deltaTime);

    ResponseCode handleCommand(RakNet::Packet *p);

    //void handleInput();

    bool doQuery(const std::string & queryCmd);

private:

    RakNet::RakPeerInterface * m_server;
    DataBaseHandler * m_dbh;

    lua_State * m_script;

    
};




#endif // SERVERSCRIPTINGMANAGER_H
