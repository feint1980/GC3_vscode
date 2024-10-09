#include "ClientHandler.h"



int _kbhit (void)
{  struct timeval tv;
  fd_set rdfs;
 
  tv.tv_sec = 0;
  tv.tv_usec = 0;
 
  FD_ZERO(&rdfs);
  FD_SET (STDIN_FILENO, &rdfs);
 
  select(STDIN_FILENO+1, &rdfs, NULL, NULL, &tv);
  return FD_ISSET(STDIN_FILENO, &rdfs);
 
}

void ClientHandler::init(unsigned int port)
{
	m_client = RakNet::RakPeerInterface::GetInstance();
	m_clientPort = port;
	m_client->AllowConnectionResponseIPMigration(false);
	clientID = RakNet::UNASSIGNED_SYSTEM_ADDRESS;
	std::cout << "init with port " << port << "\n";
	//m_socketDescriptor = Raknet::SocketDescriptor(atoi(m_clientPort),0);
	
	//Raknet::SocketDescriptor socketDescriptor(atoi(m_clientPort),0);
	//m_socketDescriptor.socketFamily=AF_INET;
	//m_client->Startup(8,&socketDescriptor,1);
	m_client->SetOccasionalPing(true);
	m_password = "Studio-WaVN";
	m_downloadHandler.init(m_ip,60000,1,-999);
}


void ClientHandler::showCommand()
{
	std::cout << "'quit' to quit \n";
	std::cout << "'ping' to ping \n";
	std::cout << "'disconnect' to disconnect \n";
	std::cout << "'reconnect' to reconnnect \n";

}

CommandCode ClientHandler::getCommand(char* command)
{
	std::string tVerifystr(command);

	if (strcmp(command, "quit") == 0)
	{
		return quit;
	}
	if (strcmp(command, "ping") == 0)
	{
		return ping;
	}
	if (strcmp(command, "reconnect") == 0)
	{
		return reconnect;
	}
	if (strcmp(command, "disconnect") == 0)
	{
		return disconnect;
	}
	
	std::string subCMD = tVerifystr.substr(0,5);
	if(subCMD.find("login") != std::string::npos)
	{
		if(tVerifystr.find("_BEGIN_") != std::string::npos && tVerifystr.find("_MID_") != std::string::npos && tVerifystr.find("_END_") != std::string::npos)
		{
			if(subCMD == "login")
			{
				std::cout << "request login \n";	
				return request_login;
			}
		}
	}
	
	subCMD = tVerifystr.substr(0,8);// resub the str for more secure
	if(subCMD.find("download") != std::string ::npos)
	{
		if(tVerifystr.find("_BEGIN_") != std::string::npos && tVerifystr.find("_MID_") != std::string::npos && tVerifystr.find("_END_") != std::string::npos)
		{
			if(subCMD == "download")
			{
				std::cout << "request download \n";
				return request_download;
			}
		}
	}
	return undefined;
}


std::string ClientHandler::getLoginInfo(const std::string & str, int location)
{
	std::string returnVal = "";

	unsigned int begin       = str.find("_BEGIN_") + 7;
	unsigned int mid_start   = str.find("_MID_")   + 0;
	unsigned int mid_end     = str.find("_MID_")   + 5;
	unsigned int end         = str.find("_END_")   + 0;

	switch(location)
	{
		case 1 :
			returnVal = str.substr(begin,mid_start - begin);		
			std::cout << returnVal << "\n";
		break;
		case 2:
			returnVal = str.substr(mid_end,end - mid_end);
			std::cout << returnVal << "\n";
		break;
		default:
		std::cout << "invalid search range\n";
		break;

	}
	
	return returnVal;

}


