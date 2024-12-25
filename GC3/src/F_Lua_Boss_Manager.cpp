#include "F_Lua_Boss_Manager.h"
#include "EngineSetting.h"

#pragma region lua_expose
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
	return 1.0; // 0 may cause error (it was intented to be wrong rather than error)
}
#pragma endregion

#pragma region lua_function

int lua_setObjectChargingEffect(lua_State * L)
{
	if(lua_gettop(L) != 8)
	{
		std::cout << "(lua_setChargingEffect) bad gettop " << lua_gettop(L) << " \n";
	}
	F_Lua_GenericObject * dynamicObject = static_cast<F_Lua_GenericObject *>(lua_touserdata(L, 1)); // dynob
	std::string tableName = lua_tostring(L, 2); // table name

	int type = lua_type(L,3);
	if(type != LUA_TTABLE)
	{
		std::cout << "lua_setObjectChargingEffect : arg 3 is not a table\n";
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
		}
		lua_pop(L,1);
	}
	lua_pop(L,1);

	std::vector<Feintgine::F_Sprite> tSprites;
	for (int i = 0; i < tAssets.size(); i++)
	{
		tSprites.emplace_back(Feintgine::SpriteManager::Instance()->getSprite(tAssets[i]));
	}
	float time = lua_tonumber(L,4);
	float radius = lua_tonumber(L,5);
	int maxCount = lua_tonumber(L,6);
	float minSpeed = lua_tonumber(L,7);
	float maxSpeed = lua_tonumber(L,8);	
	dynamicObject->setCharging(tSprites, time, radius, maxCount, minSpeed, maxSpeed);
	return 0;
}

