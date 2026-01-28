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


// struct internalLuaHandler
// {
//     bool isDefault = false;
//     RakNet::MessageID messageIDType;
//     std::string functionName;
//     internalLuaHandler(RakNet::MessageID messageID, std::string functionName, bool isDefault = false) : messageIDType(messageID), functionName(functionName) { 
//         this->isDefault = isDefault;
//     }
// };

constexpr float NET_BUDGET_RATIO = 0.1f; // 10% of frame time
constexpr float NET_BUDGET = 0.1f; // 10% of frame time
constexpr float MAX_NET_BUDGET  = 0.003f; // hard cap: 3ms

struct RakNetPacketDeleter
{
    void operator()(RakNet::Packet* p) const
    {
        if (!p) return;
        delete[] p->data;
        delete p;
    }
};

struct wrappedPacket
{
    unsigned char packetIdentifier = 0;
    std::unique_ptr<RakNet::Packet, RakNetPacketDeleter> packet;

    explicit  wrappedPacket(unsigned char id, RakNet::Packet* p)
        : packetIdentifier(id)
    {
        RakNet::Packet* copy = new RakNet::Packet();
        copy->length = p->length;
        copy->data = new unsigned char[p->length];
        memcpy(copy->data, p->data, p->length);
        copy->systemAddress = p->systemAddress;
        copy->guid = p->guid;

        packet.reset(copy);
    }
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

    void updateV2(float deltaTime);

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

    void disconnectFromCurrentBattleServer();

    void setCommonHandlingLuaFunction(const std::string & functionName) { m_luaCommonMessageHandlingFunctionName = functionName; }

    void setWrappedMessageHandlingLuaFunction(RakNet::MessageID messageID, const std::string & functionName) { m_wrappedMessageHandlingFunctionNames[messageID] = functionName; }

    // void handlePacketInLua(RakNet::Packet *p);

    void handleWrappedPacketInLua(float deltaTime);

    void handleDefaultPacketInLua(float deltaTime);

    void filterPacketForLua(RakNet::Packet *p);

    std::string getCurrentBattleServerGUID()const{ return m_currentBattleServerGUID; }

    RakNet::SystemAddress getServerIPAddr() { return m_serverIPAddr; }

    RakNet::SystemAddress * getCurrentBattleServerIP() { return m_currentBattleServerIP; }

    void setBattleServerIPMap(std::unordered_map<std::string, RakNet::SystemAddress * > map) { m_battleServerIPMap = std::move(map); }

    std::unordered_map<std::string, RakNet::SystemAddress * > getBattleServerIPMap() { return m_battleServerIPMap; }

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

    Feintgine::F_Cryptor_sodium * m_battleServerCryptor;

    std::unordered_map<std::string, int> m_battleServerPingMap;

    std::unordered_map<std::string, RakNet::SystemAddress * > m_battleServerIPMap;

    RakNet::SystemAddress * m_currentBattleServerIP = nullptr;

    std::string m_currentBattleServerGUID = "";

    RakNet::SystemAddress m_serverIPAddr;

    std::queue <RakNet::Packet *> m_responseQueue;

    std::queue <RakNet::Packet *> m_storedPacket;

    std::unordered_map<std::string, Feintgine::F_Cryptor_sodium *> m_cryptors;
    
    std::queue <wrappedPacket> m_luaWrappedPacketQueue;
    std::queue <std::unique_ptr<RakNet::Packet>> m_luaDefaultPacketQueue;

    std::string m_luaCommonMessageHandlingFunctionName;
    std::unordered_map<RakNet::MessageID, std::string> m_wrappedMessageHandlingFunctionNames;

    std::unordered_map<RakNet::MessageID, Feintgine::F_Cryptor_sodium *> m_wrappedMessageHandlingFunctionCryptors;

    float m_wrapperElapseCounter = 0;
    float m_defaultElapseCounter = 0;

};

#endif