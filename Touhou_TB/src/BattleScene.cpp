
#include "BattleScene.h"


int lua_CreateEntity(lua_State * L)
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


int lua_CreateSlot(lua_State * L)
{
	if (lua_gettop(L) != 4)
	{
		std::cout << "gettop failed (lua_CreateSlot) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}
	std::cout << "[C++] lua_CreateSlot called \n";
	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));
	int row = (int)lua_tonumber(L, 2);
	int colum = (int)lua_tonumber(L, 3);
	int side = (int)lua_tonumber(L, 4);
	Slot * slot = battleScene->addSlot(row, colum, side);
	lua_pushlightuserdata(L, slot);
	return 1;
} 

void BattleScene::init(Feintgine::Camera2D * camera )
{

	m_camera = camera;
	 // init lua
    m_script = luaL_newstate();
    luaL_openlibs(m_script);

	// register lua function
	lua_register(m_script, "cppCreateEnity", lua_CreateEntity);
	lua_register(m_script, "cppCreateSlot", lua_CreateSlot);

	

	if (LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, "./Assets/lua/test.lua")))
	{
		std::cout << "read script OK \n";
	
	}

	lua_getglobal(m_script, "init");// get the function name to the top of the stack
	if (lua_isfunction(m_script, -1))
	{
		//std::cout << "host is " << this << "\n";
		lua_pushlightuserdata(m_script, this);
		//std::cout << "C++ called " + functionName << "\n";
		const int argCount = 1;
		const int returnCount =1;
		if (LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, argCount, returnCount, 0)))
		{
			
		}
	}

    // lua register 1 ( lua state ) , 2 name will be called in lua, 3 the pointer to function
    //lua_register(m_script, "cppCreateEntity", lua_createEntity);
}

BattleScene::BattleScene()
{

   
}

BattleScene::~BattleScene()
{

}

Slot * BattleScene::addSlot(int row, int colum, int side)
{
	Slot * slot = new Slot();
	slot->init(row, colum, side);
	m_slots.push_back(slot);

	return slot;
}

void BattleScene::handleInput(Feintgine::InputManager & inputManager)
{
	glm::vec2 mousePos = inputManager.getMouseCoords();

	for(int i = 0 ; i < m_slots.size(); i++)
	{
		if(m_slots[i]->isHovered(m_camera->convertScreenToWorld(mousePos)))
		{
			m_slots[i]->setState(1);
		}
		else
		{
			m_slots[i]->setState(0);
		}
	}

}

void BattleScene::draw(Feintgine::SpriteBatch & spriteBatch)
{

	for(int i = 0 ; i < m_slots.size(); i++)
	{
		m_slots[i]->draw(spriteBatch);
	}

}
void BattleScene::update(float deltaTime)
{

	for(int i = 0 ; i < m_slots.size(); i++)
	{
		m_slots[i]->update(deltaTime);
	}
}