void ClientHandler::handleCommand()
{
	if (_kbhit())
	{
		// Todo -> unclear if this loop need thread
		Gets(buffer, sizeof(buffer));
		CommandCode cc = getCommand(buffer);
		switch (cc)
		{
		case quit:
			std::cout << "quit app \n";
			exit(69);
			break;
		case disconnect:
			std::cout << "disconnecting from server \n";
			m_client->CloseConnection(m_client->GetSystemAddressFromIndex(0), true);
			std::cout << "disconnected \n";
			break;
		case ping:
			if (m_client->GetSystemAddressFromIndex(0) != RakNet::UNASSIGNED_SYSTEM_ADDRESS)
			{
				//m_client->Ping(m_client->GetSystemAddressFromIndex(0));
				m_client->Ping(m_ip.c_str(),m_serverPort,false);
			}
			else
			{
				std::cout << " can't ping \n";
			}
			break;
		case reconnect:
		{
			bool b = m_client->Connect(m_ip.c_str(), m_serverPort, m_password.c_str(), m_password.size()) == RakNet::CONNECTION_ATTEMPT_STARTED;
			if (b)
			{
				std::cout << "reconnecting ... \n";
			}
			else
			{
				std::cout << "unable to connect ... \n";
				exit(33);
			}
		}
			break;
		case request_login:
			{
				memset(buffer2,0,2048);
				strncpy(buffer2,"|LOGIN_REQUEST|" ,15);// why 0xF69420 ? ask Hoang pls
				//strncat(buffer2,"\0",1);
				//strncpy(buffer2,"davai::::",10);

				//strncpy(buffer2,m_client->GetMyBoundAddress().ToString(true),sizeof(buffer2));
			
				// TODO add TIME_STAMP for security reason	
				std::string holder(buffer);
				std::string holder1 = getLoginInfo(holder,1);
				std::string holder2 = getLoginInfo(holder,2);
				strncat(buffer2,holder1.c_str(),holder1.size());
				strncat(buffer2,"|_ENCRYPED_METHOD_|",19);
				strncat(buffer2,holder2.c_str(),holder2.size());
				strncat(buffer2,"|REQUEST_END|",13);
				m_client->Send(buffer2, (int) strlen(buffer2) + 1, HIGH_PRIORITY, RELIABLE_ORDERED, 0,RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);			
			}
			break;
		case request_download:
			{
				memset(buffer2,0,2048);
				strncpy(buffer2, "|DOWNLOAD_REQUEST|", 18);
				std::string holder(buffer);
				std::string holder1 = getLoginInfo(holder,1);
				std::string holder2 = getLoginInfo(holder,2);
				strncat(buffer2, holder1.c_str(), holder1.size());
				strncat(buffer2, "|_GENERATED_ID_|",16); 
				strncat(buffer2, holder2.c_str(), holder2.size());
				strncat(buffer2, "|REQUEST_END|",13);
				m_client->Send(buffer2, (int) strlen(buffer2) + 1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
			
			}
			break;
		case undefined:
			strncpy(buffer2,m_client->GetMyBoundAddress().ToString(true),sizeof(buffer2));
			strncat(buffer2, " :", 2);
			strncat(buffer2, buffer, sizeof(buffer));
			m_client->Send(buffer2, (int) strlen(buffer2) + 1, HIGH_PRIORITY, RELIABLE_ORDERED, 0,RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
			memset(buffer,0,2048);
			break;
		default:
			break;
		}

	}
}
void ClientHandler::listen()
{
	unsigned char packetIdentifier;
	for (m_packet = m_client->Receive(); m_packet; m_client->DeallocatePacket(m_packet), m_packet = m_client->Receive())
	{
		packetIdentifier = GetPacketIdentifier(m_packet);
		switch (packetIdentifier)
		{
		case ID_DISCONNECTION_NOTIFICATION:
			std::cout << "ID_DISCONNECTION_NOTIFICATION \n";
			break;

		case ID_REMOTE_NEW_INCOMING_CONNECTION: 
			std::cout << "ID_REMOTE_NEW_INCOMING_CONNECTION\n";
			break;
		case ID_ALREADY_CONNECTED:
			printf("ID_ALREADY_CONNECTED with guid %" PRINTF_64_BIT_MODIFIER "u\n", m_packet->guid);
			break;
		case ID_INCOMPATIBLE_PROTOCOL_VERSION : 
			std::cout << "ID_INCOMPATIBLE_PROTOCOL_VERSION \n";
			break;
		case ID_REMOTE_DISCONNECTION_NOTIFICATION :
			std::cout << "ID_REMOTE_DISCONNECTION_NOTIFICATION \n";
			break;
		case ID_REMOTE_CONNECTION_LOST : 
			std::cout << "ID_REMOTE_CONNECTION_LOST \n";
			break;
		case ID_CONNECTION_BANNED : 
			std::cout << "ID_CONNECTION_BANNED \n";
			break;
		case ID_CONNECTION_ATTEMPT_FAILED : 
			std::cout << "ID_CONNECTION_ATTEMPT_FAILED \n";
			break;
		case ID_NO_FREE_INCOMING_CONNECTIONS : 
			std::cout << "The server is full \n";
			break;
		case ID_CONNECTED_PING :
		case ID_UNCONNECTED_PING :
			std::cout << "ping from " << m_packet->systemAddress.ToString(true) << "\n";
			break;
		case ID_CONNECTION_REQUEST_ACCEPTED:
			std::cout << "ID_CONNECTION_REQUEST_ACCEPTED to " << m_packet->systemAddress.ToString(true) << " with GUID " << m_packet->guid.ToString() << "\n";
			std::cout << "my external address is " << m_client->GetExternalID(m_packet->systemAddress).ToString(true) << "\n";
			break;
		
		default:
			std::cout << m_packet->data << "\n";
			std::string mainStr = std::string(m_packet->data);
			std::string DLRequest = mainStr.substr(0,19);
			if(DLRequest == "|DOWNLOAD_RESPONSE|")
			{
				std::cout << "request download get\n";
				m_downloadHandler.download();
				m_downloadHandler.downloading();
				
			}
			else
			{
			//	std::cout << "invalid cut \n";
			//	std::cout << DLRequest << "\n";
			}
			break;
		}
	}
}

void ClientHandler::update()
{
	while (isRunning)
	{
		//RakSleep(30);
		handleCommand();
		listen();
		m_downloadHandler.downloading();
		m_downloadHandler.update();
	}
	m_client->Shutdown(300);

	RakNet::RakPeerInterface::DestroyInstance(m_client);

}


void ClientHandler::connect(const std::string& ip, unsigned int serverPort)
{
	
	m_serverPort = serverPort;
	m_ip = ip;
	std::cout << "connect to " << m_ip << " with port " << m_serverPort << "\n";
	RakNet::SocketDescriptor socketDescriptor(m_clientPort,0);
	socketDescriptor.socketFamily = AF_INET;
	m_client->Startup(8, &socketDescriptor, 1);
	m_client->SetOccasionalPing(true);
	RakNet::ConnectionAttemptResult car = m_client->Connect(m_ip.c_str(), m_serverPort, m_password.c_str(), m_password.size());
	
	std::cout << "connect status " << car << "\n";
	RakAssert(car == RakNet::CONNECTION_ATTEMPT_STARTED);

	std::cout << " The IP is : \n";
	
	for (unsigned int i = 0; i < m_client->GetNumberOfAddresses(); i++)
	{
		std::cout << i << " : " << m_client->GetLocalIP(i) << " \n";
	}
	std::cout << " GUID is " << m_client->GetGuidFromSystemAddress(RakNet::UNASSIGNED_SYSTEM_ADDRESS).ToString() << "\n";

	showCommand();

}

unsigned char ClientHandler::GetPacketIdentifier(RakNet::Packet* p)
{
	if (!p)
	{
		return 255;
	}
	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
	{
		RakAssert(p->length > sizeof(RakNet::MessageID) + sizeof(RakNet::Time));
		return (unsigned char)p->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time)];

	}
	else
	{
		return (unsigned char)p->data[0];
	}
}
