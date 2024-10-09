#include "ClientHandler.h"


int main()
{
	ClientHandler ch;
	std::cout << "client start up \n";
	std::cout << "input the port for the client \n";
	int port;
	std::cin >> port;
	ch.init(port);
	//std::cin.get();
	ch.connect("127.0.0.1", 19090);
	ch.update();

	return 0;
}
