#include "BattleDataRegister.h"

BattleDataRegister* BattleDataRegister::m_instance = 0;


bool BattleDataRegister::registerWhiteListClient(const std::string & guid, const std::string & id)
{
    if (m_whiteListClientAddressTable.find(guid) != m_whiteListClientAddressTable.end())
    {

        std::cout << "guid " << guid << " already exist \n";
        return false;
    }

    m_whiteListClientAddressTable[guid] = id;
    return true;
}

bool BattleDataRegister::removeWhiteListClient(const std::string & guid)
{
    if (m_whiteListClientAddressTable.find(guid) != m_whiteListClientAddressTable.end())
    {
        m_whiteListClientAddressTable.erase(guid);
        return true;
    }
    else
    {
        std::cout << "[C++][BattleDataRegister] no client with guid " << guid << "\n";
        return false;
    }
}

bool BattleDataRegister::addClientOnlineSession(const std::string & guid, const  std::string & id, RakNet::SystemAddress * address)
{

    if (m_onlineSessionsGUIDTable.find(guid) != m_onlineSessionsGUIDTable.end())
    {

        std::cout << "guid " << guid << " already exist \n";
        return false;
    }
    if (m_onlineSessionsIDTable.find(id) != m_onlineSessionsIDTable.end())
    {

        std::cout << "id " << id << " already exist \n";
        std::cout << "multiple clients with same id detected, reconnect or login in other IP \n";
        // 
        m_onlineSessionsGUIDTable.erase(m_onlineSessionsIDTable[id].guid);

        m_onlineSessionsIDTable.erase(id);
        // remove from white list ( old client )
        removeWhiteListClient(m_onlineSessionsIDTable[id].guid);
    }
    m_onlineSessionsGUIDTable[guid] = ClientOnlineSession(guid, id, address);
    m_onlineSessionsIDTable[id] = ClientOnlineSession(guid, id, address);
    return true;
}

ClientOnlineSession * BattleDataRegister::getClientOnlineSessionByGUID(const std::string & guid)
{
    if (m_onlineSessionsGUIDTable.find(guid) != m_onlineSessionsGUIDTable.end())
    {
        return &m_onlineSessionsGUIDTable[guid];
    }
    return nullptr;
}

ClientOnlineSession * BattleDataRegister::getClientOnlineSessionByID(const std::string & id)
{
    if (m_onlineSessionsIDTable.find(id) != m_onlineSessionsIDTable.end())
    {
        return &m_onlineSessionsIDTable[id];
    }
    return nullptr;
}