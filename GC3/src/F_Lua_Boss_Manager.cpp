#include "F_Lua_Boss_Manager.h"
#include "EngineSetting.h"
//#include "F_Komachi_Souls_Object.cpp" // I am sorry, Feint   | -  Belai



int lua_HostFunction(lua_State *L)
{
	float a = (float)lua_tonumber(L, 1); // get arg 1 
	float b = (float)lua_tonumber(L, 2); // get arg 2
	//std::cout << "[C++] HostFunction " << a << " " << b << " called \n";

	float c = a * b;

	lua_pushnumber(L, c);
	return 1; // this host function return 1 number
}

float sinCosCalCulator(int type, float val)
{
	switch (type)
	{
	case 1 : 
		return cos(val);
		break;
	case 2:
		return sin(val);
		break;
	default:
		return 1.0f;
		break;
	}
}

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
	
	F_Lua_Boss_Manager * object = static_cast<F_Lua_Boss_Manager*>(lua_touserdata(L, 1));
	std::string animationPath = lua_tostring(L, 2);
	float posX = (float)lua_tonumber(L, 3);
	float posY = (float)lua_tonumber(L, 4);
	pos = glm::vec2(posX, posY);
	float scale = (float)lua_tonumber(L, 5);
	int depth = (int)lua_tonumber(L, 6);
	float angle = (float)lua_tonumber(L, 7);

	F_Lua_GenericObject * createdDynamicObj = object->createBoss(pos, animationPath, glm::vec2(scale), depth, angle);// createObject(pos, animationPath, 1, 15, 0);
																										//moveOb
																										//std::cout << "create object " << createdDynamicObj << "\n";
																						//std::cout << "create |||| " << createdDynamicObj << "\n";
	lua_pushlightuserdata(L, createdDynamicObj);
	return 1; // this host function return 1 number 
}

int lua_removeFromLua(lua_State * L)
{
	if (lua_gettop(L) != 2)
	{
		std::cout << "bad gettop " << lua_gettop(L) << " \n";
		return -1;
	}
	//std::cout << "[C++] lua_RemoveFromLua called \n";
	F_Lua_Boss_Manager * object = static_cast<F_Lua_Boss_Manager*>(lua_touserdata(L, 1));
	F_Lua_GenericObject * dynamicObject = static_cast<F_Lua_GenericObject *>(lua_touserdata(L, 2));
	object->removeObject(dynamicObject);
	return 0;
}
int lua_setObjectVel(lua_State * L)
{
	std::cout << "lua_setObjectVel called \n";
	if (lua_gettop(L) != 3)
	{
		std::cout << "(lua_setObjectVel) bad gettop " << lua_gettop(L) << " \n";
		return;
	}
	F_Lua_GenericObject * dynamicObject = static_cast<F_Lua_GenericObject *>(lua_touserdata(L, 1)); // dynob
	glm::vec2 vel = glm::vec2(lua_tonumber(L, 2), lua_tonumber(L, 3));
	dynamicObject->setVel(vel);
	return 0;
}
int lua_MoveObject(lua_State * L)
{
	if (lua_gettop(L) != 5)
	{
		std::cout << "bad gettop " << lua_gettop(L) << " \n";
		return -1;
	}
	//std::cout << "[C++] lua_MoveObject called \n";
	//F_Lua_Boss_Manager
	F_Lua_Boss_Manager * objectManager = static_cast<F_Lua_Boss_Manager*>(lua_touserdata(L, 1));
	F_Lua_GenericObject * dynamicObject = static_cast<F_Lua_GenericObject *>(lua_touserdata(L, 2));
	float x = lua_tonumber(L, 3);
	float y = lua_tonumber(L, 4);
	float time = lua_tonumber(L, 5);
	objectManager->MoveObject(dynamicObject, x, y, time);
	return 0;
}

