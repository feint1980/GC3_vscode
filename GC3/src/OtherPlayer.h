// #pragma once
// #include <InputManager.h>
// #include <SDL2/SDL.h>
// #include <TileSheet.h>
// #include "PushableObject.h"
// #include "HitBox.h"
// #include "TownTile.h"
// #include "Grid.h"
// #include <GUI.h>
// #include "Camera2D.h"
// #include <SpriteFont.h>
// #include <Window.h>
// #include "Player.h"
// #include "Profile.h"
// #include "ChatBubble.h"


// // 
// // const float ANIMATION_SPEED = 0.12f;
// // const float MOVEMENT_SPEED = 0.08;

// // enum class PlayerFacing { DOWN, UP, LEFT, RIGHT };
// // enum class PlayerAction { IDLE, PUSH };



// class OtherPlayer
// {
// public:
// 	void init( glm::vec2 position,
// 		const glm::vec2& dims,
// 		const glm::vec2 &collisonDims,
// 		Feintgine::Color color,
// 		Feintgine::Window & window, Feintgine::Camera2D * camera, const std::string & name);


// 	void draw(Feintgine::SpriteBatch& spriteBatch);
// 	void drawGUI(Feintgine::SpriteBatch& GUIspriteBatch);
// 	void loadGUI(Feintgine::GUI &gui);


// 	void handleInput(Feintgine::InputManager& inputManager);

// 	void update(glm::vec2 playerPos,std::vector<Grid> & gridList, std::vector<PushableObject> &objectList, std::vector<TownTile> & simpleObjectList);

// 	void move();

// 	void say(const std::string & msg);

// 	bool isMoving() const { return m_moving; }
// 	void drawDebug(Feintgine::DebugRender & renderer);

// 	void destroy();
// 	bool isActive() const { return m_isAlive; }
// 	//void addMon(float value);
// 	void moveToGrid(glm::vec2 & gridPos);
// 	void stahp();
// 	glm::vec2 getPos() { return m_pos; }

// 	glm::vec2 getDims() const { return m_colisDims; }

// 	void setPos(const glm::vec2 & pos);

// 	PlayerFacing getFacing() const { return m_facing; }

// 	void moveLeft();
// 	void moveRight();
// 	void moveUp();
// 	void moveDown();
	
// 	void setFacing(int value);

// 	std::string getName() const { return m_name; }

// 	//void refreshItem();

// 	HitBox * getHitBox() { return m_hitBox; }
// 	void velSet(const glm::vec2 &vel);
// 	int deadType = 0;


// 	void updateGUI(glm::vec2 playerPos);

// 	CEGUI::Sizef getLongest(CEGUI::Sizef a, CEGUI::Sizef b);

// 	int getNearst(const std::string &ts);

// private:

// 	Feintgine::GUI  m_gui;
// 	char * buffer_name;
// 	/*char * buffer_mon;*/

// 	ChatBubble m_chatBub;

// 	std::string m_name;
// 	void push();

// 	void checkOuter(std::vector<Grid>& gridList);

// 	void tileCollide(std::vector<PushableObject> & objectList);
// 	bool checkColide(PushableObject & objectList);

// 	void tileCollide(std::vector<TownTile> & objectList);
// 	bool checkColide(TownTile & objectList);




// 	Feintgine::SpriteFont * m_playerName;
// 	/*Feintgine::SpriteFont * m_playerMon;*/
// 	void animation();
// 	glm::vec2 m_dims;
// 	glm::vec2 m_pos;
// 	glm::vec2 m_colisDims;
// 	glm::vec2 vel;
// 	Feintgine::Color m_color;
// 	Feintgine::TileSheet m_texture;

// 	/*glm::vec2 mon_pos;*/

// 	HitBox * m_hitBox = nullptr;

// 	PlayerFacing m_facing = PlayerFacing::DOWN;
// 	PlayerAction m_action = PlayerAction::IDLE;
// 	float m_animTime = 0.0f;
// 	int m_direction = 1; // 1 or -1
// 	bool m_moving = false;
// 	bool m_isPushing = false;
// 	bool m_isAlive = true;

// 	bool m_moveHor = false;
// 	bool m_moveVer = false;

// 	bool m_controlable = true;
// 	int tileIndex;
// 	int numTiles;
// 	int stack = 0;
// 	float deathTime = 0.0f;


// 	float m_moveSpeed = 0;


// 	float stamina_bar = 1.0f;

// 	//bool UDPSent = false;

// 	Feintgine::Window m_paste_window;
// 	Feintgine::Camera2D * converter;

// 	CEGUI::DefaultWindow * m_CEChatbub;

// 	bool m_chatActive = false;
// 	int chatLifeTime = 0;

// 	float line;

// 	//std::vector<QuickSlot> m_quickSlot;

// };

