
#include "BattleClient.h"
#include <unordered_map>
#include <memory>

class BattleClientManager
{
public:
    BattleClientManager() {};

    ~BattleClientManager() {};

    void update(float deltaTime);

    void addClient(const std::string& guid, const std::string& name,  const RakNet::SystemAddress & address);

    private:

    std::vector<std::unique_ptr<BattleClient>> m_clientsPtr; 

    std::unordered_map<std::string, BattleClient*> m_clientsMap;

};