int lua_HoldPosition(lua_State * L)
{
	if (lua_gettop(L) < 4 || lua_gettop(L) > 5)
	{
		std::cout << "bad gettop " << lua_gettop(L) << " \n";
		return -1;
	}

	F_Lua_Boss_Manager * objectManager = static_cast<F_Lua_Boss_Manager*>(lua_touserdata(L, 1));
	F_Lua_GenericObject * dynamicObject = static_cast<F_Lua_GenericObject *>(lua_touserdata(L, 2));
	float time = lua_tonumber(L, 3);
	std::string t_anim = lua_tostring(L, 4);
	bool isOverRide = true;
	if(lua_gettop(L) == 5)
	{
		isOverRide = lua_toboolean(L, 5);
	}
	//std::cout << "t_anim " << t_anim << "\n";
	objectManager->standIdle(dynamicObject,time,t_anim,isOverRide);

	return 0;
}
int lua_setFireTypePE(lua_State * L)
{
	if (lua_gettop(L) != 15)
	{
		std::cout << "bad gettop " << lua_gettop(L) << " \n";
		return -1;
	}
	//std::cout << "lua_AddEvent called \n";
	F_Lua_Boss_Manager * objectManager = static_cast<F_Lua_Boss_Manager*>(lua_touserdata(L, 1)); //host
	F_Lua_GenericObject * dynamicObject = static_cast<F_Lua_GenericObject *>(lua_touserdata(L, 2)); // dynob
	std::string asset = lua_tostring(L, 3); // asset
	float speed = lua_tonumber(L, 4); // speed
	float lifeTime = lua_tonumber(L, 5); // lifeTime
	int peType = lua_tonumber(L, 6); // arcType
	float startRange = lua_tonumber(L, 7); // a
	float rangeCover = lua_tonumber(L, 8); // b
	float angleStep = lua_tonumber(L, 9); // angleStep 
	float startAngle = lua_tonumber(L, 10); //startAngle
	int petalCount = lua_tonumber(L, 11); // petalCount
	int interval = lua_tonumber(L, 12); // interval
	float rotation = lua_tonumber(L, 13); // rotation
	int count = lua_tonumber(L, 14); // count;
	double time = lua_tonumber(L, 15);

	rotation = rotation / 57.2957795f;
	startAngle = startAngle / 57.2957795f;


	switch (peType)
	{
	case 1:

	case 2:

	default:
		break;
	}

	//std::cout << "time !!! " << time << "\n";

	int totalInterval = 0;
	objectManager->rw_addEvent_PE(dynamicObject, asset, speed, lifeTime, peType, startRange, rangeCover,
		angleStep, startAngle, petalCount, interval, rotation, count, time);


	return 0;
}
int lua_setFireType1(lua_State * L)
{
	if (lua_gettop(L) != 17)
	{
		std::cout << "bad gettop " << lua_gettop(L) << " \n";
		return -1;
	}
	//std::cout << "lua_AddEvent called \n";
	F_Lua_Boss_Manager * objectManager = static_cast<F_Lua_Boss_Manager*>(lua_touserdata(L, 1)); //host
	F_Lua_GenericObject * dynamicObject = static_cast<F_Lua_GenericObject *>(lua_touserdata(L, 2)); // dynob
	std::string asset = lua_tostring(L, 3); // asset
	float speed = lua_tonumber(L, 4); // speed
	float lifeTime = lua_tonumber(L, 5); // lifeTime
	int arcType = lua_tonumber(L, 6); // arcType
	float fA = lua_tonumber(L, 7); // a
	float fB = lua_tonumber(L, 8); // b
	float fC = lua_tonumber(L, 9); // c
	float fD = lua_tonumber(L, 10); // d
	float fR = lua_tonumber(L, 11); // r
	float angleStep = lua_tonumber(L, 12); // angleStep 
	float startAngle = lua_tonumber(L, 13); //startAngle
	float rotation = lua_tonumber(L, 14); // rotation
	int interval = lua_tonumber(L, 15); // interval
	int count = lua_tonumber(L, 16); // count;
	double time = lua_tonumber(L, 17);

	fR = fR * 0.01f;

	int totalInterval = 0;
	objectManager->rw_addEvent_T1(dynamicObject, asset, speed, lifeTime, arcType, fA, fB, fC,fD, fR,
		angleStep, startAngle, rotation, interval, count, time);
		
	return 0;
}

int lua_setFireMACustomAFF(lua_State * L)
{
	if (lua_gettop(L) != 16)
	{
		std::cout << "bad gettop " << lua_gettop(L) << " \n";
		return -1;
	}
	//std::cout << "lua_AddEvent called \n";
	F_Lua_Boss_Manager * objectManager = static_cast<F_Lua_Boss_Manager*>(lua_touserdata(L, 1)); //host
	F_Lua_GenericObject * dynamicObject = static_cast<F_Lua_GenericObject *>(lua_touserdata(L, 2)); // dynob
	std::string asset = lua_tostring(L, 3); // asset
	float speed = lua_tonumber(L, 4); // speed
	float lifeTime = lua_tonumber(L, 5); // lifeTime
	int k = lua_tonumber(L, 6); // arcType
	int n = lua_tonumber(L, 7); // a
	int n2 = lua_tonumber(L, 8); // b
	int l1 = lua_tonumber(L, 9); // c
	int l2 = lua_tonumber(L, 10); // r
	int posneg = lua_tonumber(L, 11); // r
	float startAngle = lua_tonumber(L, 12); //startAngle
	float angleStep = lua_tonumber(L, 13); // angleStep
	float rotation = lua_tonumber(L, 14); // rotation
	int interval = lua_tonumber(L, 15); // interval
	double time = lua_tonumber(L, 16);

	objectManager->rw_addEvent_MA_custom_aff(dynamicObject, asset, speed, lifeTime, k, n, n2, l1, l2, posneg,
		startAngle, angleStep, rotation, interval, time);

	return 0;
}


