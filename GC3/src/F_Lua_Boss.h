#pragma once
#include "F_Lua_GenericObject.h"


class F_Lua_Boss : public F_Lua_GenericObject
{
public:
	F_Lua_Boss();
	~F_Lua_Boss();

	virtual void update(float deltaTime)override;

private :


};

