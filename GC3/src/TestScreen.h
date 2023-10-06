// #pragma once
// #include <IGameScreen.h>
// #include <IMainGame.h>
// #include <GLSLProgram.h>
// #include <SpriteBatch.h>
// #include <InputManager.h>
// #include <Window.h>
// #include <Camera2D.h>
// #include "EmptyObject.h"
// #include <ResourceManager.h>
// #include "ScreenIndices.h"
// 
// #include <Box2D/Box2D.h>
// #include "Patchouli.h"
// 
// #include <time.h>
// 
// #include "block.h"
// 
// #include "Light.h"
// class TestScreen : public Feintgine::IGameScreen
// {
// public:
// 	TestScreen();
// 	TestScreen(Feintgine::Window * window);
// 	~TestScreen();
// 
// 	virtual int getNextScreenIndex() const override;
// 
// 	virtual int getPreviousScreenIndex() const override;
// 
// 	virtual void build() override;
// 
// 	virtual void destroy() override;
// 
// 	virtual void onEntry() override;
// 
// 	virtual void onExit() override;
// 
// 	virtual void update(float deltaTime) override;
// 
// 	virtual void draw() override;
// 
// 	void initWOrld();
// 
// 	void physicMode();
// 
// 	void createTheWall();
// 
// 	void createTheBlocks(int seed);
// 	void createBlocks();
// 
// 	void stahp(float stap_man);
// 
// 	void initBlock(int instance);
// 	
// 	void summonBlock();
// 	
// 
// private:
// 	bool cheat_physic = false;
// 	Feintgine::GLSLProgram m_normalShader;
// 	
// 	Feintgine::GLSLProgram m_shadowShader;
// 
// 	Feintgine::GLSLProgram m_lighShader; 
// 
// 	Feintgine::SpriteBatch m_spriteBatch;
// 	Feintgine::Window *m_window;
// 	Feintgine::Camera2D m_camera;
// 	
// 	EmptyObject bg;
// 
// 	Light mouseLight;
// 
// 	std::vector<Feintgine::Vertex> m_vertex;
// 
// 	std::vector<block> m_blocks;
// 
// 	Patchouli m_patchy;
// 	
// 	void initShader();
// 	void checkInput();
// 	void handleInput(Feintgine::InputManager &inputManager);
// 
// 	b2World * m_world = nullptr;
// 
// 	bool activePhysic = false;
// 
// 	float stahper = 0.0f;
// 	bool isStahp = false;
// 	
// 	bool active_camMove = false;
// 
// 
// 
// 
// };
// 
