

#include "ClientCharacterHandler.h"


int lua_CharacterFillData(lua_State * L)
{
    if (lua_gettop(L) != 3)
	{
		std::cout << "gettop failed (lua_SetAtrribute) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}
    ClientCharacterHandler * handler = static_cast<ClientCharacterHandler*>(lua_touserdata(L, 1));
    std::string name = lua_tostring(L, 2);
    CharacterStats  *returnStats = static_cast<CharacterStats*>(lua_touserdata(L, 3));
    // CharacterDesc desc 


    // handler->addCharacterDesc(name, returnStats);
    return 0;
}


void ClientCharacterHandler::addCharacterDesc(std::string & name ,CharacterDesc * characterDesc)
{

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