int lua_setFireBase(lua_State * L)
{

	//std::cout << "here \n";
	if (lua_gettop(L) != 9)
	{
		std::cout << "bad gettop " << lua_gettop(L) << " \n";
		return -1;
	}
	//	void rw_addEvent_base(F_Lua_GenericObject * dynamicObject, 
	//const std::string & asset, float speed, float lifeTime, 
	//float x, float y, float currentAngle, double time);
	F_Lua_Boss_Manager * objectManager = static_cast<F_Lua_Boss_Manager*>(lua_touserdata(L, 1)); //host
	F_Lua_GenericObject * dynamicObject = static_cast<F_Lua_GenericObject *>(lua_touserdata(L, 2)); // dynob
	std::string asset = lua_tostring(L, 3); // 
	float speed = lua_tonumber(L, 4); // 
	float lifeTime = lua_tonumber(L, 5); // 
	float x = lua_tonumber(L, 6); // 
	float y = lua_tonumber(L, 7); // 
	float currentAngle = lua_tonumber(L, 8); // 
	double time = lua_tonumber(L, 9); // 

	objectManager->rw_addEvent_base(dynamicObject, asset, speed, lifeTime, x, y, currentAngle, time);

	return 0;

}

int lua_setKomachiCoin(lua_State * L)
{
	//std::cout << "here \n";
	if (lua_gettop(L) != 11)
	{
		std::cout << "bad gettop " << lua_gettop(L) << " \n";
		return -1;
	}
	//	void rw_addEvent_base(F_Lua_GenericObject * dynamicObject, 
	//const std::string & asset, float speed, float lifeTime, 
	//float x, float y, float currentAngle, double time);
	F_Lua_Boss_Manager * objectManager = static_cast<F_Lua_Boss_Manager*>(lua_touserdata(L, 1)); //host
	F_Lua_GenericObject * dynamicObject = static_cast<F_Lua_GenericObject *>(lua_touserdata(L, 2)); // dynob

	std::string tableName = lua_tostring(L,3);

	int type = lua_type(L,4);
	if(type != LUA_TTABLE)
	{
		std::cout << "lua_setKomachiCoin : arg 3 is not a table\n";
	}

	lua_getglobal(L,tableName.c_str());
	lua_pushnil(L);
	std::vector<std::string> tAssets;
	while(lua_next(L,-2))
	{
		if(lua_isstring(L,-1))
		{
			std::string name = lua_tostring(L,-1);
			tAssets.push_back(name);
			//std::cout << "name " << name << "\n";
		}
		lua_pop(L,1);
		
	}
	lua_pop(L,1);
	//std::string asset = lua_tostring(L, 3); // 
	int tier = lua_tonumber(L,5);
	float speed = lua_tonumber(L, 6); // 
	float lifeTime = lua_tonumber(L, 7); // 
	float x = lua_tonumber(L, 8); // 
	float y = lua_tonumber(L, 9); // 
	float currentAngle = lua_tonumber(L, 10); // 
	double time = lua_tonumber(L, 11); // 

	objectManager->rw_addEvent_fire_komachi_coin(dynamicObject,tAssets,tier,speed,lifeTime,x,y,currentAngle,time);

	// rw_addEvent_fire_komachi_coin(F_Lua_GenericObject * dynamicObject, const std::vector<std::string> & assets, int tier, float speed, float lifeTime, float x, float y, float currentAngle, double time)

	// objectManager->rw_addEvent_base(dynamicObject, asset, speed, lifeTime, x, y, currentAngle, time);

	return 0;
}
int lua_createHelper(lua_State * L)
{
	//createObject(F_Lua_GenericObject * dynamicObject, const std::string & objectName,
	//const std::string & asset, float x, float y, float scaleX, float scaleY, float depth,float velX, float velY,int afterImageCount, float afterImageRate, double time);

	if(lua_gettop(L) != 16)
	{
		std::cout << "bad gettop " << lua_gettop(L) << " \n";
		return -1;
	}
	std::cout << "lua create helper called \n";
	F_Lua_Boss_Manager * objectManager = static_cast<F_Lua_Boss_Manager*>(lua_touserdata(L, 1)); //host
	F_Lua_GenericObject * dynamicObject = static_cast<F_Lua_GenericObject *>(lua_touserdata(L, 2)); // dynob
	unsigned int id = lua_tonumber(L, 3); //
	std::string objectName = lua_tostring(L, 4); //
	std::string asset = lua_tostring(L, 5); //
	float x = lua_tonumber(L, 6); //
	float y = lua_tonumber(L, 7); //
	float scaleX = lua_tonumber(L, 8); //
	float scaleY = lua_tonumber(L, 9); //
	float depth = lua_tonumber(L, 10); //
	float velX = lua_tonumber(L, 11); //
	float velY = lua_tonumber(L, 12); //
	int afterImageCount = lua_tonumber(L, 13); //
	float afterImageRate = lua_tonumber(L, 14); //
	float scaleRate = lua_tonumber(L, 15); //
	double time = lua_tonumber(L, 16); //

	objectManager->createHelper(dynamicObject,id, objectName, asset, x, y, scaleX, scaleY, depth, velX, velY, afterImageCount, afterImageRate,scaleRate, time);
	
	return 0 ;
}

