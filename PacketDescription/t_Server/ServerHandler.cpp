#include "ServerHandler.h"

int _kbhit (void)
{
	struct timeval tv;
	fd_set rdfs;
	
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	
	FD_ZERO(&rdfs);
	FD_SET (STDIN_FILENO, &rdfs);
	
	select(STDIN_FILENO+1, &rdfs, NULL, NULL, &tv);
	return FD_ISSET(STDIN_FILENO, &rdfs);
	
}


int ServerHandler::init(unsigned int port, const std::string& Password, long timeout, unsigned int maxConnection)
{


	std::cout << "|=========================================|\n";
	std::cout << "|            Init DataBase                |\n";
	m_dbh.loadDataBase("/var/sqlite3/RIMM_Next.db");
	std::cout << "|=========================================|\n";


	std::cout << "|=========================================|\n";
        std::cout << "|       Init File Transfer Host           |\n";
        m_fth.init(60000);
        std::cout << "|=========================================|\n";

	int setupStatus = 0;
	m_port = port;
	m_server = RakNet::RakPeerInterface::GetInstance();
	
	m_server->SetIncomingPassword(Password.c_str(), Password.size());
	std::cout << "Password " << Password.c_str() << "\n";
	m_server->SetTimeoutTime(30000, RakNet::UNASSIGNED_SYSTEM_ADDRESS);

	m_clientID = RakNet::UNASSIGNED_SYSTEM_ADDRESS;

	//RakNet::SocketDescriptor socketDescriptors[2];
	socketDescriptors[0].port = m_port;
	socketDescriptors[0].socketFamily = AF_INET; 
	socketDescriptors[1].port = m_port;
	socketDescriptors[1].socketFamily = AF_INET6;
	m_maxConnections = maxConnection;
	std::cout << "setting up server with dual IPV4 IPV6  using port " << m_port << "\n";
	bool b = m_server->Startup(m_maxConnections, socketDescriptors, 2)==RakNet::RAKNET_STARTED;
	m_server->SetMaximumIncomingConnections(m_maxConnections);
	if (!b)
	{
		std::cout << "failed to start dual IVP4 and IPV6 ports, try IVP4 \n";
		b = m_server->Startup(m_maxConnections, socketDescriptors, 1) == RakNet::RAKNET_STARTED;
		if (!b)
		{
			std::cout << "unble to set up any ports, terminating ...\n";
			setupStatus = b;
			//return b;
		}
	}
	
	std::cout << "set up done ... \n";
	m_server->SetOccasionalPing(true);
	m_server->SetUnreliableTimeout(1000);

	DataStructures::List<RakNet::RakNetSocket2*> sockets;
	m_server->GetSockets(sockets);
	std::cout << "Socket address used by Raknet : \n";
	for (unsigned int i = 0; i < sockets.Size(); i++)
	{
		std::cout << "Address : " << i << "\t" << sockets[i]->GetBoundAddress().ToString(true);
	}
	std::cout << "IP Address :\n";
	for (unsigned int i = 0; i < m_server->GetNumberOfAddresses(); i++)
	{
		RakNet::SystemAddress sa = m_server->GetInternalID(RakNet::UNASSIGNED_SYSTEM_ADDRESS, i);
		std::cout << " - " << i << " " << sa.ToString(false) << " (LAN =" << sa.IsLANAddress() << ")\n";
	}
	std::cout << "GUID : " << m_server->GetGuidFromSystemAddress(RakNet::UNASSIGNED_SYSTEM_ADDRESS).ToString() << " \n";
	showCommand();
	std::cout << "setup status " << setupStatus << "\n";
	return setupStatus;
}

