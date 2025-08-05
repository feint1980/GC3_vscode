#ifndef CLIENTEP_H
#define CLIENTEP_H

#include <RakNet/MessageIdentifiers.h>

#include <RakNet/RakPeerInterface.h>
#include <RakNet/RakNetStatistics.h>
#include <RakNet/RakNetTypes.h>
#include <RakNet/BitStream.h>
#include <RakNet/RakSleep.h>
#include <RakNet/PacketLogger.h>
#include <RakNet/Gets.h>
#include <RakNet/Kbhit.h>

#include <vector>
#include <unordered_map>

#include "CharacterDes.h"
#include "SkillDesc.h"


class ClientEP
{
public:
    ClientEP();
    ~ClientEP();

    void init(RakNet::SystemAddress *ip, const std::string &guid, const std::string &name) ;

    void setIP(RakNet::SystemAddress *ip) { m_ip = ip; }
    RakNet::SystemAddress *getIP() const { return m_ip; }
    
    std::string getIPString() const { return m_ip->ToString(); }

    void setGUID(const std::string &guid) { m_guid = guid; }
    std::string getGUID() const { return m_guid; }

    void addCharacter(CharacterDesc* character) ;

    CharacterDesc* getCharacter(const std::string & characterID) const 
    {
        if(m_characterTable.find(characterID) != m_characterTable.end())
        {
            return m_characterTable.at(characterID);
        }
        return nullptr;
    }

    private:

    RakNet::SystemAddress *m_ip = nullptr;
    std::string m_guid;
    std::string m_name;

    std::unordered_map<std::string, CharacterDesc *> m_characterTable;
    std::vector<CharacterDesc*> m_characters;

};


#endif