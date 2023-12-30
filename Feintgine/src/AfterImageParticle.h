#pragma once
#include "F_Sprite.h"
#include "SpriteBatch.h"
#include "F_AnimatedObject.h"
#include <vector>
#include <algorithm>

const int DRAW_MODE_GL_TEXTURE = 1;
const int DRAW_MODE_F_SPRITE = 2;

class AfterImageTrace 
{
public :
	AfterImageTrace();
	~AfterImageTrace();

	void init(const Feintgine::F_Sprite & sprite,
		const glm::vec2 & pos, const glm::vec2 & scale, const Feintgine::Color & color,
		float lifeTime,float angle,float scaleRate = 0.0f);

	void init(const Feintgine::GLTexture & texture,
		const glm::vec2 & pos, const glm::vec2 & scale, const Feintgine::Color & color,
		float lifeTime, float angle,float scaleRate = 0.0f);

	void draw(Feintgine::SpriteBatch & spriteBatch);
	void update(float deltaTime);

	void setScale(const glm::vec2 & scale);
	void setAlphaRate(float value);
	void setScaleRate(float value);
	
	float getLifeTime() const { return m_lifeTime; }

private:
	int drawMode = 0;
	Feintgine::F_Sprite m_sprite;
	glm::vec2 m_pos;
	float m_lifeTime;
	Feintgine::Color m_color;
	glm::vec2 m_scale = glm::vec2(1.0f);
	float m_alphaRate;
	float m_angle;
	float m_scaleRate;
	bool m_isShrink = false;
	Feintgine::GLTexture m_texture;
};

class AfterImageObject 
{
public :
	AfterImageObject();
	~AfterImageObject();
	
	void init(glm::vec2 * pos,Feintgine::F_AnimatedObject * animatedObject, Feintgine::Color * color, float traceInterval,int numberOfTrace,float scaleRate = 0.0f);
	void init(glm::vec2 * pos,const Feintgine::F_Sprite & sprite,Feintgine::Color * color , float traceInterval, int numberOfTrace, float scaleRate = 0.0f);
	void init(glm::vec2 * pos, Feintgine::Color * color, float traceInterval, int numberOfTrace);

	void setTraceLifeTime(float val);

	void draw(Feintgine::SpriteBatch & spriteBatch);
	void update(float deltaTime, int animationIndex,float angle);

	void setTotalTrace(int num);
	void setTraceInterval(float val);

	void update(float deltaTime, const Feintgine::F_Sprite & sprite);

	void update(const glm::vec2 pos ,float deltaTime, const Feintgine::GLTexture  & sprite,float angle, bool isDone);
	void setAlphaRate(float value);
	void setScaleRate(float value);	
	bool isAnimated() { return (m_animatedObj != nullptr); }

	void setScale(const glm::vec2 & scale);

	void setOffsetPos(const glm::vec2 & pos);
	
	void clear();

	void addTrace(const AfterImageTrace & trace);

private:
	//bool m_isAnimated;
	float m_traceLifeTime = 2.0f;
	glm::vec2 * m_pos = nullptr;
	Feintgine::F_Sprite m_sprite ;
	Feintgine::Color * m_color;

	glm::vec2 m_offsetPos = glm::vec2(0);

	glm::vec2 m_scale;
	Feintgine::F_AnimatedObject * m_animatedObj = nullptr;
	float m_currentTraceTrack;
	float m_traceInterval;
	int m_numberOfTrace;

	float m_scaleRate;
	//float m_angle;
	float m_alphaRate;
	std::vector<AfterImageTrace> m_traces;


};

class AfterImageParticle
{
public:	
	AfterImageParticle();
	~AfterImageParticle();

	//void init()

private:
	//std::vector<
	
};

