#include "SkillHandler.h"

static void to_json(json& j, const SkillStats& s)
{
    j = json{
        {"skillName", s.skillName},
        {"description", s.description},
        {"effect", s.effect},
        {"quote", s.quote},
        {"iconPath", s.iconPath},
        {"ID", s.ID},
        {"skillType", s.skillType}
    };
}

static void from_json(const json& j, SkillStats& s)
{
    j.at("skillName").get_to(s.skillName);
    j.at("description").get_to(s.description);
    j.at("effect").get_to(s.effect);
    j.at("quote").get_to(s.quote);
    j.at("iconPath").get_to(s.iconPath);
    j.at("ID").get_to(s.ID);
    j.at("skillType").get_to(s.skillType);
}

SkillStats parseSkillStatFromStr(const std::string & str)
{
    SkillStats result;
    json j = json::parse(str);
    result = j.get<SkillStats>();
    return result;
}

int lua_Skill_GetSkillAttributeInt(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_ParseCharacterFromJson) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        SkillDesc * desc = static_cast<SkillDesc*>(lua_touserdata(L, 1));
        std::string characterName = lua_tostring(L, 2);
        int result = desc->getAttributeInt(characterName);
        lua_pushnumber(L, result);
        return 1;
    }
    return 0;
}

int lua_Skill_GetSkillAttributeStr(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_ParseCharacterFromJson) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        SkillDesc * desc = static_cast<SkillDesc*>(lua_touserdata(L, 1));
        std::string characterName = lua_tostring(L, 2);
        std::string result = desc->getAttribute(characterName);
        lua_pushstring(L, result.c_str());
        return 1;
    }
    return 0;
}

int lua_SkillStat_parseFromStr(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_ParseCharacterFromJson) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }    
    else
    {
        SkillStats * returnStats = new SkillStats();
        *returnStats = parseSkillStatFromStr(lua_tostring(L, 1));
        // std::cout << "skill stat parse check \n";
        // std::cout << returnStats->skillName << "\n";
        lua_pushlightuserdata(L, returnStats);
        return 1;
    }
    return 0;
}

int lua_Skill_AddSkillDesc(lua_State * L)
{
    if(lua_gettop(L) != 4)
    {
        std::cout << "gettop failed (lua_Skill_AddSkillDesc) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        SkillHandler * host = static_cast<SkillHandler*>(lua_touserdata(L, 1));
        std::string characterName = lua_tostring(L, 2);
        std::string skillName = lua_tostring(L, 3);
        std::string skillStatsStr = lua_tostring(L, 4);
        SkillStats * skillStats = new SkillStats();
        *skillStats = parseSkillStatFromStr(skillStatsStr);
        SkillDesc * skillDesc = new SkillDesc();
        skillDesc->setSkillStats(*skillStats);

        host->addSkillDesc(characterName, skillName, skillDesc);
        return 0;
    }
}

int lua_Skill_GetSkillDesc(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_Skill_GetSkillDesc) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        SkillHandler * host = static_cast<SkillHandler*>(lua_touserdata(L, 1));
        std::string characterName = lua_tostring(L, 2);
        std::string skillName = lua_tostring(L, 3);
        SkillDesc * skillDesc = host->getSkillDesc(characterName, skillName);
        lua_pushlightuserdata(L, skillDesc);
        return 1;
    }
}

// -----------------------------------------------------------
SkillHandler::SkillHandler()
{

}

SkillHandler::~SkillHandler()
{

}

void  SkillHandler::addSkillDesc(const std::string  &characterName, const std::string & skillName, SkillDesc * skillDesc)
{   
    m_skillDescs[characterName][skillName] = skillDesc;
}


SkillDesc * SkillHandler::getSkillDesc(const std::string & characterName, const std::string & skillName)
{
    return m_skillDescs[characterName][skillName];
}

void SkillHandler::init(lua_State * script)
{
    m_script = script;

    // init lua component
    if(LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, "../../Lua/system/GUI/tguiScript.lua")))
    {
        std::cout << "Run script OK \n";
    }
    lua_register(m_script, "cpp_SkillStat_parseFromStr", lua_SkillStat_parseFromStr);
    lua_register(m_script, "cpp_Skill_AddSkillDesc", lua_Skill_AddSkillDesc);
    lua_register(m_script, "cpp_Skill_GetSkillDesc", lua_Skill_GetSkillDesc);
    lua_register(m_script, "cpp_Skill_GetSkillAttributeInt", lua_Skill_GetSkillAttributeInt);
    lua_register(m_script, "cpp_Skill_GetSkillAttributeStr", lua_Skill_GetSkillAttributeStr);

}