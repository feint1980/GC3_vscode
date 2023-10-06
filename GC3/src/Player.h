
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
// #include "Stamina.h"
// #include "Profile.h"
// #include <feint_common.h>
// #include <ClientSocket.h>
// #include <Enet_UDP.h>
// #include "Profile.h"
// #include "ChatBubble.h"
// #include <feint_common.h>
// #include <functional>
// const float ANIMATION_SPEED = 0.12f;
// const float MOVEMENT_SPEED = 0.08;

// enum class PlayerFacing { DOWN, UP, LEFT, RIGHT };
// enum class PlayerAction { IDLE, PUSH };





// class Player
// {
// public:
// 	void init(glm::vec2 position,
// 		const glm::vec2& dims,
// 		const glm::vec2 &collisonDims,
// 		Feintgine::Color color,
// 		Feintgine::Window & window, Feintgine::Camera2D * camera ,  std::string name);


// 	void draw(Feintgine::SpriteBatch& spriteBatch);
// 	void drawGUI(Feintgine::SpriteBatch& GUIspriteBatch);


// 	void handleInput(Feintgine::InputManager& inputManager);

// 	void update(std::vector<Grid> & gridList, std::vector<PushableObject> &objectList, std::vector<TownTile> & simpleObjectList);

// 	void move();

// 	void loadGUI(Feintgine::GUI &gui);


// 	void chat();
// 	void moveLeft();
// 	void moveRight(); 
// 	void moveUp();
// 	void moveDown();

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

// 	void setInit(bool value);

// 	void say(const std::string & msg);

// 	bool getInit() const { return is_init; }

// 	//void setFacing(int value);


// 	void updateGUI();

	
// 	int getNearst(const std::string &ts);
	

// 	//void refreshItem();

// 	HitBox * getHitBox() { return m_hitBox; }
// 	void velSet(const glm::vec2 &vel);
// 	int deadType = 0;

// 	void drawChat(Feintgine::SpriteBatch & spriteBatch);


// 	CEGUI::Sizef getLongest(CEGUI::Sizef a, CEGUI::Sizef b);

// private:

// 	//GUI stuff////////////////////////////////////////////////////////////////////////

// 	CEGUI::Editbox * m_chatBox = nullptr;
// 	CEGUI::PushButton * m_submitbutton = nullptr;

// 	/////////////////////////////////////////////GUI//////////////////////////////////////////

// 	//Feintgine::GUI  m_gui;
// 	char * buffer_name;
// 	/*char * buffer_mon;*/

// 	void push();

// 	void checkOuter(std::vector<Grid>& gridList);

// 	void tileCollide(std::vector<PushableObject> & objectList);
// 	bool checkColide(PushableObject & objectList);

// 	void tileCollide(std::vector<TownTile> & objectList);
// 	bool checkColide(TownTile & objectList);

// 	bool isGUIfree = true;

// 	std::string m_name;

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

// 	bool is_init = false;

// 	float m_moveSpeed = 0;

// 	Stamina m_stamina;
// 	float stamina_bar = 1.0f;

// 	//bool UDPSent = false;
// 	//ChatBubble m_chatBub;

// 	Feintgine::Window m_paste_window;
// 	Feintgine::Camera2D *converter;


// 	CEGUI::DefaultWindow * m_CEChatbub;
	
// 	bool m_chatActive = false;
// 	int chatLifeTime = 0;
	
// 	//std::vector<QuickSlot> m_quickSlot;

// };

