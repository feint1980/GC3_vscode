#pragma once

#include <IMainGame.h>

//#include "GameplayScreen.h"
//#include "MainMenuScreen.h"
//#include "GameTownScreen.h"
#include "TestScreen.h"
#include "SelectScreen.h"
#include "TestScreeb.h"
#include "DemoScreen.h"
#include "DemoScreen2.h"
#include "ShaderToy.h"
#include "PaternTestScreen.h"
#include "HiganMainMenuScreen.h"
#include "CharacterTestScreen.h"
#include "Extra_DemoScreen.h"
#include "ReplayScreen.h"
#include "TestRenderScreen.h"
#include "TestRender3D.h"


class App : public Feintgine::IMainGame
{
public:
	App();
	~App();

	virtual void onInit() override;
	virtual void addScreen() override;
	virtual void onExit() override;

private:
	//std::unique_ptr<GameTownScreen>m_gametownScreen = nullptr;
	//std::unique_ptr<MainMenuScreen>m_mainmenuScreen = nullptr;
	//std::unique_ptr<GameplayScreen>m_gameplayScreen = nullptr;
	std::unique_ptr<DemoScreen>m_demo = nullptr;
	std::unique_ptr<HiganMainMenuScreen> m_higanScreen = nullptr;

	std::unique_ptr<CharacterTestScreen> m_testCharScreen = nullptr;

	std::unique_ptr<TestRenderScreen> m_testRenderScreen = nullptr;

	//std::unique_ptr<TestScreen> m_testScreen = nullptr;
	//std::unique_ptr<SelectScreen> m_selectScreen = nullptr;
	std::unique_ptr<TestScreeb> m_test = nullptr;
	std::unique_ptr<DemoScreen2> m_test2 = nullptr;
	std::unique_ptr<ShaderToy> m_shaderToy = nullptr;
	std::unique_ptr<PaternTestScreen> m_paternTest = nullptr;
	
	// Demo 
	std::unique_ptr<Extra_DemoScreen> m_extraDemo = nullptr;

	//Replay 
	std::unique_ptr<ReplayScreen> m_replayScreen = nullptr;

	// 3D test render
	std::unique_ptr<TestRender3D> m_3dScreen = nullptr;


};

