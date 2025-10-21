
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
    BattleMain server;
    server.init("DavaiMachi", 1123, 100);

    server.run();

	return 0;
}