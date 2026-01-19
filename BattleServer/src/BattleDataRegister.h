
#ifndef BATTLEDATAREGISTER_H
#define BATTLEDATAREGISTER_H
#include <string>
#include <RakNet/MessageIdentifiers.h>
#include <RakNet/RakPeerInterface.h>
#include <RakNet/RakNetStatistics.h>
#include <RakNet/RakNetTypes.h>
#include <RakNet/BitStream.h>
#include <RakNet/RakSleep.h>
#include <RakNet/PacketLogger.h>
#include <RakNet/Gets.h>
#include <RakNet/Kbhit.h>
#include <RakNet/RakNetTime.h>
#include <RakNet/RakMemoryOverride.h>
#include <RakNet/GetTime.h>
#include <assert.h>
#include <cstdio>
#include <cstring>
#include <stdlib.h>

#include <unordered_map>
#include <iostream>

struct ClientOnlineSession 
{
    std::string guid ;
    std::string name ;
    RakNet::SystemAddress address;

    ClientOnlineSession() 
    {
        guid = "";
        name = "";
        address = RakNet::UNASSIGNED_SYSTEM_ADDRESS;
    }

    ClientOnlineSession(const std::string & t_guid, const std::string & t_name, RakNet::SystemAddress * t_address) {
        guid = t_guid;
        name = t_name;
        address = *t_address;
    }

    ~ClientOnlineSession() 
    {

    }
};

class BattleDataRegister
{

public:
    static BattleDataRegister * getInstance() 
    {
        if (m_instance == nullptr)
        {
            m_instance = new BattleDataRegister();
        }
        return m_instance;
    
    }

    bool registerWhiteListClient_ByGUID(const std::string & guid, const std::string & id);

    bool removeWhiteListClientID_ByGUID(const std::string & guid);

    bool removeWhiteListClientID_ByID(const std::string & id);


    bool addClientOnlineSession(const std::string & guid, const  std::string & id, RakNet::SystemAddress * address);

    ClientOnlineSession * getClientOnlineSessionByGUID(const std::string & guid);

    ClientOnlineSession * getClientOnlineSessionByID(const std::string & id);

    std::string getWhiteListClientIDByGUID(const std::string & guid)
    {
        if (m_whiteListClient_GUID_2_ID.find(guid) != m_whiteListClient_GUID_2_ID.end())
        {
            return m_whiteListClient_GUID_2_ID[guid];
        }
        return "";
    }



private:
    static BattleDataRegister* m_instance;

    std::unordered_map<std::string , ClientOnlineSession> m_onlineSessionsGUIDTable;
    std::unordered_map<std::string , ClientOnlineSession> m_onlineSessionsIDTable;

    std::unordered_map<std::string , std::string> m_whiteListClient_GUID_2_ID;
    std::unordered_map<std::string , std::string> m_whiteListClient_ID_2_GUID;
    

};


#endif