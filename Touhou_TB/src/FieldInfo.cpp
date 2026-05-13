
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
    std::cout << "List all info \n";
    // iterate the map
    for (auto it = m_statMap.begin(); it != m_statMap.end(); it++) 
    {
        std::cout << "|====================" << it->first << "====================|\n";
        std::cout << "| Owner: " << it->second.ownerID << "\n";
        std::cout << "| Character ID: " << it->second.characterID << "\n";
        std::cout << "|-------Stats-------|\n";
        std::cout << "| STR : " << it->second.strength << "\n";
        std::cout << "| VIT : " << it->second.vitality << "\n";
        std::cout << "| DEX : " << it->second.dexterity << "\n";
        std::cout << "| AGI : " << it->second.agility << "\n";
        std::cout << "| INT : " << it->second.intelligence << "\n";
        std::cout << "| WIS : " << it->second.wisdom << "\n";
        std::cout << "| PHY DMG : " << it->second.physicDmg << "\n";
        std::cout << "| MAG DMG : " << it->second.magicDmg << "\n";
        std::cout << "| PHY DEF : " << it->second.physicDef << "\n";
        std::cout << "| MAG DEF : " << it->second.magicDef << "\n";
        std::cout << "| PHY ACC : " << it->second.physicalAccuracy << "\n";
        std::cout << "| MAG ACC : " << it->second.magicalAccuracy << "\n";
        std::cout << "| EVA : " << it->second.evasion << "\n";
        std::cout << "| CRIT : " << it->second.critChance << "\n";
        std::cout << "| SPD : " << it->second.speed << "\n";
        std::cout << "| DD SURVIVAL  : " << it->second.deathDoorSurvival << "\n";
        std::cout << "| MAX HP       : " << it->second.maxHP << "\n";
        std::cout << "| CURRENT HP   : " << it->second.currentHP << "\n";
        std::cout << "| MAX MANA     : " << it->second.maxMana << "\n";
        std::cout << "| CURRENT MANA : " << it->second.currentMana << "\n";
        std::cout << "| MAX AP       : " << it->second.maxAP << "\n";
        std::cout << "| CURRENT AP   : " << it->second.currentAP << "\n";
        std::cout << "| MAX SP       : " << it->second.maxSP << "\n";
        std::cout << "| CURRENT SP   : " << it->second.currentSP << "\n";
        std::cout << "|---------------------------------------|\n";
        std::cout << "| POS : " << it->second.rowPos << "|| " << it->second.colPos << "|\n";
        std::cout << "|=======================================|\n";

    }
}