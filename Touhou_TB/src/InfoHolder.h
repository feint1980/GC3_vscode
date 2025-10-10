

#pragma once

// class ClientScriptingManager;
// #include "ClientScriptingManager.h"
#include <RakNet/MessageIdentifiers.h>
//#pragma pack(push, 1)
#include <RakNet/RakPeerInterface.h>
#include <RakNet/RakNetStatistics.h>
#include <RakNet/RakNetTypes.h>
#include <RakNet/BitStream.h>
#include <RakNet/RakSleep.h>
#include <RakNet/PacketLogger.h>

#include <F_Cryptor.h>
#include <map>

class InfoHolder
{

public:
    static InfoHolder* getInstance()
    { 

        if (m_inforHolder == 0)
			{
				m_inforHolder = new InfoHolder();
				return m_inforHolder;
			}
			return m_inforHolder;
    }

    void registerClient(RakNet::RakPeerInterface * client)
    {
    
        // m_clientScriptingManager = clientScriptingManager;
        m_client = client;
        // std::cout << "register client " << m_client << "\n";
    }

    // void registerClientScriptingManager(ClientScriptingManager * clientScriptingManager) { m_clientScriptingManager = clientScriptingManager; }

    void registerCryptorMap(Feintgine::F_Cryptor * cryptor, const std::string & id) { m_cryptorMap[id] = cryptor; }


    void registerPersonalData(const std::string & guid, const std::string & id, const std::string & pw) { m_guid = guid; m_id = id; m_pw = pw; }


    void getData(std::vector<std::string> & data) 
    {
        data.clear();
        data.push_back(m_id);
        data.push_back(m_pw);
        data.push_back(m_guid);
    }

    RakNet::RakPeerInterface * getClient() { 
        
        // std::cout << "get client " << m_client << "\n";
        return m_client; }


    // ClientScriptingManager * getClientScriptingManager() { return m_clientScriptingManager; }


    void saveServerIP(const RakNet::SystemAddress &serverIPAddr) { m_serverIPAddr = serverIPAddr; }

    RakNet::SystemAddress getServerIP() { return m_serverIPAddr; }

private:

    static InfoHolder* m_inforHolder ;

    std::string m_guid;
    std::string m_id;
    std::string m_pw;

    RakNet::SystemAddress m_serverIPAddr;

    // ClientScriptingManager * m_clientScriptingManager = nullptr;

    RakNet::RakPeerInterface * m_client = nullptr;

    std::map<std::string,Feintgine::F_Cryptor *> m_cryptorMap;


};