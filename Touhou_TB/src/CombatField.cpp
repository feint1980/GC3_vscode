#include "CombatField.h"


CombatField::CombatField()
{

}

CombatField::~CombatField()
{

}


void CombatField::init(const std::string & scriptPath, lua_State * script)
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
}



void CombatField::draw(Feintgine::SpriteBatch & spriteBatch)
{

}

void CombatField::update(float deltaTime)
{

}
