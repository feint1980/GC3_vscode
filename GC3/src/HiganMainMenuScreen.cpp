#include "HiganMainMenuScreen.h"

#pragma execution_character_set( "utf-8" )

HiganMainMenuScreen::HiganMainMenuScreen()
{
	

}

HiganMainMenuScreen::HiganMainMenuScreen(Feintgine::Window * window)
{
	initShader();

	m_screenIndex = 3;
	m_alpha = 1;

	m_titleJapTextPos_1 = glm::vec2(0, 250);
	m_titleEngTextPos_1 = glm::vec2(0, 150);



	m_titleJapTextPos_2 = glm::vec2(-450,-320);
	m_titleEngTextPos_2 = glm::vec2(-450,-360);

	currentJapTextPos = m_titleJapTextPos_1;
	currentEngTextPos = m_titleEngTextPos_1;

	m_textScale = 1.0f;
}

HiganMainMenuScreen::~HiganMainMenuScreen()
{

}

int HiganMainMenuScreen::getNextScreenIndex() const
{
	return -1;
	//throw std::logic_error("The method or operation is not implemented.");
}

int HiganMainMenuScreen::getPreviousScreenIndex() const
{
	return -1;
	//throw std::logic_error("The method or operation is not implemented.");
}

void HiganMainMenuScreen::build()
{
	//throw std::logic_error("The method or operation is not implemented.");
}

void HiganMainMenuScreen::destroy()
{
	//throw std::logic_error("The method or operation is not implemented.");
}

void HiganMainMenuScreen::onEntry()
{

	m_audioEngine.init();
	m_camera.init(1366, 768);
	m_camera.setScale(1.0f);
	m_camera.startShake(0, 0, 0);
	m_camera.setPosition(glm::vec2(0));
	glm::vec2 originalResolution(2500, 1553);
	float resolutionScale = 1366.0f / 2500.0f;

	Feintgine::SpriteManager::Instance()->loadFromDirectory("Assets/", 0);

	bg.init(Feintgine::ResourceManager::getTexture(
		"./Assets/Textures/shiki_furahata_gen.png"), glm::vec2(0),
		originalResolution * resolutionScale,
		Feintgine::Color(255, 255, 255, 255));


	selectBg.init(Feintgine::ResourceManager::getTexture(
		"./Assets/Textures/selectBG.png"), glm::vec2(0),
		glm::vec2(1366, 768),
		Feintgine::Color(200, 200, 200, 200));


	m_reimu.init(Feintgine::ResourceManager::getTexture(
		"./Assets/Textures/Reimu_framed.png"), glm::vec2(250, 200),
		glm::vec2(160, 288),glm::vec4(0, 0.0, 0, 0), 5.0f);

	m_reimu.addDesciptionTexture(Feintgine::ResourceManager::getTexture(
		"./Assets/Textures/Reimu_name_light_sd.png"), glm::vec2(420, 0));
	//m_reimu.setVisible(false);

	m_marisa.init(Feintgine::ResourceManager::getTexture(
		"./Assets/Textures/Marisa_framed.png"), glm::vec2(420, 200), 
		glm::vec2(160, 288),glm::vec4(0, 0.0, 0, 0), 6.0f);
	m_marisa.addDesciptionTexture(Feintgine::ResourceManager::getTexture(
		"./Assets/Textures/marisa_name_light_sd.png"), glm::vec2(420, 0));
	//m_marisa.setVisible(false);

	m_patchouli.init(Feintgine::ResourceManager::getTexture(
		"./Assets/Textures/patchouli_framed.png"), glm::vec2(600, 200),
		glm::vec2(160, 288), glm::vec4(0, 0.0, 0, 0), 6.0f);
	//m_patchouli.setVisible(false);


	m_avtSelection.addCharacter(m_reimu);
	m_avtSelection.addCharacter(m_marisa);
	m_avtSelection.addCharacter(m_patchouli);
	m_avtSelection.setVisible(false);

	std::cout << "here \n";
	m_camera.update();
	m_spriteBatch.init();
	m_timerSpriteBatch.init();
	
	

	m_spriteFont = new Feintgine::SpriteFont("font/ARIALUNI.ttf", 30);

	initGUI();


}