int lua_setAfterImage(lua_State * L)
{
	if (lua_gettop(L) <4 ||  lua_gettop(L) > 7)
	{
		std::cout << "(lua_setAfterImage) bad gettop " << lua_gettop(L) << " \n";
		return;
	}
	F_Lua_GenericObject * dynamicObject = static_cast<F_Lua_GenericObject *>(lua_touserdata(L, 1)); // dynob
	float interval = lua_tonumber(L, 2);
	float lifeTime = lua_tonumber(L, 3);
	int maxNum = 10;
	float scaleRate = 0.0f;
	float alphaRate = 0.5f;
	float traceLifeTime = 2.0f;
	if(lua_gettop(L) >= 4)
	{
		maxNum = lua_tonumber(L, 4);
	}
	if(lua_gettop(L) >= 5)
	{
		scaleRate = lua_tonumber(L, 5);
	}
	if(lua_gettop(L) >= 6)
	{
		alphaRate = lua_tonumber(L, 6);
	}
	if(lua_gettop(L) == 7)
	{
		traceLifeTime = lua_tonumber(L, 7);
	}

	dynamicObject->setTrace(interval, lifeTime, maxNum, scaleRate, alphaRate,traceLifeTime);
	return 0;
}


int lua_getObjectPos(lua_State * L)
{
	if (lua_gettop(L) != 1)
	{
		std::cout << "(lua_getObjectPos) bad gettop " << lua_gettop(L) << " \n";
		return;
	}
	F_Lua_GenericObject * dynamicObject = static_cast<F_Lua_GenericObject *>(lua_touserdata(L, 1)); // dynob
	glm::vec2 pos = dynamicObject->getPos();
	//std::cout << "get pos " << pos.x << " " << pos.y << "\n";
	//lua_newtable(L);
	lua_pushnumber(L, pos.x);
	lua_pushnumber(L, pos.y);
	//lua_settable(L, -3);
	return 2;
}

int lua_getObjectAngle(lua_State * L)
{
	if (lua_gettop(L) != 1)
	{
		std::cout << "(lua_getObjectAngle) bad gettop " << lua_gettop(L) << " \n";
		return;
	}
	F_Lua_GenericObject * dynamicObject = static_cast<F_Lua_GenericObject *>(lua_touserdata(L, 1)); // dynob
	float angle = dynamicObject->getAngle();
	//std::cout << "angle return " << angle << "\n";
	lua_pushnumber(L, angle);
	return 1;
}

int lua_waitFor(lua_State * L)
{
	if (lua_gettop(L) != 3)
	{
		std::cout << "(lua_waitFor) bad gettop " << lua_gettop(L) << " \n";
		return;
	}
	F_Lua_Boss_Manager * objectManager = static_cast<F_Lua_Boss_Manager*>(lua_touserdata(L, 1)); //host
	F_Lua_GenericObject * dynamicObject = static_cast<F_Lua_GenericObject *>(lua_touserdata(L, 2)); // dynob
	float time = lua_tonumber(L, 3);
	objectManager->waitFor(dynamicObject, time);
	return 0;
}

int lua_playAnimation(lua_State * L)
{
	if (lua_gettop(L) < 2 && lua_gettop(L) > 4)
	{
		std::cout << "(lua_playAnimation) bad gettop " << lua_gettop(L) << " \n";
	}
	F_Lua_GenericObject * dynamicObject = static_cast<F_Lua_GenericObject *>(lua_touserdata(L, 1)); // dynob
	std::string animationName = lua_tostring(L, 2);
	int loopTime = 0;
	bool isOverride = false;
	if(lua_gettop(L) >= 3)
	{
		loopTime = lua_tonumber(L, 3);
	}
	if(lua_gettop(L) == 4)
	{
		isOverride = lua_toboolean(L, 4);
	}
	dynamicObject->playAnimation(animationName, loopTime);
	dynamicObject->setAnimOverRide(isOverride);

}


F_Lua_Boss_Manager::F_Lua_Boss_Manager()
{

	// Init Map 
	m_objectMap.insert(std::make_pair("komachi_souls", ObjectType::komachi_souls));

	m_script = luaL_newstate();
	luaL_openlibs(m_script);

	// lua register 1 ( lua state ) , 2 name will be called in lua, 3 the pointer to function
	lua_register(m_script, "HostFunction", lua_HostFunction);
	lua_register(m_script, "cppCreateFromLua", lua_CreateFromLua);
	lua_register(m_script, "cppMoveObject", lua_MoveObject);
	lua_register(m_script, "cppHoldPosition", lua_HoldPosition);
	lua_register(m_script, "cppSetFire_Type1", lua_setFireType1);
	lua_register(m_script, "cppSetFire_TypePE", lua_setFireTypePE);
	lua_register(m_script, "cppSetFire_MA_custom_aff", lua_setFireMACustomAFF);
	lua_register(m_script, "cppSetFire_Base", lua_setFireBase);
	lua_register(m_script, "cppCreateHelper", lua_createHelper);
	lua_register(m_script, "cppRemoveFromLua", lua_removeFromLua);
	lua_register(m_script, "cppSetFire_KomachiCoin",lua_setKomachiCoin);
	lua_register(m_script, "cppSetAfterImage", lua_setAfterImage);
	lua_register(m_script, "cppGetObjectPos", lua_getObjectPos);
	lua_register(m_script, "cppSetObjectVel", lua_setObjectVel);
	lua_register(m_script, "cppGetObjectAngle", lua_getObjectAngle);
	lua_register(m_script, "cppWaitFor", lua_waitFor);
	lua_register(m_script, "cppPlayAnimation", lua_playAnimation);
	//std::cout << "called  F_Lua_Boss_Manager |||||||||||||||\n";
}


