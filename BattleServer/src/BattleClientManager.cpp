
#include "BattleClientManager.h"


void BattleClientManager::addClient(const std::string& guid, const std::string& name, const RakNet::SystemAddress& address)
{
    std::unique_ptr<BattleClient> client = std::make_unique<BattleClient>();
    client->init(guid, name, address);
    m_clientsPtr.push_back(std::move(client));
    m_clientsMap[guid] = std::move(client);
}