void HiganMainMenuScreen::onExit()
{
	//throw std::logic_error("The method or operation is not implemented.");
}

void HiganMainMenuScreen::update(float deltaTime)
{

	if (!loaded && !startLoad)
	{
		
		firstCheckPoint();
		startLoad = true;
		//std::thread load(&ShaderToy::firstCheckPoint, this);
		//load.join();

		return;
	}
	else
	{
		//std::cout << "loaded \n";
		updateStartupEffect(deltaTime);

		fadeMainMenu(deltaTime);
		showMainMenu(deltaTime);

		showBackgound(deltaTime);
		hideBackgound(deltaTime);
	
		updateTextPos(deltaTime);

		m_avtSelection.update(deltaTime);
		m_demoBoard.update(deltaTime);
		m_demoBoard.updateSelection(m_avtSelection.getCurrentSelection());

		m_camera.update();
	}
	
	//throw std::logic_error("The method or operation is not implemented.");
}

void HiganMainMenuScreen::draw()
{

	if (!loaded)
	{
		drawLoadingScreen();
	}
	else
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
		drawBackground();
		drawMainMenu();
		drawAvat();
		drawDemoType();
		drawDemoText();
		m_gui.draw();
		m_gui2.draw();	
	}


}

void HiganMainMenuScreen::checkInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{
		m_game->onSDLEvent(evnt);
		m_gui.onSDLEvent(evnt);
		m_gui2.onSDLEvent(evnt);
		
		
		
		
	}
	handleInput(m_game->m_inputManager);
	m_camera.handleInput(m_game->m_inputManager, evnt);
	if (currentScreenState == SELECTION_STATE)
	{
		m_avtSelection.handleInput(m_game->m_inputManager,m_camera);
	}
	else
	{
		m_avtSelection.clearAllSelection();
	}
}

void HiganMainMenuScreen::initShader()
{
	m_shader.compileShaders("Shaders/HiganMainMenuScreen/texture.vert", "Shaders/HiganMainMenuScreen/texture.frag");
	m_shader.addAttribute("vertexPosition");
	m_shader.addAttribute("vertexColor");
	m_shader.addAttribute("vertexUV");
	m_shader.linkShaders();

	m_selectScreenShader.compileShaders("Shaders/HiganMainMenuScreen/texture.vert", "Shaders/HiganMainMenuScreen/texture.frag");
	m_selectScreenShader.addAttribute("vertexPosition");
	m_selectScreenShader.addAttribute("vertexColor");
	m_selectScreenShader.addAttribute("vertexUV");
	m_selectScreenShader.linkShaders();

	m_shaderNormal.compileShaders("Shaders/ShaderToy/texture.vert", "Shaders/ShaderToy/texture.frag");
	m_shaderNormal.addAttribute("vertexPosition");
	m_shaderNormal.addAttribute("vertexColor");
	m_shaderNormal.addAttribute("vertexUV");
	m_shaderNormal.linkShaders();
 
	m_avtShader.compileShaders("Shaders/HiganMainMenuScreen/avtShader.vert", "Shaders/HiganMainMenuScreen/avtShader.frag");
	m_avtShader.addAttribute("vertexPosition");
	m_avtShader.addAttribute("vertexColor");
	m_avtShader.addAttribute("vertexUV");
	m_avtShader.linkShaders();



}

void HiganMainMenuScreen::handleInput(Feintgine::InputManager & inputManager)
{
	if (inputManager.isKeyPressed(SDLK_ESCAPE))
	{
		handleBackPress(); 
	}
}

