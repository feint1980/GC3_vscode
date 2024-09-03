#ifndef CLIENTMAIN_H
#define CLIENTMAIN_H

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
#ifdef _WIN32
#include <RakNet/WindowsIncludes.h>
#else 
#include <unistd.h>
#endif

#include <stdio.h>
#include <string.h>
//#include "Gets.h"


#include <iostream>



enum ClientCommand
{
    QUIT = 22,
    STATS,
    PING,
    GETLASTPING,
    CONNECT,
    DISCONNECT,
    STARTUP, // 
    SHUTDOWN, // 
    UNKNOWN = 792
};

class ClientMain
{
public:
    ClientMain();
    ~ClientMain();

    void init(const std::string & serverIP, unsigned int port, unsigned int serverSize);

    void update(float deltaTime);

    void run();

    void handleInput();

    void handleCommand(const std::string & command);

    ClientCommand getCommand(const std::string & command);

    private:

private: 

    std::string m_serverIP;
    int m_port;

    bool m_clientOn = true;

    unsigned int m_connectionSize = 0;

    std::string pw ;

    RakNet::RakPeerInterface *m_client;

    RakNet::SocketDescriptor m_socketDescriptor;

    RakNet::RakNetStatistics * m_statistics;

    RakNet::Packet * m_currentPacket;

    RakNet::SystemAddress m_clientID =RakNet::UNASSIGNED_SYSTEM_ADDRESS;

    char messageBuffer[2048];
    char serverBroadcast[2048];

};


#endif // ClientMain_H