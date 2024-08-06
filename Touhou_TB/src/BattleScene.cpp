
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

int lua_GetSlotCol(lua_State * L)
{
	if (lua_gettop(L) != 1)
	{
		std::cout << "gettop failed (lua_GetSlotCol) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}
	Slot * slot = static_cast<Slot*>(lua_touserdata(L, 1));
	int col = slot->getIndex().x;
	lua_pushnumber(L, col);
	return 1;
}

int lua_GetEntitySlot(lua_State * L)
{
	if (lua_gettop(L) != 1)
	{
		std::cout << "gettop failed (lua_GetEntitySlot) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	F_Lua_BaseEntity * object = static_cast<F_Lua_BaseEntity*>(lua_touserdata(L, 1));
	Slot * slot = object->getCurrentSlot();
	lua_pushlightuserdata(L, slot);

	return 1;
}

int lua_EntityPlayAnimation(lua_State * L)
{

	if (lua_gettop(L) < 3 || lua_gettop(L) > 5)
	{
		std::cout << "gettop failed (lua_EntityPlayAnimation) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));
	F_Lua_BaseEntity * object = static_cast<F_Lua_BaseEntity*>(lua_touserdata(L, 2));
	std::string animationName = lua_tostring(L, 3);

	int time = 0;
	if (lua_gettop(L) >= 4)
	{
		time = (int)lua_tonumber(L, 4);
	}
	float duration = 500.0f;
	if(lua_gettop(L) == 5)
	{
		
		duration = (float)lua_tonumber(L, 5);
		std::cout << " has duration " << duration << "\n";
	}
	

	F_Lua_EntityManipulator * manipulator = new F_Lua_EntityManipulator();

	manipulator->playAnimation(object, animationName, time, duration);

	battleScene->addEntityManipulator(manipulator);


	return 0;
}

int lua_EntityMoveToSlot(lua_State * L)
{

	if (lua_gettop(L) != 4)
	{
		std::cout << "gettop failed (lua_EntityMoveToSlot) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));
	F_Lua_BaseEntity * object = static_cast<F_Lua_BaseEntity*>(lua_touserdata(L, 2));
	Slot * slot = static_cast<Slot*>(lua_touserdata(L, 3));
	float time = (float)lua_tonumber(L, 4);

	F_Lua_EntityManipulator * manipulator = new F_Lua_EntityManipulator();

	manipulator->moveToSlot(object, slot, time);

	battleScene->addEntityManipulator(manipulator);	

	return 0;
}

void BattleScene::addEntityManipulator(F_Lua_EntityManipulator * entityManipulator)
{

	m_entityManipulators.push_back(entityManipulator);
}


int lua_EntityGetTargetSlot(lua_State * L)
{
	if (lua_gettop(L) != 1)
	{
		std::cout << "gettop failed (lua_EntityGetTargetSlot) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	F_Lua_BaseEntity * object = static_cast<F_Lua_BaseEntity*>(lua_touserdata(L, 1));

	Slot * slot = object->getTargetSlot();

	lua_pushlightuserdata(L, slot);
	return 1;	

}

int lua_CreateGUIHandler(lua_State * L)
{

	if (lua_gettop(L) != 4)
	{
		std::cout << "gettop failed (lua_CreateGUIHandler) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));
	std::string selectionTexturePath = lua_tostring(L, 2);
	glm::vec2 dim = glm::vec2(0);

	dim.x = (float)lua_tonumber(L, 3);
	dim.y = (float)lua_tonumber(L, 4);

	GUI_handler * handler =  battleScene->createGUIHandler(selectionTexturePath, dim);

	lua_pushlightuserdata(L, handler);

	return 1;
}

GUI_handler * BattleScene::createGUIHandler(const std::string & selectionTexturePath, const glm::vec2 & dim)
{

	if(m_guiHandler == nullptr)
	{
		m_guiHandler = new GUI_handler();	
		m_guiHandler->init(selectionTexturePath, dim);
	}
	
	
	return m_guiHandler;
}

int lua_CreateIcon(lua_State * L)
{

	if (lua_gettop(L) < 7 || lua_gettop(L) > 8)
	{
		std::cout << "gettop failed (lua_CreateIcon) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));
	std::string texturePath = lua_tostring(L, 2);
	glm::vec2 dim = glm::vec2(0);

	dim.x = (float)lua_tonumber(L, 3);
	dim.y = (float)lua_tonumber(L, 4);
	std::string name = lua_tostring(L, 5);
	std::string description = lua_tostring(L, 6);
	float turnCost = (float)lua_tonumber(L, 7);

	unsigned int specialID = 0;
	if(lua_gettop(L) == 8)
	{
		specialID = (unsigned int)lua_tonumber(L, 8);
	}

	GUI_icon * icon =  battleScene->createIcon(texturePath,glm::vec2(0), dim);
	icon->setName(name);
	icon->setDescription(description);
	icon->setTurnCost(turnCost);
	icon->setSpecialID(specialID);

	lua_pushlightuserdata(L, icon);
	return 1;

}

GUI_icon * BattleScene::createIcon(const std::string & texturePath, const glm::vec2 & pos, const glm::vec2 & dim)
{


	GUI_icon * icon = new GUI_icon();
	icon->init(texturePath, pos, dim);
	m_icons.push_back(icon);

	return icon;
}


int lua_GUIHandlerAddIcon(lua_State * L)
{

	if (lua_gettop(L) != 2)
	{
		std::cout << "gettop failed (lua_GUIHandlerAddIcon) \n";	
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));
	GUI_icon * icon = static_cast<GUI_icon*>(lua_touserdata(L, 2));

	battleScene->GUIHandlerAddIcon(icon);
	
	return 0;
}

void BattleScene::GUIHandlerAddIcon(GUI_icon * icon)
{
	
	if(m_guiHandler != nullptr)
	{
		m_guiHandler->addIcon(icon);
	}
}

void BattleScene::setGUIHandlerIconPos(GUI_icon * icon, const glm::vec2 & pos)
{
	if(m_guiHandler != nullptr)
	{
		m_guiHandler->setIconPos(icon, pos);
	}
}

int lua_GuiHandlerSetIconPos(lua_State * L)
{

	if (lua_gettop(L) != 4)
	{
		std::cout << "gettop failed (lua_GuiHandlerSetIconPos) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));
	GUI_icon * icon = static_cast<GUI_icon*>(lua_touserdata(L, 2));
	glm::vec2 pos = glm::vec2(0);

	pos.x = (float)lua_tonumber(L, 3);
	pos.y = (float)lua_tonumber(L, 4);

	battleScene->setGUIHandlerIconPos(icon, pos);
	return 0;

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
	lua_register(m_script, "cppGetSlotCol", lua_GetSlotCol);
	lua_register(m_script, "cppGetEntitySlot", lua_GetEntitySlot);
	lua_register(m_script, "cppEntityPlayAnimation", lua_EntityPlayAnimation);
	lua_register(m_script, "cppEntityMoveToslot", lua_EntityMoveToSlot);
	lua_register(m_script, "cppEntityGetTargetSlot", lua_EntityGetTargetSlot);

	// GUI_handler data 
	lua_register(m_script, "cppCreateGUIHandler", lua_CreateGUIHandler);
	lua_register(m_script, "cppGUIHandlerAddIcon", lua_GUIHandlerAddIcon);
	lua_register(m_script, "cppGuiHandlerSetIconPos", lua_GuiHandlerSetIconPos);

	// create gui icon
	lua_register(m_script, "cppCreateIcon", lua_CreateIcon);


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
	if(m_guiHandler)
	{
		m_guiHandler->draw(spriteBatch);
	}

}

void BattleScene::setMoveTargetSlot(F_Lua_BaseEntity * entity, Slot * slot)
{
		entity->setTargetSlot(slot);
		lua_getglobal(m_script, "setEntityMoveToSlot");
		if (lua_isfunction(m_script, -1))
		{
			//m_luaBossStates[i]->m_luaBoss;
			
			//lua_pushlightuserdata(m_script, pThread);
			lua_pushlightuserdata(m_script, this); // host

			//std::cout << "Issue next task pointer " << object << "\n";

			lua_pushlightuserdata(m_script, entity);

			// lua_pushlightuserdata(m_script, entity->getTargetSlot());

			if (!LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, 2, 1, 0)))
			{
				std::cout << "call setEntityMoveToSlot failed \n";
			}
		}
}

void BattleScene::update(float deltaTime)
{

	for(int i = 0 ; i < m_slots.size(); i++)
	{
		m_slots[i]->update(deltaTime);
		if(m_currentEntity && !m_isMove)
		{
			if(m_currentEntity->isActive())
			{
				//std::cout << "has active entity \n";
				if(m_slots[i]->getState() == 1)
				{
					setMoveTargetSlot(m_currentEntity, m_slots[i]);
					m_isMove = true;
				}
			}
		}
	}

	for(int i = 0 ; i < m_entities.size(); i++)
	{
		m_entities[i]->update(deltaTime);
	}

	// update manipulator
	for(int i = 0 ; i < m_entityManipulators.size(); i++)
	{
		if(m_entityManipulators[i])
		{
				
			if(m_entityManipulators[i]->update(deltaTime))
			{
				lua_getglobal(m_script, "HandleMovingTask");
				if (lua_isfunction(m_script, -1))
				{
					//m_luaBossStates[i]->m_luaBoss;
					F_Lua_BaseEntity * entity = m_entityManipulators[i]->getEntity();
					//lua_pushlightuserdata(m_script, pThread);
					lua_pushlightuserdata(m_script, this); // host

					//std::cout << "Issue next task pointer " << object << "\n";

					lua_pushlightuserdata(m_script, entity);

					// lua_pushlightuserdata(m_script, entity->getTargetSlot());

					if (!LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, 2, 1, 0)))
					{
						std::cout << "HandleMovingTask failed \n";
					}
				}
				// After Issued next task
				m_entityManipulators.erase(m_entityManipulators.begin() + i);
			}
				
		}
	}

}
	