void HiganMainMenuScreen::drawLoadingScreen()
{
	glViewport(0, 0, 1366, 768);
	glm::mat4 projectionMatrix;
	GLint pUniform;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_shaderNormal.use();

	//glViewport(0, 600 / 2, 1000 / 2, 600 / 2);
	// Upload texture uniform
	GLint textureUniform = m_shaderNormal.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	glActiveTexture(GL_TEXTURE0);

	// Camera matrix
	projectionMatrix = m_camera.getCameraMatrix();
	pUniform = m_shaderNormal.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	//GLint dayLightIndex = m_foregroundShader->getUniformLocation("dayLight");
	//glUniform3f(dayLightIndex, 1.0, 1.0, 1.0);

	//m_lightBatch.begin();


	//m_lightBatch.renderLight();

	char buffer2[256];

	sprintf_s(buffer2, "Loading ...");
	m_timerSpriteBatch.begin();

	m_spriteFont->draw(m_timerSpriteBatch, buffer2, glm::vec2(-100, 0), glm::vec2(1), 0, Feintgine::Color(255, 255, 255, 255));

	m_timerSpriteBatch.end();
	m_timerSpriteBatch.renderBatch();

	m_shaderNormal.unuse();



}

void HiganMainMenuScreen::firstCheckPoint()
{
	m_textRenderer.init(102, 32000, "font/OtsutomeFont_Ver3.ttf");
	m_textRendererEn.init(50, 300, "font/OtsutomeFont_Ver3.ttf");

	loaded = true;
}

