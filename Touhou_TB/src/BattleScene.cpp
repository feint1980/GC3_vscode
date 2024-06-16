
#include "BattleScene.h"


int lua_CreateFromLua(lua_State * L)
{
	if (lua_gettop(L) != 7)
	{
		std::cout << "gettop failed (lua_CreateFromLua) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}
	//std::cout << "[C++] lua_CreateFromLua called \n";
	glm::vec2 pos(0);
	
	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));
	std::string animationPath = lua_tostring(L, 2);
	float posX = (float)lua_tonumber(L, 3);
	float posY = (float)lua_tonumber(L, 4);
	pos = glm::vec2(posX, posY);
	float scale = (float)lua_tonumber(L, 5);
	int depth = (int)lua_tonumber(L, 6);
	float angle = (float)lua_tonumber(L, 7);

	// F_Lua_GenericObject * createdDynamicObj = object->createBoss(pos, animationPath, glm::vec2(scale), depth, angle);// createObject(pos, animationPath, 1, 15, 0);
	// 																									//moveOb
	// 																									//std::cout << "create object " << createdDynamicObj << "\n";
	// 		//std::cout << "create |||| " << createdDynamicObj << "\n";
	//lua_pushlightuserdata(L, createdDynamicObj);
	return 1; // this host function return 1 number 
}


BattleScene::BattleScene()
{

    // init lua
    m_script = luaL_newstate();
    luaL_openlibs(m_script);

    // lua register 1 ( lua state ) , 2 name will be called in lua, 3 the pointer to function
    //lua_register(m_script, "cppCreateEntity", lua_createEntity);
}