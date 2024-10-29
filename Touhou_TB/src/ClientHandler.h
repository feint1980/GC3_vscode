#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H


#include "../../PacketDescription/NetworkPacket.h"



class ClientHandler
{
public:
    ClientHandler();
    ~ClientHandler();

    void init(const std::string & serverIP, unsigned int port);


    private:

    std::string pw; 
    std::string m_serverIP;
    int m_port;

};


#endif