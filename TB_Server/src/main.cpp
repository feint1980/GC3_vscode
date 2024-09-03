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

#include "ServerMain.h"

#include <iostream>
    

int wmain(int argc, char const *argv[])
{
    ServerMain server;
    server.init("DavaiMachi", 1123, 10);

    server.run();

	return 0;
}

// Copied from Multiplayer.cpp
// If the first byte is ID_TIMESTAMP, then we want the 5th byte
// Otherwise we want the 1st byte
