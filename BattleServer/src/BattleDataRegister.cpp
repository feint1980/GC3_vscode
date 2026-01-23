#include "BattleDataRegister.h"

BattleDataRegister* BattleDataRegister::m_instance = 0;


bool BattleDataRegister::registerWhiteListClient_ByGUID(const std::string & guid, const std::string & id)
{
    if (m_whiteListClient_GUID_2_ID.find(guid) != m_whiteListClient_GUID_2_ID.end())
    {

        std::cout << "guid " << guid << " already exist \n";
        return false;
    }

    m_whiteListClient_GUID_2_ID[guid] = id;
    m_whiteListClient_ID_2_GUID[id] = guid; // reverse mapping
    std::cout << "added guid " << guid << " with id " << id << "\n";
    return true;
}

bool BattleDataRegister::removeWhiteListClientID_ByGUID(const std::string & guid)
{
    if (m_whiteListClient_GUID_2_ID.find(guid) != m_whiteListClient_GUID_2_ID.end())
    {
        
        std::string id = m_whiteListClient_GUID_2_ID[guid];
        m_whiteListClient_ID_2_GUID.erase(id); // reverse mapping 
        m_whiteListClient_GUID_2_ID.erase(guid);

        return true;
    }
    else
    {
        std::cout << "[C++][BattleDataRegister] no client with guid " << guid << "\n";
        return false;
    }
}

bool BattleDataRegister::removeWhiteListClientID_ByID(const std::string & id)
{

    if (m_whiteListClient_ID_2_GUID.find(id) != m_whiteListClient_ID_2_GUID.end())
    {
        std::string guid = m_whiteListClient_ID_2_GUID[id];
        m_whiteListClient_GUID_2_ID.erase(guid); // reverse mapping
        m_whiteListClient_ID_2_GUID.erase(id); 
        return true;
    }
    else
    {
        std::cout << "[C++][BattleDataRegister] no client with id " << id << "\n";
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
        removeWhiteListClientID_ByGUID(m_onlineSessionsIDTable[id].guid);
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