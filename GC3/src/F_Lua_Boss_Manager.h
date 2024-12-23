#pragma once
#include <F_LuaObjectManager.h>
#include <ResourceManager.h>
#include "F_Lua_GenericObject.h"
#include "F_Lua_Boss.h"
#include "F_Lua_Boss_State.h"
#include "F_Lua_Boss_State_MoveObject.h"
#include "ArcFunction_hypocycloid.h"
#include "ArcFunction_hypotrochoid.h"
#include "ArcFunction_feint_custom1.h"
#include "ArcFunction_feint_custom2.h"
#include "ArcFunction_Epicycloid.h"

#include "F_Player.h"
#include "BulletManupilator.h"
#include <F_BaseObject.h>
#include "F_Komachi_Souls_Object.h"
#include "F_Komachi_pillar.h"
#include <FL_Object.h>
#include "EnemyBullet_KomachiCoin.h"
#include <ParticleEngine2D.h>
#include "PaternBehavior_from_lua.h"

enum ArcType
{
	arcHypocycloid = 1,
	arcHypotrochoid = 2,
	arcFeintCustom1 = 3,
	arcFeintCustom2 = 4,
	arcEpicycloid = 5,
};

enum ObjectType
{
	komachi_souls = 1,
	komachi_pillar = 2
};


class F_Lua_Boss_Manager //: public Feintgine::F_LuaObjectManager
{
public:
	F_Lua_Boss_Manager();
	~F_Lua_Boss_Manager();

	void init();

	void update(float deltaTime);

	void updatePlayer(float deltaTime, std::vector<FairyBase *>  enemy,
	std::vector<EnemyBulletBase * > bullets);

	void updatePlayer2(float deltaTime, std::vector<FairyBase *>  enemy,
	std::vector<EnemyBulletBase * > bullets);


	void MoveObject(F_Lua_GenericObject * dynamicObject, float x, float y, float time);
	void MoveObjectNonWait(F_Lua_GenericObject * dynamicObject, float x, float y, float time);


	void setObjectVel(F_Lua_GenericObject * dynamicObject, const glm::vec2 & vel);

	void handleInput(Feintgine::InputManager & inputManager);

	void standIdle(F_Lua_GenericObject * dynamicObject, float time, const std::string & animName, bool isOverRide = false);
	void standIdleNonWait(F_Lua_GenericObject * dynamicObject, float time, const std::string & animName, bool isOverRide = false);

	void resetEvent();

	void clearBullets();

	void rw_addEvent_PE(F_Lua_GenericObject * dynamicObject, const std::string & asset, float speed, float lifeTime, \
		int peType, float startRange, float rangeCover, float angleStep, float startAngle, int petalCount, int interval, float rotation, int count, double time);

	void rw_addEvent_PE_nonWait(F_Lua_GenericObject * dynamicObject, const std::string & asset, float speed, float lifeTime, \
		int peType, float startRange, float rangeCover, float angleStep, float startAngle, int petalCount, int interval, float rotation, int count, double time);


	void rw_addEvent_T1(F_Lua_GenericObject  * dynamicObject, const std::string & asset, float speed, float lifeTime, \
		int arcType, float fA, float fB, float fC, float fD,float fR, float angleStep, float startAngle, float rotation, int interval, int count, double time,int id = 0, const std::string & eventName = "");
	

	void rw_addEvent_T1_nonWait(F_Lua_GenericObject  * dynamicObject, const std::string & asset, float speed, float lifeTime, \
		int arcType, float fA, float fB, float fC, float fD,float fR, float angleStep, float startAngle, float rotation, int interval, int count, double time,int id = 0, const std::string & eventName = "");
	

	void rw_addEvent_MA_custom_aff(F_Lua_GenericObject * dynamicObject, const std::string & asset, float speed,
		float lifeTime, int k, int n, int n2, int l1, int l2,int posneg, float startAngle, 
		float angleStep, float rotation, int interval, double time);

	
	void rw_addEvent_MA_custom_aff_nonWait(F_Lua_GenericObject * dynamicObject, const std::string & asset, float speed,
		float lifeTime, int k, int n, int n2, int l1, int l2,int posneg, float startAngle, 
		float angleStep, float rotation, int interval, double time);


	void rw_addEvent_base(F_Lua_GenericObject * dynamicObject, const std::string & asset, float speed, float lifeTime, float x, float y, float currentAngle, double time,int id = 0, const std::string & eventName = "");

	// void rw_addEvent_base_nonWait(F_Lua_GenericObject * dynamicObject, const std::string & asset, float speed, float lifeTime, float x, float y, float currentAngle, double time,int id = 0, const std::string & eventName = "");
	
