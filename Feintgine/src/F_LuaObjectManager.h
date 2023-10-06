#pragma once
#include "F_LuaDynamicObject.h"
#include "LuaManager.h"
#include "F_LuaObjectManipulator.h"
#include "F_Lua_GC3_Boss.h"

namespace Feintgine
{

	class F_LuaObjectManager
	{
	public:
		F_LuaObjectManager();
		~F_LuaObjectManager();

		bool loadLuaFile(const std::string & filePath);

		void init();

		int lua_ScriptGetTableVar_int(const std::string & name);

		void initDummy();

		void draw(SpriteBatch & spriteBatch);

		F_LuaDynamicObject * createObject(const glm::vec2 & pos,
			const Feintgine::F_AnimatedObject & t_animation,
			const glm::vec2 & scale, float depth, float angle = 0.0f);

		F_LuaDynamicObject * createObject(const glm::vec2 & pos,
			const std::string & t_animationPath,
			const glm::vec2 & scale, float depth, float angle = 0.0f);

		virtual void update(float deltaTime);

		
		void callLuaFunction(const std::string & filePath,const std::string & functionName);
		
		void callCreateFromLua(const std::string & filePath, const std::string & functionName);

		 
		void MoveObject(F_LuaDynamicObject * dynamicObject, float x, float y, float time);


		F_LuaDynamicObject * createDynamicObject(const std::string & animationPath, glm::vec2 pos);
		F_Lua_GC3_Boss * createBossObject(const std::string & animationPath, glm::vec2 pos);

		//int wrap_createDynamicObject(lua_State * L);
		//int lua_HostFunction(lua_State *L);

		protected:

		//void * coroutine;
		//lua_State *pThread;

		std::vector<F_LuaObjectManipulator *> m_manipulators;

		lua_State * m_script;
		std::vector<F_LuaDynamicObject *> m_dynamicObjects;
		std::vector<F_Lua_GC3_Boss *> m_bossObjects;
	};
}

