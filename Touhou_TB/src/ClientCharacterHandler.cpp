

#include "ClientCharacterHandler.h"


int lua_CharacterFillData(lua_State * L)
{
    if (lua_gettop(L) != 3)
	{
		std::cout << "gettop failed (lua_CharacterFillData) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}
    else
    {
        ClientCharacterHandler * handler = static_cast<ClientCharacterHandler*>(lua_touserdata(L, 1));
        std::string name = lua_tostring(L, 2);
        CharacterStats  *returnStats = static_cast<CharacterStats*>(lua_touserdata(L, 3));
        CharacterDesc * desc = new CharacterDesc();
        desc->setCharacterStats(*returnStats); 
        handler->addCharacterDesc(name, desc);
    }
    return 0;
}

int lua_GetCharacterData(lua_State * L)
{
    if (lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_GetCharacterData) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        ClientCharacterHandler * handler = static_cast<ClientCharacterHandler*>(lua_touserdata(L, 1));
        std::string name = lua_tostring(L, 2);
        CharacterDesc * desc = handler->getCharacter(name);
        lua_pushlightuserdata(L, desc);
        return 1;
    }
    return 0;
}

int lua_setEntityCharacterDesc(lua_State * L)
{
    if (lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_setEntityCharacterDesc) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        F_Lua_BaseEntity * entity = static_cast<F_Lua_BaseEntity*>(lua_touserdata(L, 1));
        CharacterDesc * desc = static_cast<CharacterDesc*>(lua_touserdata(L, 2));
        entity->setCharacterDesc(*desc);
        return 0;
    }
    return 0;
}

int lua_setCharactercAttribute(lua_State * L)
{
    if (lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_setCharactercAttribute) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        F_Lua_BaseEntity * entity = static_cast<F_Lua_BaseEntity*>(lua_touserdata(L, 1));
        std::string attributeName = lua_tostring(L, 2);
        float value = (float)lua_tonumber(L, 3);
        entity->setAttribute(attributeName, value);
        return 0;
    }
    return 0;
}

int lua_setCharactercAttributeStr(lua_State * L)
{
    if (lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_setCharactercAttributeStr) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        F_Lua_BaseEntity * entity = static_cast<F_Lua_BaseEntity*>(lua_touserdata(L, 1));
        std::string attributeName = lua_tostring(L, 2);
        std::string value = lua_tostring(L, 3);
        entity->setAttribute(attributeName, value);
        return 0;
    }
    return 0;
}

int lua_getEntityCharacterAttribute(lua_State * L)
{
    if (lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_getEntityCharacterAttribute) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        F_Lua_BaseEntity * entity = static_cast<F_Lua_BaseEntity*>(lua_touserdata(L, 1));
        std::string attributeName = lua_tostring(L, 2);
        float value = entity->getFloatAttributeByName(attributeName);
        lua_pushnumber(L, value);
        return 1;
    }
    return 0;
}

int lua_getEntityCharacterAttributeStr(lua_State * L)
{
    if (lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_getEntityCharacterAttributeStr) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        F_Lua_BaseEntity * entity = static_cast<F_Lua_BaseEntity*>(lua_touserdata(L, 1));
        std::string attributeName = lua_tostring(L, 2);
        std::string value = entity->getStrAttributeByName(attributeName);
        lua_pushstring(L, value.c_str());
        return 1;
    }
    return 0;
}

int lua_CreateCharacterNon_CB(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_CreateCharacterNon_CB) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        std::cout << "lua_CreateCharacterNon_CB called 1 \n";
        ClientCharacterHandler * handler = static_cast<ClientCharacterHandler*>(lua_touserdata(L, 1));
        std::cout << "lua_CreateCharacterNon_CB called 2 \n";
        std::string name = lua_tostring(L, 2);
        std::cout << "lua_CreateCharacterNon_CB called 3 \n";
        CharacterDesc * desc = static_cast<CharacterDesc*>(lua_touserdata(L, 3));
        if(desc == nullptr)
        {
            std::cout << "lua_CreateCharacterNon_CB desc is nullptr \n";
            return -1;
        }
        else
        {
            std::cout << "lua_CreateCharacterNon_CB desc is not nullptr \n";
        }
        std::cout << "lua_CreateCharacterNon_CB called 4 \n";
        F_Lua_BaseEntity * entity = handler->createCharacter(name, desc);
        std::cout << "lua_CreateCharacterNon_CB called 5 \n";
        lua_pushlightuserdata(L, entity);
        return 1;
    }
    return 0;
}

CharacterDesc * ClientCharacterHandler::getCharacter(const std::string & name)
{
    return m_charactersDesc[name];
}


F_Lua_BaseEntity * ClientCharacterHandler::createCharacter(const std::string & name ,CharacterDesc *characterDesc)
{
    F_Lua_BaseEntity * entity = new F_Lua_BaseEntity();
    std::cout << "new OK \n";
    entity->setCharacterDesc(*characterDesc);
    std::cout << "setCharacterDesc OK \n";
    std::cout << "insert " << name << " with value " << entity << "\n";
    // m_characters.insert(std::make_pair(name, entity));
    std::cout << "insert OK \n";
    return entity;
    // m_characters[name] = std::move(entity);
    // return m_characters[name];
}

void ClientCharacterHandler::addCharacterDesc(const std::string & name ,CharacterDesc *characterDesc)
{
    m_charactersDesc[name] = characterDesc;
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
    

    // lua_getglobal(m_script, "ClientCharacterHandlerInit");// get the function name to the top of the stack
	// if (lua_isfunction(m_script, -1))
	// {
	// 	//std::cout << "host is " << this << "\n";
	// 	lua_pushlightuserdata(m_script, this);
	// 	//std::cout << "C++ called " + functionName << "\n";
	// 	const int argCount = 1;
	// 	const int returnCount =1;
	// 	if (LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, argCount, returnCount, 0)))
	// 	{
    //         std::cout << "Init ClientCharacterHandler from C++ OK \n";
	// 	}
	// }


    lua_register(m_script, "cpp_CreateCharacterNon_CB", lua_CreateCharacterNon_CB);
    lua_register(m_script, "cpp_CharacterFillData", lua_CharacterFillData);
    lua_register(m_script, "cpp_GetCharacterData", lua_GetCharacterData);
    lua_register(m_script, "cpp_setEntityCharacterDesc", lua_setEntityCharacterDesc);
    lua_register(m_script, "cpp_setCharactercAttribute", lua_setCharactercAttribute);
    lua_register(m_script, "cpp_setCharactercAttributeStr", lua_setCharactercAttributeStr);
    lua_register(m_script, "cpp_getEntityCharacterAttribute", lua_getEntityCharacterAttribute);
    lua_register(m_script, "cpp_getEntityCharacterAttributeStr", lua_getEntityCharacterAttributeStr);
    
}
