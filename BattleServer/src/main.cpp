
#include <RakNet/MessageIdentifiers.h>

#include <RakNet/RakPeerInterface.h>
#include <RakNet/RakNetStatistics.h>
#include <RakNet/RakNetTypes.h>
#include <RakNet/BitStream.h>
#include <RakNet/RakSleep.h>
#include <RakNet/PacketLogger.h>
#include <RakNet/Gets.h>
#include <RakNet/Kbhit.h>
#include <assert.h>
#include <cstdio>
#include <cstring>
#include <stdlib.h>

#include <stdio.h>
#include <string.h>
//#include "Gets.h"

#include "BattleMain.h"

#include <iostream>
    

int wmain(int argc, char const *argv[])
{
    std::cout << "Battle Server Start ...\n";
    int index = 1;
    std::string ip = "127.0.0.1";
    if(argc > 3)
    {
        index = atoi(argv[1]);
        ip = argv[2];
    }


    BattleMain server;
    std::cout << "Davai \n";
    server.init("FFX2","DavaiMachi", 1123 + index, 100,ip);

    server.run();

	return 0;
}