#pragma once
#include <F_AnimatedObject.h>
#include <LightBatch.h>
#include <F_Dialouge_Handler.h>
#include <F_oEvent.h>

class F_Player;
class F_Boss_Base
{
public:
	F_Boss_Base();

	~F_Boss_Base();

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void update(float deltaTime, F_Player & player);

	void drawLight(Feintgine::LightBatch & lightBatch);

	void handleInput(Feintgine::InputManager & inputManager);

	void init(const std::string & animationFile, 
		const std::string & stateFile, const std::string & dialougeFile);
	void startDialouge(const std::string & dialougeID);

	void loadState(const std::string & filePath, bool preloaded = true);

	void registerTextGUI(Feintgine::GUI & gui,
		const std::string & name, const glm::vec2 & pos, const glm::vec2 & dim);



	void handleAI(float deltaTime);

protected:
	
	Feintgine::F_AnimatedObject m_animation;
	glm::vec2 m_pos;

	glm::vec2 m_destination;

	glm::vec2 m_direction;

	float m_firstDistance;

	bool m_isDecided;

	float m_AICounterTime;

	Feintgine::F_Dialouge_Handler m_dialougeHandler;

	std::priority_queue<Feintgine::oEvent,
		std::vector<Feintgine::oEvent>, Feintgine::oEvent_less> event_queue;

	int m_life = 1;

	float m_heath = 100;

};

