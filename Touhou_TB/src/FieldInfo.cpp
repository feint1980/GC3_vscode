
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


