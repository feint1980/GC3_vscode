
#include "BattleClientManager.h"


void BattleClientManager::addClient(const std::string& guid, const std::string& name,  const RakNet::SystemAddress & address)
{
    // std::unique_ptr<BattleClient> client = std::make_unique<BattleClient>();
    // client->init(guid, name, address);
    // m_clientsMap[name] = std::move(client);
    // m_clientsPtr.push_back(std::move(client));

    m_clientsPtr.push_back(std::make_unique<BattleClient>());
    m_clientsPtr.back()->init(guid, name, address);
    m_clientsMap[name] = m_clientsPtr.back().get();
}


void BattleClientManager::update(float deltaTime)
{
    
}