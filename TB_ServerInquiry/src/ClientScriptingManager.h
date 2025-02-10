#ifndef CLIENTSCRIPTINGMANAGER_H
#define CLIENTSCRIPTINGMANAGER_H

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
#include "NetworkPacket.h"
#include "DataBaseHandler.h"

#include "LuaManager.h"

#include <iostream>

class ClientScriptingManager
{
public:
    ClientScriptingManager();
    ~ClientScriptingManager();

    void init(RakNet::RakPeerInterface * client);

    ServerResponseCode handleServerResponse(RakNet::Packet *p);

    void sendData(const std::string & data);

    void update(float deltaTime);

    void handleKeyboard(const std::string & data);

    private:
    RakNet::RakPeerInterface * m_client;

    lua_State * m_script;

}




#endif // CLIENTSCRIPTINGMANAGER_H