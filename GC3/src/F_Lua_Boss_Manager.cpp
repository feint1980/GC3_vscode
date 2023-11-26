#include "F_Lua_Boss_Manager.h"
#include "EngineSetting.h"

int wrap_createDynamicObject(lua_State * L)
{
	if (lua_gettop(L) != 4)
	{
		return -1;
	}



}
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
		std::cout << "gettop failed \n";
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

	
	F_Lua_Boss * createdDynamicObj = object->createBoss(pos, animationPath, glm::vec2(scale), depth, angle);// createObject(pos, animationPath, 1, 15, 0);
																										   //moveOb
																										   //std::cout << "create object " << createdDynamicObj << "\n";
	lua_pushlightuserdata(L, createdDynamicObj);
	return 1; // no return needed
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
	F_Lua_Boss * dynamicObject = static_cast<F_Lua_Boss*>(lua_touserdata(L, 2));
	float x = lua_tonumber(L, 3);
	float y = lua_tonumber(L, 4);
	float time = lua_tonumber(L, 5);
	objectManager->MoveObject(dynamicObject, x, y, time);
	return 0;
}

int lua_HoldPosition(lua_State * L)
{
	if (lua_gettop(L) != 4)
	{
		std::cout << "bad gettop " << lua_gettop(L) << " \n";
		return -1;
	}

	F_Lua_Boss_Manager * objectManager = static_cast<F_Lua_Boss_Manager*>(lua_touserdata(L, 1));
	F_Lua_Boss * dynamicObject = static_cast<F_Lua_Boss*>(lua_touserdata(L, 2));
	float time = lua_tonumber(L, 3);
	std::string t_anim = lua_tostring(L, 4);
	//std::cout << "t_anim " << t_anim << "\n";
	objectManager->standIdle(dynamicObject,time,t_anim);

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
	F_Lua_Boss * dynamicObject = static_cast<F_Lua_Boss*>(lua_touserdata(L, 2)); // dynob
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
	if (lua_gettop(L) != 16)
	{
		std::cout << "bad gettop " << lua_gettop(L) << " \n";
		return -1;
	}
	//std::cout << "lua_AddEvent called \n";
	F_Lua_Boss_Manager * objectManager = static_cast<F_Lua_Boss_Manager*>(lua_touserdata(L, 1)); //host
	F_Lua_Boss * dynamicObject = static_cast<F_Lua_Boss*>(lua_touserdata(L, 2)); // dynob
	std::string asset = lua_tostring(L, 3); // asset
	float speed = lua_tonumber(L, 4); // speed
	float lifeTime = lua_tonumber(L, 5); // lifeTime
	int arcType = lua_tonumber(L, 6); // arcType
	float fA = lua_tonumber(L, 7); // a
	float fB = lua_tonumber(L, 8); // b
	float fC = lua_tonumber(L, 9); // c
	float fR = lua_tonumber(L, 10); // r
	float angleStep = lua_tonumber(L, 11); // angleStep 
	float startAngle = lua_tonumber(L, 12); //startAngle
	float rotation = lua_tonumber(L, 13); // rotation
	int interval = lua_tonumber(L, 14); // interval
	int count = lua_tonumber(L, 15); // count;
	double time = lua_tonumber(L, 16);

	fR = fR * 0.01f;

	int totalInterval = 0;
	objectManager->rw_addEvent_T1(dynamicObject, asset, speed, lifeTime, arcType, fA, fB, fC, fR,
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
	F_Lua_Boss * dynamicObject = static_cast<F_Lua_Boss*>(lua_touserdata(L, 2)); // dynob
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
	//	void rw_addEvent_base(F_Lua_Boss * dynamicObject, 
	//const std::string & asset, float speed, float lifeTime, 
	//float x, float y, float currentAngle, double time);
	F_Lua_Boss_Manager * objectManager = static_cast<F_Lua_Boss_Manager*>(lua_touserdata(L, 1)); //host
	F_Lua_Boss * dynamicObject = static_cast<F_Lua_Boss*>(lua_touserdata(L, 2)); // dynob
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


F_Lua_Boss_Manager::F_Lua_Boss_Manager()
{

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
	//std::cout << "called  F_Lua_Boss_Manager |||||||||||||||\n";
}


F_Lua_Boss_Manager::~F_Lua_Boss_Manager()
{
}



void F_Lua_Boss_Manager::update(float deltaTime)
{
	//std::cout << "update \n";
	for (auto i = 0; i < m_luaBosses.size(); i++)
	{
		if (m_luaBosses[i])
		{
			m_luaBosses[i]->update(deltaTime);
		}
	}
	for (auto i = 0; i < m_luaBossStates.size(); i++)
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
					F_Lua_Boss * object = m_luaBossStates[i]->m_luaBoss;
					//lua_pushlightuserdata(m_script, pThread);
					lua_pushlightuserdata(m_script, this); // host

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

void F_Lua_Boss_Manager::MoveObject(F_Lua_Boss * dynamicObject, float x, float y, float time)
{
 	F_Lua_Boss_State * manipulator = new F_Lua_Boss_State();
 	manipulator->moveObject(dynamicObject, glm::vec2(x, y), time);
 	m_luaBossStates.push_back(manipulator);
}

F_Lua_Boss * F_Lua_Boss_Manager::createBoss(const std::string & animationPath, glm::vec2 pos)
{
	std::cout << "createBoss 1 called \n";
	F_Lua_Boss * dynamicObject = new F_Lua_Boss();
	dynamicObject->createObject(pos, animationPath, glm::vec2(1), 15, 0);
	m_luaBosses.push_back(dynamicObject);
	return dynamicObject;
}

F_Lua_Boss * F_Lua_Boss_Manager::createBoss(const glm::vec2 & pos, const Feintgine::F_AnimatedObject & t_animation, const glm::vec2 & scale, float depth, float angle /*= 0.0f*/)
{
	std::cout << "createBoss 2 called \n";
	F_Lua_Boss * m_object = new F_Lua_Boss();
	m_object->createObject(pos, t_animation, scale, depth, angle);
	m_luaBosses.push_back(m_object);
	return m_object;
}

F_Lua_Boss * F_Lua_Boss_Manager::createBoss(const glm::vec2 & pos, const std::string & t_animationPath, const glm::vec2 & scale, float depth, float angle /*= 0.0f*/)
{
	std::cout << "createBoss 3 called \n";
	F_Lua_Boss * m_object = new F_Lua_Boss();
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
	for (int i = 0; i < m_luaBosses.size(); i++)
	{
		m_luaBosses[i]->draw(spriteBatch);
	}

	for (auto i = 0; i < m_bullets.size(); i++)
	{
		m_bullets[i]->draw(spriteBatch);
	}
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

void F_Lua_Boss_Manager::standIdle(F_Lua_Boss * dynamicObject,
	float time, const std::string & animName)
{
	F_Lua_Boss_State * manipulator = new F_Lua_Boss_State();
	manipulator->standIdle(dynamicObject,time,animName);
	m_luaBossStates.push_back(manipulator);
}

void F_Lua_Boss_Manager::addEvent(F_Lua_Boss * dynamicObject, 
	const Feintgine::oEvent::f_callback & cb, double when)
{
	F_Lua_Boss_State * manipulator = new F_Lua_Boss_State();
	manipulator->addDelayedEvent(dynamicObject, cb, when);
	m_luaBossStates.push_back(manipulator);
}

void F_Lua_Boss_Manager::rw_addEvent_PE(F_Lua_Boss * dynamicObject,\
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

void F_Lua_Boss_Manager::rw_addEvent_T1(F_Lua_Boss * dynamicObject, const std::string & asset,
	float speed, float lifeTime,int arcType, float fA, float fB, float fC, float fR,
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
	
	float angle = 0;
	
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


void F_Lua_Boss_Manager::rw_addEvent_MA_custom_aff(F_Lua_Boss * dynamicObject,
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

void F_Lua_Boss_Manager::rw_addEvent_base(F_Lua_Boss * dynamicObject, const std::string & asset,
	float speed, float lifeTime, float x, float y, float currentAngle, double time)
{

	dynamicObject->addEvent([=]
	{
		EnemyBulletBase * bullet = new EnemyBulletBase();
		bullet->m_lifeTime = lifeTime;


		glm::vec2 tVel = globalRotatePoint(glm::vec2(x, y), f_angle );

		glm::vec2 vel = tVel * speed;
		bullet->init(dynamicObject->getPos(), glm::vec2(1),
			Feintgine::SpriteManager::Instance()->getSprite(asset), vel, nullptr, 5);
		bullet->setDirection(tVel);

		m_bullets.push_back(bullet);
	}, ENGINE_current_tick + Feintgine::F_oEvent::convertMSToS(time ));

}

void F_Lua_Boss_Manager::callFunctionFromLua(const std::string functionName)
{

	lua_getglobal(m_script, functionName.c_str());// get the function name to the top of the stack
	if (lua_isfunction(m_script, -1))
	{
		//std::cout << "host is " << this << "\n";
		lua_pushlightuserdata(m_script, this);
		//std::cout << "C++ called " + functionName << "\n";
		if (LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, 1, 1, 0)))
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
			//m_luaBosses[i]->t_editor_reset();
			//m_luaBosses[i]->setPos(glm::vec2(0));
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
