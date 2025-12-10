
#include "BattleClientManager.h"


void BattleClientManager::addClient(const std::string& guid, const std::string& name,  RakNet::SystemAddress* address)
{
    std::unique_ptr<BattleClient> client = std::make_unique<BattleClient>();
    client->init(guid, name, address);
    m_clientsPtr.push_back(std::move(client));
    m_clientsMap[name] = std::move(client);
}


void BattleClientManager::update(float deltaTime)
{
    
}