void HiganMainMenuScreen::initGUI()
{
	m_gui.init("GUI");
	m_gui.loadScheme("TaharezLook.scheme");
	m_gui.loadScheme("VanillaSkin.scheme");
	m_gui.loadScheme("WindowsLook.scheme");
	m_gui.loadScheme("Generic.scheme");

	m_gui.setFont("DejaVuSans-12");

	m_gui2.init("GUI");
	m_gui2.loadScheme("TaharezLook.scheme");
	m_gui2.loadScheme("VanillaSkin.scheme");
	m_gui2.loadScheme("WindowsLook.scheme");
	m_gui2.loadScheme("Generic.scheme");

	m_gui2.setFont("DejaVuSans-12_a");


	m_gui2.setMouseCursor("TaharezLook/MouseArrow");
	m_gui.setMouseCursor("TaharezLook/MouseArrow");
	SDL_ShowCursor(0);

	m_startButton.init("Start Game", "m_startButton", m_gui, glm::vec4(0.08f, 0.44f, 0.15f, 0.05f),
		[&](const CEGUI::EventArgs & e) {

		std::cout << "Start \n";
		switchState(SELECTION_STATE);
// 
// 		b_fadeMainMenu = true;
// 		selectionScreen = true;
//		m_startButton.hide();
// 		m_startButton.hide();
// 		m_startButton.hide();
// 		m_startButton.hide();
		//showRegisterPanel();

		return true;
	});
	m_optionButton.init("Options", "m_optionButton", m_gui, glm::vec4(0.08f, 0.52f, 0.15f, 0.05f),
		[&](const CEGUI::EventArgs & e) {

		std::cout << "Option \n";
		//hideSlice();
		//showRegisterPanel();

		return true;
	});
	m_creditButton.init("Credit", "m_creditButton", m_gui, glm::vec4(0.08f, 0.6f, 0.15f, 0.05f),
		[&](const CEGUI::EventArgs & e) {

		std::cout << "Credit \n";
		//hideSlice();
		//showRegisterPanel();

		return true;
	});

	m_exitButton.init("Exit", "m_exitButton", m_gui, glm::vec4(0.08f, 0.68f, 0.15f, 0.05f),
		[&](const CEGUI::EventArgs & e) {

		std::cout << "Exit \n";
		m_currentState = Feintgine::ScreenState::EXIT_APPLICATION;
		return true;
	});


	m_panelUnderstand.init("I understand", "m_panelUnderstand", m_gui2, 
		glm::vec4(0.4f, 0.8f, 0.3f, 0.2f), [&](const CEGUI::EventArgs & e) {

		notePanelEnd = true;
		std::cout << "close \n";
		return true;
	});
	m_panelUnderstand.setTextAlignment("HorzFormatting", "HorzCentred");

	m_startButton.setAlpha(0);
	m_optionButton.setAlpha(0);
	m_creditButton.setAlpha(0);
	m_exitButton.setAlpha(0);

// 	m_startButton.getButton()->hide();
// 	m_optionButton.getButton()->hide();
// 	m_creditButton.getButton()->hide();
// 	m_exitButton.getButton()->hide();

	credit = static_cast<CEGUI::DefaultWindow*>(m_gui2.createWidget("Generic/LabelWithOutline", glm::vec4(0.72, .865f, 0.0f, 0.2f), glm::vec4(0.0f), "credit"));
	std::string copyright = "Blind Eye team fan-game demo (v1.00).";
	credit->setText((CEGUI::utf8*) copyright.c_str());
	//	credit->subscribeEvent(CEGUI::DefaultWindow::EventMouseLeavesSurface, CEGUI::Event::Subscriber(&MainMenuScreen::onNewGameClicked, this));
	credit->setProperty("HorzFormatting", "LeftAligned");
	credit->setAlpha(0);

	disclaimerContent = static_cast<CEGUI::DefaultWindow *> (m_gui2.createWidget(("TaharezLook/Label"), 
		glm::vec4(0.45, 0.05f, 0.08f, 0.08f), glm::vec4(0.0), "disclaimerContent"));
	disclaimerContent->setProperty("HorzFormatting", "HorzCentred");
	disclaimerContent->setText("Note");
	notePanel = static_cast<CEGUI::GroupBox *> (m_gui2.createWidget(("TaharezLook/GroupBox"), glm::vec4(0.3, 0.25f, 0.4f, 0.45f), glm::vec4(0.0), "notePanel"));
	//loginPanel->setAlpha(0.0f);
	panelBackground = static_cast<CEGUI::DefaultWindow*>(m_gui2.createWidget("TaharezLook/StaticImage", glm::vec4(0.0, 0.0f, 1.0f, 1.0f), glm::vec4(0.0f), "popup"));
	panelBackground->setAlwaysOnTop(false);

	noteContent = static_cast<CEGUI::DefaultWindow *> (m_gui2.createWidget(("TaharezLook/Label"),
		glm::vec4(0.06, 0.1f, 0.88f, 0.8f), glm::vec4(0.0), "noteContent"));
	
	noteContent->setProperty("HorzFormatting", "WordWrapLeftAligned");

	noteContent->setText("This demo is a fan-made project based on Touhou Project ,some details may not \
			be canon and some of the materials (such as arts, musics) \
			from this demo are still pending for permission from respective artists, this demo is aimed to showcase \
			the gameplay of upcoming project from Blind Eye team. \n\n \
			                                                     ~ Blind Eye team.");
	//noteContent->setHorizontalAlignment(CEGUI::HA_LEFT);
	//noteContent->setAlwaysOnTop(true);

	m_demoBoard.init(m_audioEngine);

	notePanel->addChild(panelBackground);
	notePanel->addChild(noteContent);
	notePanel->addChild(disclaimerContent);
	notePanel->addChild(m_panelUnderstand.getButton());
	notePanel->setAlpha(0);
}

void HiganMainMenuScreen::updateStartupEffect(float delta)
{
	if (doneStartup)
	{
		
		updateTextAlpha(delta);
		return;
	}
	else
	{
		
		if (peak)
		{
 			if (m_effectAlpha > 1.0f)
 			{
 				m_effectAlpha -= Higan_startdownRate * delta;
 			}
			else
			{
				doneStartup = true;
				m_effectAlpha = 1.0f;
			}
		}
		else
		{
			if (m_effectAlpha < 3.0f)
			{
				m_effectAlpha += Higan_startupRate * delta;

			}
			else
			{


				std::cout << "peak\n";
				peak = true;

			}
		}
	   // std::cout << m_effectAlpha << "\n";
		bg.setSPec(m_effectAlpha);

	}
}

