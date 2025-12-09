#ifndef BATTLEMAIN_H
#define BATTLEMAIN_H

#include <RakNet/MessageIdentifiers.h>
#include <RakNet/RakPeerInterface.h>
#include <RakNet/RakNetStatistics.h>
#include <RakNet/RakNetTypes.h>
#include <RakNet/BitStream.h>
#include <RakNet/RakSleep.h>
#include <RakNet/PacketLogger.h>
#include <RakNet/Gets.h>
#include <RakNet/Kbhit.h>
#include <RakNet/RakNetTime.h>
#include <RakNet/RakMemoryOverride.h>
#include <RakNet/GetTime.h>
#include <assert.h>
#include <cstdio>
#include <cstring>
#include <stdlib.h>

#include <stdio.h>
#include <string.h>
#include "NetworkPacket.h"
#include <F_Cryptor.h>
#include <F_Cryptor_sodium.h>
#include <sstream>
#include <iomanip>
#include <queue>
#include "LuaManager.h"

#include <iostream>
#include <bcrypt.h>
#include "CharacterDes.h"

#include <thread>
#include <set>
#include "LobbiesManager.h"

class BattleMain
{
public:
    BattleMain();
    ~BattleMain();
    void init(const std::string & password, const std::string & mainServerPassword, int port, unsigned int serverSize,const std::string & mainServerIP);

    void handleConnections(RakNet::Packet *p);

    void run();

    void update(float deltaTime);

    void listen();

    void addCommonPacket(RakNet::Packet *p);

    void handleCommonPacketQueue();

    void handleCommonPacket(RakNet::Packet *p);

    void addInternalPacket(RakNet::Packet *p);

    void handleInternalPacketQueue();

    uint32_t handleInternalPacket(RakNet::Packet *p);

    uint32_t sendWrapData(const RakNet::SystemAddress & target,const std::string & guid, const std::string & data);

    RakNet::RakPeerInterface * getServerInstance() { return m_server; }

    void addCryptor(const std::string & guid);

    void removeCryptor(const std::string & guid);

    void setName(const std::string & name) { m_name = name; }

    void sendBackPong(RakNet::Packet *p);

    void addAcceptedClientGUID(const std::string & guid) {
        
        m_acceptedClientGUID.insert(guid);
    
    }

    void removeAcceptedClientGUID(const std::string & guid) { m_acceptedClientGUID.erase(guid); }


    uint64_t createLobby(const std::string & name, const std::string & password);

    void joinLobby(uint64_t id, const std::string & guid, const RakNet::SystemAddress & address);

private:

    RakNet::RakPeerInterface * m_server = nullptr;
    RakNet::SocketDescriptor m_socketDescriptor;
    RakNet::RakNetStatistics * m_statistics = nullptr;

    lua_State * m_script = nullptr;
    std::string m_password;
    std::string m_mainServerPassword;
    std::string m_mainServerIP;
    int m_port = 0;
    int m_connectionSize = 0;

    bool m_serverOn = false;
    std::queue<RakNet::Packet*> m_commonPacketQueue;

    std::queue<RakNet::Packet*> m_internalPacketQueue;

    Feintgine::F_Cryptor_sodium m_mainServerCryptor;

    std::unordered_map<std::string , Feintgine::F_Cryptor_sodium *> m_cryptors;

    std::string m_name = "BattleServer";

    LobbiesManager m_lobbiesManager;

    std::set<std::string> m_acceptedClientGUID;

};

#endif