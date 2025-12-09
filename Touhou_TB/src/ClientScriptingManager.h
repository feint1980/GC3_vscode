#ifndef CLIENTSCRIPTINGMANAGER_H
#define CLIENTSCRIPTINGMANAGER_H

#include <RakNet/MessageIdentifiers.h>
//#pragma pack(push, 1)
#include <RakNet/RakPeerInterface.h>
#include <RakNet/RakNetStatistics.h>
#include <RakNet/RakNetTypes.h>
#include <RakNet/BitStream.h>
#include <RakNet/RakSleep.h>
#include <RakNet/PacketLogger.h>
#include <RakNet/Gets.h>
#include <RakNet/RakNetTime.h>
#include <RakNet/Kbhit.h>
#include <RakNet/GetTime.h>
#include <assert.h>
#include <cstdio>
#include <cstring>
#include <stdlib.h>

#include <stdio.h>
#include <string.h>
#include "NetworkPacket.h"
#include "CharacterDes.h"
#include <iostream>
// #include <F_Cryptor.h>
#include <F_Cryptor_sodium.h>
#include "LuaManager.h"
#include "InfoHolder.h"
#include <thread>

#include <queue>

enum ClientStatus
{
    Disconnected,
    Connected, 
    FailedAttemp,
    LoginGranted,
    Banned,
    Incompatible,
    IsFull,
    WSPacket,
};

struct ResponseMSG
{
    RakNet::Packet *packet;
    unsigned char packetIdentifier;
    ResponseMSG(RakNet::Packet *p, unsigned char packetIdentifier) : packet(p), packetIdentifier(packetIdentifier) {}
};

class ClientScriptingManager
{
public:
    ClientScriptingManager();
    ~ClientScriptingManager();

    void init(const std::string & serverIP, unsigned int port,  RakNet::RakPeerInterface * client, lua_State * script);

    uint32_t sendData(const std::string & data, uint8_t encryptIndex);

    uint32_t sendWrapData(const std::string & data);

    uint32_t sendBattleWrapData(const std::string & data);

    uint32_t handleWrapData(RakNet::Packet *p);


    std::string getDecryptMessage(const std::string & data);

    void setIPAddress(const RakNet::SystemAddress &addr) { m_serverIPAddr = addr; }

    void connect();

    void connect2BattleServer(const std::string & guid);

    void connect2BattleServer(const std::string & ipAddr, unsigned int port);

    void update(float deltaTime);

    void updateScript(float delta);

    void handleData();

    void handleReceive();

    void handleMessage(RakNet::Packet *p);

    void firstGateWay(RakNet::Packet *p);
    
    std::string getClientGUID() ;

    CharacterStats parseFromStr(const std::string & str);

    void secondGateWay(RakNet::Packet *p);

    bool sendDataToLuaScripting(RakNet::Packet *p);

    ClientStatus getStatus() { return m_status; }

    void setStataus(ClientStatus status) { m_status = status; }

    void cleanUp();

    int getPingFromServer(const RakNet::SystemAddress & addr);

    int pingToServer(const std::string & ip, int port);

    void collectPong(RakNet::Packet *p);

    void addCryptor(const std::string & guid);

    void removeCryptor(const std::string & guid);

    void selectBattleServer(const std::string & guid);

    void handleInternalPacket(float deltaTime);

    void processInternalPacket(RakNet::Packet *p);

    std::string getCurrentBattleServerGUID()const{ return m_currentBattleServerGUID; }

    RakNet::SystemAddress getServerIPAddr() { return m_serverIPAddr; }

    RakNet::SystemAddress * getCurrentBattleServerIP() { return m_currentBattleServerIP; }

    private:
    RakNet::RakPeerInterface * m_client = nullptr;

    RakNet::Packet * m_currentPacket = nullptr;

    lua_State * m_script = nullptr;

    ClientStatus m_status = ClientStatus::Disconnected;

    bool m_isConnected = false; 

    // RakNet Core component
    std::string pw; 
    std::string m_serverIP;
    unsigned int m_port;
    RakNet::SocketDescriptor m_socketDescriptor;
    bool m_RakNetCoreInitialized = false;

    std::unordered_map<std::string, CharacterStats> m_characterStatsDict;

    Feintgine::F_Cryptor_sodium * m_cryptor;

    std::unordered_map<std::string, int> m_battleServerPingMap;

    std::unordered_map<std::string, RakNet::SystemAddress * > m_battleServerIPMap;

    RakNet::SystemAddress * m_currentBattleServerIP = nullptr;

    std::string m_currentBattleServerGUID = "";

    RakNet::SystemAddress m_serverIPAddr;

    std::queue <RakNet::Packet *> m_responseQueue;

    std::queue <RakNet::Packet *> m_storedPacket;

    std::unordered_map<std::string, Feintgine::F_Cryptor_sodium *> m_cryptors;
    
};

#endif