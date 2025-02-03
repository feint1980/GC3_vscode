#pragma once
#include "MessageIdentifiers.h"

#include "RakPeerInterface.h"
#include "RakNetStatistics.h"
#include "RakNetTypes.h"
#include "BitStream.h"
#include "RakSleep.h"
#include "PacketLogger.h"
#include <assert.h>
#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include "Kbhit.h"
#include <stdio.h>
#include <string.h>
#include <string>
#include "Gets.h"
#include <iostream>
//#include "kbhit.h"

#include "DataBaseHandler.h"
#include "FileTransferHost.h"
#include <vector>



#define E_OK 0
#define E_NOT_OK 1

#define MAX_CONNECTIONS 10



enum CommandCode {
	quit,
	stats,
	ping,
	pingip,
	ban,
	kick,
	list,
	help,
	undefined
};

enum PacketCode
{
	login,
	download,
	invalid

};

class ServerHandler
{
public : 
	int init(unsigned int port ,const std::string& Password,long timeout,unsigned int maxConnection);
	void listen();
	void send();
	void update();
	void handleCommand();
	void showCommand();
	CommandCode getCommand(char* command);

	unsigned char GetPacketIdentifier(RakNet::Packet* p);
	
	PacketCode getSpecialRequestCode(RakNet::Packet *p);
	
	std::string processRequest(const std::string & mainStr, std::vector<std::string> listOfKeyword, int location);
	
	bool isLoginLegit(const std::string & tData);

private :

	std::vector<std::string> getKeyword(PacketCode requestCode);
	RakNet::RakPeerInterface * m_server;
	RakNet::RakNetStatistics * m_statistics;
	RakNet::Packet * m_packet;

	RakNet::SystemAddress m_clientID;

	unsigned int m_port;
	
	unsigned int m_maxConnections;

	bool isRunning = true;
	char buffer [2048];
	char buffer2[2048];

	RakNet::SocketDescriptor socketDescriptors[2];
	DataBaseHandler m_dbh;
	FileTransferHost m_fth;
};


