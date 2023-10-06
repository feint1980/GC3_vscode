/*
#ifndef SOCKET_H
#define SOCKET_H

#include <iostream>
#include <string>
#include <sstream>

#include <SDL2/SDL_net.h>         // Include SDL_net, which includes SDL.h for us
#include "serverData.pb.h"
#include "SocketException.h" // Include our custom exception header which defines an inline class
#include <glm/glm.hpp>
#define TCP_NODELAY 1

using std::string;
using std::cout;
using std::cerr;
using std::endl;


const int LOGIN = 1;
const int REGISTER = 2;
const int PLAYERMSG = 3;
const int CLIENT_COMMAND = 4;
const int T_ERROR = 5;
const int LOGLIST = 6;
const int LOGIN_INFO = 7;


// Type of Player State
const int MOVELEFT = 1;
const int MOVERIGHT = 2;
const int MOVEUP = 4;
const int MOVEDOWN = 8;
const int STAHP = 16;
//





class ClientSocket
{
	private:
		bool debug;                 // Flag to control whether the ServerSocket should display debug info

		unsigned int serverPort;    // The port of the server to connect to
		unsigned int bufferSize;    // The size of our message buffer

		string    serverHostname;   // The host name of the server (i.e. "localhost", "www.foo.com" etc.
		IPaddress serverIP;         // The IP address of the server to connect to (NOT in dot-quad format)
		string    dotQuadString;    // The IP address of the server to connect to as a dot-quad (i.e. 127.0.0.1)
		TCPsocket serverSocket;     // The server socket
		TCPsocket clientSocket;     // Our own client socket

		char   *pBuffer;            // A pointer to (what will be) an array of characters used to store the messages we send and receive
		string  userInput;          // User input string
		int     inputLength;        // The length of our userInput in characters

		SDLNet_SocketSet socketSet; // Our entire set of sockets (i.e. just the server socket and our client socket)

		bool shutdownClient = false;        // Flag to control when to shut down the client


		static ClientSocket * p_Instance;
		
	public:
		static const string       SERVER_NOT_FULL;
		static const string       SERVER_FULL;
		static const string       SHUTDOWN_SIGNAL;
		static const string       QUIT_SIGNAL;
		static const unsigned int CONNECTION_TIMEOUT_PERIOD;
		static const unsigned int SOCKET_SET_POLL_PERIOD;

		//ClientSocket(string theServerAddress, unsigned int theServerPort, unsigned int theBufferSize);

		ClientSocket();

		void init(string theServerAddress, unsigned int theServerPort, unsigned int theBufferSize);

		~ClientSocket();

		static ClientSocket *Instance()
		{
			if (p_Instance == 0)
			{
				p_Instance = new ClientSocket;
				return p_Instance;
			}
			return p_Instance;
		}


		TCPsocket getSocket() const { return clientSocket; }
		// Function to poll for clients connecting
		bool connectToServer();

		void disconnect();

		// Function to check the server for incoming messages
		string checkForIncomingMessages();

		// Function to display a received message
		void displayMessage(string &receivedMessage);

		// Function to send a message to the server
		//void sendOutgoingMessage();

		// Function display the prompt + any input that hasn't been sent yet
		void displayPrompt();

		// Function to get keypresses in a non-blocking manner
		void getUserInput();

		// Function to get the current contents of our outgoing message
		string getCurrentUserInputContents();

		//

		void setMSG_Login(Login &l1, Login &l2);

		void setMSG_Register(Register &r1, Register & r2);

		void setMSG_Command(ClientCommand &c1, ClientCommand &c2);

		void setMSG_PlayerState(PlayerState &s1, PlayerState &s2);

		void setMSG_PlayerMSG(PlayerMSG &m1, PlayerMSG &m2);

		//

		void sendState(std::string t_name , int t_state, glm::vec2 pos);

		void logIn(const std::string &id, const std::string &password);

		void t_register(const std::string & id, const std::string & password);

		void executeCommand(const std::string & command);

		void chat(const std::string & name, const std::string & content);


		// Function to return the shutdown status, used to control when to terminate
		bool getShutdownStatus();
};

// Template function to convert most anything to a string
template<class T>
std::string toString(const T& t)
{
	std::ostringstream stream;
	stream << t;
	return stream.str();
}

#endif
*/