
#include "BattleScene.h"


int lua_CreateEntity(lua_State * L)
{
	if (lua_gettop(L) < 3 ||  lua_gettop(L) > 5)
	{
		std::cout << "gettop failed (lua_CreateFromLua) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}
	std::cout << "[C++] lua_CreateEntity called \n";
	glm::vec2 pos(0);
	
	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));
	std::string animationPath = lua_tostring(L, 2);
	Slot * slot = static_cast<Slot*>(lua_touserdata(L, 3));

	glm::vec2 scale = glm::vec2(1.0f, 1.0f);
	if(lua_gettop(L) == 4)
	{
		float t_scale = (float)lua_tonumber(L, 4);
		scale = glm::vec2(t_scale, t_scale);

	}
	if(lua_gettop(L) == 5)
	{
		float t_scale_x = (float)lua_tonumber(L, 4);
		float t_scale_y = (float)lua_tonumber(L, 5);
		scale = glm::vec2(t_scale_x, t_scale_y);
	}
	
	F_Lua_BaseEntity * object = battleScene->addEntity(slot, animationPath, scale);
	
	lua_pushlightuserdata(L, object);
	return 1; // this host function return 1 number 
}

int lua_SetAtrribute(lua_State * L)
{
	if (lua_gettop(L) != 3)
	{
		std::cout << "gettop failed (lua_SetAtrribute) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}
	F_Lua_BaseEntity * object = static_cast<F_Lua_BaseEntity*>(lua_touserdata(L, 1));

	std::string attributeName = lua_tostring(L, 2);

	float value = (float)lua_tonumber(L, 3);

	object->setAttribute(attributeName, value);

	return 0;
}

F_Lua_BaseEntity * BattleScene::addEntity(Slot * slot, const std::string & animationPath, const glm::vec2 & scale)
{

	F_Lua_BaseEntity * object = new F_Lua_BaseEntity();
	object->init(slot, animationPath, scale);
	m_entities.push_back(object);
	return object;
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

int lua_PickActiveEntity(lua_State * L)
{
	if (lua_gettop(L) != 2)
	{
		std::cout << "gettop failed (lua_PickActiveEntity) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));
	F_Lua_BaseEntity * object = static_cast<F_Lua_BaseEntity*>(lua_touserdata(L, 2));
	battleScene->pickActiveEntity(object);
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
	lua_register(m_script, "cppSetAttribute", lua_SetAtrribute);
	lua_register(m_script, "cppPickActiveEntity", lua_PickActiveEntity);


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

void BattleScene::pickActiveEntity(F_Lua_BaseEntity * entity)
{

	for(int i = 0 ; i < m_entities.size(); i++)
	{
		if(m_entities[i] == entity)
		{
			m_currentEntity = m_entities[i];
			m_currentEntity->setActive(true);
			//m_entities[i]->setActive(true);

			return;
		}
	
	}
}


void BattleScene::draw(Feintgine::SpriteBatch & spriteBatch)
{

	for(int i = 0 ; i < m_slots.size(); i++)
	{
		m_slots[i]->draw(spriteBatch);
	}

	for(int i = 0 ; i < m_entities.size(); i++)
	{
		m_entities[i]->draw(spriteBatch);
	}

}
void BattleScene::update(float deltaTime)
{

	for(int i = 0 ; i < m_slots.size(); i++)
	{
		m_slots[i]->update(deltaTime);
		if(m_currentEntity)
		{
			if(m_currentEntity->isActive())
			{
				//std::cout << "has active entity \n";
				if(m_slots[i]->getState() == 1)
				{
					m_currentEntity->setTargetSlot(m_slots[i]);
				}
			}
		}
	}

	for(int i = 0 ; i < m_entities.size(); i++)
	{
		m_entities[i]->update(deltaTime);
	}
}
	
