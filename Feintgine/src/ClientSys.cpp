#include "ClientSys.h"

ClientSys *ClientSys::p_Instance = 0;

ClientSys::ClientSys()
{
}


ClientSys::~ClientSys()
{
}

bool ClientSys::init(const char * ip , unsigned int port)
{

#if defined WIN32
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //If WSAStartup returns anything other than 0, then that means an error has occured in the WinSock Startup.
	{
		return false;
	}
#endif

	sizeofaddr = sizeof(addr); //Need sizeofaddr for the connect function
	addr.sin_addr.s_addr = inet_addr(ip); //Address = localhost (this pc)
	addr.sin_port = htons(port); //Port = 1111
	addr.sin_family = AF_INET; //IPv4 Socket




	std::cout << " Connecting to " << ip << " with port " << port << "\n";
	Connection = socket(AF_INET, SOCK_STREAM, NULL); //Set Connection socket

// 	int iResult = ioctlsocket(Connection, FIONBIO, &iMode);
// 	if (iResult != NO_ERROR)
// 	{
// 		printf("ioctlsocket failed with error: %ld\n", iResult);
// 	}
// 	else
// 	{
// 		std::cout << " set non-blocking OK\n";
// 	}


	return true;
}

bool ClientSys::connectTo()
{

	

	if (connect(Connection, (sockaddr*)&addr, sizeofaddr) == 0)
	{
		//WSAGetLastError();

		isConnected = true;
		return true;
	}

	
	return false;

}





void ClientSys::sendUDP()
{

}



void ClientSys::update()
{
	

	//std::cout << "recevie " << foo << " bytes \n";
	//std::cout << "MOTD:" << log << std::endl;
}

void ClientSys::disconenct()
{
#ifdef _WIN32

	closesocket(Connection);
#elif __linux__ 
	close(Connection);
#endif

}

void ClientSys::shutdownClient()
{
	isConnected = false;
}
