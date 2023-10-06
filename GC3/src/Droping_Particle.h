// #pragma once
// #include "EmptyObject.h"
// #include <time.h>
// #include <Camera2D.h>
// #include <Box2D/Box2D.h>
// #include <random>
// #include <stdlib.h>

// const int MAX_PARTICLE = 185;
// class Droping_Particle : public EmptyObject
// {
// public:
// 	Droping_Particle();
// 	~Droping_Particle();

// 	void update(Feintgine::Camera2D & camera, bool isOn);

// 	void destroy();
// 	glm::vec2 getPos() const { return m_pos; }
// 	glm::vec2 getDimentions() const { return m_dims; }

// 	bool isDestroy() const { return is_destroy; }
// 	void setFreeFall();

// 	void autoPos();
// 	void firstPos();

// 	void resetPos(const glm::vec2 & pos);

// 	void loadPhysic(b2World * world);
// private:
// 	glm::vec2 m_vel;


// 	b2Fixture * m_fixture = nullptr;
// 	b2Body *m_body = nullptr;

// 	int count = 90;

// 	bool forced = false;



// 	std::mt19937 posRand;

// 	float alpha = 0.0f;
// 	bool is_destroy = false;
	
// };

