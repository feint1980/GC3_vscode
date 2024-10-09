#pragma

#include "MessageIdentifiers.h"

#include "RakPeerInterface.h"
#include "RakNetStatistics.h"
#include "RakNetTypes.h"
#include "BitStream.h"
#include "RakSleep.h"
#include "PacketLogger.h"
#include <assert.h>
#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include "Kbhit.h"
#include <stdio.h>
#include <string.h>
#include <string>
#include "Gets.h"
#include <iostream>

#include "DataBaseHandler.h"
#include "FileTransferHost.h"
#include <vector>

enum RequestCode
{
    login,
    invalid
};

class NetworkPacket
{

public:
    NetworkPacket();
    ~NetworkPacket();
    RequestCode getSpecialRequestCode(RakNet::Packet *p);
	


}