void HiganMainMenuScreen::updateTextAlpha(float delta)
{
	if (!textAlphaDone)
	{


		if (textAlpha < 1.0f)
		{
			textAlpha += Higan_startupRate * delta;
		}
		if (textAlpha > 1.0f)
		{
			textAlpha = 1.0f;
			textAlphaDone = true;
			m_startButton.setReady(true);
			m_optionButton.setReady(true);
			m_creditButton.setReady(true);
			m_exitButton.setReady(true);
		}
		
		m_startButton.setAlpha(textAlpha);
		m_optionButton.setAlpha(textAlpha);
		m_creditButton.setAlpha(textAlpha);
		m_exitButton.setAlpha(textAlpha);
		credit->setAlpha(textAlpha);
		
		//credit->setWidth(credit->getWidth() + CEGUI::UDim::UDim(0.005f, 0.0f));
		
	}
	else
	{
		updatePanelStartUp(delta);
	}
	if (withDraw <= 1.0f)
	{
		credit->setWidth(credit->getWidth() + CEGUI::UDim::UDim(0.006f, 0.0f));
		withDraw += Higan_startdownRate * delta;
	}
}

void HiganMainMenuScreen::updatePanelStartUp(float delta)
{

	if (!notePanelStart)
	{
		//glm::vec2 panelSize(0.4f, 0.45f);
		if (notePanelScale <= 1.0f)
		{
			notePanelScale += Higan_startupRate * delta;
			notePanel->setAlpha(notePanelScale);
		}
		else
		{
			m_panelUnderstand.setReady(true);
			notePanelStart = true;
		}

	}
	else
	{
		updatePanelEnd(delta);
	}
	
}

void HiganMainMenuScreen::updatePanelEnd(float delta)
{
	if (notePanelEnd)
	{
		if (notePanelScale >= 0.0f)
		{
			notePanelScale -= Higan_startupRate * delta;
			notePanel->setAlpha(notePanelScale);
		}
		if (notePanelScale < 0.0f)
		{
			notePanel->setEnabled(false);
			notePanel->hide();
		}
		//std::cout << notePanelScale << "\n";
	}
}

void HiganMainMenuScreen::fadeMainMenu(float delta)
{
	if (b_fadeMainMenu)
	{
		if (m_effectAlpha >= 0.0f)
		{

			
			m_effectAlpha -= Higan_startdownRate * delta;


			if (m_effectAlpha < 0.0f)
			{
				m_effectAlpha = 0.0f;
			}
			m_startButton.setAlpha(m_effectAlpha);
			m_optionButton.setAlpha(m_effectAlpha);
			m_creditButton.setAlpha(m_effectAlpha);
			m_exitButton.setAlpha(m_effectAlpha);
			//std::cout << m_effectAlpha << "\n";
		}
		else
		{
			m_startButton.setAlpha(0);
			m_optionButton.setAlpha(0);
			m_creditButton.setAlpha(0);
			m_exitButton.setAlpha(0);
			b_fadeMainMenu = false;
			m_startButton.getButton()->hide();
			m_optionButton.getButton()->hide();
			m_creditButton.getButton()->hide();
			m_exitButton.getButton()->hide();
		}
	}
}

void HiganMainMenuScreen::drawBackground()
{
	m_selectScreenShader.use();
	glm::mat4 projectionMatrix;
	GLint pUniform;



	GLint textureUniform = m_selectScreenShader.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	glActiveTexture(GL_TEXTURE0);
	projectionMatrix = m_camera.getCameraMatrix();
	pUniform = m_selectScreenShader.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);


	GLint alphaLocation = m_selectScreenShader.getUniformLocation("intensity");
	glUniform1f(alphaLocation, m_backgoundAlpha);

	m_spriteBatch.begin();
	selectBg.draw(m_spriteBatch);
	

	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_selectScreenShader.unuse();
	glDisable(GL_SCISSOR_TEST);

}