F_Lua_Boss_Manager::~F_Lua_Boss_Manager()
{
}



void F_Lua_Boss_Manager::removeObject(F_Lua_GenericObject * object)
{
	for (size_t i = 0; i < m_luaBosses.size(); i++)
	{
		if (m_luaBosses[i] == object)
		{
			m_luaBosses.erase(m_luaBosses.begin() + i);
			break;
		}
	}
}

void F_Lua_Boss_Manager::update(float deltaTime)
{
	//std::cout << "update \n";
	for (size_t i = 0; i < m_luaBosses.size(); i++)
	{
		if (m_luaBosses[i])
		{
			m_luaBosses[i]->update(deltaTime);
		}
	}
	for(size_t i = 0 ; i < m_objects.size() ; i++)
	{
		if (m_objects[i])
		{
			m_objects[i]->update(deltaTime);
		}
	}
	for (size_t i = 0; i < m_luaBossStates.size(); i++)
	{
		if (m_luaBossStates[i])
		{
			if (m_luaBossStates[i]->update(deltaTime))
			{
			
				//std::cout << "Issue Next Task [C++] \n";
				lua_getglobal(m_script, "IssueNextTask");
				if (lua_isfunction(m_script, -1))
				{
					//m_luaBossStates[i]->m_luaBoss;
					F_Lua_GenericObject * object = m_luaBossStates[i]->m_luaBoss;
					//lua_pushlightuserdata(m_script, pThread);
					lua_pushlightuserdata(m_script, this); // host

					//std::cout << "Issue next task pointer " << object << "\n";

					lua_pushlightuserdata(m_script, object);
					if (!LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, 2, 1, 0)))
					{
						std::cout << "script failed \n";
					}
				}

				// After Issued next task
				m_luaBossStates.erase(m_luaBossStates.begin() + i);
			}
		}
	}

	for (int i = 0; i < m_luaBosses.size(); i++)
	{
		if (m_luaBosses[i]->m_bullets.size() > 0)
		{
			for (int c = 0; c < m_luaBosses[i]->m_bullets.size(); c++)
			{
				//m_enemies[i]->m_bullets[c]->initLogic(m_world.get());
				m_bullets.push_back(m_luaBosses[i]->m_bullets[c]);
			}
			m_luaBosses[i]->m_bullets.clear();
		}
	}
	for (auto i = 0; i < m_bullets.size(); i++)
	{
		if (m_bullets[i]->m_lifeTime > 0)
		{
			m_bullets[i]->update(deltaTime);
		}
		else
		{
			m_bullets.erase(m_bullets.begin() + i);
		}
	}
}

void F_Lua_Boss_Manager::MoveObject(F_Lua_GenericObject * dynamicObject, float x, float y, float time)
{
 	F_Lua_Boss_State * manipulator = new F_Lua_Boss_State();
 	manipulator->moveObject(dynamicObject, glm::vec2(x, y), time);
 	m_luaBossStates.push_back(manipulator);
}

void F_Lua_Boss_Manager::waitFor(F_Lua_GenericObject * dynamicObject, float time)
{
	F_Lua_Boss_State * manipulator = new F_Lua_Boss_State();
 	manipulator->waitFor(dynamicObject, time);
 	m_luaBossStates.push_back(manipulator);

	// dynamicObject->addEvent([=] 
	// {

	// 	std::cout << "this end \n";

	// }, ENGINE_current_tick + Feintgine::F_oEvent::convertMSToS(time ));

}


void F_Lua_Boss_Manager::setObjectVel(F_Lua_GenericObject * dynamicObject, const glm::vec2 & vel)
{

	F_Lua_Boss_State * manipulator = new F_Lua_Boss_State();
	manipulator->setObjectVel(dynamicObject, vel);
	m_luaBossStates.push_back(manipulator);

}
F_Lua_GenericObject * F_Lua_Boss_Manager::createBoss(const std::string & animationPath, glm::vec2 pos)
{
	std::cout << "createBoss 1 called \n";
	F_Lua_GenericObject * dynamicObject = new F_Lua_Boss();
	dynamicObject->createObject(pos, animationPath, glm::vec2(1), 15, 0);
	m_luaBosses.push_back(dynamicObject);
	return dynamicObject;
}

F_Lua_GenericObject * F_Lua_Boss_Manager::createBoss(const glm::vec2 & pos, const Feintgine::F_AnimatedObject & t_animation, const glm::vec2 & scale, float depth, float angle /*= 0.0f*/)
{
	std::cout << "createBoss 2 called \n";
	F_Lua_GenericObject * m_object = new F_Lua_Boss();
	m_object->createObject(pos, t_animation, scale, depth, angle);
	m_luaBosses.push_back(m_object);
	return m_object;
}

F_Lua_GenericObject * F_Lua_Boss_Manager::createBoss(const glm::vec2 & pos, const std::string & t_animationPath, const glm::vec2 & scale, float depth, float angle /*= 0.0f*/)
{
	std::cout << "createBoss 3 called \n";
	F_Lua_GenericObject * m_object = new F_Lua_Boss();
	m_object->createObject(pos, t_animationPath, scale, depth, angle);
	m_luaBosses.push_back(m_object);
	return m_object;
}