int lua_CreateFromLua(lua_State * L)
{
	if (lua_gettop(L) != 7)
	{
		std::cout << "gettop failed (lua_CreateFromLua) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}
	glm::vec2 pos(0);
	F_Lua_Boss_Manager * object = static_cast<F_Lua_Boss_Manager*>(lua_touserdata(L, 1));
	std::string animationPath = lua_tostring(L, 2);
	float posX = (float)lua_tonumber(L, 3);
	float posY = (float)lua_tonumber(L, 4);
	pos = glm::vec2(posX, posY);
	float scale = (float)lua_tonumber(L, 5);
	int depth = (int)lua_tonumber(L, 6);
	float angle = (float)lua_tonumber(L, 7);

	F_Lua_GenericObject * createdDynamicObj = object->createBoss(pos, animationPath, glm::vec2(scale), depth, angle);

	lua_pushlightuserdata(L, createdDynamicObj);
	return 1; // this host function return 1 number 
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
	lua_pushnumber(L, pos.x);
	lua_pushnumber(L, pos.y);
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

int lua_playObjectAnimation(lua_State * L)
{
	if (lua_gettop(L) < 2 && lua_gettop(L) > 5)
	{
		std::cout << "(lua_playAnimation) bad gettop " << lua_gettop(L) << " \n";
	}
	F_Lua_GenericObject * dynamicObject = static_cast<F_Lua_GenericObject *>(lua_touserdata(L, 1)); // dynob
	std::string animationName = lua_tostring(L, 2);
	int loopTime = 0;
	bool isOverride = false;
	float playSpeed = 1.0f;
	if(lua_gettop(L) >= 3)
	{
		loopTime = lua_tonumber(L, 3);
	}
	if(lua_gettop(L) >= 4)
	{
		isOverride = lua_toboolean(L, 4);
	}
	if(lua_gettop(L) == 5)
	{
		playSpeed = lua_tonumber(L, 5);
	}
	dynamicObject->playAnimation(animationName, loopTime);
	dynamicObject->setAnimOverRide(isOverride);
	dynamicObject->setAnimationSpeed(playSpeed);

	return 0;
}

int lua_addBulletEvent(lua_State * L)
{
	if (lua_gettop(L) != 3)
	{
		std::cout << "bad gettop " << lua_gettop(L) << " \n";
		return -1;
	}
	F_Lua_Boss_Manager * object = static_cast<F_Lua_Boss_Manager*>(lua_touserdata(L, 1));
	int bulletId = (int)lua_tonumber(L, 2);
	std::string eventName = lua_tostring(L, 3); 
	object->addBulletEvent(bulletId, eventName);
	return 0;
}

int lua_removeFromLua(lua_State * L)
{
	if (lua_gettop(L) != 2)
	{
		std::cout << "bad gettop " << lua_gettop(L) << " \n";
		return -1;
	}
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
	if (lua_gettop(L) < 5 || lua_gettop(L) > 6)
	{
		std::cout << "bad gettop " << lua_gettop(L) << " \n";
		return -1;
	}
	F_Lua_Boss_Manager * objectManager = static_cast<F_Lua_Boss_Manager*>(lua_touserdata(L, 1));
	F_Lua_GenericObject * dynamicObject = static_cast<F_Lua_GenericObject *>(lua_touserdata(L, 2));
	float x = lua_tonumber(L, 3);
	float y = lua_tonumber(L, 4);
	float time = lua_tonumber(L, 5);

	bool isWait = true;
	if (lua_gettop(L) == 6)
	{
		isWait = lua_toboolean(L, 6);
	}

	if (isWait)
	{
		objectManager->MoveObject(dynamicObject, x, y, time);
	}
	else
	{
		objectManager->MoveObjectNonWait(dynamicObject, x, y, time);
	}
	
	return 0;
}

int lua_HoldPosition(lua_State * L)
{
	if (lua_gettop(L) < 4 || lua_gettop(L) > 6)
	{
		std::cout << "bad gettop " << lua_gettop(L) << " \n";
		return -1;
	}

	F_Lua_Boss_Manager * objectManager = static_cast<F_Lua_Boss_Manager*>(lua_touserdata(L, 1));
	F_Lua_GenericObject * dynamicObject = static_cast<F_Lua_GenericObject *>(lua_touserdata(L, 2));
	float time = lua_tonumber(L, 3);
	std::string t_anim = lua_tostring(L, 4);
	bool isOverRide = true;
	if(lua_gettop(L) >= 5)
	{
		isOverRide = lua_toboolean(L, 5);
	}
	bool isWait = true;
	if (lua_gettop(L) == 6)
	{
		isWait = lua_toboolean(L, 6);
	}
	if (isWait)
	{
		objectManager->standIdle(dynamicObject,time,t_anim,isOverRide);
	}
	else
	{
		objectManager->standIdleNonWait(dynamicObject, time, t_anim, isOverRide);
	}

	return 0;
}

#pragma endregion

#pragma region lua_fire

int lua_setFireTypePE(lua_State * L)
{
	if (lua_gettop(L) < 15 || lua_gettop(L) > 16)
	{
		std::cout << "bad gettop " << lua_gettop(L) << " \n";
		return -1;
	}
	F_Lua_Boss_Manager * objectManager = static_cast<F_Lua_Boss_Manager*>(lua_touserdata(L, 1)); //host
	F_Lua_GenericObject * dynamicObject = static_cast<F_Lua_GenericObject *>(lua_touserdata(L, 2)); // dynob
	std::string asset = lua_tostring(L, 3); // asset
	float speed = lua_tonumber(L, 4); // speed
	float lifeTime = lua_tonumber(L, 5); // lifeTime
	int peType = lua_tonumber(L, 6); // peType
	float startRange = lua_tonumber(L, 7); // startRange
	float rangeCover = lua_tonumber(L, 8); // rangeCover
	float angleStep = lua_tonumber(L, 9); // angleStep 
	float startAngle = lua_tonumber(L, 10); //startAngle
	int petalCount = lua_tonumber(L, 11); // petalCount
	int interval = lua_tonumber(L, 12); // interval
	float rotation = lua_tonumber(L, 13); // rotation
	int count = lua_tonumber(L, 14); // count;
	double time = lua_tonumber(L, 15);

	rotation = rotation / 57.2957795f;
	startAngle = startAngle / 57.2957795f;

	bool isWait = true;
	if (lua_gettop(L) == 16)
	{
		isWait = lua_toboolean(L, 16);
	}
	int totalInterval = 0;

	if (isWait)
	{
		objectManager->rw_addEvent_PE(dynamicObject, asset, speed, lifeTime, peType, startRange, rangeCover,
		angleStep, startAngle, petalCount, interval, rotation, count, time);
	}
	else
	{
		objectManager->rw_addEvent_PE_nonWait(dynamicObject, asset, speed, lifeTime, peType, startRange, rangeCover,
		angleStep, startAngle, petalCount, interval, rotation, count, time);
	}
	return 0;
}

int lua_addBulletManipulatorPatern(lua_State * L)
{
	if (lua_gettop(L) != 7)
	{
		std::cout << "(lua_addBulletManipulatorPatern) bad gettop " << lua_gettop(L) << " \n";
		return;
	}

	F_Lua_Boss_Manager * objectManager = static_cast<F_Lua_Boss_Manager*>(lua_touserdata(L, 1)); //host
	std::string xNodeEquation = lua_tostring(L, 2);
	std::string yNodeEquation = lua_tostring(L, 3);
	float radius = lua_tonumber(L, 4);
	std::string tableName = lua_tostring(L, 5); // table name

	int type = lua_type(L,6);
	if(type != LUA_TTABLE)
	{
		std::cout << "lua_setObjectChargingEffect : arg 3 is not a table\n";
	}

	lua_getglobal(L,tableName.c_str());
	lua_pushnil(L);
	std::vector<float> factors;
	while(lua_next(L,-2))
	{
		if(lua_isstring(L,-1))
		{
			factors.push_back(lua_tonumber(L,-1));
		}
		lua_pop(L,1);
		
	}
	lua_pop(L,1);
	int bulletID = lua_tonumber(L,6);
	objectManager->createPatern(xNodeEquation, yNodeEquation, radius, factors, bulletID);
	return 0;
}
int lua_setFireType1(lua_State * L)
{
	if (lua_gettop(L) < 17 || lua_gettop(L) > 20)
	{
		std::cout << "bad gettop " << lua_gettop(L) << " \n";
		return -1;
	}
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

	int id = 0;
	std::string eventName = "";
	if(lua_gettop(L) >= 18)
	{
		id = lua_tonumber(L, 18);
	}
	if(lua_gettop(L) >= 19)
	{
		eventName = lua_tostring(L, 19);
	}
	bool isWait = true;
	if(lua_gettop(L) == 20)
	{
		isWait = lua_toboolean(L, 20);
	}

	fR = fR * 0.01f;

	if(isWait)
	{
		objectManager->rw_addEvent_T1(dynamicObject, asset, speed, lifeTime, arcType, fA, fB, fC,fD, fR,
		angleStep, startAngle, rotation, interval, count, time, id, eventName);
	}
	else
	{
		objectManager->rw_addEvent_T1_nonWait(dynamicObject, asset, speed, lifeTime, arcType, fA, fB, fC,fD, fR,
		angleStep, startAngle, rotation, interval, count, time, id, eventName);
	}		
	return 0;
}

int lua_setFireMACustomAFF(lua_State * L)
{
	if (lua_gettop(L) <= 16 || lua_gettop(L) > 17)
	{
		std::cout << "bad gettop " << lua_gettop(L) << " \n";
		return -1;
	}
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

	bool isWait = true;
	if (lua_gettop(L) == 17)
	{
		isWait = lua_toboolean(L, 17);
	}
	if (isWait)
	{
		objectManager->rw_addEvent_MA_custom_aff(dynamicObject, asset, speed, lifeTime, k, n, n2, l1, l2, posneg,
		startAngle, angleStep, rotation, interval, time);
	}
	else
	{
		objectManager->rw_addEvent_MA_custom_aff_nonWait(dynamicObject, asset, speed, lifeTime, k, n, n2, l1, l2, posneg,
		startAngle, angleStep, rotation, interval, time);
	}
	return 0;
}

int lua_setFireBase(lua_State * L)
{
	if (lua_gettop(L) < 9 || lua_gettop(L) > 11)
	{
		std::cout << "bad gettop " << lua_gettop(L) << " \n";
		return -1;
	}
	F_Lua_Boss_Manager * objectManager = static_cast<F_Lua_Boss_Manager*>(lua_touserdata(L, 1)); //host
	F_Lua_GenericObject * dynamicObject = static_cast<F_Lua_GenericObject *>(lua_touserdata(L, 2)); // dynob
	std::string asset = lua_tostring(L, 3); // 
	float speed = lua_tonumber(L, 4); // 
	float lifeTime = lua_tonumber(L, 5); // 
	float x = lua_tonumber(L, 6); // 
	float y = lua_tonumber(L, 7); // 
	float currentAngle = lua_tonumber(L, 8); // 
	double time = lua_tonumber(L, 9); // 
	
	int id = 0;
	std::string eventName = "";
	if(lua_gettop(L) >= 10)
	{
		id = lua_tonumber(L, 10);
	}

	if(lua_gettop(L) == 11)
	{
		eventName = lua_tostring(L, 11);
	}
	objectManager->rw_addEvent_base(dynamicObject, asset, speed, lifeTime, x, y, currentAngle, time, id, eventName);
	return 0;
}

int lua_setKomachiCoin(lua_State * L)
{
	if (lua_gettop(L) != 11)
	{
		std::cout << "bad gettop " << lua_gettop(L) << " \n";
		return -1;
	}
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
		}
		lua_pop(L,1);
	}
	lua_pop(L,1);
	int tier = lua_tonumber(L,5);
	float speed = lua_tonumber(L, 6); // 
	float lifeTime = lua_tonumber(L, 7); // 
	float x = lua_tonumber(L, 8); // 
	float y = lua_tonumber(L, 9); // 
	float currentAngle = lua_tonumber(L, 10); // 
	double time = lua_tonumber(L, 11); // 

	objectManager->rw_addEvent_fire_komachi_coin(dynamicObject,tAssets,tier,speed,lifeTime,x,y,currentAngle,time);

	return 0;
}
#pragma endregion

