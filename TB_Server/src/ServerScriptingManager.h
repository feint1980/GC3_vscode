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
#include <sstream>
#include <iomanip>
#include <queue>
#include "LuaManager.h"

#include <iostream>
#include <bcrypt.h>
#include "CharacterDes.h"
#include "SkillDesc.h"

#include <thread>

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

struct MSGResponse
{
    RakNet::Packet *packet;
    PacketCode requestCode;
    MSGResponse(RakNet::Packet *p, PacketCode requestCode) : packet(p), requestCode(requestCode) {};
};

struct CommonResponse
{
    RakNet::Packet *packet;
    unsigned char packetIdentifier;
    CommonResponse(RakNet::Packet *p, unsigned char packetIdentifier) : packet(p), packetIdentifier(packetIdentifier) {};
};

class ServerScriptingManager
{
public:

    PacketCode getSpecialRequestCode(RakNet::Packet *p);

    ServerScriptingManager();
    ~ServerScriptingManager();

    void init(RakNet::RakPeerInterface * server,DataBaseHandler * dbh);
    void update(float deltaTime);

    void handleMessage();

    void handleCommonMSG();

    ClientRequestCode handleCommand(RakNet::Packet *p);

    unsigned int handleCommon(RakNet::Packet *p);

    std::string getMegFromPackget(RakNet::Packet *p);

    std::string getDecryptMessage(const std::string & data);

    uint32_t sendData(const RakNet::SystemAddress & target, const std::string & data,bool isEncrypted = true);

    uint32_t sendWrapData(const RakNet::SystemAddress & target, const std::string & data);

    uint32_t handleWrapData(RakNet::Packet *p);

    void addWrapDataPacket(RakNet::Packet *p);

    void handleWrapDataQueue(float deltaTime);

    std::string getEncryptPW(const std::string & pw);

    // int ExecuteComand(const std::string & command,);

    // std::string getDecryptMsg(const std::string & data);

    bool doQuery(const std::string & queryCmd);

    bool doQuery(sqlite3_stmt * stmt);

    sqlite3 * getDB() { return m_dbh->getDatabase();}

    void addSkillStats(const std::string & skillName, const SkillStats & skillAtt);

private:

    Feintgine::F_Cryptor m_cryptor;

    // Feintgine::F_Cryptor m_pwCryptor;

    RakNet::RakPeerInterface * m_server = nullptr;
    DataBaseHandler * m_dbh = nullptr;

    lua_State * m_script = nullptr;

    unsigned char *passwordSalt = nullptr;

    CharacterDesc m_charDesc;

    std::queue <MSGResponse> m_responseQueue;
    std::queue <CommonResponse> m_commonResponseQueue;

    std::unordered_map<std::string, SkillStats> m_skillStatsMap;


    std::queue <RakNet::Packet *> m_wrapDataQueue;

    //std::thread m_handleMessgeThread;

    //std::vector<std::thread> m_threads;

  //  std::thread m_handleCommonThread;

};

#endif // SERVERSCRIPTINGMANAGER_H