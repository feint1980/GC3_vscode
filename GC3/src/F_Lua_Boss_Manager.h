#pragma once
#include <F_LuaObjectManager.h>
#include "F_Lua_Boss.h"
#include "F_Lua_Boss_State.h"
#include "F_Lua_Boss_State_MoveObject.h"
#include "ArcFunction_hypocycloid.h"
#include "ArcFunction_hypotrochoid.h"
#include "ArcFunction_feint_custom1.h"
#include "ArcFunction_feint_custom2.h"

#include <F_BaseObject.h>
#include "F_Komachi_Souls_Object.h"





enum ArcType
{
	arcHypocycloid = 1,
	arcHypotrochoid = 2,
	arcFeintCustom1 = 3,
	arcFeintCustom2 = 4,
};

enum ObjectType
{
	komachi_souls = 1,
};


class F_Lua_Boss_Manager //: public Feintgine::F_LuaObjectManager
{
public:
	 F_Lua_Boss_Manager();
	~F_Lua_Boss_Manager();

	void init();

	void update(float deltaTime);

	void MoveObject(F_Lua_Boss * dynamicObject, float x, float y, float time);

	void standIdle(F_Lua_Boss * dynamicObject, float time, const std::string & animName);


	void resetEvent();

	void clearBullets();

	void rw_addEvent_PE(F_Lua_Boss * dynamicObject, const std::string & asset, float speed, float lifeTime, \
		int peType, float startRange, float rangeCover, float angleStep, float startAngle, int petalCount, int interval, float rotation, int count, double time);

	void rw_addEvent_T1(F_Lua_Boss  * dynamicObject, const std::string & asset, float speed, float lifeTime, \
		int arcType, float fA, float fB, float fC, float fD,float fR, float angleStep, float startAngle, float rotation, int interval, int count, double time);
	
	void rw_addEvent_MA_custom_aff(F_Lua_Boss * dynamicObject, const std::string & asset, float speed,
		float lifeTime, int k, int n, int n2, int l1, int l2,int posneg, float startAngle, 
		float angleStep, float rotation, int interval, double time);

	void rw_addEvent_base(F_Lua_Boss * dynamicObject, const std::string & asset, float speed, float lifeTime, float x, float y, float currentAngle, double time);

	void createObject(F_Lua_Boss * dynamicObject, const std::string & objectName,
	const std::string & asset, float x, float y, float scaleX, float scaleY, float depth,float velX, float velY,int afterImageCount, float afterImageRate, double time);

	void addEvent(F_Lua_Boss * dynamicObject, const Feintgine::oEvent::f_callback & cb, double when);

	F_Lua_Boss * createBoss(const std::string & animationPath, glm::vec2 pos);

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void callCreateFromLua(const std::string & filePath, const std::string & functionName);

	void callFunctionFromLua(const std::string functionName);

	bool loadLuaFile(const std::string & filePath);


	void clearBosses();

	F_Lua_Boss * createBoss(const glm::vec2 & pos,
		const Feintgine::F_AnimatedObject & t_animation,
		const glm::vec2 & scale, float depth, float angle = 0.0f);

	F_Lua_Boss * createBoss(const glm::vec2 & pos,
		const std::string & t_animationPath,
		const glm::vec2 & scale, float depth, float angle = 0.0f);

	int getTotalBullets() const { return m_bullets.size(); }

protected:

	std::vector<EnemyBulletBase *> m_bullets;

	//std::vector<F_Lua_Boss_State *> m_manipulators;
	std::vector<F_Lua_Boss_State *> m_luaBossStates;
	lua_State * m_script;
	//std::vector<F_Lua_Boss *> m_dynamicObjects;
	std::vector<F_Lua_Boss *> m_luaBosses;

	std::vector<Feintgine::F_BaseObject *> m_objects;


	std::map<std::string, ObjectType > m_objectMap;

	float f_angle;
	//std::vector<F_Lua_GC3_Boss *> m_bossObjects;

};

