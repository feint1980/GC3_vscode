
// #include "Enet_UDP.h"

// #ifdef _WIN32

// typedef unsigned char uint8;
// #elif __linux__ 

// typedef unsigned char     uint8_t;
// typedef unsigned char     UINT8;
// typedef unsigned char     uint8;

// #endif



// Enet_UDP *Enet_UDP::p_Instance = 0;

// Enet_UDP::Enet_UDP()
// {

// }


// Enet_UDP::~Enet_UDP()
// {	
// 	enet_peer_disconnect(peer, 1);
// 	//disconenct();
// 	//sendMessage("i'm done");
	
// }

// bool Enet_UDP::initEnet()
// {
// 	return enet_initialize() == 0;
// }

// void Enet_UDP::connectToServer(const char * server_address, unsigned int port)
// {
// 	enet_address_set_host(&address, server_address);
// 	address.port = port;

// 	peer = enet_host_connect(client, &address, 2, 0);
// 	if (peer == NULL)
// 	{
// 		std::cout << " can not connect to host " << server_address << "\n";
		
// 	}
// 	else
// 	{
// 		std::cout << "connected brah ! \n";
// 		sentRequest = true;
// 	}

// }

// void Enet_UDP::createHost_Self()
// {
// 	client = enet_host_create(NULL /* create a client host */,
// 		1 /* only allow 1 outgoing connection */,
// 		2 /* allow up 2 channels to be used, 0 and 1 */,
// 		57600 / 8 /* 56K modem with 56 Kbps downstream bandwidth */,
// 		14400 / 8 /* 56K modem with 14 Kbps upstream bandwidth */);
// 	if (client == NULL)
// 	{
// 		std::cout << "unable to create the Self Host\n";
		
// 	}

// }

// void Enet_UDP::getConnectionResponse()
// {
// 	while (enet_host_service(client, &e_event, 1) > 0 &&
// 		e_event.type == ENET_EVENT_TYPE_CONNECT)
// 	{
// 		uint8 * dotQuad = (UINT8*)&address.host;

// 		//... and then outputting them cast to integers. Then read the last 16 bits of the serverIP object to get the port number
// 		std::cout << "Successfully to resolved host to IP: " << (unsigned short)dotQuad[0] << "." << (unsigned short)dotQuad[1] << "." << (unsigned short)dotQuad[2] << "." << (unsigned short)dotQuad[3] << "\n";

// 		isConnected = true;



// 	}
// 	//		enet_peer_disconnect_now(peer, 0);

// }

// void Enet_UDP::setConnection(bool value)
// {
// 	isConnected = value;
// }

// void Enet_UDP::sendMessage(const std::string & msg)
// {
// 	ENetPacket * packet = enet_packet_create(msg.c_str(),
// 		strlen(msg.c_str()) + 1,
// 		ENET_PACKET_FLAG_RELIABLE);
// 	/* Extend the packet so and append the string "foo", so it now */
// 	/* contains "packetfoo\0"   */

	
// 	enet_packet_resize(packet, msg.size() + 1);
// 	//strcpy((char*)packet->data, msg.c_str());
// 	//packet->data = msg.c_str();
// 	//char feintbuf[256];
// 	//strcpy(feintbuf, msg);
// 	memcpy(packet->data, msg.data(),msg.size());
// 	//strncpy((char*)packet->data, msg.c_str(), msg.size() 
// 	/* Send the packet to the peer over channel id 0. */
// 	/* One could also broadcast the packet by         */
// 	/* enet_host_broadcast (host, 0, packet);         */
// 	int bytesent = enet_peer_send(peer, 0, packet);

// 	enet_host_flush(client);
// 		/* One could just use enet_host_service() instead. */
// 	//enet_host_flush(host);
// }

// void Enet_UDP::setRequestSend(bool value)
// {
// 	sentRequest = value;
// }



// void Enet_UDP::updateUDP()
// {
// // 	while (enet_host_service(client, &e_event, 1) > 0 )
// // 	{
// // 
// // 		switch (e_event.type)
// // 		{
// // 		case ENET_EVENT_TYPE_RECEIVE:
// // 		{
// // 
// // 			// 			printf("A packet of length %u containing %s was received from %s on channel %u.\n",
// // 			// 				m_event.packet->dataLength,
// // 			// 				m_event.packet->data,
// // 			// 				m_event.peer->data,
// // 			// 				m_event.channelID);
// // 			// 			/* Clean up the packet now that we're done using it. */
// // 			// 			sendMessage(m_event.peer, "welcome you to Blind Eye ");
// // 			UDP_msg msg;
// // 			std::string buffer;
// // 
// // 
// // 			buffer = std::string((char *)e_event.packet->data, e_event.packet->dataLength);
// // 			msg.ParseFromString(buffer);
// // 
// // 			switch (msg.type())
// // 			{
// // 			case UDP_PLAYERSTATE:
// // 			{
// // 				//if (msg.m_playerstate().has_x_pos() && msg.m_playerstate().has_y_pos())
// // 				//{
// // 				std::cout << " contain action " << msg.m_playerstate().action()
// // 					<< "\n name " << msg.m_playerstate().name() << " \n "
// // 					<< "x : " << msg.m_playerstate().x_pos() << " y " << msg.m_playerstate().y_pos()
// // 					<< "\n";
// // 
// // 			
// // 				//}
// // 				// 				else
// // 				// 				{
// // 				// 					std::cout << " lack of data \n";
// // 				// 				}
// // 
// // 			}
// // 			break;
// // 			default:
// //				break;
// // 			}
// // 			break;
// // 		}
// // 		default:
// // 			break;
// // 		}
// // 
// // 
// // 	}
// }

// void Enet_UDP::disconenct()
// {
// 	enet_peer_disconnect(peer, 1);
// 	//enet_peer_reset(peer);
// }

// void Enet_UDP::sendPlayerState(const std::string & name, int action, glm::vec2 pos)
// {
// 	UDP_msg sendPack;
// 	sendPack.set_type(UDP_PLAYERSTATE);

// 	PlayerState state;
// 	state.set_action(action);
// 	state.set_name(name);
// 	state.set_x_pos(pos.x);
// 	state.set_y_pos(pos.y);
// 	Enet_UDP::Instance()->UDP_setPlayerState(state, *sendPack.mutable_m_playerstate());
// 	//sendPack.set_allocated_m_playerstate(&state);

// 	//Enet_UDP::Instance()->sendMessage("yo yo yo 1 4 8 3 to the 3 to the 6 to the 9 \n");
// 	Enet_UDP::Instance()->sendMessage(sendPack.SerializeAsString());
// }

// std::string Enet_UDP::checkForIncomingMessages()
// {

// 	std::string data = "";
// 	while (enet_host_service(client, &e_event, 1) > 0)
// 	{

// 		switch (e_event.type)
// 		{
// 		case ENET_EVENT_TYPE_RECEIVE:
// 		{


// 			std::string buffer;

// 			if (e_event.packet->dataLength < 0)
// 			{
// 				exit(1);
// 			}
// 			buffer = std::string((char *)e_event.packet->data, e_event.packet->dataLength);
// 			data = buffer;
		
// 			break;
// 		}
// 		default:
// 			break;
// 		}


// 	}
// 	return data;


// }
