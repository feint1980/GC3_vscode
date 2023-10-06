// #pragma once
// #include "SimpleObject.h"
// #include <SDL2`/SDL.h>
// #include <TileSheet.h>
// #include <ResourceManager.h>
// #include "PushableObject.h"
// #include "Grid.h"
// #include <time.h>
// #include <iostream>
// #include "OutsideGrid.h"
// #include "Player.h"
// #include "Fire.h"
// const float MONSTER_ANIM_SPEED = 0.1f;
// const float MONSTER_MOVE_SPEED = 0.06;

// const int AI_RECALCULATE = 20;


// enum class MonsterFacing { DOWN, UP, LEFT, RIGHT };
// enum class MonsterAction { IDLE, SKILL };

// class BasicMonster 
// {
// public:
// 	BasicMonster();
// 	~BasicMonster();

// 	void init(const glm::vec2& position,
// 		const glm::vec2& dims,
// 		const glm::vec2 &collisonDims,
// 		Feintgine::Color color);


// 	void draw(Feintgine::SpriteBatch& spriteBatch);


	

// 	void update(std::vector<Grid> & gridList, std::vector<PushableObject> &objectList , std::vector<OutsideGrid> & outList, Player & player);

// 	void move();


// 	bool isMoving() const { return m_moving; }
// 	void drawDebug(Feintgine::DebugRender & renderer);



// 	void moveToGrid(glm::vec2 & gridPos);
// 	void stahp();
// 	glm::vec2 getPos() const { return m_pos; }

// 	void setPos(const glm::vec2 & pos);

// 	MonsterFacing getFacing() const { return m_facing; }

// 	HitBox * getHitBox() { return m_hitBox; }
// 	void velSet(const glm::vec2 &vel);
// 	void destroy();
// 	bool getLife() const { return isAlive; }
// private:

// 	int move_delay = 0;
// 	bool move_blocked = false;
// 	void AI();
// 	void fire();
	

// 	void checkOuter(std::vector<Grid>& gridList);
// 	void tileCollide(std::vector<PushableObject> & objectList);
// 	void tileCollide(std::vector<OutsideGrid> & objectList);
// 	bool checkColide(PushableObject & objectList);
// 	bool checkColide(Player & objectList);
// 	bool checkColide(OutsideGrid & objectList);

// 	void animation();
// 	glm::vec2 m_dims;
// 	glm::vec2 m_pos;
// 	glm::vec2 m_colisDims;
// 	glm::vec2 vel;
// 	Feintgine::Color m_color;
// 	Feintgine::TileSheet m_texture;

// 	bool foundTarget = false;

// 	HitBox * m_hitBox = nullptr;
// 	Fire * m_fire = nullptr;

// 	Feintgine::GLTexture m_fireTexture;

// 	MonsterFacing m_facing = MonsterFacing::DOWN;
// 	MonsterAction m_action = MonsterAction::IDLE;
// 	float m_animTime = 0.0f;
// 	int m_direction = 1; // 1 or -1
// 	bool m_moving = false;
// 	bool m_isPushing = false;

// 	bool m_moveHor = false;
// 	bool m_moveVer = false;

// 	bool m_controlable = true;
// 	int tileIndex;
// 	int numTiles;
// 	int stack = 0;
// 	float m_animSpeed = MONSTER_ANIM_SPEED;
// 	bool flameable = true;
// 	bool m_isSkill = false;
// 	bool m_isdraged = false;
// 	bool isAlive = true;
// };

