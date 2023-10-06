#include "GlobalValueClass.h"

GlobalValueClass *GlobalValueClass::p_Instance = 0;

GlobalValueClass::GlobalValueClass()
{
}


GlobalValueClass::~GlobalValueClass()
{
}


void GlobalValueClass::savePlayer(F_Player * player)
{
	m_player = player;
}

void GlobalValueClass::setAmbientLight(const glm::vec3 & light)
{
	m_ambientLight = light;
}

