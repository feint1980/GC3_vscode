#include "LobbiesManager.h"

static std::mutex t_mutex;


void LobbiesManager::init(int maxLobbies)
{
    m_maxLobbies = maxLobbies;
    m_lobbies.reserve(m_maxLobbies);

    std::cout << "Thread pool workers : " << m_threadPool.getNumThreads() << "\n";
    // createDummyLobbies();
}

Lobby * LobbiesManager::getLobby(uint64_t id)
{
    auto it = m_lobbiesMap.find(id);
    if (it != m_lobbiesMap.end())
    {
        return m_lobbies[it->second].get();
    }
    return nullptr;
}

void LobbiesManager::createDummyLobbies()
{
    for (int i = 0; i < 10; i++)
    {
        addLobby("Lobby " + std::to_string(i), "");
    }
}

void LobbiesManager::update(float deltaTime)
{
    std::vector<std::future<void>> futures;
    // std::vector<std::string> infoBuffer;
    futures.reserve(m_lobbies.size());
    // infoBuffer.reserve(m_lobbies.size());
    for (auto& lobbyPtr : m_lobbies)
    {
        futures.push_back(
        m_threadPool.enqueue([lobbyPtr = lobbyPtr.get(), deltaTime]() {
            lobbyPtr->update(deltaTime);
            
        })
    );
    }

    for (auto& f : futures) f.get(); // ensures all updates done this tick
    // for (auto& str : infoBuffer) std::cout << str << "\n";
}


bool LobbiesManager::joinLobby(uint64_t lobbyID, RakNet::SystemAddress * address, const std::string & accountID, const std::string & guid)
{

    

    // // client = m_clientsMap.find(accountID)->second.get(); 
    // if(m_clientsMap.find(accountID)->second.get() == nullptr)
    // {
    //     client = std::make_unique<BattleClient>(); // if client already exists, create new client
    // }
    // else
    // {
    //     client.get()->init(guid, accountID, address); //
    // }

    //m_clientsMap[accountID] = std::move(client);

    return true;
   // return getLobby(lobbyID)->addPlayer(*address);

}