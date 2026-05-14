
#include "FieldInfo.h"


FieldInfo::FieldInfo()
{

}

FieldInfo::~FieldInfo()
{

}

void FieldInfo::init(const std::string & scriptPath, lua_State * script)
{

    m_script = script;

    if(LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, scriptPath.c_str())))
    {
        std::cout << "Run script " << scriptPath << " OK \n";
    }
    else
    {
        std::cout << "Run script " << scriptPath << " failed \n";
        return;
    }

    m_portraitMap["S_Reimu"] = "./Assets/TB_GUI/faces/Reimu_face.png";
    m_portraitMap["S_Meiling"] = "./Assets/TB_GUI/faces/Meiling_face.png";
    m_portraitMap["S_Yukari"] = "./Assets/TB_GUI/faces/Yukari_face.png";
    m_portraitMap["S_Patchouli"] = "./Assets/TB_GUI/faces/Patchouli_face.png";

    std::cout << "Field Info init OK |||||||||||||||||||| \n";

}

std::string FieldInfo::getPortraitPath(const std::string & characterName)
{
    std::string retVal ;

    retVal = "./Assets/TB_GUI/faces/missing.png";
    if(m_portraitMap.find(characterName) != m_portraitMap.end())
    {
        retVal = m_portraitMap[characterName];
    }
    return retVal;
}

void FieldInfo::addCharacter(const std::string & ID, int side, const dCharacterStats & charStat )
{
    std::string key = ID + "_" + std::to_string(side);


    m_statMap[key] = charStat;
    std::cout << "add or rewrite character " << key << "\n";

}

dCharacterStats FieldInfo::getCharacterStats(const std::string & ID, int side)
{
    std::string key = ID + "_" + std::to_string(side);
    dCharacterStats retVal;
    retVal.characterID = "Invalid \n";
    if(m_statMap.find(key) != m_statMap.end())
    {
        retVal = m_statMap[key]; // Should overwrite characterID
    }
    return retVal;
}

void FieldInfo::listAllInfo()
{

}