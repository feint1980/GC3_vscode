#ifndef CHARACTERMANAGER_H
#define CHARACTERMANAGER_H

#include "CharacterDes.h"
#include "SkillDesc.h"
#include "LuaManager.h"
#include <unordered_map>

class CharacterManager
{
public:
    CharacterManager();
    ~CharacterManager();

    void init(lua_State * script);

    void addCharacterDesc(const std::string & guid,const std::string & characterID ,CharacterDesc *characterDesc);

    CharacterDesc * getCharacterDesc(const std::string & guid,const std::string & characterID);


private:

    lua_State * m_script;
    std::unordered_map<std::string, CharacterDesc *> m_charactersDesc;

};


#endif