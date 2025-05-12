#pragma once

#include <unordered_map>    
#include "LuaManager.h"
#include "CharacterDes.h"


class ClientCharacterHandler
{
public:
    ClientCharacterHandler();

    ~ClientCharacterHandler();

    void init(lua_State * script);

    void addCharacterDesc(std::string & name ,CharacterDesc * characterDesc);
    // CharacterDesc * getCharacter(const std::string & name);

private:
    std::unordered_map<std::string, CharacterDesc > m_characters;

    lua_State * m_script;
};