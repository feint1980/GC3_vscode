#ifndef SERVERSCRIPTINGMANAGER_H
#define SERVERSCRIPTINGMANAGER_H

#include <RakNet/MessageIdentifiers.h>
//#pragma pack(push, 1)
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
#include <F_Cryptor_sodium.h>
#include "DataBaseHandler.h"
#include <sstream>
#include <iomanip>
#include <queue>
#include "LuaManager.h"
#include "ClientEPHandler.h"

#include <iostream>
#include <bcrypt.h>
#include "CharacterDes.h"
#include "SkillDesc.h"
#include "CharacterManager.h"

#include "ServerDataRegister.h"

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

    void handleInput(const std::string & command);

    ClientRequestCode handleCommand(RakNet::Packet *p);

    unsigned int handleCommon(RakNet::Packet *p);

    std::string getMegFromPackget(RakNet::Packet *p);

    std::string getDecryptMessage(const std::string & data, const std::string & guid);

    uint32_t getTargetPing(const RakNet::SystemAddress & target);

    uint32_t sendData(const RakNet::SystemAddress & target, const std::string & data,bool isEncrypted = true);

    uint32_t sendWrapData(const RakNet::SystemAddress & target, const std::string & guid, const std::string & data);

    uint32_t sendWrapData2BatlleServer(const RakNet::SystemAddress & target, const std::string & guid, const std::string & data);


    uint32_t handleWrapData(RakNet::Packet *p);

    uint32_t handleBattleServerPacket(RakNet::Packet *p);

    void addWrapDataPacket(RakNet::Packet *original);

    void addBattleServerPacket(RakNet::Packet *original);

    void handleWrapDataQueue(float deltaTime);

    void handleBattleServerQueue(float deltaTime);

    std::string getEncryptPW(const std::string & pw);

    SkillStats getSkillStats(const std::string & skillName);

    // int ExecuteComand(const std::string & command,);

    // std::string getDecryptMsg(const std::string & data);

    bool doQuery(const std::string & queryCmd);

    bool doQuery(sqlite3_stmt * stmt);

    sqlite3 * getDB() { return m_dbh->getDatabase();}

    void addSkillStats(const std::string & skillName, const SkillStats & skillAtt);

    void addCryptor(const std::string & guid);

    void removeCryptor(const std::string & guid);

    void registerIP(const std::string & guid, RakNet::SystemAddress * ip);
    RakNet::SystemAddress * getRegisterIP(const std::string & guid);


private:

    // Feintgine::F_Cryptor m_cryptor;

    std::unordered_map<std::string , Feintgine::F_Cryptor_sodium *> m_cryptors;


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

    std::queue <RakNet::Packet *> m_battleServerPacketQueue;

    // std::unordered_map<std::string, CharacterDesc* > m_characterMaps;

    ClientEPHandler * m_clientEPHandler = nullptr;

    CharacterManager * m_characterManager = nullptr;

    std::unordered_map<std::string, RakNet::SystemAddress *> m_registerIPMap;

    //std::vector<std::thread> m_threads;

    // Feintgine::F_Cryptor_sodium m_cryptorSodium;

  //  std::thread m_handleCommonThread;

};

#endif // SERVERSCRIPTINGMANAGER_H