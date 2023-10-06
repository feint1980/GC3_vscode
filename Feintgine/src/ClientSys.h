#ifndef _CLIENTSYS_H_
#define _CLIENTSYS_H_


/*
#ifdef _WIN32

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>

#elif __linux__ 

#include <sys/socket.h>

#endif
*/



#ifdef _WIN32
  /* See http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32 */
#pragma comment(lib,"ws2_32.lib")
  #ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x0501  /* Windows XP. */
  #endif
  #include <winsock2.h>
  #include <Ws2tcpip.h>
#elif __linux__
  /* Assume that any non-Windows platform uses POSIX-style sockets instead. */
  #include <sys/socket.h>
  #include <arpa/inet.h>
  #include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
  #include <unistd.h> /* Needed for close() */
#endif


#include <iostream>
#include <string>


class ClientSys
{
public:
	ClientSys();
	~ClientSys();

	static ClientSys *Instance()
	{
		if (p_Instance == 0)
		{
			p_Instance = new ClientSys;
			return p_Instance;
		}
		return p_Instance;
	}

	bool init(const char * ip, unsigned int port);
	bool connectTo();

	
	void sendUDP();

	int getSock() const { return Connection; }
	bool is_Connected() const { return isConnected; }
	void update();
	
	void disconenct();

	void shutdownClient();
private:
	static ClientSys *p_Instance;
#ifdef _WIN32
	WSAData wsaData;

#elif __linux__ 
	int wsaData;
#endif
	sockaddr_in addr;
	int sizeofaddr;
	int Connection;
	u_long iMode = 1;
	bool isConnected = false;
};

#endif

