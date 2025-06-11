#ifndef CLIENTSCRIPTINGMANAGER_H
#define CLIENTSCRIPTINGMANAGER_H

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
#include "CharacterDes.h"
#include <iostream>
#include <F_Cryptor.h>
#include "LuaManager.h"

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

    void connect();

    void update(float deltaTime);

    void handleData();

    void handleMessage(RakNet::Packet *p);

    void firstGateWay(RakNet::Packet *p);
    
    CharacterStats parseFromStr(const std::string & str);

    void secondGateWay(RakNet::Packet *p);

    bool sendDataToLuaScripting(RakNet::Packet *p);

    ClientStatus getStatus() { return m_status; }

    void setStataus(ClientStatus status) { m_status = status; }

    void cleanUp();

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

    Feintgine::F_Cryptor m_cryptor;

    std::queue <RakNet::Packet *> m_responseQueue;

};

#endif