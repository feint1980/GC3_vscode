
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


struct InGamePlayer {
    RakNet::SystemAddress * m_addr;
};

class PlayerPair {
    InGamePlayer m_players[2];
};

class Lobby {
public:
    Lobby (const std::string & name, const std::string & password) : m_name(name), m_password(password) {}
    ~Lobby() {}


private:
    std::string m_name;
    std::string m_password;
};