void F_Lua_Boss_Manager::clearBosses()
{
	for(auto i = 0; i < m_luaBosses.size(); i++)
	{	
		m_luaBosses.erase(m_luaBosses.begin() + i);
		delete m_luaBosses[i];
	}
	m_luaBosses.clear();
}

bool F_Lua_Boss_Manager::loadLuaFile(const std::string & filePath)
{
	if (LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, filePath.c_str())))
	{
		lua_getglobal(m_script, "movingObject");
		if (lua_istable(m_script, -1))
		{

			glm::vec2 pos;
			// get pos 
			lua_pushstring(m_script, "posX"); // get posX to top of the stack // now posX's index -1,table's index is -2
			lua_gettable(m_script, -2); // get posX from the table index -2 
			pos.x = lua_tonumber(m_script, -1); // get value at the top of the stack
			lua_pop(m_script, 1); // pop 1 at the top, now table back to index -1

			lua_pushstring(m_script, "posY");
			lua_gettable(m_script, -2);
			pos.y = lua_tonumber(m_script, -1);
			lua_pop(m_script, 1);


			// get animationPath
			std::string animationPath;
			lua_pushstring(m_script, "animationPath");
			lua_gettable(m_script, -2);
			animationPath = lua_tostring(m_script, -1);
			lua_pop(m_script, 1);

			glm::vec2 scale;
			// get scale 
			lua_pushstring(m_script, "scaleX");
			lua_gettable(m_script, -2);
			scale.x = lua_tonumber(m_script, -1);
			lua_pop(m_script, 1);

			lua_pushstring(m_script, "scaleY");
			lua_gettable(m_script, -2);
			scale.y = lua_tonumber(m_script, -1);
			lua_pop(m_script, 1);

			float depth;
			// get depth 
			lua_pushstring(m_script, "depth");
			lua_gettable(m_script, -2);
			depth = lua_tonumber(m_script, -1);
			lua_pop(m_script, 1);

			float angle;
			// get angle 
			lua_pushstring(m_script, "angle");
			lua_gettable(m_script, -2);
			angle = lua_tonumber(m_script, -1);
			lua_pop(m_script, 1);

			/* note : this version is to cause object init animation from file path, please add 
			 a copy version if you have time */
			// Feint~ 

			createBoss(pos, animationPath, scale, depth, angle);

		}
	}

	return false;
}

void F_Lua_Boss_Manager::draw(Feintgine::SpriteBatch & spriteBatch)
{
	for (size_t i = 0; i < m_luaBosses.size(); i++)
	{
		m_luaBosses[i]->draw(spriteBatch);
	}

	for(size_t i = 0 ; i < m_objects.size() ; i++)
	{
		m_objects[i]->draw(spriteBatch);
	}

	for (size_t i = 0; i < m_bullets.size(); i++)
	{
		m_bullets[i]->draw(spriteBatch);
	}
	// for(size_t i = 0 ; i < m_fl_object.size() ; i++)
	// {
	// 	m_fl_object[i]->draw(spriteBatch);
	// }

}

void F_Lua_Boss_Manager::init()
{

}

void F_Lua_Boss_Manager::callCreateFromLua(const std::string & filePath, const std::string & functionName)
{
	if (LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, filePath.c_str())))
	{
		lua_getglobal(m_script, functionName.c_str());// get the function name to the top of the stack
		if (lua_isfunction(m_script, -1))
		{
			//std::cout << "host is " << this << "\n";
			lua_pushlightuserdata(m_script, this);
			//std::cout << "C++ called " + functionName << "\n";
			if (LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, 1, 1, 0)))
			{
				//std::cout << "[C++] callCreateFromLua OK \n";

				//std::cout << "pointer of return value : \n";
				//F_LuaDynamicObject* object = (F_LuaDynamicObject*)lua_touserdata(m_script, -1);

			}


		}
	}
}

void F_Lua_Boss_Manager::standIdle(F_Lua_GenericObject * dynamicObject,
	float time, const std::string & animName, bool isOverRide /*= false*/)
{
	F_Lua_Boss_State * manipulator = new F_Lua_Boss_State();
	manipulator->standIdle(dynamicObject,time,animName,isOverRide);
	m_luaBossStates.push_back(manipulator);
}

void F_Lua_Boss_Manager::addEvent(F_Lua_GenericObject * dynamicObject, 
	const Feintgine::oEvent::f_callback & cb, double when)
{
	F_Lua_Boss_State * manipulator = new F_Lua_Boss_State();
	manipulator->addDelayedEvent(dynamicObject, cb, when);
	m_luaBossStates.push_back(manipulator);
}

