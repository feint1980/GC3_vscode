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
    void * rawData;
    std::vector<std::string> columnNames;
    std::vector<std::string> data;
    int recordCount;
};

static SQLResponse m_response;


static lua_State * shared_luaState;

class ServerScriptingManager
{
public:
    ServerScriptingManager();
    ~ServerScriptingManager();

    void init(RakNet::RakPeerInterface * server,DataBaseHandler * dbh);
    void update(float deltaTime);

    ClientRequestCode handleCommand(RakNet::Packet *p);

    //void handleInput();

    std::string getMegFromPackget(RakNet::Packet *p);

    bool doQuery(const std::string & queryCmd);

    //int serverScriptingCallback(void *NotUsed, int argc, char **argv, char **azColName);

private:

    RakNet::RakPeerInterface * m_server;
    DataBaseHandler * m_dbh;

    lua_State * m_script;

    
};

#endif // SERVERSCRIPTINGMANAGER_H
