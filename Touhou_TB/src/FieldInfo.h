
#ifndef FIELD_INFO_H
#define FIELD_INFO_H

#include <unordered_map>
#include <LuaManager.h>
#include <nlohmann/json.hpp>
#include "CombatCharacter.h"

using json = nlohmann::json;

class FieldInfo
{
public:
    FieldInfo();
    ~FieldInfo();

    void init(const std::string & scriptPath, lua_State * script);

    std::string getPortraitPath(const std::string & characterName);

    void addCharacter(const std::string & ID, int side,const dCharacterStats & charStat);

    dCharacterStats getCharacterStats(const std::string & ID, int side);

    private:

    std::unordered_map<std::string, std::string> m_portraitMap;
    
    std::unordered_map<std::string, dCharacterStats> m_statMap;


    lua_State * m_script = nullptr;

};

#endif