#include "F_LuaObjectManager.h"


namespace Feintgine
{
	static int wrap_createDynamicObject(lua_State * L)
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
		std::cout << "[C++] HostFunction " << a << " " << b << " called \n";

		float c = a * b;

		lua_pushnumber(L, c);
		return 1; // this host function return 1 number
	}

	int lua_CreateFromLua(lua_State * L)
	{
		if (lua_gettop(L) != 1)
		{
			std::cout << "gettop failed \n";
			return -1;
		}
		//std::cout << "[C++] lua_CreateFromLua called \n";
		glm::vec2 pos(0);
		std::string animationPath = "./Assets/F_AObjects/boss_eiki.xml";
		F_LuaObjectManager * object = static_cast<F_LuaObjectManager*>(lua_touserdata(L, 1));



		F_LuaDynamicObject * createdDynamicObj =  object->createObject(pos, animationPath, glm::vec2(1), 15, 0);// createObject(pos, animationPath, 1, 15, 0);
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
		F_LuaObjectManager * objectManager = static_cast<F_LuaObjectManager*>(lua_touserdata(L, 1));
		F_LuaDynamicObject * dynamicObject = static_cast<F_LuaDynamicObject*>(lua_touserdata(L, 2));
		float x = lua_tonumber(L, 3);
		float y = lua_tonumber(L, 4);
		float time = lua_tonumber(L, 5);
		objectManager->MoveObject(dynamicObject, x, y, time);
		return 0;
	}


	F_LuaObjectManager::F_LuaObjectManager()
	{
		m_script = luaL_newstate();
		luaL_openlibs(m_script);

		// lua register 1 ( lua state ) , 2 name will be called in lua, 3 the pointer to function
		lua_register(m_script, "HostFunction", lua_HostFunction);
		lua_register(m_script, "cppCreateFromLua", lua_CreateFromLua);
		lua_register(m_script, "cppMoveObject", lua_MoveObject);
		std::cout << "called  F_LuaObjectManager |||||||||||||||\n";
	}


	F_LuaObjectManager::~F_LuaObjectManager()
	{
		delete m_script;
	}

	bool F_LuaObjectManager::loadLuaFile(const std::string & filePath)
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

				// note : this version is to cause object init animation from file path, please add 
				// a copy version if you have time
				// Feint~ 

				std::cout << "create object with \n" << "pos : " << feint_common::Instance()->convertiVec2toString(pos) << "\n"\
					<< "path " << animationPath << "\n";

				createObject(pos, animationPath, scale, depth, angle);

			}
		}

		return false;
	}

	void F_LuaObjectManager::init()
	{
		//lua_register
	}

	int F_LuaObjectManager::lua_ScriptGetTableVar_int(const std::string & name)
	{
		//lua_pushstring(m_script, name.c_str());
		//lua_gettable()

		return 0;
	}

	void F_LuaObjectManager::initDummy()
	{
		createObject(glm::vec2(0), "Assets/F_AObjects/reimu.xml", glm::vec2(1), 15, 0);
	}

	void F_LuaObjectManager::draw(SpriteBatch & spriteBatch)
	{
		for (auto i = 0; i < m_dynamicObjects.size(); i++)
		{
			if (m_dynamicObjects[i])
			{
				m_dynamicObjects[i]->draw(spriteBatch);
			}
		}
	}

	F_LuaDynamicObject * F_LuaObjectManager::createObject(const glm::vec2 & pos,
		const Feintgine::F_AnimatedObject & t_animation, 
		const glm::vec2 & scale, float depth, float angle /*= 0.0f*/)
	{
		F_LuaDynamicObject * m_object = new F_Lua_GC3_Boss();
		m_object->createObject(pos, t_animation, scale, depth, angle);
		m_dynamicObjects.push_back(m_object);
		return m_object;
	}
	
	F_LuaDynamicObject * F_LuaObjectManager::createObject(const glm::vec2 & pos,
		const std::string & t_animationPath, const glm::vec2 & scale,
		float depth, float angle /*= 0.0f*/)
	{
		F_LuaDynamicObject * m_object = new F_Lua_GC3_Boss();
		m_object->createObject(pos, t_animationPath, scale, depth, angle);
		//MoveObject(m_object, 100, 10, 100);
		m_dynamicObjects.push_back(m_object);

		return m_object;
		//std::cout << "now size is " << m_dynamicObjects.size() << "\n";
	}

	void F_LuaObjectManager::update(float deltaTime)
	{
		for (auto i = 0; i < m_dynamicObjects.size(); i++)
		{
			if (m_dynamicObjects[i])
			{
				m_dynamicObjects[i]->update(deltaTime);
			}

			
		}
		for (auto i = 0; i < m_manipulators.size(); i++)
		{
			if (m_manipulators[i])
			{
				if (m_manipulators[i]->update(deltaTime))
				{
					//std::cout << "Issue Next Task [C++] \n";
					lua_getglobal(m_script, "IssueNextTask");
					if (lua_isfunction(m_script, -1))
					{
						
						F_LuaDynamicObject * object = m_manipulators[i]->m_dynamicObject;
						//lua_pushlightuserdata(m_script, pThread);
						lua_pushlightuserdata(m_script, this); // host
						
						lua_pushlightuserdata(m_script, object);
						if (!LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, 2, 1, 0)))
						{
							std::cout << "script failed \n";
						}
					}
					
					// After Issued next task
					m_manipulators.erase(m_manipulators.begin() + i);
				}
				

			}
		}
	}



	void F_LuaObjectManager::callLuaFunction(const std::string & filePath, const std::string & functionName)
	{
		// this function is to purely call TestFunc
		if (LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script,filePath.c_str())))
		{
			lua_getglobal(m_script, functionName.c_str());// get the function name to the top of the stack
			if (lua_isfunction(m_script, -1))
			{
				lua_pushnumber(m_script, 10);
				lua_pushnumber(m_script, 40);
				if (LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, 2, 1, 0)))
				{
					//std::cout << "C++ called " + functionName << "\n";
				}
			}
		}
	}



	void F_LuaObjectManager::callCreateFromLua(const std::string & filePath, const std::string & functionName)
	{
		// this function is to purely call CreateFromLua
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

	void F_LuaObjectManager::MoveObject(F_LuaDynamicObject * dynamicObject, float x, float y, float time)
	{
// 		F_LuaObjectManipulator * manipulator = new F_LuaObjectManipulator();
// 		manipulator->moveObject(dynamicObject, glm::vec2(x, y), time);
// 		m_manipulators.push_back(manipulator);


	}

	Feintgine::F_LuaDynamicObject * F_LuaObjectManager::createDynamicObject(const std::string &
		animationPath, glm::vec2 pos)
	{
		F_LuaDynamicObject * dynamicObject = new F_Lua_GC3_Boss();
		dynamicObject->createObject(pos, animationPath, glm::vec2(1), 15, 0);
		m_dynamicObjects.push_back(dynamicObject);
		return dynamicObject;
	}

	Feintgine::F_Lua_GC3_Boss * F_LuaObjectManager::createBossObject(const std::string &
		animationPath, glm::vec2 pos)
	{
		F_Lua_GC3_Boss * dynamicObject = new F_Lua_GC3_Boss();
		//dynamicObject->createObject()
		//dynamicObject->createObject(pos,)
		dynamicObject->createObject(pos, animationPath, glm::vec2(1), 15, 0);
		m_bossObjects.push_back(dynamicObject);
		return dynamicObject;
	}

	

}
