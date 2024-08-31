#include <RakNet/MessageIdentifiers.h>

#include <RakNet/RakPeerInterface.h>
#include <RakNet/RakNetStatistics.h>
#include <RakNet/RakNetTypes.h>
#include <RakNet/BitStream.h>
#include <RakNet/RakSleep.h>
#include <RakNet/PacketLogger.h>
#include <assert.h>
#include <cstdio>
#include <cstring>
#include <stdlib.h>

#include <stdio.h>
#include <string.h>


#include <iostream>
int wmain(int argc, char const *argv[])
{
    RakNet::RakPeerInterface *server=RakNet::RakPeerInterface::GetInstance();
    std::cout<< "Hello World!" << std::endl;
    return 0;
}