void HiganMainMenuScreen::showBackgound(float delta)
{
	if (showSelectionScreen)
	{
		if (m_backgoundAlpha <= 1.0f)
		{
			m_backgoundAlpha += Higan_startdownRate * delta;

		}
		else
		{

			showSelectionScreen = false;
			
		}
	}
}

void HiganMainMenuScreen::drawMainMenu()
{

	m_shader.use();
	glm::mat4 projectionMatrix;
	GLint pUniform;

	GLint textureUniform = m_shader.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	glActiveTexture(GL_TEXTURE0);
	projectionMatrix = m_camera.getCameraMatrix();
	pUniform = m_shader.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);


	GLint alphaLocation = m_shader.getUniformLocation("intensity");
	glUniform1f(alphaLocation, m_effectAlpha);

	m_spriteBatch.begin();
	bg.draw(m_spriteBatch);

	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_shader.unuse();
	//glDisable(GL_SCISSOR_TEST);
	m_textRenderer.renderText(m_camera, L"東方彼岸秘密",
		currentJapTextPos,
		Feintgine::Color(255, 255, 255, 255 * textAlpha), m_textScale, ALIGN_FT_CENTER);
	m_textRendererEn.renderText(m_camera, L"Higan's Hidden Path",
		currentEngTextPos,
		Feintgine::Color(255, 255, 255, 255 * textAlpha), m_textScale, ALIGN_FT_CENTER);

}

void HiganMainMenuScreen::handleState(float delta)
{
	switch (currentScreenState)
	{
	case MAIN_MENU_STATE:

		m_startButton.setReady(false);
		m_optionButton.setReady(false);
		m_creditButton.setReady(false);
		m_exitButton.setReady(false);

		m_startButton.getButton()->show();
		m_optionButton.getButton()->show();
		m_creditButton.getButton()->show();
		m_exitButton.getButton()->show();

		hideSelectionScreen = true;
		b_showMainMenu = true;

		b_fadeMainMenu = false;
		showSelectionScreen = false;
		m_avtSelection.setVisible(false);
	
		break;
	case SELECTION_STATE:

		m_startButton.setReady(false);
		m_optionButton.setReady(false);
		m_creditButton.setReady(false);
		m_exitButton.setReady(false);

		b_fadeMainMenu = true;
		showSelectionScreen = true;

		hideSelectionScreen = false;
		b_showMainMenu = false;
		m_avtSelection.setVisible(true);

		break;
	default:
		break;
	}
}

void HiganMainMenuScreen::switchState(int val)
{
	previousState = currentScreenState;
	currentScreenState = val;
	handleState(0);

}

void HiganMainMenuScreen::handleBackPress()
{
	currentScreenState = previousState;
	previousState = MAIN_MENU_STATE;
	handleState(0);
}

void HiganMainMenuScreen::hideBackgound(float delta)
{
	if (hideSelectionScreen)
	{
		if (m_backgoundAlpha >= 1.0f)
		{
			m_backgoundAlpha -= Higan_startdownRate * delta;

		}
		else
		{

			hideSelectionScreen = false;

		}
	}
}

void HiganMainMenuScreen::showMainMenu(float delta)
{
	if (b_showMainMenu)
	{
			

		if (m_effectAlpha <= 1.0f)
		{
			if (m_effectAlpha < 0.0f)
			{
				m_effectAlpha = 0.0f;
			}
			m_effectAlpha += Higan_startdownRate * delta;
			m_startButton.setAlpha(m_effectAlpha);
			m_optionButton.setAlpha(m_effectAlpha);
			m_creditButton.setAlpha(m_effectAlpha);
			m_exitButton.setAlpha(m_effectAlpha);		
			
		}
		else
		{
			m_startButton.setAlpha(1.0f);
			m_optionButton.setAlpha(1.0f);
			m_creditButton.setAlpha(1.0f);
			m_exitButton.setAlpha(1.0f);
			m_startButton.setReady(true);
			m_optionButton.setReady(true);
			m_creditButton.setReady(true);
			m_exitButton.setReady(true);
			b_showMainMenu = false;
		
		}
	}
}