	void rw_addEvent_fire_komachi_coin(F_Lua_GenericObject * dynamicObject, const std::vector<std::string> & assets, int tier, float speed, float lifeTime, float x, float y, float currentAngle, double time);

	Feintgine::F_BaseObject * createHelper(F_Lua_GenericObject * dynamicObject, unsigned int id, const std::string & objectName,
	const std::string & asset, float x, float y, float scaleX, float scaleY, float depth,float velX, float velY,int afterImageCount, float afterImageRate, float scaleRate,double time);

	

	void waitFor(F_Lua_GenericObject * dynamicObject, float time);
	
	Feintgine::FL_Object * createFLObject(F_Lua_GenericObject * dynamicObject, unsigned int id, 
		const std::string & asset, float x, float y, float scaleX, float scaleY, float depth, float destinationX, float destinationY);

	void addEvent(F_Lua_GenericObject * dynamicObject, const Feintgine::oEvent::f_callback & cb, double when);

	F_Lua_GenericObject * createBoss(const std::string & animationPath, glm::vec2 pos);

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void drawLight(Feintgine::LightBatch & lightBatch);

	void drawBossesLight(Feintgine::LightBatch & lightBatch);

	void drawPlayer(Feintgine::SpriteBatch & spriteBatch);

	void drawLight2(Feintgine::LightBatch & lightBatch);

	void drawPlayer2(Feintgine::SpriteBatch & spriteBatch);

	void drawParticle(Feintgine::SpriteBatch * spriteBatch);


	void drawPlayerSpellcard(Feintgine::SpriteBatch & spriteBatch);

	void drawPlayerSpellcard2(Feintgine::SpriteBatch & spriteBatch);
	

	void callCreateFromLua(const std::string & filePath, const std::string & functionName);

	void callFunctionFromLua(const std::string functionName);

	bool loadLuaFile(const std::string & filePath);

	void addBulletEvent(int bulletID, const std::string & eventName);

	void clearBosses();

	F_Lua_GenericObject * createBoss(const glm::vec2 & pos,
		const Feintgine::F_AnimatedObject & t_animation,
		const glm::vec2 & scale, float depth, float angle = 0.0f);

	F_Lua_GenericObject * createBoss(const glm::vec2 & pos,
		const std::string & t_animationPath,
		const glm::vec2 & scale, float depth, float angle = 0.0f);

	void removeObject(F_Lua_GenericObject * dynamicObject);

	int getTotalBullets() const { return m_bullets.size(); }

	//Feintgine::FL_Object * createObject(const glm::vec2 & pos, const glm::vec2 & scale, const std::string & assetString);

	std::vector<EnemyBulletBase *> * getBullets() { return &m_bullets; }


	// move the player part into F_Lua_Boss_Manager
	void addExplosion(const Feintgine::F_Sprite & sprite, const glm::vec2 & pos, const glm::vec2 & scale, const glm::vec2 & explosionRate, const Feintgine::Color & color, float depth, float liveRate /*= 0.1f*/);


	//void manipulateBullet()

	void createPatern(const std::string & xNodeEquation, const std::string & yNodeEquation, float radius, const std::vector<float> & factors, int bulletID);

	void reloadPlayer(int val);
	void initPlayer(int val, Feintgine::AudioEngine * audioEngine, KanjiEffectManager * kanjiEffectManager, Feintgine::Camera2D * cam,Feintgine::EffectBatch * effectBatch);

	void loadTextures();

	// Komachi's addon 
	F_Komachi_pillar * createPillar(const std::string & texturePath1, const std::string & texturePath2, const glm::vec2 & pos, const glm::vec2 & dim, const Feintgine::Color & color);

protected:

	F_Player m_player;
	F_Player m_player2;

	lua_State * m_script;

	Feintgine::Camera2D * m_cam;
	KanjiEffectManager  * m_kanjiEffectManager;
	Feintgine::ParticleEngine2D m_particleEngine;

	std::vector<EnemyBulletBase *> m_bullets;
	std::vector<F_Lua_Boss_State *> m_nonWaitLuaBossStates;
	std::vector<F_Lua_Boss_State *> m_luaBossStates;
	std::vector<F_Lua_GenericObject *> m_luaBosses;
	std::vector<Feintgine::F_BaseObject *> m_objects;
	std::vector<F_Komachi_pillar *> m_komachiPillars;
	std::vector<ExplosionRing> m_exlosions;

	std::map<std::string, ObjectType > m_objectMap;
	std::map<std::string, Feintgine::GLTexture> m_preloadedTextures;

	BulletManupilator bulletManipulator;
	float f_angle;

};

