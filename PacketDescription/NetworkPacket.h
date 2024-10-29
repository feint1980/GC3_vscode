#pragma

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

#include <string>
#include <vector>
#include <string.h>
#ifdef _WIN32
#include <RakNet/WindowsIncludes.h>
#else 
#include <unistd.h>
#endif

enum RequestCode
{
    login,
    invalid
};
RequestCode getSpecialRequestCode(RakNet::Packet *p);


