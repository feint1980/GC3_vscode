#include "CharacterManager.h"
#include "Json2Struct.h"

int lua_CM_CreateCharacter(lua_State * L)
{
    if(lua_gettop(L) != 4)
    {
        std::cout << "gettop failed (lua_CM_CreateCharacter) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        CharacterManager * host = static_cast<CharacterManager*>(lua_touserdata(L, 1));
        std::string guid = lua_tostring(L, 2);
        std::string characterID = lua_tostring(L, 3);
        CharacterStats * stats = static_cast<CharacterStats*>
        (lua_touserdata(L, 4));
        CharacterDesc * charDesc = host->getCharacterDesc(guid, characterID);
        if(!charDesc)
        {
            charDesc = new CharacterDesc();
        }

        charDesc->setCharacterStats(*stats);
        host->addCharacterDesc(guid, characterID, charDesc);

        json j = charDesc->getCharacterStats();

        // std::cout << "stat dump check \n";

        // std::cout << j.dump(4,'.') << "\n";

        lua_pushlightuserdata(L, charDesc);
        return 1;
    }
    return 0;
}

//

// MARK: Lua functions
/// Parse Character Stat from String
int lua_ParseCharacterFromString(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_ParseCharacterFromString) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        CharacterStats *result = new CharacterStats();
        std::string str = lua_tostring(L, 1);
        json j = json::parse(str);
        *result = j.get<CharacterStats>();
        lua_pushlightuserdata(L, result);
        return 1;
    }
    return 0;
}

int lua_CM_GetCharacter(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_CM_GetCharacter) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        CharacterManager * host = static_cast<CharacterManager*>(lua_touserdata(L, 1));
        std::string userID = lua_tostring(L, 2);
        std::string characterID = lua_tostring(L, 3);
        CharacterDesc * result = host->getCharacterDesc(userID, characterID);
        lua_pushlightuserdata(L, result);
        return 1;
    }
    return 0;
}

int lua_CM_GetCharacterAttribute(lua_State * L)
{
    if (lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_getEntityCharacterAttribute) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        CharacterDesc * entity = static_cast<CharacterDesc*>(lua_touserdata(L, 1));
        std::string attributeName = lua_tostring(L, 2);
        float value = entity->getFloatAttributeByName(attributeName);
        lua_pushnumber(L, value);
        return 1;
    }
    return 0;
}

int lua_CM_GetCharacterAttributeStr(lua_State * L)
{
    if (lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_getEntityCharacterAttribute) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        CharacterDesc * entity = static_cast<CharacterDesc*>(lua_touserdata(L, 1));
        std::string attributeName = lua_tostring(L, 2);
        std::string value = entity->getStrAttributeByName(attributeName);
        lua_pushstring(L, value.c_str());
        return 1;
    }
    return 0;
}

int lua_CM_GetCharacterStatsAsString(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_CM_GetCharacterStatsAsString) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        CharacterDesc * entity = static_cast<CharacterDesc*>(lua_touserdata(L, 1));
        json j = entity->getCharacterStats();
        lua_pushstring(L, j.dump(0, '.').c_str());
        return 1;
    }
    return 0;
}

int lua_CM_SetCharacterAttribute(lua_State * L)
{
    if (lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_CM_SetCharacterAttribute) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        CharacterDesc * desc = static_cast<CharacterDesc*>(lua_touserdata(L, 1));
        std::string attributeName = lua_tostring(L, 2);
        float value = lua_tonumber(L, 3);
        desc->setAttribute(attributeName, value);
        return 0;
    }
    return 0;

}

int lua_CM_SetCharacterAttributeStr(lua_State * L)
{
    if (lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_CM_SetCharacterAttributeStr) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        CharacterDesc * desc = static_cast<CharacterDesc*>(lua_touserdata(L, 1));
        std::string attributeName = lua_tostring(L, 2);
        std::string value = lua_tostring(L, 3);
        desc->setAttribute(attributeName, value);
        return 0;
    }
    return 0;
}

/////////////////////////

CharacterManager::CharacterManager()
{

}
CharacterManager::~CharacterManager()
{

}

void CharacterManager::init(lua_State * script)
{
    m_script = script;

    if(LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, "../luaFiles/characterManager.lua")))
    {
        std::cout << "CharacterManager Run script characterManager.lua OK \n";
    }

    lua_getglobal(m_script, "CharacterManagerInit");
    if(lua_isfunction(m_script, -1))
    {
        lua_pushlightuserdata(m_script, this);
        const int argc = 1;
        const int returnCount = 0;
        if(LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, argc, returnCount, 0)))
        {
            std::cout << "Call CharacterManagerInit from C++ OK \n";
        }
    }
    // Character Handling 
    lua_register(m_script, "cpp_ParseCharacterFromString", lua_ParseCharacterFromString);
    lua_register(m_script, "cpp_CM_CreateCharacter", lua_CM_CreateCharacter);
    lua_register(m_script, "cpp_CM_GetCharacter", lua_CM_GetCharacter);

    lua_register(m_script, "cpp_CM_CharacterGetAttribute", lua_CM_GetCharacterAttribute);
    lua_register(m_script, "cpp_CM_CharacterGetAttributeStr", lua_CM_GetCharacterAttributeStr);

    lua_register(m_script, "cpp_CM_CharacterSetAttribute", lua_CM_SetCharacterAttribute);
    lua_register(m_script, "cpp_CM_CharacterSetAttributeStr", lua_CM_SetCharacterAttributeStr);

    lua_register(m_script, "cpp_CM_GetCharacterStatsAsString", lua_CM_GetCharacterStatsAsString);
    
}

void CharacterManager::addCharacterDesc(const std::string & guid,const std::string & characterID ,CharacterDesc *characterDesc)
{
    std::string combineID = guid + "_" +  characterID;   
    m_charactersDesc[combineID] = characterDesc;
}

CharacterDesc * CharacterManager::getCharacterDesc(const std::string & guid,const std::string & characterID)
{
    std::string combinedKey = guid + "_" + characterID;
    if(m_charactersDesc.find(combinedKey) != m_charactersDesc.end())
    {
        return m_charactersDesc[combinedKey];
    }
    return nullptr;
}    