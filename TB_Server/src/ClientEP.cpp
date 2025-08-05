
#include "ClientEP.h"



ClientEP::ClientEP()
{

}

ClientEP::~ClientEP()
{

}

void ClientEP::init(RakNet::SystemAddress *ip, const std::string &guid, const std::string &name)
{
    m_ip = ip;
    m_guid = guid;
    m_name = name;
}

void ClientEP::addCharacter(CharacterDesc* character) 
{
    if(character != nullptr)
    {
        if(m_characterTable.find(character->getCharacterStats().ID.c_str()) != m_characterTable.end())
        {
            std::cout << "warning, found the same character " << character->getCharacterStats().ID << ", replacing ... \n";
        }
        m_characterTable[character->getCharacterStats().ID.c_str()] = character; // add or replace
    }
}
