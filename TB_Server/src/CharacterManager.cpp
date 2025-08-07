

#include "CharacterManager.h"


CharacterManager::CharacterManager()
{

}
CharacterManager::~CharacterManager()
{

}

void CharacterManager::init(lua_State * script)
{
    m_script = script;

}

void CharacterManager::addCharacterDesc(const std::string & guid,const std::string & characterID ,CharacterDesc *characterDesc)
{
    std::string combineID = guid + "_" +  characterID;   
    m_charactersDesc[combineID] = characterDesc;
}