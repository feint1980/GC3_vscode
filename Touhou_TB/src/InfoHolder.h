

#pragma once


#include "ClientScriptingManager.h"
#include <F_Cryptor.h>
#include <map>

class InfoHolder
{

public:
    static InfoHolder* getInstance()
    { 

        if(!m_inforHolder)
        {
            m_inforHolder = new InfoHolder();

        }
        else
        {
            return m_inforHolder;
        }
    }

    void registerClientScriptingManager(ClientScriptingManager * clientScriptingManager)
    {
        m_clientScriptingManager = clientScriptingManager;
    }

    void registerCryptorMap(Feintgine::F_Cryptor * cryptor, const std::string & id) { m_cryptorMap[id] = cryptor; }


    void registerPersonalData(const std::string & guid, const std::string & id, const std::string & pw) { m_guid = guid; m_id = id; m_pw = pw; }


    void getData(std::vector<std::string> & data) 
    {
        data.clear();
        data.push_back(m_id);
        data.push_back(m_pw);
        data.push_back(m_guid);
    }


    ClientScriptingManager * getClientScriptingManager() { return m_clientScriptingManager; }



private:

    static InfoHolder* m_inforHolder;

    std::string m_guid;
    std::string m_id;
    std::string m_pw;

    ClientScriptingManager * m_clientScriptingManager = nullptr;

    std::map<std::string,Feintgine::F_Cryptor *> m_cryptorMap;


};