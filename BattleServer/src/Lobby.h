
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
#include "BattleClient.h"
#include "BattleInstance.h"

class PlayerPair {

    public: 

    PlayerPair() {
    m_playerCount = 0; }

    bool addPlayer(const std::string& guid, const std::string& name,const RakNet::SystemAddress & address) {
        if (m_playerCount < 2) 
        {
            BattleClient client = BattleClient();
            client.init(guid, name, address);
            m_players[m_playerCount] = client;
            m_playersMap[guid] = m_playerCount;
            m_playerCount++;

            return true;
        }
        return false;
    }

    bool isFull() { return m_playerCount == 2; }

    bool removePlayer(const std::string & guid) {
        if(m_playersMap.find(guid) != m_playersMap.end())
        {
            int index = m_playersMap[guid];
            m_players[index] = BattleClient();
            m_playersMap.erase(guid);
            m_playerCount--;
            return true;
        }
        return false;
    }


    int getPlayerCount() { return m_playerCount; }

    private:

    BattleClient m_players[2];

    std::unordered_map<std::string , int> m_playersMap;

    int m_playerCount = 0;
    
};



enum LobbyState {
    LOBBY_STATE_OPEN,
    LOBBY_STATE_CLOSED,
    LOBBY_STATE_IN_GAME,
    LOBBY_STATE_EXPIRING,
    LOBBY_STATE_LOCK_IN,

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

    void destroyLobby();

    std::string getInfo() const;

    bool isRequiredPassword() const { return !m_password.empty(); }

    void update(float deltaTime);
    
    uint64_t getId() { return m_id; }

    LobbyState getState() const { return m_state; }

    bool addPlayer(const std::string& guid, const std::string& name,const RakNet::SystemAddress & address);
    
    void setLobbyState(LobbyState state);

private:

    uint64_t m_id = 0;
    std::string m_name;
    std::string m_password;

    LobbyState m_state = LOBBY_STATE_CLOSED;

    PlayerPair m_playerPair;

    BattleInstance m_battleInstance;
};

