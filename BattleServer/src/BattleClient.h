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

    void init(const std::string& guid, const std::string& id, const RakNet::SystemAddress & address);

    const std::string& getGUID() const { return m_guid; }
    const std::string& getID() const { return m_id; }
    RakNet::SystemAddress getAddress() const { return m_address; }

    

private: 
    RakNet::SystemAddress m_address = RakNet::UNASSIGNED_SYSTEM_ADDRESS;
    std::string m_guid = "";
    std::string m_id = "";
    uint64_t m_roomID = 0;

};