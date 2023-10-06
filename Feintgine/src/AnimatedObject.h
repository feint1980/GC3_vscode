
#ifndef ANIMATION_OBJECT_H_
#define ANIMATION_OBJECT_H_
#include <rapidxml.hpp>
#include <string>
#include "SpriteBatch.h"
#include <vector>
#include "GLTexture.h"
#include <fstream>
#include <iostream>
#include "ResourceManager.h"
#include <map>

using namespace rapidxml;

struct anim
{
	int time;
	int index;

};
struct animation
{


	//std::string name;
	int loopKey;
	std::vector<anim> anims;
	int getTotalAnimSize()
	{
		int total = 0;
		for (int i = 0; i < anims.size(); i++)
		{
			total += anims[i].time;
		}
		return total;
	}
};

class AnimatedObject
{
public:
	AnimatedObject();
	~AnimatedObject();
	void init(const std::string & filePath);

	void startAnimation(const std::string & name);

	//void stopAnimation();

	void updateAnim();

	glm::vec4 CalculateUV();

	void update();


	void draw(Feintgine::SpriteBatch & spriteBatch);

	
	bool isPlaying() const { return m_playing; }

	void setPlaying(bool val);

	void setPos(const glm::vec2 & pos);
	void toggleAnim();

	bool isInit() const { return is_init; }

	glm::vec2 getDim() const { return m_dims; }

	

	std::map<std::string, animation > getAnimationMap() const { return m_animations; }

	void setInvert(bool value);

private:

	bool is_init = false;
	// Animation stuff start 

	bool m_playing;

	std::map<std::string, animation> m_animations;
	int col = 0;
	int row = 0;
	int m_index = 0;
	
	int currentTime = 0;
	
	int displayAnim = 0;

	int currentAnim = 0;

//	float m_animTime = 0;
	animation m_currentAnimation;

	// Animation stuff end 
	glm::vec4 m_uv;
	

	Feintgine::GLTexture m_texture;
	

	glm::vec2 m_dims;
	glm::vec2 m_pos;

	float m_depth = 5;

	float m_angle = 0;

	float m_spec = 1;

	bool invert = false;

	Feintgine::Color m_color;


	std::string m_name;

	

};

#endif
