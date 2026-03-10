#include "BattleClient.h"

void BattleClient::init(const std::string& guid, const std::string& id, const RakNet::SystemAddress & address)
{
    m_guid = guid;
    m_id = id;
    m_address = address;
}