void HiganMainMenuScreen::updateTextPos(float delta)
{
	if (b_fadeMainMenu)
	{
		if (m_textScale > 0.5f)
		{
			m_textScale -= 0.0125f * delta;
		}
		else
		{
			m_textScale = 0.5f;
		}
		if (currentJapTextPos.x > m_titleJapTextPos_2.x && currentJapTextPos.y > m_titleJapTextPos_2.y)
		{

			glm::vec2 directionJap = m_titleJapTextPos_1 - m_titleJapTextPos_2;
			

			directionJap *= 0.05f;
			
			currentJapTextPos -= directionJap * delta;
			
		}
		else
		{
			currentJapTextPos = m_titleJapTextPos_2;
			
		}
		if (currentEngTextPos.x > m_titleEngTextPos_2.x && currentEngTextPos.y > m_titleEngTextPos_2.y)
		{
			glm::vec2 directionEng = m_titleEngTextPos_1 - m_titleEngTextPos_2;
			directionEng *= 0.05f;
			currentEngTextPos -= directionEng * delta;
		}
		else
		{
			currentEngTextPos = m_titleEngTextPos_2;
		}
	}
	if (b_showMainMenu)
	{
		if (m_textScale <= 1.0f)
		{
			m_textScale += 0.025f * delta;
			if (m_textScale > 1.0f)
			{
				m_textScale = 1.0f;
			}
			//std::cout << m_textScale << "\n";
		}
		else
		{
			m_textScale = 1.0f;

		}
		if (currentJapTextPos.x < m_titleJapTextPos_1.x && currentJapTextPos.y < m_titleJapTextPos_1.y)
		{

			glm::vec2 directionJap = m_titleJapTextPos_1 - m_titleJapTextPos_2;


			directionJap *= 0.05f;


			currentJapTextPos += directionJap * delta;

		}
		else
		{
			currentJapTextPos = m_titleJapTextPos_1;

		}
		if (currentEngTextPos.x < m_titleEngTextPos_1.x && currentEngTextPos.y < m_titleEngTextPos_1.y)
		{
			glm::vec2 directionEng = m_titleEngTextPos_1 - m_titleEngTextPos_2;
			directionEng *= 0.05f;
			currentEngTextPos += directionEng * delta;
			//std::cout << feint_common::Instance()->convertiVec2toString(currentEngTextPos) << "\n";
		}
		else
		{
			currentEngTextPos = m_titleEngTextPos_1;
		}
	}
}

void HiganMainMenuScreen::drawAvat()
{
	m_avtShader.use();
	glm::mat4 projectionMatrix;
	GLint pUniform;

	GLint textureUniform = m_avtShader.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	glActiveTexture(GL_TEXTURE0);
	projectionMatrix = m_camera.getCameraMatrix();
	pUniform = m_avtShader.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);


	m_spriteBatch.begin(Feintgine::GlyphSortType::FRONT_TO_BACK);
	m_avtSelection.draw(m_spriteBatch);
	//m_demoBoard.draw(m_spriteBatch);
	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_avtShader.unuse();

}

void HiganMainMenuScreen::drawDemoType()
{
	m_shaderNormal.use();
	glm::mat4 projectionMatrix;
	GLint pUniform;

	GLint textureUniform = m_shaderNormal.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	glActiveTexture(GL_TEXTURE0);
	projectionMatrix = m_camera.getCameraMatrix();
	pUniform = m_shaderNormal.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);


	m_spriteBatch.begin(Feintgine::GlyphSortType::FRONT_TO_BACK);
	//m_avtSelection.draw(m_spriteBatch);
	m_demoBoard.draw(m_spriteBatch);
	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_shaderNormal.unuse();
}

void HiganMainMenuScreen::drawDemoText()
{
	m_demoBoard.drawDecription(m_camera, m_textRenderer);
}
