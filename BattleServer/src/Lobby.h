
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


class PlayerPair {

    public: 

    PlayerPair() { m_players[0] = m_players[1] = RakNet::UNASSIGNED_SYSTEM_ADDRESS; 
    m_host = nullptr; m_playerCount = 0; }

    bool addPlayer(RakNet::SystemAddress address) {
        if (m_playerCount < 2) 
        {
            m_players[m_playerCount] = address;
            m_playerCount++;

            return true;
        }

        return false;
    }

    bool isFull() { return m_playerCount == 2; }

    bool removePlayer(RakNet::SystemAddress address) {
        if (m_players[0] == address || m_players[1] == address) 
        {
            m_players[0] = m_players[1] = RakNet::UNASSIGNED_SYSTEM_ADDRESS;
            m_playerCount = 0;
            return true;
        }
        return false;
    }

    int getPlayerCount() { return m_playerCount; }

    private:

    RakNet::SystemAddress m_players[2];

    RakNet::SystemAddress * m_host = nullptr;

    int m_playerCount = 0;
    
};

enum LobbyState {
    LOBBY_STATE_OPEN,
    LOBBY_STATE_CLOSED,
    LOBBY_STATE_IN_GAME,
    LOBBY_STATE_EXPIRING,
};

class Lobby {
public:
    Lobby (uint64_t id, const std::string & name, const std::string & password) : m_name(name), m_password(password), m_id(id) 
    {
        m_state = LOBBY_STATE_OPEN;
    }
    ~Lobby() 
    {
        
    }

    std::string getInfo() const;

    bool isRequiredPassword() const { return !m_password.empty(); }

    void update(float deltaTime);
    
    uint64_t getId() { return m_id; }

    LobbyState getState() const { return m_state; }

    bool addPlayer(RakNet::SystemAddress address);
private:

    uint64_t m_id = 0;
    std::string m_name;
    std::string m_password;

    LobbyState m_state = LOBBY_STATE_CLOSED;

    PlayerPair m_playerPair;

};