void F_Lua_Boss_Manager::rw_addEvent_PE(F_Lua_GenericObject * dynamicObject,\
	const std::string & asset, float speed, float lifeTime,\
	int peType, float startRange, float rangeCover, float angleStep,\
	float startAngle, int petalCount, int interval, float rotation, int count, double time)
{


	F_Lua_Boss_State * manipulator = new F_Lua_Boss_State();
	manipulator->addDelayedEvent(dynamicObject, [=] {
	}, 0);



	float angle = 0;
	for (int i = 0; i < count; i++)
	{

		dynamicObject->addEvent([=]
		{
			  
			EnemyBulletBase * bullet = new EnemyBulletBase();
			bullet->m_lifeTime = lifeTime;
			float totalAngle = angle + rotation;
			float range1 = startRange *  sinCosCalCulator(peType,totalAngle * petalCount);
			float x = range1 * cos(totalAngle);
			float y = range1  * sin(totalAngle);
			glm::vec2 tVel = glm::vec2(x, y) * speed;
			bullet->setDirection(tVel);
			tVel = globalRotatePoint(tVel, rotation);
			bullet->setDirection(tVel);
			bullet->init(dynamicObject->getPos(), glm::vec2(1),
				Feintgine::SpriteManager::Instance()->getSprite(asset), tVel, nullptr, 5);
			dynamicObject->m_bullets.push_back(bullet);
		}, ENGINE_current_tick + Feintgine::F_oEvent::convertMSToS(time + (interval *i)) );

		angle += angleStep;

	}
		
	m_luaBossStates.push_back(manipulator);

		//std::cout << i << "\n";
		//
}

void F_Lua_Boss_Manager::rw_addEvent_T1(F_Lua_GenericObject * dynamicObject, const std::string & asset,
	float speed, float lifeTime,int arcType, float fA, float fB, float fC, float fD, float fR,
	float angleStep, float startAngle, float rotation, int interval, int count, double time)
{
	F_Lua_Boss_State * manipulator = new F_Lua_Boss_State();
	manipulator->addDelayedEvent(dynamicObject, [=] 
	{
	}, 0);

	//fR = fR * 0.01f;

	std::vector<float> factor;

	ArcFunction * arc = nullptr;
	switch (arcType)
	{
	case ArcType::arcHypocycloid:
		arc = new ArcFunction_hypocycloid();
		factor.push_back(fA);
		factor.push_back(fB);
		break;
	case ArcType::arcHypotrochoid:
		arc = new ArcFunction_hypotrochoid();
		factor.push_back(fA);
		factor.push_back(fB);
		factor.push_back(fC);
		break;
	case ArcType::arcFeintCustom1:
		arc = new ArcFunction_feint_custom1();
		factor.push_back(fA);
		factor.push_back(fB);
		factor.push_back(fC);
		break;
	case ArcType::arcFeintCustom2:
		arc = new ArcFunction_feint_custom2();
		factor.push_back(fA);
		factor.push_back(fB);
		factor.push_back(fC);
		factor.push_back(fD);
		break;
	case ArcType::arcEpicycloid:
		arc = new ArcFunction_Epicycloid();
		factor.push_back(fA);
		factor.push_back(fB);
		break;
	default:
		break;
	}
	if(arc)
	{
		arc->init(fR, factor);	
	}
	else
	{
		std::cout << "arc is null \n";
		return;
	}
	
	float angle = startAngle;
	
	for (int i = 0; i < count; i++)
	{

		dynamicObject->addEvent([=] 
		{

			EnemyBulletBase * bullet = new EnemyBulletBase();
			bullet->m_lifeTime = lifeTime;
			glm::vec2 tVel = globalRotatePoint(arc->getValue(angle), rotation);
			glm::vec2 vel = tVel * speed;
			bullet->init(dynamicObject->getPos(), glm::vec2(1),
				Feintgine::SpriteManager::Instance()->getSprite(asset), vel, nullptr, 5);
			dynamicObject->m_bullets.push_back(bullet);


		}, ENGINE_current_tick + Feintgine::F_oEvent::convertMSToS(time + (interval *i)));
		angle += angleStep;
	}
		

	m_luaBossStates.push_back(manipulator);
}


void F_Lua_Boss_Manager::rw_addEvent_MA_custom_aff(F_Lua_GenericObject * dynamicObject,
	const std::string & asset, float speed, float lifeTime, int k, int n, int n2,
	int l1, int l2, int posneg, float startAngle, float angleStep, float rotation, int interval, double time)
{
	F_Lua_Boss_State * manipulator = new F_Lua_Boss_State();
	manipulator->addDelayedEvent(dynamicObject, [=]
	{
	}, 0);

	//fR = fR * 0.01f;
	float angle = 0;
	f_angle = angle;
	for (int k = 0; k < 1; k++)
	{

		for (int t_l1 = 0; t_l1 < l1; t_l1++)
		{
			f_angle += angleStep;
			for (int t_l2 = 0; t_l2 < l2; t_l2++)
			{

				f_angle += angleStep;
				//f_angle = t_angle;
				for (int f = 0; f < n2; f++)
				{

					f_angle += angleStep;
					for (int c = 0; c < n; c++)
					{

						dynamicObject->addEvent([=]
						{
							EnemyBulletBase * bullet = new EnemyBulletBase();
							bullet->m_lifeTime = lifeTime;
							float x = cos(f_angle * posneg);
							float y = sin(f_angle * posneg);
							f_angle += degreeToRad((360 / n));


							glm::vec2 tVel = globalRotatePoint(glm::vec2(x, y), f_angle * posneg);

							glm::vec2 vel = tVel * speed;
							bullet->init(dynamicObject->getPos(), glm::vec2(1),
								Feintgine::SpriteManager::Instance()->getSprite(asset), vel, nullptr, 5);
							bullet->setDirection(tVel);

							m_bullets.push_back(bullet);
						}, ENGINE_current_tick + Feintgine::F_oEvent::convertMSToS(time + (interval * c)));

					}
					f_angle += angleStep;
				}
			}
		}
	}
	m_luaBossStates.push_back(manipulator);
}

