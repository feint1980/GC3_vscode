#include "ClientSocket.h"

/*


// Static constants
const std::string  ClientSocket::SERVER_NOT_FULL           = "OK";        // Server's response when there are free spots a client can join
const std::string  ClientSocket::SERVER_FULL               = "FULL";      // Server's response when there are no free spots, so a client cannot join
const std::string  ClientSocket::SHUTDOWN_SIGNAL           = "/shutdown"; // What you type to shutdown the server
const std::string  ClientSocket::QUIT_SIGNAL               = "/quit";     // What you type to shutdown the client
const unsigned int ClientSocket::CONNECTION_TIMEOUT_PERIOD = 5000;        // 5 second connection timeout
const unsigned int ClientSocket::SOCKET_SET_POLL_PERIOD    = 1;          // 50ms, so poll 500 times/second

// ClientSocket constructor

//void setData(TCP_msg_Type)

ClientSocket *ClientSocket::p_Instance = 0;

void ClientSocket::init(string theServerAddress, unsigned int theServerPort, unsigned int theBufferSize)
{
	debug          = true;      // Flag to control whether to output debug info
	shutdownClient = false;     // Flag to control whether it's time to shut down the client

	// The host name of the server.
	// This can be either a dot-quad like 127.0.0.1 or a hostname like "localhost" or "foo.com" etc.
	serverHostname = theServerAddress;

	serverPort = theServerPort; // The port on the server to connect to
	bufferSize = theBufferSize; // The maximum message size

	inputLength = 0;

	try
	{
		pBuffer = new char[bufferSize]; // Create the transmission buffer character array

		// Create a socket set big enough to hold the server socket and our own client socket
		socketSet = SDLNet_AllocSocketSet(2);

		// If we couldn't create the socket set then throw an exception
		if (socketSet == NULL)
		{
			string msg = "Failed to allocate the socket set in ClientSocket constructor: ";
			msg += SDLNet_GetError();

			SocketException e(msg);
			throw e;
		}
	}
	catch (SocketException e)
	{
		// Re-throw the exception to be dealt with appropriately elsewhere
		throw e;
	}

} // End of ClientSocket constructor


ClientSocket::ClientSocket()
{

}

// ClientSocket destructor
ClientSocket::~ClientSocket()
{
	// Close our server and client sockets
	SDLNet_TCP_Close(serverSocket);
	SDLNet_TCP_Close(clientSocket);
	

	// Free our socket set (i.e. all the clients in our socket set)
	SDLNet_FreeSocketSet(socketSet);

	// Release any properties on the heap
	delete pBuffer;
}

bool ClientSocket::connectToServer()
{
	// Try to resolve the hostname to an IP address, if it's already an IP address then that's fine
	// If successful, this places the connection details in the serverIP object.
	int hostResolved = SDLNet_ResolveHost(&serverIP, serverHostname.c_str(), serverPort);

	// If we couldn't resolve the hostname then throw an error
	if (hostResolved == -1)
	{
		string msg = "Error: Failed to resolve the server hostname to an IP address.";
		std::cout << msg << "\n";
		return false;
// 		SocketException e(msg);
// 		throw e;
		
	}
	else // otherwise if we successfully resolved the hostname...
	{
		// ...get our IP address in dot-quad format by breaking up the 32-bit unsigned host address
		// and splitting it into an array of four 8-bit unsigned numbers...
		Uint8 * dotQuad = (Uint8*)&serverIP.host;

		dotQuadString  = toString( (unsigned short)dotQuad[0] );
		dotQuadString += ".";
		dotQuadString += toString( (unsigned short)dotQuad[1] );
		dotQuadString += ".";
		dotQuadString += toString( (unsigned short)dotQuad[2] );
		dotQuadString += ".";
		dotQuadString += toString( (unsigned short)dotQuad[3] );

		//... and then outputting them. Then read the last 16 bits of the serverIP object to get the port number
		if (debug)
		{
			cout << "Successfully resolved server to IP: " << dotQuadString;
			cout << ", will use port " << SDLNet_Read16(&serverIP.port) << endl;

			// Try to resolve the hostname from the IP address, just for kicks

			

			const char *pHostname;
			if (!(pHostname = SDLNet_ResolveIP(&serverIP)))
			{
				cout << "Failed to resolve the server IP to hostname: " << SDLNet_GetError() << endl;
				cout << "Attempting to continue as we have a (technically) valid IP address..." << endl;
				
			}
			else
			{
				serverHostname = toString(pHostname);
				cout << "Successfully resolved IP to hostname: " << serverHostname << endl;
				
			}
		}
	}

	// Try to open a connection between the client and the server - quit out if we can't connect
	clientSocket = SDLNet_TCP_Open(&serverIP);
	if (!clientSocket)
	{
		string msg = "Error: Failed to open connection to server: ";
		msg += SDLNet_GetError();

		std::cout << msg << "\n";

		return false;
		
	}
	else // If we successfully opened a connection then check for the server response to our connection
	{
		if (debug) { cout << "Connection okay, about to read connection status from the server..." << endl; }

		// Add our socket to the socket set for polling
		SDLNet_TCP_AddSocket(socketSet, clientSocket);

		// Wait for up to five seconds for a response from the server.
		// Note: If we don't check the socket set and WAIT for the response, we'll be checking before the
		// server can respond, and it'll look as if the server sent us nothing back!
		int activeSockets = SDLNet_CheckSockets(socketSet, ClientSocket::CONNECTION_TIMEOUT_PERIOD);

		if (debug)
		{
			cout << "There are " << activeSockets << " socket(s) with data on them at the moment." << endl;
		}

		// Check if we got a response from the server
		int gotServerResponse = SDLNet_SocketReady(clientSocket);

		if (gotServerResponse != 0)
		{
			// Read the message on the client socket
			int serverResponseByteCount = SDLNet_TCP_Recv(clientSocket, pBuffer, bufferSize);

			if (debug)
			{
				cout << "Message from server: " << pBuffer << "(" << serverResponseByteCount << " bytes)" << endl;
			}

			// Get the contents of the buffer as a string
			string bufferContents = pBuffer;

			// If we got the SERVER_NOT_FULL response from the server then we can join!
			if ( pBuffer == ClientSocket::SERVER_NOT_FULL )
			{
				if (debug) { cout << "Joining server now..." << endl; }
				return true;
			}
			else // Otherwise we must have got the SERVER_FULL response so we can't.
			{
				string msg = "Error: Server is full...";


				std::cout << msg << "\n";
				return false;
				
			}
		}
		else // If there's no activity on the client socket then we've failed to connect
		{
			string msg = "Error: No response from server: ";
			msg       += serverHostname;
			msg       += " at IP: ";
			msg       += dotQuadString;
			msg       += " on port ";
			msg       += serverIP.port;

			std::cout << msg << "\n";
			return false;
		}

	} // End of if we managed to open a connection to the server condition

	return true;
}


void ClientSocket::disconnect()
{
	SDLNet_TCP_Close(clientSocket);
}

// Function to check for any incoming messages
string ClientSocket::checkForIncomingMessages()
{


		string receivedMessage = "";



		// Define a string with a blank message


		// Poll for messages for a specified time (default: 10ms, so 100 times per second)
		int activeSockets = SDLNet_CheckSockets(socketSet, ClientSocket::SOCKET_SET_POLL_PERIOD);

		// This produces a LOT of debug output, so only uncomment if the code's really misbehaving...
		//if (debug) { cout << "There are " << activeSockets << " socket(s) with data on them at the moment." << endl; }

		if (activeSockets != 0)
		{
			// Check if we got a message from the server
			int gotMessage = SDLNet_SocketReady(clientSocket);

			if (gotMessage != 0)
			{

				char buffer[256];
				int serverResponseByteCount = SDLNet_TCP_Recv(clientSocket, buffer, sizeof(buffer));
				
			
				if (serverResponseByteCount < 0)
				{
					return "@SHUTDOWN";
				}
				if (serverResponseByteCount != 0)
				{
					//std::cout << " recv count " << serverResponseByteCount ;
					receivedMessage = std::string(buffer,serverResponseByteCount);
					


				//	receivedMessage
					
				}
			

			}
			if(gotMessage < 0)
			{
				receivedMessage = "@SHUTDOWN";
				
			}// End of if (gotMessage != 0) section

		} // End of if (activeSockets != 0) section
		return receivedMessage;
		// Return the message, whether the actually is a message, or whether it's blank
	

}

// Function do display a received message and then blank the message
void ClientSocket::displayMessage(string &receivedMessage)
{
	// Display the message and then...
	cout << endl << "Received: " << receivedMessage << endl;

	// Blank it! Because we pass a reference to a string into this function
	// it's the actual receivedMessage that's blanked and not just a copy
	receivedMessage = "";
}

// Function to display the prompt + any user input that hasn't been sent yet
void ClientSocket::displayPrompt()
{
	cout << "Write something >>> " << getCurrentUserInputContents();
	fflush(stdout);
}

// Function to get user input in a non-blocking manner
void ClientSocket::getUserInput()
{
	// If we've detected that the user has pressed a key..
	int status = getchar();

	//cout << "status is: " << status << endl;

	if (status != 0)
	{
		//cout << "key was pressed and status is" << status << endl;

		// Read what the keypress was
		char theChar = getchar();

		// Output the character to stdout
		cout << theChar;

		// Flush the character to the screen
		fflush(stdout);

		// If the key pressed wasn't return then add the character to our message string
		if ((int)theChar != 13)
		{
			//cout << "Got the character: " << theChar << " (which is number: " << int(theChar) << ")" << endl;

			// Add the character to our input string
			userInput += theChar;
		}
		else // Otherwise (if the user pressed enter) then send the message
		{
			//if (debug) { cout << "User pressed return - will attempt to send message..." << endl; }

			// Copy our user's string into our char array called "buffer"
			strcpy( pBuffer, userInput.c_str() );

			// Calculate the length of our input and then add 1 (for the terminating character) to get the total number of characters we need to send
			inputLength = strlen(pBuffer) + 1;

			// If we've got normal input then...


		} // End of message sending section

	} // End of if the user pressed a key test
}

// Function to return the contents of any user input (prior to it being sent)
// Used to keep what we've typed so far displayed at the prompt when receiving incoming messages
string ClientSocket::getCurrentUserInputContents()
{
	return userInput;
}


void ClientSocket::setMSG_Login(Login &l1, Login &l2)
{
	l2 = l1;
}


void ClientSocket::setMSG_Register(Register &r1, Register & r2)
{
	r2 = r1;
}


void ClientSocket::setMSG_Command(ClientCommand &c1, ClientCommand &c2)
{
	c2 = c1;
}


void ClientSocket::setMSG_PlayerState(PlayerState &s1, PlayerState &s2)
{
	s2 = s1;
}


void ClientSocket::setMSG_PlayerMSG(PlayerMSG &m1, PlayerMSG &m2)
{
	m2 = m1;
}

void ClientSocket::sendState(std::string t_name, int state, glm::vec2 pos)
{
// 	TCP_msg sendPack;
// 	sendPack.set_type(PLAYERSTATE);
// 	PlayerState playerstt;
// 
// 	playerstt.set_name(t_name);
// 	playerstt.set_action(state);
// 	playerstt.set_x_pos(pos.x);
// 	playerstt.set_y_pos(pos.y);
// 
// 	setMSG_PlayerState(playerstt, *sendPack.mutable_m_playerstate());
// 
// 	std::string data = sendPack.SerializeAsString();
// 
// 	SDLNet_TCP_Send(clientSocket, data.c_str(), data.size());

}

void ClientSocket::logIn(const std::string &id, const std::string &password)
{
	TCP_msg msg;
	msg.set_type(LOGIN);
	Login msg_log;

	msg_log.set_id(id);
	msg_log.set_password(password);

	//setData(log_msg, *msg.mutable_msg_log());
	//*msg.mutable_m_login() = msg_log;
	setMSG_Login(msg_log, *msg.mutable_m_login());
	std::string data = msg.SerializeAsString();

	
	SDLNet_TCP_Send(clientSocket, data.c_str(), data.size());

}


void ClientSocket::t_register(const std::string & id, const std::string & password)
{
	TCP_msg msg;
	msg.set_type(REGISTER);
	Register msg_reg;

	msg_reg.set_id(id);
	msg_reg.set_password(password);

	//setData(log_msg, *msg.mutable_msg_log());
	//*msg.mutable_m_login() = msg_log;
	setMSG_Register(msg_reg, *msg.mutable_m_register());
	std::string data = msg.SerializeAsString();

	SDLNet_TCP_Send(clientSocket, data.c_str(), data.size());
}


void ClientSocket::executeCommand(const std::string & command)
{

	std::cout << "execute " << command << "\n";
	TCP_msg msg;
	msg.set_type(CLIENT_COMMAND);
	ClientCommand msg_command;

	msg_command.set_command(command);

	setMSG_Command(msg_command, *msg.mutable_m_clientcommand());
	std::string data = msg.SerializeAsString();
	SDLNet_TCP_Send(clientSocket, data.c_str(), data.size());

}


void ClientSocket::chat(const std::string & name, const std::string & content)
{
	TCP_msg msg;
	msg.set_type(PLAYERMSG);
	PlayerMSG msg_content;
	msg_content.set_name(name);
	msg_content.set_msg(content);

	setMSG_PlayerMSG(msg_content,*msg.mutable_m_playermsg());
	std::string data = msg.SerializeAsString();
	

	SDLNet_TCP_Send(clientSocket, data.c_str(), data.size());


}

// Function to return the shutdownStatus, used by our main loop
bool ClientSocket::getShutdownStatus()
{
	return shutdownClient;
}
*/