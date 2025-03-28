#pragma once

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


enum PacketCode
{
    
    QUIT = 22,
    STATS,
    PING,
    PINGIP,
    KICK,
    BAN,
    LIST,
    BC,
    GETLASTPING,
    CONNECT,
    DISCONNECT,
    STARTUP, // 
    SHUTDOWN, // 
    LOGIN,
    REGISTER,
    REQUEST_KEY,
    USERDATA = 65,
    INVALID = 322,
    UNKNOWN = 792

};

enum ClientRequestCode
{
    Login = 12,
    Register = 13,
    RequestKey = 193,
    Client_Invalid = 277

};

enum ServerResponseCode
{
    Login_OK = 22,
    Login_Fail = 23,
    Register_OK = 33,
    Register_Fail = 34,
    Server_Invalid = 277
    
};


//PacketCode getSpecialRequestCode(RakNet::Packet *p);

unsigned char GetPacketIdentifier(RakNet::Packet *p);

std::string combine2Package(const std::string & type,const std::string & id, const std::string & pw);

std::string combine3Package(const std::string & type,const std::string & id, const std::string & pw, const std::string & key);


