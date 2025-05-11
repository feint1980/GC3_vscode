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

private:
    std::unordered_map<std::string, CharacterDesc * > m_characters;

    lua_State * m_script;
};