#pragma region lua_helpers
int lua_createHelper(lua_State * L)
{
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

int lua_Komachi_summon_pillar(lua_State * L)
{
	if(lua_gettop(L) != 12)
	{
		std::cout << "bad gettop " << lua_gettop(L) << " \n";
		return -1;
	}

	F_Lua_Boss_Manager * objectManager = static_cast<F_Lua_Boss_Manager*>(lua_touserdata(L, 1)); //host
	F_Lua_GenericObject * dynamicObject = static_cast<F_Lua_GenericObject *>(lua_touserdata(L, 2)); // dynob
	std::string asset1 = lua_tostring(L, 3); //
	std::string asset2 = lua_tostring(L, 4); //
	float x = lua_tonumber(L, 5); //
	float y = lua_tonumber(L, 6); //
	float dimX = lua_tonumber(L, 7); //
	float dimY = lua_tonumber(L, 8); //
	float r = lua_tonumber(L, 9); //
	float g = lua_tonumber(L, 10); //
	float b = lua_tonumber(L, 11); //
	float a = lua_tonumber(L, 12); //

	F_Komachi_pillar * pillar = objectManager->createPillar(asset1, asset2,glm::vec2(x,y), glm::vec2(dimX, dimY),Feintgine::Color(r, g, b, a));

	lua_pushlightuserdata(L, pillar);
	return 1; // return 1 value (pillar) 
}

int lua_Komachi_pillar_expand(lua_State * L)
{
	if(lua_gettop(L) != 4)
	{
		std::cout << "bad gettop " << lua_gettop(L) << " \n";
		return -1;
	}
	F_Komachi_pillar * pillar = static_cast<F_Komachi_pillar *>(lua_touserdata(L, 1)); // pillar
	float dimX = lua_tonumber(L, 2); //
	float dimY = lua_tonumber(L, 3); //
	float time = lua_tonumber(L, 4); //
	pillar->setExpand(glm::vec2(dimX, dimY), time);
	return 0;
}

int lua_Komachi_pillar_setLightEffect(lua_State * L)
{
	if (lua_gettop(L) != 9)
	{
		std::cout << "(lua_Komachi_pillar_setLightEffect) bad gettop " << lua_gettop(L) << " \n";
		return;
	}

	F_Komachi_pillar * pillar = static_cast<F_Komachi_pillar *>(lua_touserdata(L, 1)); // pillar
	float colorR = lua_tonumber(L, 2); //
	float colorG = lua_tonumber(L, 3); //
	float colorB = lua_tonumber(L, 4); //
	float colorA = lua_tonumber(L, 5); //
	float attentionuaX = lua_tonumber(L, 6); //
	float attentionuaY = lua_tonumber(L, 7); //
	float attentionuaZ = lua_tonumber(L, 8); //
	float time = lua_tonumber(L, 9); //
	std::cout << "set light \n";
	pillar->setLight(glm::vec4(colorR, colorG, colorB, colorA), glm::vec3(attentionuaX, attentionuaY, attentionuaZ), time);
	return 0;
}

int lua_Komachi_pillar_setLightAttenuation(lua_State * L)
{
	if (lua_gettop(L) != 5)
	{
		std::cout << "(lua_Komachi_pillar_setLightAttenuation) bad gettop " << lua_gettop(L) << " \n";
		return;
	}

	F_Komachi_pillar * pillar = static_cast<F_Komachi_pillar *>(lua_touserdata(L, 1)); // pillar
	float attentionuaX = lua_tonumber(L, 2); //
	float attentionuaY = lua_tonumber(L, 3); //
	float attentionuaZ = lua_tonumber(L, 4); //
	float time = lua_tonumber(L, 5); //
	pillar->setLightAttenuationTarget(glm::vec3(attentionuaX, attentionuaY, attentionuaZ), time);
	return 0;
}

int lua_Komachi_pillar_setLightColor(lua_State * L)
{
	if (lua_gettop(L) != 6)
	{
		std::cout << "(lua_Komachi_pillar_setLightAttenuation) bad gettop " << lua_gettop(L) << " \n";
		return;
	}

	F_Komachi_pillar * pillar = static_cast<F_Komachi_pillar *>(lua_touserdata(L, 1)); // pillar
	float colorR = lua_tonumber(L, 2); //
	float colorG = lua_tonumber(L, 3); //
	float colorB = lua_tonumber(L, 4); //
	float colorA = lua_tonumber(L, 5); //
	float time = lua_tonumber(L, 6); //
	pillar->setLightColorTarget(glm::vec4(colorR, colorG, colorB, colorA), time);
	return 0;
}

int lua_Komachi_pillar_setFlashEffect(lua_State * L)
{
	if (lua_gettop(L) != 3)
	{
		std::cout << "bad gettop " << lua_gettop(L) << " \n";
		return -1;
	}

	F_Komachi_pillar * pillar = static_cast<F_Komachi_pillar *>(lua_touserdata(L, 1)); // pillar
	float time = lua_tonumber(L, 2); //
	float freq = lua_tonumber(L, 3); //
	pillar->setFlash(time, freq);

	return 0;
}

int lua_Komachi_pillar_setColor(lua_State * L)
{
	if (lua_gettop(L) != 6)
	{
		std::cout << "bad gettop " << lua_gettop(L) << " \n";
		return -1;
	}
	F_Komachi_pillar * pillar = static_cast<F_Komachi_pillar *>(lua_touserdata(L, 1)); // pillar
	float r = lua_tonumber(L, 2); //
	float g = lua_tonumber(L, 3); //
	float b = lua_tonumber(L, 4); //
	float a = lua_tonumber(L, 5); //
	float time = lua_tonumber(L, 6); //
	pillar->setColorChange(Feintgine::Color(r, g, b, a), time);
	return 0;
}

int lua_Komachi_pillar_move(lua_State * L)
{
	if(lua_gettop(L) != 4)
	{
		std::cout << "bad gettop " << lua_gettop(L) << " \n";
		return -1;
	}
	F_Komachi_pillar * pillar = static_cast<F_Komachi_pillar *>(lua_touserdata(L, 1)); // pillar
	float x = lua_tonumber(L, 2); //
	float y = lua_tonumber(L, 3); //
	float time = lua_tonumber(L, 4); //
	pillar->setMove(glm::vec2(x, y), time);
	return 0;
}
#pragma endregion

#pragma region CPP_lua_e
F_Lua_Boss_Manager::F_Lua_Boss_Manager()
{
	loadTextures();
	// Init Map 
	m_objectMap.insert(std::make_pair("komachi_souls", ObjectType::komachi_souls));

	m_script = luaL_newstate();
	luaL_openlibs(m_script);

	// lua register 1 ( lua state ) , 2 name will be called in lua, 3 the pointer to function
	lua_register(m_script, "cppCreateFromLua", lua_CreateFromLua);
	lua_register(m_script, "cppMoveObject", lua_MoveObject);
	lua_register(m_script, "cppHoldPosition", lua_HoldPosition);
	lua_register(m_script, "cppCreateHelper", lua_createHelper); // this is unused, no wrapper 
	lua_register(m_script, "cppRemoveFromLua", lua_removeFromLua);
	lua_register(m_script, "cppSetAfterImage", lua_setAfterImage);
	lua_register(m_script, "cppGetObjectPos", lua_getObjectPos);
	lua_register(m_script, "cppSetObjectVel", lua_setObjectVel);
	lua_register(m_script, "cppGetObjectAngle", lua_getObjectAngle);
	lua_register(m_script, "cppWaitFor", lua_waitFor);
	lua_register(m_script, "cppObjectPlayAnimation", lua_playObjectAnimation);
	lua_register(m_script, "cppObjectSetChargingEffect", lua_setObjectChargingEffect);
	
	// fire bullets
	lua_register(m_script, "cppSetFire_Type1", lua_setFireType1);
	lua_register(m_script, "cppSetFire_TypePE", lua_setFireTypePE);
	lua_register(m_script, "cppSetFire_MA_custom_aff", lua_setFireMACustomAFF);
	lua_register(m_script, "cppSetFire_Base", lua_setFireBase);
	lua_register(m_script, "cppSetFire_KomachiCoin",lua_setKomachiCoin);
	lua_register(m_script, "cppSetBulletEvent", lua_addBulletEvent);
	lua_register(m_script, "cppAddBulletManipulatorPatern", lua_addBulletManipulatorPatern);

	//std::cout << "called  F_Lua_Boss_Manager |||||||||||||||\n";
	// Komachi's helper start
	lua_register(m_script, "cppKomachi_summon_pillar", lua_Komachi_summon_pillar);
	lua_register(m_script, "cppKomachi_pillar_expand", lua_Komachi_pillar_expand);
	lua_register(m_script, "cppKomachi_pillar_move", lua_Komachi_pillar_move);
	lua_register(m_script, "cppKomachi_pillar_setColor", lua_Komachi_pillar_setColor);
	lua_register(m_script, "cppKomachi_pillar_setFlashEffect", lua_Komachi_pillar_setFlashEffect);
	lua_register(m_script, "cppKomachi_pillar_setLightEffect", 
	lua_Komachi_pillar_setLightEffect);
	lua_register(m_script, "cppKomachi_pillar_setLightAttenuation", 
	lua_Komachi_pillar_setLightAttenuation);
	// declare cppKomachi_pillar_setLightColor
	lua_register(m_script, "cppKomachi_pillar_setLightColor", 
	lua_Komachi_pillar_setLightColor);

	// Komachi's helper end	
	bulletManipulator.init(&m_bullets);
}

#pragma endregion

F_Lua_Boss_Manager::~F_Lua_Boss_Manager()
{

}
void F_Lua_Boss_Manager::addBulletEvent(int bulletID, const std::string & eventName)
{
	for(auto i = 0 ;i < m_bullets.size() ;i++)
	{
		if(m_bullets[i]->getSpecialID() == bulletID)
		{
			m_bullets[i]->loadEvent(eventName);
		}
	}
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

F_Komachi_pillar * F_Lua_Boss_Manager::createPillar(const std::string & texturePath1, const std::string & texturePath2, const glm::vec2 & pos, const glm::vec2 & dim, const Feintgine::Color & color)
{
	F_Komachi_pillar * pillar = new F_Komachi_pillar();
	pillar->init(Feintgine::ResourceManager::getTexture(texturePath1) , Feintgine::ResourceManager::getTexture(texturePath2), pos, dim, color);

	pillar->spawn(pos, dim, color);
	m_komachiPillars.push_back(pillar);
	return pillar;
}

void F_Lua_Boss_Manager::update(float deltaTime)
{
	bulletManipulator.update(deltaTime);
	for (size_t i = 0; i < m_luaBosses.size(); i++)
	{
		if (m_luaBosses[i])
		{
			m_luaBosses[i]->update(deltaTime);
		}
	}
	
	for(int i = 0; i < m_komachiPillars.size(); i++)
	{
		if(m_komachiPillars[i])
		{
			m_komachiPillars[i]->update(deltaTime);
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
				lua_getglobal(m_script, "IssueNextTask");
				if (lua_isfunction(m_script, -1))
				{
					F_Lua_GenericObject * object = m_luaBossStates[i]->m_luaBoss;
					lua_pushlightuserdata(m_script, this); // host, yes, "this" is the host
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
	for (size_t i = 0; i < m_nonWaitLuaBossStates.size(); i++)
	{
		if (m_nonWaitLuaBossStates[i])
		{
			if (m_nonWaitLuaBossStates[i]->update(deltaTime))
			{		
				// this update will not call next task after done
				m_nonWaitLuaBossStates.erase(m_nonWaitLuaBossStates.begin() + i);
			}
		}
	}
	for (int i = 0; i < m_luaBosses.size(); i++)
	{
		if (m_luaBosses[i]->m_bullets.size() > 0)
		{
			for (int c = 0; c < m_luaBosses[i]->m_bullets.size(); c++)
			{
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

void F_Lua_Boss_Manager::MoveObjectNonWait(F_Lua_GenericObject * dynamicObject, float x, float y, float time)
{
 	F_Lua_Boss_State * manipulator = new F_Lua_Boss_State();
	manipulator->moveObject(dynamicObject, glm::vec2(x, y), time);
	m_nonWaitLuaBossStates.push_back(manipulator);
}
void F_Lua_Boss_Manager::waitFor(F_Lua_GenericObject * dynamicObject, float time)
{
	F_Lua_Boss_State * manipulator = new F_Lua_Boss_State();
	manipulator->waitFor(dynamicObject, time);
	m_luaBossStates.push_back(manipulator);
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

void F_Lua_Boss_Manager::loadTextures()
{
	Feintgine::ResourceManager::getTexture("Textures/pillar_1.png");
	Feintgine::ResourceManager::getTexture("Textures/pillar_2.png");
	
}

void F_Lua_Boss_Manager::drawLight(Feintgine::LightBatch & lightBatch)
{
	m_player.drawLight(lightBatch);
}
void F_Lua_Boss_Manager::drawLight2(Feintgine::LightBatch & lightBatch)
{
	m_player2.drawLight(lightBatch);
}

void F_Lua_Boss_Manager::drawBossesLight(Feintgine::LightBatch & lightBatch)
{
	m_particleEngine.drawLight(lightBatch);	
	for(int i = 0; i < m_komachiPillars.size(); i++)
	{
		m_komachiPillars[i]->drawLight(lightBatch);
	}
}

void F_Lua_Boss_Manager::handleInput(Feintgine::InputManager & inputManager)
{
	m_player2.handleInput(inputManager);
	m_player.handleInput(inputManager);
}

void F_Lua_Boss_Manager::drawPlayer(Feintgine::SpriteBatch & spriteBatch)
{	
	m_player.draw(spriteBatch);
	
	m_kanjiEffectManager->draw(spriteBatch);
	for (int i = 0; i < m_exlosions.size(); i++)
	{
		m_exlosions[i].draw(spriteBatch);
	}
}

void F_Lua_Boss_Manager::drawPlayer2(Feintgine::SpriteBatch & spriteBatch)
{
	m_player2.draw(spriteBatch);
	m_kanjiEffectManager->draw(spriteBatch);
	for (int i = 0; i < m_exlosions.size(); i++)
	{
		m_exlosions[i].draw(spriteBatch);
	}
}

void F_Lua_Boss_Manager::createPatern(const std::string & xNodeEquation, const std::string & yNodeEquation, float radius, const std::vector<float> & factors, int bulletID)
{
	PaternBehavior_from_lua * pat;
	pat = new PaternBehavior_from_lua();
	pat->setFactor(factors);
	pat->setRadius(radius);
	pat->create(xNodeEquation, yNodeEquation, radius);
	pat->setRate(0.001f);
	bulletManipulator.addPatern(pat,bulletID);
}

void F_Lua_Boss_Manager::updatePlayer(float deltaTime, std::vector<FairyBase *>  enemy,
	std::vector<EnemyBulletBase * > bullets)
{
	m_player.update(deltaTime,enemy,m_bullets);
	m_particleEngine.update(deltaTime);
	m_kanjiEffectManager->update(deltaTime);
	for (int i = 0; i < m_exlosions.size(); i++)
	{
		m_exlosions[i].update(deltaTime);
	}
}

void F_Lua_Boss_Manager::updatePlayer2(float deltaTime, std::vector<FairyBase *>  enemy,
	std::vector<EnemyBulletBase * > bullets)
{
	m_player2.update(deltaTime,enemy,m_bullets);
	m_particleEngine.update(deltaTime);
	m_kanjiEffectManager->update(deltaTime);
	for (int i = 0; i < m_exlosions.size(); i++)
	{
		m_exlosions[i].update(deltaTime);
	}
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

	for(int i = 0; i < m_komachiPillars.size(); i++)
	{
		if(m_komachiPillars[i])
		{
			m_komachiPillars[i]->draw(spriteBatch);
		}
	}
}

void F_Lua_Boss_Manager::drawPlayerSpellcard(Feintgine::SpriteBatch & spriteBatch)
{
	m_player.drawSpellSelector(spriteBatch);
}

void F_Lua_Boss_Manager::drawPlayerSpellcard2(Feintgine::SpriteBatch & spriteBatch)
{
	m_player2.drawSpellSelector(spriteBatch);
}

void F_Lua_Boss_Manager::reloadPlayer(int val)
{
	// unused
}

void F_Lua_Boss_Manager::addExplosion(const Feintgine::F_Sprite & sprite, const glm::vec2 & pos, const glm::vec2 & scale, const glm::vec2 & explosionRate, const Feintgine::Color & color, float depth, float liveRate /*= 0.1f*/)
{
	m_exlosions.emplace_back(sprite, pos, scale, explosionRate, color, depth, liveRate);
}

void F_Lua_Boss_Manager::initPlayer(int val, Feintgine::AudioEngine * audioEngine, KanjiEffectManager * kanjiEffectManager,Feintgine::Camera2D * cam,Feintgine::EffectBatch * effectBatch)
{
	m_player.setCharacterSpell(1);
	m_player.init("Assets/F_AObjects/reimu.xml", "character/reimu_accessory_3.png",false);
	m_player.setPrimaryShot(true, "Assets/F_AObjects/reimu_normal_projectile.xml", 5.0f, 90.0f);
	m_player.setAccessoryShot(0);
	m_player.setDeathCallback([&] {
		addExplosion(
			Feintgine::SpriteManager::Instance()->getSprite("projectile/death_anim_2.png"),
			m_player.getPos(), glm::vec2(1), glm::vec2(0.56), Feintgine::Color(255, 255, 255, 255), 4, 0.02f);
	});	
	m_player.registerExplosionRing(&m_exlosions);

	//std::cout << "incoming register logic camera " << cam << "\n";
	m_player.registerLogicCamera(cam);
	m_player.registerKanjiEffect(kanjiEffectManager);

	m_player.registerAudioEngine(audioEngine);
	m_player.initSound();
	m_kanjiEffectManager = kanjiEffectManager;	
	m_player.setPos(glm::vec2(25, -100));
	m_player.reset();

	m_player.registerEffectBatch(effectBatch);
	m_player.setSpellSelectorPos(glm::vec2(330, 0));
	m_particleEngine.addParticleBatch(m_player.getHitParticle());
	m_particleEngine.addParticleBatch(m_player.getLeftAccessosry().getParticleBatch());
	m_particleEngine.addParticleBatch(m_player.getRightAccesory().getParticleBatch());

	m_player2.setCharacterSpell(2);
	m_player2.init("Assets/F_AObjects/Marisa_own.xml", "character/marisa_accessory_3.png",true);
	m_player2.setPrimaryShot(true, "Assets/F_AObjects/marisa_normal_projectile.xml", 5.0f, 90.0f);
	m_player2.setAccessoryShot(4);

	m_player2.setDeathCallback([&] {
		addExplosion(
			Feintgine::SpriteManager::Instance()->getSprite("projectile/death_anim_2.png"),
			m_player2.getPos(), glm::vec2(1), glm::vec2(0.56), Feintgine::Color(255, 255, 255, 255), 4, 0.02f);
	});	
	m_player2.registerExplosionRing(&m_exlosions);

	//std::cout << "incoming register logic camera " << cam << "\n";
	m_player2.registerLogicCamera(cam);
	m_player2.registerKanjiEffect(kanjiEffectManager);

	m_player2.registerAudioEngine(audioEngine);
	m_player2.initSound();
	m_kanjiEffectManager = kanjiEffectManager;
	m_player2.setPos(glm::vec2(25, -100));
	m_player2.reset();
	m_player2.registerEffectBatch(effectBatch);
	m_player2.setSpellSelectorPos(glm::vec2(330, 0));
	m_particleEngine.addParticleBatch(m_player2.getHitParticle());
	m_particleEngine.addParticleBatch(m_player2.getLeftAccessosry().getParticleBatch());
	m_particleEngine.addParticleBatch(m_player2.getRightAccesory().getParticleBatch());

}

void F_Lua_Boss_Manager::drawParticle(Feintgine::SpriteBatch * spriteBatch)
{
	m_particleEngine.draw(spriteBatch);
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
			lua_pushlightuserdata(m_script, this);
			if (LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, 1, 1, 0)))
			{
				// a print to check if function called
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

void F_Lua_Boss_Manager::standIdleNonWait(F_Lua_GenericObject * dynamicObject, float time, const std::string & animName, bool isOverRide /*= false*/)
{
	F_Lua_Boss_State * manipulator = new F_Lua_Boss_State();
	manipulator->standIdle(dynamicObject, time, animName, isOverRide);
	m_nonWaitLuaBossStates.push_back(manipulator);

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

}
void F_Lua_Boss_Manager::rw_addEvent_PE_nonWait(F_Lua_GenericObject * dynamicObject,\
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
	m_nonWaitLuaBossStates.push_back(manipulator);

}

void F_Lua_Boss_Manager::rw_addEvent_T1(F_Lua_GenericObject * dynamicObject, const std::string & asset,
	float speed, float lifeTime,int arcType, float fA, float fB, float fC, float fD, float fR, float angleStep, float startAngle, float rotation, int interval, int count, double time,int id /*= 0*/, const std::string & eventName /*= ""*/)
{
	F_Lua_Boss_State * manipulator = new F_Lua_Boss_State();
	manipulator->addDelayedEvent(dynamicObject, [=] 
	{
	}, 0);

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
			bullet->setSpecialID(id);
			if(eventName != "")
			{
				bullet->loadEvent(eventName);
			}
			dynamicObject->m_bullets.push_back(bullet);
		}, ENGINE_current_tick + Feintgine::F_oEvent::convertMSToS(time + (interval *i)));
		angle += angleStep;
	}
	m_luaBossStates.push_back(manipulator);
}

void F_Lua_Boss_Manager::rw_addEvent_T1_nonWait(F_Lua_GenericObject * dynamicObject, const std::string & asset,
	float speed, float lifeTime,int arcType, float fA, float fB, float fC, float fD, float fR, float angleStep, float startAngle, float rotation, int interval, int count, double time,int id /*= 0*/, const std::string & eventName /*= ""*/)
{
	F_Lua_Boss_State * manipulator = new F_Lua_Boss_State();
	manipulator->addDelayedEvent(dynamicObject, [=] 
	{
	}, 0);

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
			bullet->setSpecialID(id);
			if(eventName != "")
			{
				bullet->loadEvent(eventName);
			}
			dynamicObject->m_bullets.push_back(bullet);
		}, ENGINE_current_tick + Feintgine::F_oEvent::convertMSToS(time + (interval *i)));
		angle += angleStep;
	}
	m_nonWaitLuaBossStates.push_back(manipulator);
}

void F_Lua_Boss_Manager::rw_addEvent_MA_custom_aff(F_Lua_GenericObject * dynamicObject,
	const std::string & asset, float speed, float lifeTime, int k, int n, int n2,
	int l1, int l2, int posneg, float startAngle, float angleStep, float rotation, int interval, double time)
{
	F_Lua_Boss_State * manipulator = new F_Lua_Boss_State();
	manipulator->addDelayedEvent(dynamicObject, [=]
	{
	}, 0);
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

void F_Lua_Boss_Manager::rw_addEvent_MA_custom_aff_nonWait(F_Lua_GenericObject * dynamicObject,
	const std::string & asset, float speed, float lifeTime, int k, int n, int n2,
	int l1, int l2, int posneg, float startAngle, float angleStep, float rotation, int interval, double time)
{
	F_Lua_Boss_State * manipulator = new F_Lua_Boss_State();
	manipulator->addDelayedEvent(dynamicObject, [=]
	{
	}, 0);
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
	m_nonWaitLuaBossStates.push_back(manipulator);
}

void F_Lua_Boss_Manager::rw_addEvent_base(F_Lua_GenericObject * dynamicObject, const std::string & asset,
	float speed, float lifeTime, float x, float y, float currentAngle, double time,int id , const std::string & eventName )
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
		bullet->setSpecialID(id);
		if(eventName != "")
		{
			bullet->loadEvent(eventName);
		}
		m_bullets.push_back(bullet);
	}, ENGINE_current_tick + Feintgine::F_oEvent::convertMSToS(time ));
}

void F_Lua_Boss_Manager::rw_addEvent_fire_komachi_coin(F_Lua_GenericObject * dynamicObject, const std::vector<std::string> & assets, int tier, float speed, float lifeTime, float x, float y, float currentAngle, double time)
{
	dynamicObject->addEvent([=]
	{
		EnemyBulletBase * bullet = new EnemyBullet_KomachiCoin();
		bullet->m_lifeTime = lifeTime;
		glm::vec2 tVel = globalRotatePoint(glm::vec2(x, y), f_angle );
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

Feintgine::F_BaseObject * F_Lua_Boss_Manager::createHelper(F_Lua_GenericObject * dynamicObject,unsigned int id , const std::string & objectName,
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
		return object;
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
		lua_pushlightuserdata(m_script, this);
		const int argCount = 1;
		const int returnCount =1;
		if (LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, argCount, returnCount, 0)))
		{
			// safe check
		}
	}	
}

void F_Lua_Boss_Manager::resetEvent()
{
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

	for (int i = 0; i < m_komachiPillars.size(); i++)
	{
		m_komachiPillars.erase(m_komachiPillars.begin() + i);
	}
	m_komachiPillars.clear();
}
