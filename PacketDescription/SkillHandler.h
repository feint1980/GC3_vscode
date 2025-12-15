#pragma once

#include "SkillDesc.h"
#include "LuaManager.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class SkillHandler
{
public: 
    SkillHandler();
    ~SkillHandler();
    void init(lua_State * script);

    void addSkillDesc(const std::string & characterName, const std::string & skillName, SkillDesc * skillDesc);

    SkillDesc * getSkillDesc(const std::string & characterName, const std::string & skillName);
private:
    std::unordered_map<std::string, std::unordered_map<std::string, SkillDesc *>> m_skillDescs;

    lua_State * m_script = nullptr;

};