#pragma once
#include "F_Player.h"
#include <SpriteBatch.h>
#include <Camera2D.h>


const float LIGHT_BALANCE_FULL = 1.0f;
const float LIGHT_BALANCE_CLOUD = 0.1f;


class GlobalValueClass
{
public:
	GlobalValueClass();
	~GlobalValueClass();

	static GlobalValueClass *Instance()
	{
		if (p_Instance == 0)
		{
			p_Instance = new GlobalValueClass;
			return p_Instance;
		}
		return p_Instance;
	}

	void setTimeStep(float value)
	{
		m_timestep = value;
	}
	float getTimeStep() const { return m_timestep; }

	void savePlayer(F_Player * player);
	F_Player * getPlayer() const { return m_player; }
	Feintgine::Camera2D * savedCamera;


	void setAmbientLight(const glm::vec3 & light);

	glm::vec3 getAmbientLight() const { return m_ambientLight; }

	Feintgine::Camera2D * getGameplayCamera()
	{
		if (!m_gameplayCamera)
		{
			Feintgine::fatalError("Gameplay camera is not set before get value getGameplayCamera ( GlobalValueClass) ");
		}
		return m_gameplayCamera;
	}

	void setGameplayCamera(Feintgine::Camera2D * camera)
	{
		m_gameplayCamera = camera;
	}


	void setLightBalance(bool val)
	{
		m_isLightBalance = val;
		if (m_isLightBalance)
		{
			m_lightBalance = LIGHT_BALANCE_CLOUD;
		}
		else
		{
			m_lightBalance = LIGHT_BALANCE_FULL;
		}
	}
	
	bool isLightBalance() const { return m_isLightBalance; }

	float getLightBalance() const { return m_lightBalance; }


// 	float getLaserEnergy() const { return m_laserEnergy; }
// 	void setLaserEnergy(float val);


	//void setAmbientRGB(float r, float g, float b);

	//float get
	

private : 
	F_Player * m_player;

	glm::vec3 m_ambientLight;
	float m_timestep = 144.0f;

	bool m_isLightBalance = false;

	float m_lightBalance = 1.0f; // T AFK ti sorry sorry


	Feintgine::Camera2D * m_gameplayCamera;

	//float m_laserEnergy = MAX_ENERGY;
	
	static GlobalValueClass *p_Instance;
};

