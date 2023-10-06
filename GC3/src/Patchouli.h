// #pragma once
// #include "Boss.h"
// #include "Philosopher.h"
// #include <time.h>
// #include "InputManager.h"
// #include "GLSLProgram.h"
// #include "EmptyObject.h"
// #include "Light.h"
// 
// class Patchouli : public Boss
// {
// public:
// 
// 	virtual void update() override;
// 	
// 	
// 	void draw(Feintgine::SpriteBatch & spriteBatch);
// 
// 	void drawChildren(Feintgine::SpriteBatch & spriteBatch);
// 
// 	void drawLight(Feintgine::SpriteBatch & spriteBatch);
// 	
// 	void moveLeft();
// 	void moveRight();
// 	
// 	Light getLight() const { return m_light; }
// 
// 	void velSet(glm::vec2 newLoc, float time);
// 
// 	void handleInput(Feintgine::InputManager& inputManager);
// 
// 	void addStone();
// 	void handleStone();
// 	float getChange()const { return m_stoneAlpha; }
// 	void setAngle(const float angle){ m_angle = angle; }
// 
// 	void onInit();
// 
// 
// 
// 	void createTheWall();
// 
// 	bool starLight = false;
// 	bool offTrigger = false;
// 
// 	void setB2World(b2World * world);
// 
// 	void setBlocks(std::vector<	block> blocks);
// 
// 	void explod();
// 
// 	bool cheat_physic = false;
// 
// 	//std::vector<Philosopher *> getStones() const{ return stones; }
// 	
// private : 
// 
// 
// 	std::vector<block> m_blocks;
// 	Light m_light;
// 	float m_angle = 0.0f;
// 	float m_moveSpeed = 0.2;
// 	float m_animTime = 0;
// 	bool isMoving = false;
// 	glm::vec2 m_velset;
// 	float m_moveTime;
// 	float m_anchorTime;
// 	int count = 0;
// 
// 	bool m_isControling = false;
// 
// 	bool isChange = false;
// 	bool triggered = false;
// 	float m_stoneAlpha = 2;
// 
// 	EmptyObject m_sigil;
// 	
// 	Philosopher m_stone;
// 	Philosopher m_core_stone;
// 
// 	b2World * m_world;
// 
// 	std::vector<Philosopher> m_stones;
// };