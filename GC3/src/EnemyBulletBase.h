#pragma once
#include <F_Sprite.h>
#include <F_AnimatedObject.h>
#include <functional>
#include <F_oEvent.h>
#include <DebugRender.h>
#include <math.h>
#include <chrono>
#include <Box2D/Box2D.h>
extern int def;
extern int daf;


#define DISTANCE_THRESHOLD  3.5f

class EnemyBulletBase
{
	enum destinationState
	{
		NotDefined,
		Reaching,
		Following
	};


public:
	EnemyBulletBase();
	virtual ~EnemyBulletBase();

	void defaultUpdate(float deltaTime) 
	{

		switch (m_destinationState)
		{
		case EnemyBulletBase::NotDefined:	
		{
			updateRotateVec(deltaTime);
			if (m_isRotate)
			{
				m_pos = (m_rotateVec + (m_vel)* deltaTime);

			}
			else
			{
				m_pos += (m_vel)* deltaTime;
			}
			m_angle = atan2(m_vel.y, m_vel.x) + degreeToRad(90);
		}
			break;
		case EnemyBulletBase::Reaching:
		{
			float distance =  abs(glm::distance(m_pos, m_destination));
			if (distance < 5.0f)
			{
				//m_isReachDestination = true;
				m_pos = m_destination;
				m_vel = glm::vec2(0.0f);
				m_destinationState = EnemyBulletBase::Following;
				
			}
			else
			{

				glm::vec2 direction = glm::normalize(m_destination - m_pos);
				m_pos += direction * (m_reachDestinationSpeed + distance * 0.01f) ;
				m_angle = atan2(direction.y, direction.x);

			}
		}
			break;
		case EnemyBulletBase::Following:
		{
			glm::vec2 direction = glm::normalize(m_destination - m_pos);
			m_pos += direction * m_reachDestinationSpeed;
			m_angle = atan2(direction.y, direction.x) + degreeToRad(90);
		}
			break;
		default:
			break;
		}
		
		m_lifeTime -= m_decayTime * deltaTime;
	}

	void setLifeTime(float lifeTime);

	void init(const glm::vec2 & pos, const glm::vec2 & scale, const Feintgine::F_Sprite & sprite,
		glm::vec2 vel, std::function<void(float)> updateFunc,float depth );
	void init(const glm::vec2 & pos, const glm::vec2 & scale, const Feintgine::F_AnimatedObject & animObj,
		glm::vec2 vel, std::function<void(float)> updateFunc,float depth);

	void loadPattern(const std::string & pattern);

	std::priority_queue<Feintgine::oEvent, std::vector<Feintgine::oEvent>, Feintgine::oEvent_less> event_queue;

	void addEvent(const Feintgine::oEvent::f_callback & cb, double when);

	void timer();

	void loadEvent(const std::string & stateName, bool preloaded = true);

	void setRotateVec(float angleStart, float angleEnd, float step);

	void updateRotateVec(float deltaTime);
	virtual void update(float deltaTime);
	void setAngle(float angle);
	void rotate(float angle);
	void setPos(const glm::vec2 & pos);
	void setColor(const Feintgine::Color & color);

	void setSpeedChange(float speedWanted, float time);

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void drawHitbox(Feintgine::DebugRender & debugRenderer);

	void setDestination(const glm::vec2 & val);

	glm::vec2 getPos() const { return m_pos; }
	glm::vec2 getDim()const
	{
		if (!m_isAnim)
		{
			return m_scale * m_sprite.getDim();
		}
		else
		{
			return m_scale * m_animObj.getDim();
		}
	}

	
	glm::vec2 getScale() const { return m_scale; }

	void setDirection(const glm::vec2 & dir);

	void setVel(const glm::vec2 & vel);

	glm::vec2 getVel() const { return m_vel; }

	float m_lifeTime = 3.0f;
	float m_decayTime = 0.008f;

	void setGrazeable(bool val);

	bool isGrazeable() const { return m_isGrazeable; }

	void setDisabled(bool val);

	bool isDisabled() const { return m_isDisabled; }

	void updateSpeedChange(float deltaTime);

	int getSpecialID() const { return m_specialID; }

	int getSpecialIndex() const { return m_specialIndex; }

	void setSpecialID(int val)
	{
		m_specialID = val;

	}
	void setSpecialIndex(int val)
	{
		m_specialIndex = val;
	}
	void setSpecialID_Index(int id, int index)
	{
		m_specialID = id;
		m_specialIndex = index;
	}

protected:

	glm::vec2 m_pos;
	glm::vec2 m_scale;
	glm::vec2 m_vel;
	Feintgine::F_Sprite m_sprite;
	Feintgine::F_AnimatedObject m_animObj;
	std::function<void(float)> m_updateFunc  = nullptr;

	glm::vec2 m_direction;

	bool m_isDisabled;  

	float m_depth = 0.0f;
	Feintgine::Color m_color = Feintgine::Color(255,255,255,255);
	Feintgine::Color m_hitboxColor = Feintgine::Color(255, 0, 0, 255);
	float m_angle = 0.0f;

	bool m_isRotate = false;
	
	bool m_isGrazeable = true;

	int m_specialID = -1;
	int m_specialIndex = -1;

	bool m_isStop = false;


	glm::vec2 m_destination;
	bool m_isReachDestination = true;
	float m_reachDestinationSpeed = 1.7f;

	destinationState m_destinationState = NotDefined;


	//b2Body * m_body = nullptr;

	//b2Fixture * m_fixture = nullptr;

	float m_startAngle = 0;
	float m_endAngle = 0;
	float m_currentAngle = 0;
	float m_rotateStep = 0;
	glm::vec2 m_rotateVec = glm::vec2(1);


	bool m_isAmplified = false;

	bool m_isAnim = false;

	float t_speed = 1.0f;
	float t_currentSpeed = 1.0f;

	float t_deltaSpeed = 0.0f;

	float m_speedChangeTime = 0.0f;

	float m_firstChangeTime = 0.0f;

	int m_isSpeedPositive = 0; // 0 undefine, -1 negative, 1 positive
	
};

