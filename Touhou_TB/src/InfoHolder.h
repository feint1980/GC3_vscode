

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
#include "TGUIScriptingManager.h"
#include <map>
#include <IMainGame.h>

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


    // removed ... for now
    // void saveLuaState(lua_State * state) { m_saveLuaState = state; }
    // lua_State * getLuaState() { return m_saveLuaState; }

    

    void registerGUIScriptingManager(TGUIScriptingManager * guiScriptingManager) {
        
        std::cout << "registering GUI scripting instance " << guiScriptingManager << "\n";
        m_guiScriptingManager = guiScriptingManager; }

    TGUIScriptingManager * getGUIScriptingManager() { 
        
        std::cout << "returning gui scripting instance " << m_guiScriptingManager << "\n";
        return m_guiScriptingManager; }

    void registerGame(Feintgine::IMainGame * game) { m_game = game; }

    Feintgine::IMainGame * getGame() { return m_game; }

    void saveStrValue(const std::string & key, const std::string & value) { m_savedStrValue[key] = value; }

    void saveNumberValue(const std::string & key, double value) { m_savedNumberValue[key] = value; }

    void savePointerValue(const std::string & key, void * value) { m_savedPointerValue[key] = value; }

    std::string getStrValue(const std::string & key) { 
        
        if(m_savedStrValue.find(key) == m_savedStrValue.end())
        {
            return key + "_null";
        }
        return m_savedStrValue[key]; }

    double getNumberValue(const std::string & key) { 
        if(m_savedNumberValue.find(key) == m_savedNumberValue.end())
        {
            return -322.0;
        }
        return m_savedNumberValue[key]; }



    void setUserLightData(const std::string & key, void * value) { m_savedPointerValue[key] = value; }

    void * getUserLightData(const std::string & key) {
        if(m_savedPointerValue.find(key) == m_savedPointerValue.end())
        {
            return nullptr;
        }
        return m_savedPointerValue[key]; }


    void initLuaInterface(lua_State * script);

private:

    static InfoHolder* m_inforHolder ;

    std::string m_guid;
    std::string m_id;
    std::string m_pw;

    RakNet::SystemAddress m_serverIPAddr;

    // ClientScriptingManager * m_clientScriptingManager = nullptr;



    RakNet::RakPeerInterface * m_client = nullptr;

    std::map<std::string,Feintgine::F_Cryptor *> m_cryptorMap;

    lua_State * m_script = nullptr;

    TGUIScriptingManager * m_guiScriptingManager = nullptr;

    Feintgine::IMainGame * m_game = nullptr;

    std::unordered_map<std::string, std::string > m_savedStrValue;
    std::unordered_map<std::string, double> m_savedNumberValue;
    std::unordered_map<std::string, void*> m_savedPointerValue;

};