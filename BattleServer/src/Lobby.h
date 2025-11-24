
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

struct InGamePlayer {
    RakNet::SystemAddress * m_addr;
};

class PlayerPair {
    InGamePlayer m_players[2];
};

class Lobby {
public:
    Lobby (uint64_t id, const std::string & name, const std::string & password) : m_name(name), m_password(password), m_id(id) 
    {

    }
    ~Lobby() 
    {

    }

    std::string getInfo() const;
    
    void update(float deltaTime);
    
    uint64_t getId() { return m_id; }
private:

    uint64_t m_id = 0;
    std::string m_name;
    std::string m_password;
};
