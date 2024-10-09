#include <stdio.h>
//#include <sqlite3.h>
#include "ServerHandler.h"

int main(int argc, char* argv[])
{

	ServerHandler handler;
	handler.init(19090,"Studio-WaVN", 1000, 10);
	handler.update();	

	return 0;
}


