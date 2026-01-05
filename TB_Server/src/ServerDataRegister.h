

#ifndef SERVERDATAREGISTER_H
#define SERVERDATAREGISTER_H
#include <RakNet/MessageIdentifiers.h>
#include <RakNet/RakPeerInterface.h>
#include <RakNet/RakNetStatistics.h>
#include <RakNet/RakNetTypes.h>
#include <RakNet/BitStream.h>
#include <RakNet/RakSleep.h>
#include <RakNet/PacketLogger.h>
#include <RakNet/Gets.h>
#include <RakNet/Kbhit.h>

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>


struct OnlineSession
{
    std::string accoundID;
    std::string guid;
    RakNet::SystemAddress address;
    OnlineSession()
    {
        accoundID = "";
        guid = "";
        address = RakNet::UNASSIGNED_SYSTEM_ADDRESS;
    }
    OnlineSession(const std::string & id, const std::string & guid, RakNet::SystemAddress * t_address) : accoundID(id), guid(guid) 
    {
        std::cout << "t_address " << t_address->ToString(false) << "\n";


        // std::cout << "create new RakNet::SystemAddress \n";
        address =  *t_address;

        // address = new RakNet::SystemAddress(t_address->ToString(false),t_address->GetPort());
        std::cout << "copied address " << address.ToString(false) << "\n";

    }
    ~OnlineSession() 
    { 
        // if(address != nullptr)
        // {
        //     delete(address);
        // } 
    }
};

class ServerDataRegister
{
public:
    static ServerDataRegister* GetInstance()
    {
        if (m_instance == nullptr)
        {
            m_instance = new ServerDataRegister();
        }
        return m_instance;
    }

    bool addClientOnlineSession(const std::string & guid, const  std::string & id, RakNet::SystemAddress * address)
    {

        if(m_sessionGUIDTable.find(guid) != m_sessionGUIDTable.end())
        {
            std::cout << "guid " << guid << " already exist \n"; 
            return false;
        }
        if(m_sessionIDTable.find(id) != m_sessionIDTable.end())
        {
            std::cout << "id " << id << " already exist \n";
            std::cout << "multiple clients with same id detected, reconnect or login in other IP \n"; 
            // 
            m_sessionGUIDTable.erase(m_sessionIDTable[id].guid); 
            
            
        }
        m_sessionGUIDTable[guid] = OnlineSession(id, guid, address);
        m_sessionIDTable[id] = OnlineSession(id, guid, address);
        return true;
    }

    bool removeClientOnlineSessionByGUID(const std::string & guid)
    {
        if(m_sessionGUIDTable.find(guid) != m_sessionGUIDTable.end())
        {

            m_sessionIDTable.erase(m_sessionGUIDTable[guid].accoundID);
            m_sessionGUIDTable.erase(guid);
            return true;
        }
        else
        {
            std::cout << "[C++][ServerDataRegister] no client with guid " << guid << "\n";
            return false;
        }
    }

    bool removeClientOnlineSessionByID(const std::string & id)
    {
        if(m_sessionIDTable.find(id) != m_sessionIDTable.end())
        {
            m_sessionGUIDTable.erase(m_sessionIDTable[id].guid);
            m_sessionIDTable.erase(id);
            return true;
        }
        else
        {
            std::cout << "[C++][ServerDataRegister] no client with id " << id << "\n";
            return false;
        }
    }

    OnlineSession * getClientOnlineSessionByGUID(const std::string & guid)
    {
        if(m_sessionGUIDTable.find(guid) != m_sessionGUIDTable.end())
        {
            return &m_sessionGUIDTable[guid];
        }
        return nullptr;
    }

    OnlineSession * getClientOnlineSessionByID(const std::string & id)
    {
        if(m_sessionIDTable.find(id) != m_sessionIDTable.end())
        {
            return &m_sessionIDTable[id];
        }
        return nullptr;
    }

private:
    static ServerDataRegister* m_instance;
    std::unordered_map<std::string, OnlineSession> m_sessionGUIDTable;
    std::unordered_map<std::string, OnlineSession> m_sessionIDTable;

};

#endif // SERVERDATAREGISTER_H