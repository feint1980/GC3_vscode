
#ifndef _CLIENT_HANDLER_H_
#define _CLIENT_HANDLER_H_


#include "MessageIdentifiers.h"

#include "RakPeerInterface.h"
#include "RakNetStatistics.h"
#include "RakNetTypes.h"
#include "BitStream.h"
#include "PacketLogger.h"
#include <assert.h>
#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include "RakNetTypes.h"
#include "RakSleep.h"
#ifdef _WIN32
#include "Kbhit.h"
#include "WindowsIncludes.h" // Sleep
#else
#include "Kbhit.h"
#include <unistd.h> // usleep
#endif
#include "Gets.h"

#include <string>
#include <iostream>

#include "ClientDownloadHandler.h"



enum CommandCode {
	quit,
	disconnect,
	ping,
	reconnect,
	request_login,
	request_download,
	undefined
};


class ClientHandler
{
public :

	void init(unsigned int port);
	void connect(const std::string & ip , unsigned int serverPort);

	void showCommand();

	unsigned char GetPacketIdentifier(RakNet::Packet* p);

	void listen();

	void update();

	CommandCode getCommand(char* command);

	void handleCommand();

	
	std::string getLoginInfo(const std::string & str, int location);	

	//void init()


private:

	RakNet::RakNetStatistics* m_statictis;

	RakNet::RakPeerInterface* m_client;

	RakNet::Packet* m_packet;

	RakNet::SystemAddress clientID;
	
	ClientDownloadHandler m_downloadHandler;

	std::string m_ip;
	unsigned int m_serverPort;
	unsigned int m_clientPort;

//	Raknet::SocketDescriptor m_socketDescriptor;

	char buffer[2048];
	char buffer2[2048];
	bool isRunning = true;
	std::string m_password;

};

#endif
