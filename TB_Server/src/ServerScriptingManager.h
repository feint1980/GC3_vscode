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
#include <F_Cryptor.h>
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

    
    PacketCode getSpecialRequestCode(RakNet::Packet *p);

    ServerScriptingManager();
    ~ServerScriptingManager();

    void init(RakNet::RakPeerInterface * server,DataBaseHandler * dbh);
    void update(float deltaTime);

    ClientRequestCode handleCommand(RakNet::Packet *p);

    std::string getMegFromPackget(RakNet::Packet *p);

    uint32_t sendData(const RakNet::SystemAddress & target, const std::string & data);

    std::string getEncryptPW(const std::string & pw);

    // std::string getDecryptMsg(const std::string & data);

    bool doQuery(const std::string & queryCmd);

    bool doQuery(sqlite3_stmt * stmt);

    sqlite3 * getDB() { return m_dbh->getDatabase();}

private:

    Feintgine::F_Cryptor m_cryptor;

    Feintgine::F_Cryptor m_pwCryptor;

    RakNet::RakPeerInterface * m_server;
    DataBaseHandler * m_dbh;

    lua_State * m_script;

    unsigned char *passwordSalt;


};

#endif // SERVERSCRIPTINGMANAGER_H