void ServerHandler::handleCommand()
{
	if (_kbhit())
	{
		Gets(buffer, sizeof(buffer));
		CommandCode cc = getCommand(buffer);
		switch (cc)
		{
		case quit :
			exit(6969);
			break;
		case stats:
		{
			
			std::cout << "stat call\n";
			RakNet::SystemAddress address[MAX_CONNECTIONS];
			unsigned short numConnections = MAX_CONNECTIONS;
			m_server->GetConnectionList((RakNet::SystemAddress*)&address, &numConnections);


			for (int i = 0; i < numConnections; i++)
			{
				m_statistics = m_server->GetStatistics(m_server->GetSystemAddressFromIndex(i));
				RakNet::StatisticsToString(m_statistics, buffer, 2);
				std::cout << buffer << " !!!! \n";
				printf("Ping %i\n", m_server->GetAveragePing(m_server->GetSystemAddressFromIndex(i)));
			}
		}
			break;
		case ping:
			m_server->Ping(m_clientID);
			break;
		case pingip:
			std::cout << "Enter the IP you want to ping \n";
			Gets(buffer, sizeof(buffer));
			m_server->Ping(buffer, m_port, false);
			break;

		case help:
			showCommand();
			break;
		case kick:
			m_server->CloseConnection(m_clientID, true, 0);
			break;
			//StatisticsToString()
		case list:
		{
			std::cout << "list of connected client : \n";
			RakNet::SystemAddress address[MAX_CONNECTIONS];
			unsigned short numConnections = MAX_CONNECTIONS;
			m_server->GetConnectionList((RakNet::SystemAddress*)&address, &numConnections);
			for (int i = 0; i < numConnections; i++)
			{
				std::cout << i << " : " << address[i].ToString(true) << "\n";
			}
		}break;
		case undefined:
			const static char prefix[] = "Server: ";
			strncpy(buffer2, prefix, sizeof(buffer2));
			strncat(buffer2, buffer, sizeof(buffer2) - strlen(prefix) - 1);
			m_server->Send(buffer2, (const int)strlen(buffer2) + 1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
			break;
		}
	}
}

CommandCode ServerHandler::getCommand(char* command)
{
	if (strcmp(command, "quit") == 0)
	{
		return quit;
	}
	if (strcmp(command, "stat") == 0)
	{
		return stats;
	}
	if (strcmp(command, "ping") == 0)
	{
		return ping;
	}
	if (strcmp(command, "pingip") == 0)
	{
		return pingip;
	}
	if (strcmp(command, "ban") == 0)
	{
		return ban;
	}
	if (strcmp(command, "kick") == 0)
	{
		return kick;
	}
	if (strcmp(command, "list") == 0)
	{
		return list;
	}
	if (strcmp(command, "help") == 0)
	{
		return help;
	}
	return undefined;
}



void ServerHandler::showCommand()
{
	std::cout << "'quit' to quit. \n";
	std::cout << "'stat' to show statistics. \n";
	std::cout << "'ping' to ping \n";
	std::cout << "'pingip' to ping an ip address \n";
	std::cout << "'ban' to ban an IP from connecting \n";
	std::cout << "'kick' to kick first connected client \n";
	std::cout << "'list' to list all connected \n";
	std::cout << "'help' for help \n";


}

std::string ServerHandler::processRequest(const std::string & mainStr, std::vector<std::string> listOfKeyword, int location)
{

	std::string returnVal = "";


	if(location > listOfKeyword.size() || location == 0) // NOTE this location we count from 1 
	{
		std::cout << "Error, attemp to process the keyword outside of range\n";
		return "Error code 52 \n";	
	}
	
	unsigned int begin = mainStr.find(listOfKeyword[location -1]) + listOfKeyword[location -1].size();
	unsigned int end   = mainStr.find(listOfKeyword[location]);
	returnVal = mainStr.substr(begin, end - begin);
	

	return returnVal;


}


bool ServerHandler::isLoginLegit(const std::string & tData)
{
	
		
	
	return false;
}

PacketCode ServerHandler::getSpecialRequestCode(RakNet::Packet *p)
{
	std::cout << "check Special Request... \n";
	// check for Login Request 
	std::string cData((const char*) p->data);	
	//std::cout << cData << "\n";
	if(cData.find("|LOGIN_REQUEST|") != std::string::npos)
	{
		std::cout << "Login request found !!!\n";
		//proceed to verify login
		
		return PacketCode::login;	
	}
	if(cData.find("|DOWNLOAD_REQUEST|") != std::string::npos)
	{
		std::cout << "Download request found !!!\n";
		return PacketCode::download;
	}
	std::cout << "Not a request, normal message : \n";
	return PacketCode::invalid;

}


void ServerHandler::listen()
{
	unsigned char packetIdentifier;
	for (m_packet = m_server->Receive(); m_packet; m_server->DeallocatePacket(m_packet), m_packet = m_server->Receive())
	{
		packetIdentifier = GetPacketIdentifier(m_packet);
		switch (packetIdentifier)
		{
		case ID_DISCONNECTION_NOTIFICATION:
			std::cout << "ID_DISCONNECTION_NOTIFICATION from " << m_packet->systemAddress.ToString(true) << " \n";
			break;
		case ID_NEW_INCOMING_CONNECTION:
			std::cout << "ID_DISCONNECTION_NOTIFICATION from " << m_packet->systemAddress.ToString(true) << " \n";
			std::cout << "with GUID : " << m_packet->guid.ToString() << "\n";

			m_clientID = m_packet->systemAddress;
			std::cout << "Remote internal IDs : \n";

			// TODO : research what is INTERNAL IDS
			for (int i = 0; i < MAXIMUM_NUMBER_OF_INTERNAL_IDS; i++)
			{
				RakNet::SystemAddress internalID = m_server->GetInternalID(m_packet->systemAddress, i);
				if (internalID != RakNet::UNASSIGNED_SYSTEM_ADDRESS)
				{
					std::cout << i << " :" << internalID.ToString(true) << "\n";
				}
			}
			break;
		case ID_INCOMPATIBLE_PROTOCOL_VERSION:
			std::cout << "ID_INCOMPATIBLE_PROTOCOL_VERSION detected \n";
			break;
		case ID_CONNECTED_PING : 
			std::cout << "Ping from connected client : " << m_packet->systemAddress.ToString(true) << "\n";
			break;
		case ID_UNCONNECTED_PING:
			std::cout << "Ping from UNCONNECTED devices : " << m_packet->systemAddress.ToString(true) << "\n";
			break;
		case ID_CONNECTION_LOST :
			std::cout << "ID_CONNECTION_LOST from " << m_packet->systemAddress.ToString(true) << "\n";
			break;

		case ID_INVALID_PASSWORD:
			std::cout << "Password invalid from " << m_packet->systemAddress.ToString(true) << "\n";
			break;
		default:

			
			PacketCode requestCode = getSpecialRequestCode(m_packet);
			std::vector<std::string> keywords;
			switch(requestCode)
			{
				case PacketCode::login:
				{
					std::cout << "request login from " << m_packet->systemAddress.ToString() << "\n";
					keywords = getKeyword(requestCode);
					std::string mainStr = std::string(m_packet->data);
					std::string str_id = processRequest(mainStr,keywords,1);
					std::string str_pw = processRequest(mainStr,keywords,2);
					std::cout << "id :" << str_id << "\n";
					std::cout << "pw :" << str_pw << "\n"; 
					memset(buffer2,0,2048);
					if(m_dbh.access_user_info(str_id,str_pw))
					{
						// establish tag for user
						// send back granted acess
						strncpy(buffer2,"|LOGIN_RESPONSE|OK|",19);
					}		
					else
					{
						// send back failed message 
						strncpy(buffer2,"|LOGIN_RESPONSE|FAILED|",23);
						
					}
						m_server->Send(buffer2,(int)strlen(buffer2) + 1, HIGH_PRIORITY, RELIABLE_ORDERED,0,m_packet->systemAddress,false);
				}	
				break;
				case PacketCode::invalid:
				{
					
					std::cout << "================================\n";
					std::cout <<   m_packet->data << "\n";
					std::cout << "================================\n";	
					sprintf(buffer2, "%s",m_packet->data);
					m_server->Send(buffer2, (const int)strlen(buffer2) + 1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_packet->systemAddress, true);
				}
				break;
				case PacketCode::download:
				{
					std::cout << "Request Download from " << m_packet->systemAddress.ToString() << "\n";
					keywords = getKeyword(requestCode);
					std::string mainStr = std::string(m_packet->data);
                                        std::string str_id = processRequest(mainStr,keywords,1);
                                        std::string str_fp = processRequest(mainStr,keywords,2);
                                        std::cout << "generatedid :" << str_id << "\n";
                                        std::cout << "file path   :" << str_fp << "\n";
                                        memset(buffer2,0,2048);
					//Send file 	
					std::string filePath = "/root/download/master.zip";
					m_fth.sendFile(filePath);
					
					strncpy(buffer2,"|DOWNLOAD_RESPONSE|",19);
					strncat(buffer2,filePath.c_str(), filePath.size());
					m_server->Send(buffer2, (int)strlen(buffer2)  + 1, HIGH_PRIORITY, RELIABLE_ORDERED,0, m_packet->systemAddress,false);	
					
				}
				break;
				default:
				break;
			}
			break;
		}
	}
}
void ServerHandler::send()
{

}
std::vector<std::string> ServerHandler::getKeyword(PacketCode requestCode)
{
	std::vector<std::string> returnVec;	
	switch(requestCode)
	{
		case PacketCode::login:
		{
			returnVec.push_back("|LOGIN_REQUEST|");
			returnVec.push_back("|_ENCRYPED_METHOD_|");
			returnVec.push_back("|REQUEST_END|");
		}
		break;	
		case PacketCode::download:
		{
			returnVec.push_back("|LOGIN_DOWNLOAD|");
			returnVec.push_back("|_GENERATED_ID_|");
			returnVec.push_back("|REQUEST_END|");
		}	
		break;	
		default: 
			// not decided yet 
		break;

	}	
	//std::cout << "Server Handler checkout \n";
	return returnVec;
		
}

void ServerHandler::update()
{
	while (isRunning)
	{
		RakSleep(30);
		handleCommand();
		listen();
		m_fth.update();		
	}

	m_server->Shutdown(300);
	RakNet::RakPeerInterface::DestroyInstance(m_server);
}

unsigned char ServerHandler::GetPacketIdentifier(RakNet::Packet* p)
{
	if (!p)
	{
		return 255;
	}
	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
	{
		//std::cout << "packge valid \n";
		RakAssert(p->length > sizeof(RakNet::MessageID) + sizeof(RakNet::Time));
		return (unsigned char)p->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time)];

	}
	else
	{
		//std::cout << "package is custom \n";
		return (unsigned char)p->data[0];
	}


}
