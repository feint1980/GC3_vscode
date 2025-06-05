#pragma once

#include <unordered_map>    
#include "LuaManager.h"
#include "CharacterDes.h"
#include "F_Lua_BaseEntity.h"

class ClientCharacterHandler
{
public:
    ClientCharacterHandler();

    ~ClientCharacterHandler();

    void init(lua_State * script);

    void addCharacterDesc(const std::string & name ,CharacterDesc *characterDesc);

    F_Lua_BaseEntity * createCharacter(const std::string & name ,CharacterDesc *characterDesc);

    CharacterDesc * getCharacter(const std::string & name);

private:
    std::unordered_map<std::string, CharacterDesc * > m_charactersDesc;
    //std::unordered_map<std::string, F_Lua_BaseEntity * > m_characters;

    lua_State * m_script;
};