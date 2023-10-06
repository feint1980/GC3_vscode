
/*
#pragma once
#pragma comment(lib,"ws2_32.lib")
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <enet/enet.h>
#include <string>
#include "serverData.pb.h"
#include <glm/glm.hpp>

const int UDP_PLAYERSTATE = 1;

class Enet_UDP
{
public:
	Enet_UDP();
	~Enet_UDP();

	bool initEnet();

	void connectToServer(const char * server_address , unsigned int port);

	void createHost_Self();

	void getConnectionResponse();

	void setConnection(bool value);

	void sendMessage(const std::string & msg);

	bool getConnectionState() const { return isConnected; }

	bool getSentRequuest() const { return sentRequest; }

	void setRequestSend(bool value);

	void updateUDP();

	void disconenct();

	void sendPlayerState(const std::string & name,int action , glm::vec2 post );


	void UDP_setPlayerState(PlayerState &p1, PlayerState &p2)
	{
		p2 = p1;
	}

	static Enet_UDP *Instance()
	{
		if (p_Instance == 0)
		{
			p_Instance = new Enet_UDP;
			return p_Instance;
		}
		return p_Instance;
	}

	std::string checkForIncomingMessages();

	

private:

	bool isConnected = false;

	bool sentRequest = false;

	ENetHost * client;
	ENetPeer *peer;
	ENetAddress address;
	ENetEvent e_event;

	static Enet_UDP * p_Instance;
};

*/