void F_Lua_Boss_Manager::rw_addEvent_base(F_Lua_GenericObject * dynamicObject, const std::string & asset,
	float speed, float lifeTime, float x, float y, float currentAngle, double time)
{

	dynamicObject->addEvent([=]
	{
		EnemyBulletBase * bullet = new EnemyBulletBase();
		bullet->m_lifeTime = lifeTime;


		glm::vec2 tVel = globalRotatePoint(glm::vec2(x, y), f_angle ); // investigate this 
																	   // f_angle || currentAngle

		glm::vec2 vel = tVel * speed;
		bullet->init(dynamicObject->getPos(), glm::vec2(1),
			Feintgine::SpriteManager::Instance()->getSprite(asset), vel, nullptr, 5);
		bullet->setDirection(tVel);

		m_bullets.push_back(bullet);
	}, ENGINE_current_tick + Feintgine::F_oEvent::convertMSToS(time ));

}

void F_Lua_Boss_Manager::rw_addEvent_fire_komachi_coin(F_Lua_GenericObject * dynamicObject, const std::vector<std::string> & assets, int tier, float speed, float lifeTime, float x, float y, float currentAngle, double time)
{
	dynamicObject->addEvent([=]
	{
		EnemyBulletBase * bullet = new EnemyBullet_KomachiCoin();
		bullet->m_lifeTime = lifeTime;

		glm::vec2 tVel = globalRotatePoint(glm::vec2(x, y), f_angle ); // same thing with rw_addEvent_base                                                                                           
		glm::vec2 vel = tVel * speed;
		bullet->init(dynamicObject->getPos(), glm::vec2(1),
			Feintgine::SpriteManager::Instance()->getSprite(assets[tier]), vel, nullptr, 5);
		bullet->setDirection(tVel);
		EnemyBullet_KomachiCoin * casted_bullet = dynamic_cast<EnemyBullet_KomachiCoin*>(bullet);  
		dynamic_cast<EnemyBullet_KomachiCoin*>(bullet)->initTierSetting(assets);
		dynamic_cast<EnemyBullet_KomachiCoin*>(bullet)->setTier(tier);
		

		m_bullets.push_back(bullet);
	}, ENGINE_current_tick + Feintgine::F_oEvent::convertMSToS(time ));

}



void F_Lua_Boss_Manager::createHelper(F_Lua_GenericObject * dynamicObject,unsigned int id , const std::string & objectName,
	const std::string & asset, float x, float y, float scaleX, float scaleY, float depth,float velX, float velY,int afterImageCount, float afterImageRate, float scaleRate,double time)
{

	ObjectType type = m_objectMap.find(objectName)->second;
	switch (type)
	{
	case ObjectType::komachi_souls:
	{

		Feintgine::F_BaseObject * object =  new F_Komachi_Souls_Object();//new Feintgine::F_BaseObject();
		object->init(id,glm::vec2(scaleX, scaleY),asset,Feintgine::Color(255,255,255,255),glm::vec2(velX,velY),glm::vec2(x,y) , depth, afterImageCount,afterImageRate);
		object->setAfterImageScaleRate(scaleRate);
		dynamicObject->addEvent([=]
		{
			m_objects.push_back(object);
		}, ENGINE_current_tick + Feintgine::F_oEvent::convertMSToS(time));
	}
		break;
	default:
		break;
	}	
}

void F_Lua_Boss_Manager::callFunctionFromLua(const std::string functionName)
{

	lua_getglobal(m_script, functionName.c_str());// get the function name to the top of the stack
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
	
}

void F_Lua_Boss_Manager::resetEvent()
{
	//callFunctionFromLua("resetFunction");
	for (int i = 0; i < m_luaBossStates.size(); i++)
	{
		m_luaBossStates.erase(m_luaBossStates.begin() + i);
	}
	m_luaBossStates.clear();
	for (int i = 0; i < m_bullets.size(); i++)
	{
		m_bullets.erase(m_bullets.begin() + i);
	}
	m_bullets.clear();
	for (int i = 0; i < m_bullets.size(); i++)
	{
		m_bullets[i]->setLifeTime(0.0f);
		for (int i = 0; i < m_luaBosses.size(); i++)
		{
			m_luaBosses.erase(m_luaBosses.begin() + i);

		}
		//update(0.001f);
	}
	m_luaBosses.clear();

	callFunctionFromLua("CreateFromLua");
	
}

void F_Lua_Boss_Manager::clearBullets()
{
	for (int i = 0; i < m_bullets.size(); i++)
	{
		m_bullets.erase(m_bullets.begin() + i);
	}
	m_bullets.clear();
}
