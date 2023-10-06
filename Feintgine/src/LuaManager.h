#ifndef _LUAMANAGER_H_
#define _LUAMANAGER_H_

#include <string>
#include <iostream>
extern "C"
{
#include <lua.h>
#include <lauxlib.h> 
#include <lualib.h>
}


#ifdef _WIN32
#pragma comment(lib, "lua.a")
#endif


class LuaManager
{
public:
	
	LuaManager();
	~LuaManager();

	static LuaManager *Instance()
	{
		if (p_Instance == 0)
		{
			p_Instance = new LuaManager;
			return p_Instance;
		}
		return p_Instance;
	}

	// read an int value in lua
	int LGetInt(const std::string & name);

	// read a float value in lua
	float LGetFloat(const std::string & name);


	std::string LGetString(const std::string & name);

	bool checkLua(lua_State * L, int returnCode)
	{
		if (returnCode != LUA_OK)
		{
			std::cout << lua_tostring(L, -1) << " This function message was called in LuaManager \n";
			return false;
		}
		return true;
	}


	// print error
	void printErrorMessage();

private:
 
	lua_State * m_LuaState;
	static LuaManager *p_Instance;
};

#endif