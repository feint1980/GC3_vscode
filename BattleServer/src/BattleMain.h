#ifndef BATTLEMAIN_H
#define BATTLEMAIN_H

#include <RakNet/MessageIdentifiers.h>
//#pragma pack(push, 1)
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
#include "NetworkPacket.h"
#include <F_Cryptor.h>
#include <F_Cryptor_sodium.h>
#include "DataBaseHandler.h"
#include <sstream>
#include <iomanip>
#include <queue>
#include "LuaManager.h"
#include "ClientEPHandler.h"

#include <iostream>
#include <bcrypt.h>
#include "CharacterDes.h"
#include "SkillDesc.h"
#include "CharacterManager.h"
#include <thread>


class BattleMain
{
public:
    BattleMain();
    ~BattleMain();
    void init(const std::string & password, int port, unsigned int serverSize,const std::string & mainServerIP);

    void run();

    void update(float deltaTime);

private:

    RakNet::RakPeerInterface * m_server = nullptr;
    RakNet::SocketDescriptor m_socketDescriptor[2];
    RakNet::RakNetStatistics * m_statistics = nullptr;

    lua_State * m_script = nullptr;
    std::string m_password;
    std::string m_mainServerIP;
    int m_port = 0;
    int m_connectionSize = 0;

    bool m_serverOn = false;

};




#endif