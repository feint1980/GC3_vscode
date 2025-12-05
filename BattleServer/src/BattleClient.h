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


#include <string>
#include <iostream>

#include <vector>

class BattleClient
{
public : 
    BattleClient()
    {

    }
    ~BattleClient()
    {

    }

    void init(const std::string& guid, const std::string& name, const RakNet::SystemAddress& address);

    const std::string& getGuid() const { return m_guid; }
    const std::string& getName() const { return m_name; }
    const RakNet::SystemAddress& getAddress() const { return m_address; }

private: 
    RakNet::SystemAddress m_address;
    std::string m_guid = "";
    std::string m_name = "";
    uint64_t m_roomID = 0;


};