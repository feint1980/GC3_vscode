#pragma once
#include "EmptyObject.h"
#include "Light.h"
enum Stone
{
	Fire ,
	Water , 
	Wood , 
	Metal , 
	Earth , 
	Sun , 
	Moon
};

class Philosopher : public EmptyObject
{
public :
	Philosopher()
	{};
	~Philosopher(){};
	
	void changeForm(Stone type);
	void update(glm::vec2 bossPos);
	void setCirCleAngle(float angle);

	void fayde_alpha(float speed);

	std::string getName() const { return m_name; }

	Feintgine::Color lerp(Feintgine::Color colorstart,Feintgine::Color colorEnd, float changeTime);
	void setCore(bool value);
	bool isCore() const { return v_isCore; }
	
private: 
	float m_radius = 7.2f;
	float m_circle_angle = 0;
	std::string m_name;
	Stone m_type = Stone::Fire;

	Feintgine::Color m_currentColor;
	Feintgine::Color m_targetColor;
	bool m_isTranforming = false;
	bool v_isCore = false;
	int count = 0;
	float a = 0;

	float alphaTagPoint = 1.0f;
	
	
	
};

