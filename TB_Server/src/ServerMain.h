#ifndef SERVERMAIN_H
#define SERVERMAIN_H

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
#include <array>
#include "NetworkPacket.h"
#include "DataBaseHandler.h"
#include <RakNet/SecureHandshake.h>
//#include "Gets.h"


#include <iostream>


class ServerScriptingManager;


class ServerMain
{
public:
    ServerMain();
    ~ServerMain();

    void init(const std::string & password, int port, unsigned int serverSize);

    void update(float deltaTime);

    void run();

    void handleInput();

    void handleCommand(const std::string & command);

    // void handleCommon(RakNet::Packet *p);

    // int handleStep2Request(RakNet::Packet *p);

    PacketCode getCommand(const std::string & command);

    private:

private: 

    std::string m_password;
    int m_port;

    bool m_serverOn = true;

    unsigned int m_connectionSize = 0;

    RakNet::RakPeerInterface *m_server;

    RakNet::SocketDescriptor m_socketDescriptor[2];

    RakNet::RakNetStatistics * m_statistics;

    RakNet::Packet * m_currentPacket;

    RakNet::SystemAddress m_clientID =RakNet::UNASSIGNED_SYSTEM_ADDRESS;

    DataBaseHandler * m_dbh;

    ServerScriptingManager * m_scriptManager;

    char messageBuffer[2048];
    char serverBroadcast[2048];


    //std::array<RakNet::SystemAddress ,100> m_systems;

};


#endif // SERVERMAIN_H