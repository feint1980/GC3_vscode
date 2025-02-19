#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H


#include "../../PacketDescription/NetworkPacket.h"
#include <iostream>


class ClientHandler
{
public:
    ClientHandler();
    ~ClientHandler();

    void init(const std::string & serverIP, unsigned int port);

    void update(float deltaTime);

    void connect();

    bool isConnected() { return m_isConnected; }
    private:

    std::string pw; 
    std::string m_serverIP;
    int m_port;

    RakNet::RakPeerInterface *m_client;

    RakNet::SocketDescriptor m_socketDescriptor;

    RakNet::RakNetStatistics * m_statistics;

    RakNet::Packet * m_currentPacket;

    RakNet::SystemAddress m_clientID =RakNet::UNASSIGNED_SYSTEM_ADDRESS;

    bool m_isInited = false;

    bool m_isConnected = false;

};


#endif