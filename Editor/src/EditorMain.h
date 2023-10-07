#pragma once

#include <IMainGame.h>
#include "EditorScreen.h"
#include "TestCEGUIScreen.h"
#include "NewRenderModel.h"


class EditorMain : public Feintgine::IMainGame
{
public:
	EditorMain();
	~EditorMain();

	virtual void onInit() override;
	virtual void addScreen() override;
	virtual void onExit() override;

private:

	std::unique_ptr<EditorScreen>m_screen = nullptr;
	std::unique_ptr<TestCEGUIScreen> m_test = nullptr;
	std::unique_ptr<NewRenderModel> m_renderTest = nullptr;



};

