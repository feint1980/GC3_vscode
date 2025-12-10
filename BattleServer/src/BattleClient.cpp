#include "BattleClient.h"

void BattleClient::init(const std::string& guid, const std::string& name, RakNet::SystemAddress * address)
{
    m_guid = guid;
    m_name = name;
    m_address = address;
}