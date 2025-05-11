

#include "ClientCharacterHandler.h"


int lua_CharacterFillData(lua_State * L)
{

    return 0;
}

ClientCharacterHandler::ClientCharacterHandler()
{

}

ClientCharacterHandler::~ClientCharacterHandler()
{

}

void ClientCharacterHandler::init(lua_State * script)
{
    m_script = script;
    if(luaL_dofile(m_script, "../../Lua/TouhouTB/data/ClientCharacterHandler.lua") == 0)
    {
        std::cout << "Run script ClientCharacterHandler OK \n";
    }
    
    lua_register(m_script, "cpp_CharacterFillData", lua_CharacterFillData);

}
