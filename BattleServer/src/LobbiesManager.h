
#ifndef LOBBIESMANAGER_H
#define LOBBIESMANAGER_H

#include "Lobby.h"
#include <unordered_map>
#include <vector>
#include <memory>
#include <random>
#include "ThreadPool.h"
#include "BattleClient.h"


class LobbiesManager
{
public:
    LobbiesManager() {}

    ~LobbiesManager() {

        for (size_t i = 0; i < m_lobbies.size(); i++)
        {
            // delete m_lobbies[i];
            m_lobbies.erase(m_lobbies.begin() + i);
        }
        
        for (auto it = m_lobbiesMap.begin(); it != m_lobbiesMap.end(); it++)
        {
            m_lobbiesMap.erase(it);
        }

    }

    uint64_t addLobby(const std::string & name, const std::string & password)
    {

        uint64_t id = generateRoomId();
        std::cout << "generated id " << id << "\n";
        m_lobbies.emplace_back(std::make_unique<Lobby>(id, name, password)); // Lobby(id, name, password));
        m_lobbiesMap[id] = m_lobbies.size() - 1;

        return id;
    }

    void removeLobby(uint64_t id)
    {
        size_t index = m_lobbiesMap[id];
        size_t lastIndex = m_lobbies.size() - 1;

        std::swap(m_lobbies[index], m_lobbies[lastIndex]);

        m_lobbiesMap[m_lobbies[index]->getId()] = index;

        m_lobbies.pop_back();
        m_lobbiesMap.erase(id);
    }

    bool joinLobby(uint64_t lobbyID, RakNet::SystemAddress * address, const std::string &accountID , const std::string & guid);

    void init(int maxLobbies);
    
    Lobby * getLobby(uint64_t id);

    void update(float deltaTime);

    void createDummyLobbies();

    bool lobbiesAvailable() { return m_lobbies.size() >= m_maxLobbies; }

private:

    uint64_t generateRoomId() 
    {
        static thread_local std::mt19937_64 rng(std::random_device{}());
        std::uniform_int_distribution<uint64_t> dist;
        return dist(rng);
    }

    ThreadPool m_threadPool;

    int m_maxLobbies = 50;

    std::unordered_map<uint64_t, size_t> m_lobbiesMap;
    // std::vector<Lobby> m_lobbies;
    std::vector<std::unique_ptr<Lobby>> m_lobbies;


    std::unordered_map<std::string, std::unique_ptr<BattleClient>> m_clientsMap;
    // std::vector<std::unique_ptr<BattleClient>> m_clientsPtr;

    // std::pai
    

} ;

#endif // LOBBIESMANAGER_H