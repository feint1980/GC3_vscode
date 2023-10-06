#include "LuaManager.h"

LuaManager *LuaManager::p_Instance = 0;

LuaManager::LuaManager()
{

	m_LuaState = luaL_newstate();
	luaL_openlibs(m_LuaState);
}


LuaManager::~LuaManager()
{
	lua_close(m_LuaState);
}


int LuaManager::LGetInt( const std::string & name)
{
	int returnValue = -999;// default value if not found
	lua_getglobal(m_LuaState, name.c_str()); // Get the value stack name as requested to top of the stack
	if (lua_isnumber(m_LuaState,-1)) // -1 indicates top of the stack
	{
		returnValue = (int)lua_tonumber(m_LuaState, -1);
	}
	else
	{
		printErrorMessage();
	}
	return returnValue;
}

float LuaManager::LGetFloat(const std::string & name)
{
	float returnValue = -999.999f;// default value if not found
	lua_getglobal(m_LuaState, name.c_str()); // Get the value stack name as requested to top of the stack
	if (lua_isnumber(m_LuaState, -1)) // -1 indicates top of the stack
	{
		returnValue = (float)lua_tonumber(m_LuaState, -1);
	}
	else
	{
		printErrorMessage();
	}
	return returnValue;
}

std::string LuaManager::LGetString(const std::string & name)
{
	std::string returnValue = "LGetString_error_not_found";//default value if not found
	lua_getglobal(m_LuaState, name.c_str()); // Get the value stack name as requested to top of the stack
	if (lua_isnumber(m_LuaState, -1)) // -1 indicates top of the stack
	{
		returnValue = (std::string)lua_tostring(m_LuaState, -1);
	}
	else
	{
		printErrorMessage();
	}
	return returnValue;
}

void LuaManager::printErrorMessage()
{
	std::string errorMessage = lua_tostring(m_LuaState, -1);
	std::cout << "Lua Error : " << errorMessage << "\n";
}
