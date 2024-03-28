
#include "Extra_DemoScreen.h"

void capture()
{
	//for (int i = 0; i < 100; i++)
	//{
		
		//Feintgine::F_ScreenCapture::Instance()->captureScreen(1, 1);
		//std::this_thread::sleep_for(std::chrono::milliseconds(16));
	//}
	
}

ShaderValueType getShaderValueType(const std::string & typeName)
{
	
	if (typeName == "Float")
	{
		return T_Float;
	}
	if (typeName == "Int")
	{
		return T_Int;
	}
	if (typeName == "Vec2")
	{
		return T_Vec2;
	}
	if (typeName == "Vec3")
	{
		return T_Vec3;
	}

	return T_Undefined;
}


Extra_DemoScreen::Extra_DemoScreen()
{
}

Extra_DemoScreen::Extra_DemoScreen(Feintgine::Window * window)
{
	m_screenIndex = 32;
	std::cout << "number " << SHADER_TEST_MODE << "\n";
	m_window = window;
	m_alpha = 1;

	initShader();
	m_foregroundShader = &m_shader;
	m_backgroundShader = &m_whiteBlackShader;
}

Extra_DemoScreen::~Extra_DemoScreen()
{
}

int Extra_DemoScreen::getNextScreenIndex() const
{
	return 33;
}

int Extra_DemoScreen::getPreviousScreenIndex() const
{
	return -1;
}

void Extra_DemoScreen::build()
{
	// build screen
}

void Extra_DemoScreen::destroy()
{
	// unload screen
}

void Extra_DemoScreen::onEntry()
{
	//auto task = async::spawn([&]() {
	
	//});
	TTF_Init();
	m_debug.init();
	m_camera.init(768, 768, 0);

	GlobalValueClass::Instance()->setGameplayCamera(&m_camera);

	//m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight(),7);
	//m_window->getScreenWidth(), m_window->getScreenHeight());
	m_sideCam.init(1366, 768);

	m_camera.setScale(1.0f);
	m_camera.setPosition(glm::vec2(0));

	m_sideCam.setScale(1.0f);
	m_sideCam.setPosition(glm::vec2(0));
	
	bg.init(Feintgine::ResourceManager::getTexture("./Assets/Textures/Spider_lily.png"), glm::vec2(0), glm::vec2(1366, 768),
		Feintgine::Color(255, 255, 255, 255));
	bg1.init(Feintgine::ResourceManager::getTexture("./Assets/Textures/noise_4.png"), glm::vec2(0), glm::vec2(1366, 768),
		Feintgine::Color(255, 255, 255, 255));

	bg2.init(Feintgine::ResourceManager::getTexture("./Assets/Textures/shadowing.png"), glm::vec2(0), glm::vec2(2000, 1000),
		Feintgine::Color(-100,-100, -100, 40));
	
	m_camera.update();
	m_sideCam.update();
	m_spriteBatch.init();
	m_timerSpriteBatch.init();

	GlobalValueClass::Instance()->savedCamera = &m_camera;

	//m_spriteFont = new Feintgine::SpriteFont("font/ARIALUNI.ttf", 30);
	m_audioEngine.init();
	//m_audioEngine.setVolume(10); // turn off volume (




	GlobalValueClass::Instance()->setAmbientLight(glm::vec3(dayLight));
	SDL_GL_SetSwapInterval(1);


	//Feintgine::F_ScreenCapture::Instance()->init();
	//m_capture.init();

	GlobalValueClass::Instance()->setLightBalance(false);

	//m_imgui.init(m_window->getWindow(), m_window->getGLContext());
	// m_text_test.init("test", glm::vec2(250, 250));

	// m_text_fps.init("m_text_fps", glm::vec2(920, 690));

	// m_text_realTime.init("m_text_realTime", glm::vec2(800, 0));

	//toggleLight();

	
	m_tgui = new tgui::Gui(m_window->getWindow());
	m_tgui_load = new tgui::Gui(m_window->getWindow());
	//std::cout << "font is " << m_tgui->getFont().ge << "\n";

	//m_tgui->setP

	//tgui::BackendText text;
	
	//m_tgui->add(text);

	tgui::Font font("font/ARIALUNI.ttf");
	tgui::Font font_load("font/Chronicle.ttf");
	m_tgui->setFont(font);
	m_tgui_load->setFont(font_load);
	
	//m_tgui->setAbsoluteView

	m_text_realTime_tgui = tgui::Label::create();
	m_text_fps_tgui = tgui::Label::create();
	m_text_eventTime_tgui = tgui::Label::create();
	m_text_spellName = tgui::Label::create();
	m_text_spellSign = tgui::Label::create();
	m_text_load = tgui::Label::create();
	


	m_text_load->setPosition(m_window->getScreenWidth() / 2, m_window->getScreenHeight() / 2);
	m_text_load->setTextSize(32);
	m_text_load->getRenderer()->setTextColor(tgui::Color::White);
	m_text_load->getRenderer()->setBorderColor(tgui::Color::Black);
	m_text_load->getRenderer()->setTextOutlineThickness(4);
	m_text_load->setText("Loading");


	m_text_realTime_tgui->setPosition(800, 50);
	m_text_realTime_tgui->setTextSize(32);
	m_text_realTime_tgui->getRenderer()->setTextColor(tgui::Color::White);
	m_text_realTime_tgui->getRenderer()->setBorderColor(tgui::Color::Black);
	m_text_realTime_tgui->getRenderer()->setTextOutlineThickness(4);
	//m_text_eventTime_tgui->getRenderer()->

	m_text_fps_tgui->setPosition(1200, 720);
	m_text_fps_tgui->setTextSize(32);
	m_text_fps_tgui->getRenderer()->setTextColor(tgui::Color::White);
	m_text_fps_tgui->getRenderer()->setBorderColor(tgui::Color::Black);
	m_text_fps_tgui->getRenderer()->setTextOutlineThickness(4);


	m_text_eventTime_tgui->setPosition(800,100);
	m_text_eventTime_tgui->setTextSize(32);
	m_text_eventTime_tgui->getRenderer()->setTextColor(tgui::Color::White);
	m_text_eventTime_tgui->getRenderer()->setBorderColor(tgui::Color::Black);
	m_text_eventTime_tgui->getRenderer()->setTextOutlineThickness(12);

	m_text_spellName->setPosition(250, 520);
	m_text_spellName->setTextSize(27);
	m_text_spellName->getRenderer()->setTextColor(tgui::Color::White);
	m_text_spellName->getRenderer()->setBorderColor(tgui::Color::Black);
	m_text_spellName->setWidth("100%");
	m_text_spellName->setHeight(50);
	m_text_spellName->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	m_text_spellName->getRenderer()->setTextOutlineThickness(4);


	m_text_spellSign->setPosition(250, 560);
	m_text_spellSign->setTextSize(24);
	m_text_spellSign->getRenderer()->setTextColor(tgui::Color::White);
	m_text_spellSign->getRenderer()->setBorderColor(tgui::Color::Black);
	m_text_spellSign->setWidth("100%");
	m_text_spellSign->setHeight(50);
	m_text_spellSign->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	m_text_spellSign->getRenderer()->setTextOutlineThickness(4);

	m_tgui->add(m_text_realTime_tgui);
	m_tgui->add(m_text_fps_tgui);
	m_tgui->add(m_text_eventTime_tgui);
	m_tgui->add(m_text_spellName);
	m_tgui->add(m_text_spellSign);

	m_tgui_load->add(m_text_load);

	m_bgmLabel.init(m_tgui, glm::vec2(-400,700), L"",0.0f);
	m_chapterLabel.init(m_tgui, glm::vec2(280, 300), L"", L"",0.0f);

}

void Extra_DemoScreen::onExit()
{
	std::cout << "onExit called \n";
}

void Extra_DemoScreen::update(float deltaTime)
{

	if(!loaded)
	{
		if(!startLoad)
		{
			startLoad = true;
			// auto task1 = async::spawn([&] {
			
			// 	firstCheckPoint();
			// });
			firstCheckPoint();
			return;
		}
	}

	m_camera.update();

	updateShaderCamera(deltaTime);

	m_shaderTime += 0.01075f* deltaTime;

	if (loaded)
	{
		m_player.update(deltaTime, m_enemies, m_bullets, m_guardians, m_amplifiers);

		m_bg.update(deltaTime);
		//m_bg2.update(deltaTime);

		if (startCount)
		{
			m_particleEngine.update(deltaTime);
			for (auto it = m_enemies.begin(); it != m_enemies.end(); )
			{
				(*it)->update(deltaTime);

				if (!(*it)->isAlive())
				{
					delete * it;
					it = m_enemies.erase(it);
				}
				else
				{
					++it;
				}
			}
			for (auto it = m_guardians.begin(); it != m_guardians.end(); )
			{
				(*it)->update(deltaTime, m_enemies, m_amplifiers, m_player);

				if (!(*it)->isAlive())
				{
					delete * it;
					it = m_guardians.erase(it);
				}
				else
				{
					++it;
				}
			}

			for (auto it = m_amplifiers.begin(); it != m_amplifiers.end(); )
			{
				(*it)->update(deltaTime, m_amplifiers, m_player);

				if (!(*it)->isAlive())
				{
					delete * it;
					it = m_amplifiers.erase(it);
				}
				else
				{
					++it;
				}
			}
			for (int i = 0; i < m_enemies.size(); i++)
			{
				if (m_enemies[i]->m_bullets.size() > 0)
				{
					for (int c = 0; c < m_enemies[i]->m_bullets.size(); c++)
					{
						//m_enemies[i]->m_bullets[c]->initLogic(m_world.get());
						m_bullets.push_back(m_enemies[i]->m_bullets[c]);
					}
					m_enemies[i]->m_bullets.clear();
				}
			}

			for (int i = 0; i < m_exlosions.size(); i++)
			{
				m_exlosions[i].update(deltaTime);
				if (m_exlosions[i].lifeTime < 0)
				{
					m_exlosions.erase(m_exlosions.begin() + i);
				}
			}
			for (int i = 0; i < m_bullets.size(); i++)
			{
				if (m_bullets[i]->m_lifeTime > 0)
				{
					m_bullets[i]->update(deltaTime);
				}
				else
				{
					//delete m_bullets[i];
					m_bullets.erase(m_bullets.begin() + i);
					//std::cout << "erase " << i << "\n";
				}

			}

			for (int i = 0; i < m_labels.size(); i++)
			{
				if (m_labels[i]->isAlive())
				{
					m_labels[i]->update(deltaTime);
				}
				else
				{
					m_labels.erase(m_labels.begin() + i);
				}

			}
			ENGINE_current_tick += (ENGINE_tick_speed * deltaTime);
			Feintgine::F_oEvent::getInstance()->timer();

			updateShader(deltaTime);
			// m_chapterLabel.update(deltaTime);
			// m_bmLabel.update(deltaTime);
			m_linkCreator.update(deltaTime, m_amplifiers, m_bullets, m_player);

		}
		m_kanjiEffectManager.update(deltaTime);

		bulletManipulator.update(deltaTime);

		Feintgine::F_Event::Instance()->timer();
	}
	if (lightChange)
	{

		if (lightPositive)
		{
			if (dayLight < m_lightMaxVal)
			{
				dayLight += m_lightRate;
			}
			else
			{
				lightChange = false;
			}

		}
		else
		{
			if (dayLight > m_lightMaxVal)
			{
				dayLight -= m_lightRate;
			}
			else
			{
				lightChange = false;
			}
		}
	}

	// Update FPS
	t_duration = (SDL_GetTicks() - t_start) / (double)CLOCKS_PER_SEC;
//	m_text_realTime.setText(L" Real time(s) : " + feint_common::Instance()->convertPreciousFloatToWString(t_duration));

	// m_text_eventTime.setText(L"Event time(s): " + feint_common::Instance()->convertPreciousFloatToWString(ENGINE_current_tick));

	std::wstring fps = L"Fps: " + std::to_wstring((int) m_game->getFps());
	//std::cout << fps << "\n";
	//m_text_fps.setText(fps);
	m_text_fps_tgui->setText(fps);
	std::string realTime = "Real time(s) : " + std::to_string(t_duration);
	m_text_realTime_tgui->setText(realTime);

	m_text_eventTime_tgui->setText(L"Event time(s): " + feint_common::Instance()->convertPreciousFloatToWString(ENGINE_current_tick));


	int fpsValue = (int) m_game->getFps();
	if(fpsValue > 60)
	{
		m_text_fps_tgui->setTextColor(tgui::Color::White);
	}
	else if(fpsValue < 40)
	{
		m_text_fps_tgui->setTextColor(tgui::Color::Yellow);
	}
	else if(fpsValue < 30)
	{
		m_text_fps_tgui->setTextColor(tgui::Color::Red);
	}


	int tIndex = m_player.getSpellSelector().getCurrentSelection();
	m_text_spellSign->setText(m_player.getSpellSelector().getSpellcards()[tIndex]->getSignName());
	m_text_spellName->setText(m_player.getSpellSelector().getSpellcards()[tIndex]->getSpellName());

	// Update reach timer

	// update recorder 

	m_recorder.update(deltaTime);
	m_effectBatch.update(deltaTime);

	m_bgmLabel.update(deltaTime);
	m_chapterLabel.update(deltaTime);
	//m_tgui->updateTime(deltaTime);
	//Feintgine::F_ScreenCapture::Instance()->saveData();
	

}

void Extra_DemoScreen::draw()
{

	if (!loaded)
	{
		// std::cout << "test \n";
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_tgui_load->draw();
		// drawLoadingScreen();
		return;
	}
	
 	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//drawCustomShader();
	
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// m_shaderNormal.use();
	// m_shaderNormal.unuse();

	//m_frameBuffer.bind();
	//drawBackup(); // was for debug

	// if (GlobalValueClass::Instance()->isLightBalance())
	// {
	// 	drawCustomShader();
	// }
	drawGameplay();
	// m_frameBuffer.unbind();
	// m_frameBufferScreen.use();
	// m_effectBatch.draw();
 	// m_frameBufferScreen.draw();
 	// m_frameBufferScreen.unuse();

	drawTimer();
	//drawGameplay();
	
	//drawGameplay();

	//drawBackup();

	t_currentTick = SDL_GetTicks();
	Uint32 frameTime = t_currentTick - t_prevTick;
	
	t_prevTick = t_currentTick;

	t_counter += (float)frameTime / 1000.0;

	if (t_counter >= 1.0f/60.0f)
	{
		//Feintgine::F_ScreenCapture::Instance()->captureScreen(1, 1);
		t_counter = 0;
	}
	drawGUIText();
}

void Extra_DemoScreen::drawGUIText()
{
	m_tgui->draw();
	// glViewport(0, 0, 1366, 768);

	// m_imgui.begin( ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground );

	// m_text_realTime.update(0.1f);
	// m_text_realTime.render();

	// m_text_spellName.update(0.1f);
	// m_text_spellName.render();

	// m_text_spellSign.update(0.1f);
	// m_text_spellSign.render();

	// m_text_fps.update(0.1f);
	// m_text_fps.render();

	// m_imgui.render();
}

void Extra_DemoScreen::checkInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{

		m_game->onSDLEvent(evnt);
		m_camera.handleInput(m_game->m_inputManager, evnt);

	}
	handleInput(m_game->m_inputManager);
}

void Extra_DemoScreen::initShader()
{
	m_shader.compileShaders("Shaders/ShaderToy/normal.vert", "Shaders/ShaderToy/normal.frag");
	m_shader.addAttribute("vertexPosition");
	m_shader.addAttribute("vertexColor");
	m_shader.addAttribute("vertexUV");
	m_shader.linkShaders();


	m_shaderNormal.compileShaders("Shaders/ShaderToy/texture.vert", "Shaders/ShaderToy/texture.frag");
	m_shaderNormal.addAttribute("vertexPosition");
	m_shaderNormal.addAttribute("vertexColor");
	m_shaderNormal.addAttribute("vertexUV");
	m_shaderNormal.linkShaders();



	m_blackWhiteShader.compileShaders("Shaders/ShaderToy/blackWhite.vert", "Shaders/ShaderToy/blackWhite.frag");
	m_blackWhiteShader.addAttribute("vertexPosition");
	m_blackWhiteShader.addAttribute("vertexColor");
	m_blackWhiteShader.addAttribute("vertexUV");
	m_blackWhiteShader.linkShaders();

	m_whiteBlackShader.compileShaders("Shaders/ShaderToy/whiteBlack.vert", "Shaders/ShaderToy/whiteBlack.frag");
	m_whiteBlackShader.addAttribute("vertexPosition");
	m_whiteBlackShader.addAttribute("vertexColor");
	m_whiteBlackShader.addAttribute("vertexUV");
	m_whiteBlackShader.linkShaders();

	// m_magicalShader.compileShaders("Shaders/MagicalShader/star.vert", "Shaders/MagicalShader/star.frag");
	// m_magicalShader.addAttribute("vertexPosition");
	// m_magicalShader.addAttribute("vertexColor");
	// m_magicalShader.addAttribute("vertexUV");
	// m_magicalShader.linkShaders();

	// m_crystalShader.compileShaders("Shaders/MagicalShader/crystal.vert", "Shaders/MagicalShader/crystal.frag");
	// m_crystalShader.addAttribute("vertexPosition");
	// m_crystalShader.addAttribute("vertexColor");
	// m_crystalShader.addAttribute("vertexUV");
	// m_crystalShader.linkShaders();


	// m_glitchShader.compileShaders("Shaders/MagicalShader/glitch.vert", "Shaders/MagicalShader/glitch.frag");
	// m_glitchShader.addAttribute("vertexPosition");
	// m_glitchShader.addAttribute("vertexColor");
	// m_glitchShader.addAttribute("vertexUV");
	// m_glitchShader.linkShaders();

	// m_portalShader.compileShaders("Shaders/MagicalShader/crystal_fix.vert", "Shaders/MagicalShader/crystal_fix.frag");
	// m_portalShader.addAttribute("vertexPosition");
	// m_portalShader.addAttribute("vertexColor");
	// m_portalShader.addAttribute("vertexUV");
	// m_portalShader.linkShaders();

	
	// m_portalShader.compileShaders("Shaders/MagicalShader/cloud.vert", "Shaders/MagicalShader/cloud.frag");
	// m_portalShader.addAttribute("vertexPosition");
	// m_portalShader.addAttribute("vertexColor");
	// m_portalShader.addAttribute("vertexUV");
	// m_portalShader.linkShaders();


	GLuint tex_fb  = m_frameBuffer.init(768, 768,false);


	//GLuint tex_fb = m_frameBuffer.init(m_window->getScreenWidth(), m_window->getScreenHeight());


	m_frameBufferScreen.initShader("Shaders/FBO/defaultshader_FBO.vert", "Shaders/FBO/defaultshader_FBO.frag");

	m_frameBufferScreen.initFrameTexture(tex_fb,768, 768);

	m_frameBufferScreen.initFrameTexture(tex_fb, m_window->getScreenWidth(), m_window->getScreenHeight());

	m_effectBatch.initEffectBatch(&m_frameBufferScreen, &m_camera);


	m_lightBatch.initShader(&m_shader);


	std::cout << " init shader called \n";
}

void Extra_DemoScreen::handleInput(Feintgine::InputManager & inputManager)
{
	if (ENGINE_isGameRunning)
	{
		m_player.handleInput(inputManager);
	}

	if (inputManager.isKeyPressed(SDLK_ESCAPE))
	{
		togglePause();
		m_pauseMenu.togglePause();
		togglePauseLogic();
	}

	//if (inputManager.isKeyPressed(SDL_BUTTON_LEFT))
	//{
	//	m_effectBatch.addRippleEffect(m_camera.convertScreenToWorld(inputManager.getMouseCoords()), 0.5f, 3.5f, 0.0f);
	//}

	

	if (inputManager.isKeyPressed(SDL_QUIT))
	{
		m_currentState = Feintgine::ScreenState::EXIT_APPLICATION;
	}

	if (inputManager.isKeyPressed(SDLK_F3))
	{
		toggleLight();

	}
	// if (inputManager.isKeyPressed(SDLK_p))
	// {
	// 	Feintgine::F_ScreenCapture::Instance()->manualSave();
	// }

	

	if (inputManager.isKeyPressed(SDLK_HOME))
	{
		toggleLightAE();
	}

	if (inputManager.isKeyPressed(SDLK_TAB))
	{

		switchShader();
	}

	if (inputManager.isKeyPressed(SDLK_BACKSPACE))
	{
		reloadLevel();
	}
	if (inputManager.isKeyPressed(SDLK_F6))
	{
		//m_recorder.writeRecord("test.txt");
		m_player.writeRecord("test.txt");
	}
	if (inputManager.isKeyPressed(SDLK_F7))
	{

		bulletManipulator.addPatern(-1, 0);
		//m_player.writeRecord("test.txt");
		//m_recordPlayer.loadFromFile("test.txt");
	}
	if (inputManager.isKeyPressed(SDLK_F3))
	{
		toggleLight();

	}
	if (inputManager.isKeyPressed(SDLK_F5))
	{
		toggleBalanceLight();

	}

	if (inputManager.isKeyPressed(SDLK_z))
	{
		m_cloudCameraViewFlag = 0;
		m_cloudCameraPosFlag = 0;

	}
	if (inputManager.isKeyPressed(SDLK_LCTRL))
	{
		toggleCTRL();
	}
	




// 	if (inputManager.isKeyDown(SDLK_4))
// 	{
// 		m_camVel.y -= 0.01f;;
// 	}
// 
// 	if (inputManager.isKeyDown(SDLK_5))
// 	{
// 		m_camVel.y += 0.01f;;
// 	}

	/*
	if (isControlMode)
	{

		if (inputManager.isKeyPressed(SDLK_LEFT))
		{
			m_cloudCameraViewFlag |= CLOUD_CAM_ROT_LEFT;
			
			if (m_cloudCameraViewFlag &CLOUD_CAM_ROT_RIGHT)
			{
				m_cloudCameraViewFlag -= CLOUD_CAM_ROT_RIGHT;
			}
		}

		if (inputManager.isKeyPressed(SDLK_RIGHT))
		{
			m_cloudCameraViewFlag |= CLOUD_CAM_ROT_RIGHT;
			if (m_cloudCameraViewFlag & CLOUD_CAM_ROT_LEFT)
			{
				m_cloudCameraViewFlag -= CLOUD_CAM_ROT_LEFT;
			}
			
		}

		if (inputManager.isKeyPressed(SDLK_UP))
		{
			//ENGINE_targetFPS *= 1.01f;

			m_cloudCameraViewFlag |= CLOUD_CAM_ROT_UP;
			if (m_cloudCameraViewFlag & CLOUD_CAM_ROT_DOWN)
			{
				m_cloudCameraViewFlag -= CLOUD_CAM_ROT_DOWN;
			}
			

		}
		if (inputManager.isKeyPressed(SDLK_DOWN))
		{

			
			m_cloudCameraViewFlag |= CLOUD_CAM_ROT_DOWN;
			if (m_cloudCameraViewFlag & CLOUD_CAM_ROT_UP)
			{
				m_cloudCameraViewFlag -= CLOUD_CAM_ROT_UP;
			}
			
			//std::cout << "slow \n";
			//ENGINE_targetFPS *= 0.99f;
		}
	}
	else
	{
// 		if (inputManager.isKeyPressed(SDLK_LEFT))
// 		{
// 			m_cloudCameraPosFlag |= CLOUD_CAM_MOVE_LEFT;
// 			m_cloudCameraPosFlag -= CLOUD_CAM_MOVE_RIGHT;
// 		}
// 
// 		if (inputManager.isKeyPressed(SDLK_RIGHT))
// 		{
// 			m_cloudCameraPosFlag |= CLOUD_CAM_MOVE_RIGHT;
// 			m_cloudCameraPosFlag -= CLOUD_CAM_MOVE_LEFT;
// 		}

		if (inputManager.isKeyPressed(SDLK_UP))
		{
			//ENGINE_targetFPS *= 1.01f;

			m_cloudCameraPosFlag |= CLOUD_CAM_MOVE_UP;
			if (m_cloudCameraPosFlag & CLOUD_CAM_MOVE_DOWN)
			{
				m_cloudCameraPosFlag -= CLOUD_CAM_MOVE_DOWN;
			}
			

		}
		if (inputManager.isKeyPressed(SDLK_DOWN))
		{

			
			
			m_cloudCameraPosFlag |= CLOUD_CAM_MOVE_DOWN;
			if (m_cloudCameraPosFlag & CLOUD_CAM_MOVE_UP)
			{
				m_cloudCameraPosFlag -= CLOUD_CAM_MOVE_UP;
			}

			//std::cout << "slow \n";
			//ENGINE_targetFPS *= 0.99f;
		}
	}
	*/
	if (inputManager.isKeyPressed(SDLK_PAGEDOWN))
	{
		m_currentState = Feintgine::ScreenState::CHANGE_NEXT;
	}
	if (inputManager.isKeyPressed(SDLK_PAGEUP))
	{
		m_currentState = Feintgine::ScreenState::CHANGE_PREVIOUS;
	}



}

void Extra_DemoScreen::firstCheckPoint()
{

	// auto taskLoad = async([&]()
	// {
	// 	reloadLevel();
	// });

	m_bg.init(Feintgine::ResourceManager::getTexture(
	"Assets/Lazy/bg.png"), glm::vec2(-0,0), glm::vec2(768, 768));

	m_bg2.init(Feintgine::ResourceManager::getTexture(
	"Assets/Lazy/mountains.png"), glm::vec2(-50, 0), glm::vec2(768  , 768));
	


	Feintgine::SpriteManager::Instance()->loadFromDirectory("Assets/", 0);

	std::cout << "wait \n";
	while(!Feintgine::SpriteManager::Instance()->isLoadingDone())
	{
		checkInput();
		//std::cout << "loading \n";
	}
	std::cout << "loaded !!!!!!! \n";

	m_player.setCharacterSpell(1);
	// m_player.init("Assets/F_AObjects/Marisa_own.xml", "character/marisa_accessory_3.png",true);
	m_player.init("Assets/F_AObjects/reimu.xml", "character/reimu_accessory_3.png",false);
	
	//m_player.init("Assets/F_AObjects/Marisa_own.xml", "character/marisa_accessory_3.png");

	//reimu_normal_projectile   | reimu_double_projectile

	m_player.setPrimaryShot(true, "Assets/F_AObjects/reimu_normal_projectile.xml", 5.0f, 90.0f);
	// m_player.setPrimaryShot(true, "Assets/F_AObjects/marisa_normal_projectile.xml", 5.0f, 90.0f);

	// 1 HOMING, 2 Missle , 3 needles, 4 laser
	m_player.setAccessoryShot(1);

	m_bg2.setColor(Feintgine::Color(255, 255, 255, 100));

	m_player.setDeathCallback([&] {
		addExplosion(
			Feintgine::SpriteManager::Instance()->getSprite("projectile/death_anim_2.png"),
			m_player.getPos(), glm::vec2(1), glm::vec2(0.56), Feintgine::Color(255, 255, 255, 255), 4, 0.02f);
	});

	m_player.registerExplosionRing(&m_exlosions);

	m_particleEngine.addParticleBatch(m_player.getHitParticle());
	m_particleEngine.addParticleBatch(m_player.getLeftAccessosry().getParticleBatch());
	m_particleEngine.addParticleBatch(m_player.getRightAccesory().getParticleBatch());

	m_player.registerLogicCamera(&m_camera);

	m_player.registerKanjiEffect(&m_kanjiEffectManager);
	m_player.registerAudioEngine(&m_audioEngine);
	
	m_player.initSound();

	m_music = m_audioEngine.loadMusic("Sounds/bgm/f2.mp3");

	m_pauseMenu.init();

	
	m_player.setPos(glm::vec2(25, -100));
	m_player.reset();
	GlobalValueClass::Instance()->savePlayer(&m_player);

	auto now = std::chrono::system_clock::now();
	Feintgine::F_Event::Instance()->add([=] {
		startCount = true;
		t_start = SDL_GetTicks();
		
	}, now + std::chrono::milliseconds(100));

	m_showHitBox = false;
	is_lightOn = true;
	m_shaderTime = 0.0;

	
	m_recorder.init(&m_player, &ENGINE_current_tick);
	//startCount = true;

	m_player.registerEffectBatch(&m_effectBatch);

	m_linkCreator.registerAudioEngine(&m_audioEngine);

	m_shaderDirection = new Feintgine::F_ShaderEvent_Vec3();
	m_shaderDirection->init(&m_portalShader, "lookDir");
	m_shaderDirection->setDefaultvalue(glm::vec3(1.0f, 0, 0.f));

	m_shaderVel = new Feintgine::F_ShaderEvent_Vec3();
	m_shaderVel->init(&m_portalShader, "camVel");
	m_shaderVel->setDefaultvalue(glm::vec3(0.0f, 0, 0.f));


	m_cloudAlpha = new Feintgine::F_ShaderEvent_Float();

	m_cloudAlpha->init(&m_portalShader, "cloudAlpha");
	m_cloudAlpha->setDefaultvalue(1.0f);

	m_shaderEventHandler.addEvent(m_shaderDirection);
	m_shaderEventHandler.addEvent(m_shaderVel);
	m_shaderEventHandler.addEvent(m_cloudAlpha);

	reloadLevel();
	loaded = true;
	

}

void Extra_DemoScreen::addExplosion(const Feintgine::F_Sprite & sprite, const glm::vec2 & pos, const glm::vec2 & scale, const glm::vec2 & explosionRate, const Feintgine::Color & color, float depth, float liveRate /*= 0.1f*/)
{
	m_exlosions.emplace_back(sprite, pos, scale, explosionRate, color, depth, liveRate);
}

void Extra_DemoScreen::drawLoadingScreen()
{
	glViewport(0, 0, 1366, 768);
	glm::mat4 projectionMatrix;
	GLint pUniform;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	std::cout << "loading screen \n";

}



void Extra_DemoScreen::drawGameplay()
{
	
	glViewport(12.5, 0, 768, 768);

	glm::mat4 projectionMatrix;
	GLint pUniform;
	if (m_foregroundShader)
	{
		m_foregroundShader->use();
		
		GLint textureUniform = m_foregroundShader->getUniformLocation("mySampler");
		glUniform1i(textureUniform, 0);
		glActiveTexture(GL_TEXTURE0);

		// Camera matrix
		projectionMatrix = m_camera.getCameraMatrix();
		pUniform = m_foregroundShader->getUniformLocation("P");
		glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

		if (m_foregroundShader == &m_shader)
		{
			GLint dayLightIndex = m_foregroundShader->getUniformLocation("dayLight");
			glUniform3f(dayLightIndex, dayLight, dayLight, dayLight);
		}

		m_lightBatch.begin();

		if (is_lightOn)
		{
			m_player.drawLight(m_lightBatch);
			//m_particleEngine.
			m_particleEngine.drawLight(m_lightBatch);
			for (auto i = 0; i < m_enemies.size(); i++)
			{
				m_enemies[i]->drawLight(m_lightBatch);
			}
			for (auto i = 0; i < m_guardians.size(); i++)
			{
				m_guardians[i]->drawLight(m_lightBatch);
			}
			for (auto i = 0; i < m_amplifiers.size(); i++)
			{
				m_amplifiers[i]->drawLight(m_lightBatch);
			}
		}

		m_lightBatch.renderLight();

		m_spriteBatch.begin(Feintgine::GlyphSortType::FRONT_TO_BACK);

		if (m_pauseMenu.isPause())
		{
			m_pauseMenu.drawBG(m_spriteBatch);
		}

		if (!GlobalValueClass::Instance()->isLightBalance())
		{
			m_bg.draw(m_spriteBatch);
		}
		
		bg2.draw(m_spriteBatch);
		m_player.draw(m_spriteBatch);
		
		m_kanjiEffectManager.draw(m_spriteBatch);

		for (int i = 0; i < m_exlosions.size(); i++)
		{
			m_exlosions[i].draw(m_spriteBatch);

		}

		for (int i = 0; i < m_enemies.size(); i++)
		{
			m_enemies[i]->draw(m_spriteBatch);
		}
		for (int i = 0; i < m_guardians.size(); i++)
		{
			m_guardians[i]->draw(m_spriteBatch);
		}
		for (int i = 0; i < m_amplifiers.size(); i++)
		{
			m_amplifiers[i]->draw(m_spriteBatch);
		}


		for (int i = 0; i < m_bullets.size(); i++)
		{
			m_bullets[i]->draw(m_spriteBatch);
		}
		m_linkCreator.draw(m_spriteBatch);

		m_spriteBatch.end();
		m_spriteBatch.renderBatch();

		m_particleEngine.draw(&m_spriteBatch);

		m_foregroundShader->unuse();

	}

}

void Extra_DemoScreen::drawTimer()
{
	glViewport(0, 0, 1366, 768);
	glm::mat4 projectionMatrix;
	GLint pUniform;

	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	m_shaderNormal.use();

	//glViewport(0, 600 / 2, 1000 / 2, 600 / 2);
	// Upload texture uniform
	GLint textureUniform = m_shaderNormal.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	glActiveTexture(GL_TEXTURE0);

	// Camera matrix
	projectionMatrix = m_sideCam.getCameraMatrix();
	pUniform = m_shaderNormal.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	m_timerSpriteBatch.begin(Feintgine::GlyphSortType::FRONT_TO_BACK);
	
	bg.draw(m_timerSpriteBatch);
	m_player.drawSpellSelector(m_timerSpriteBatch);
	//m_pauseMenu.drawContext()
	m_timerSpriteBatch.end();
	m_timerSpriteBatch.renderBatch();
	//glEnable(GL_BLEND);

	m_shaderNormal.unuse();

	// m_CEGUI_textRenderer.draw();
	// m_CEGUI_textRenderer2.draw();
}

void Extra_DemoScreen::togglePause()
{
	if (ENGINE_isGameRunning)
	{
		ENGINE_isGameRunning = false;
	}
	else
	{
		ENGINE_isGameRunning = true;
	}
}

void Extra_DemoScreen::togglePauseLogic()
{
	if (ENGINE_isGameRunning)
	{
		m_music.resume();
	}
	else
	{
		m_music.pause();
	}
}

void Extra_DemoScreen::toggleLight()
{
	if (is_lightOn)
	{
		is_lightOn = false;
	}
	else
	{
		is_lightOn = true;
	}
}

void Extra_DemoScreen::drawBackground()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(25, 0, m_window->getScreenWidth(), m_window->getScreenHeight());

	glm::mat4 projectionMatrix;
	GLint pUniform;

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_ONE, GL_ONE);

	if (m_backgroundShader)
	{
		m_backgroundShader->use();

		//glViewport(0, 600 / 2, 1000 / 2, 600 / 2);
		// Upload texture uniform
		GLint textureUniform = m_backgroundShader->getUniformLocation("mySampler");
		glUniform1i(textureUniform, 0);

		glActiveTexture(GL_TEXTURE0);
		// Camera matrix
		projectionMatrix = m_camera.getCameraMatrix();
		pUniform = m_backgroundShader->getUniformLocation("P");
		glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

		m_spriteBatch.begin();
		m_bg.draw(m_spriteBatch);
		//m_bg2.draw(m_spriteBatch);
		m_spriteBatch.end();
		m_spriteBatch.renderBatch();
		m_backgroundShader->unuse();

	}
}

void Extra_DemoScreen::switchShader()
{
	if (m_blackWhiteMode)
	{
		m_foregroundShader = &m_blackWhiteShader;
		m_backgroundShader = &m_whiteBlackShader;
		m_blackWhiteMode = false;
	}
	else
	{
		m_foregroundShader = &m_shader;
		m_backgroundShader = &m_shader;
		m_blackWhiteMode = true;
	}
}

void Extra_DemoScreen::drawCustomShader()
{
	glViewport(0, 0, 768, 768);
	//glViewport(0, 0, 1366, 768);
	//glViewport(0, 0, 1920, 1080);
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	GLuint timeLoc;
	GLuint resLoc;
	GLuint lookDir;
	GLuint alphaRateLoc;
	GLuint camVel;

	//m_currentEffect = &m_glitchShader;
	m_currentEffect = &m_portalShader;

	glm::mat4 projectionMatrix;
	GLint pUniform;

	m_currentEffect->use();

	// Camera matrix

	timeLoc = m_currentEffect->getUniformLocation("time");
	glUniform1f(timeLoc, m_shaderTime);

	resLoc = m_currentEffect->getUniformLocation("resolution");
	glUniform2f(resLoc, 768, 768);
	//glUniform2f(resLoc, 1920, 1080);
	

	//guard 
	if (m_currentEffect == &m_portalShader)
	{

		GLint textureUniform = m_currentEffect->getUniformLocation("iChannel0");
		glUniform1i(textureUniform, 0);
		glActiveTexture(GL_TEXTURE0);

		glm::vec4 mousePos(m_game->m_inputManager.getMouseCoords(), 0, 0);
		GLint mouseLoc = m_currentEffect->getUniformLocation("iMouse");
		glUniform4f(mouseLoc, mousePos.x, mousePos.y, mousePos.z, mousePos.w);

		m_shaderEventHandler.applyToShader();

		/*	lookDir = m_currentEffect->getUniformLocation("lookDir");
			glUniform3f(lookDir, m_lookDir.x, m_lookDir.y, m_lookDir.z);*/

			/*camVel = m_currentEffect->getUniformLocation("camVel");
			glUniform3f(camVel, m_camVel.x, m_camVel.y, m_camVel.z);*/

		//alphaRateLoc = m_currentEffect->getUniformLocation("alphaRate");
		//glUniform1f(alphaRateLoc, m_portalAlpha);

	}



	projectionMatrix = m_sideCam.getCameraMatrix();
	pUniform = m_currentEffect->getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	m_spriteBatch.begin();

	bg1.draw(m_spriteBatch);
	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_currentEffect->unuse();

}

void Extra_DemoScreen::updateShader(float deltaTime)
{
	m_reachTimer += 0.1f * deltaTime;
	if (m_portalAlpha < 0.5f)
	{
		m_portalAlpha += 0.00025f * deltaTime;
	}
	if (m_reachTimer >= 10.0f)
	{
		if (m_reach > 28)
		{
			m_reachTimer = 0;
			m_reach--;
		}
	}
}

void Extra_DemoScreen::reloadLevel()
{
	m_player.clearBullet();
	for (auto i = 0; i < m_enemies.size(); i++)
	{
		m_enemies.erase(m_enemies.begin() + i);
	}
	for (auto i = 0; i < m_guardians.size(); i++)
	{
		m_guardians.erase(m_guardians.begin() + i);
	}

	for (auto i = 0; i < m_amplifiers.size(); i++)
	{
		m_amplifiers.erase(m_amplifiers.begin() + i);
	}
	for (auto i = 0; i < m_bullets.size(); i++)
	{
		m_bullets.erase(m_bullets.begin() + i);
	}
	m_bullets.clear();
	m_enemies.clear();
	m_guardians.clear();
	m_amplifiers.clear();
	m_linkCreator.clearList();

	loadLevel("Data/stageData/levelState/demo.lvl");
	
	dayLight = 1.0f;

	ENGINE_current_tick = 0.0;

	auto now = std::chrono::system_clock::now();
	Feintgine::F_Event::Instance()->add([=] {
		startCount = true;
		t_start = SDL_GetTicks();
	}, now + std::chrono::milliseconds(100));
	m_player.setPos(glm::vec2(25, -100));
	m_player.reset();
	m_bg.resetUV();
	//m_music.stahp();
	m_music.play(1);
	//m_music.
	isDone = true;
	//m_animatObj.setPos(glm::vec2(25, 720));
	//m_shaderTime =  54.0;
	m_reach = 100;
	m_shaderTime = 0.0;
	m_reachTimer = 0.0f;
	m_portalAlpha = 0.0f;
	m_showHitBox = false;
	is_lightOn = true;

	bulletManipulator.init(&m_bullets);

	
	//toggleBalanceLight();
	//GlobalValueClass::Instance()->setLightBalance(false);

	m_lookDir = glm::vec3(1.0f, 0, 0.f);// glm::vec3(0, 0.0f, 0.0f); glm::vec3(1.f, -0.45f, 0.f);
	m_camVel = glm::vec3(0.0f, 0.0f, 0.0f);

	m_forwardCamVel = glm::vec3(-3.0f, 0.0f, 0.0f);
}

void Extra_DemoScreen::loadLevel(const std::string & levelPath)
{
	Feintgine::F_oEvent::getInstance()->clearEvent();
	xml_document<> doc;

	// 	std::ifstream file(levelPath.c_str());
	// 	if (!file)
	// 	{
	// 		std::cout << "nothing found \n";
	// 		return;
	// 	}
	// 	else
	// 	{
	// 		std::cout << "found the file \n";
	// 	}
	std::vector<char> buffer = Feintgine::ResourceManager::getPreloadedFile(levelPath.c_str()); //((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);

	xml_node<> * Level_node = nullptr;

	Level_node = doc.first_node("Level");

	if (!Level_node)
	{
		std::cout << "Error while parsing value Shadertoy.cpp \n";
	}

	xml_node<> * Events_node = Level_node->first_node("Events");
	if (Events_node)
	{
		std::cout << "Format valid \n";
	}
	else
	{
		std::cout << "wrong format \n";
	}
	auto now = std::chrono::system_clock::now();
	for (xml_node<> * Event_node = Events_node->first_node("Event");
		Event_node; Event_node = Event_node->next_sibling())
	{

		std::string t_type = Event_node->first_attribute("type")->value();
		if (t_type == "changeEnvLight")
		{
			xml_node<> * Prop_node = nullptr;
			Prop_node = Event_node->first_node("Prop");
			if (Prop_node)
			{
				float maxVal = std::stof(Prop_node->first_attribute("maxVal")->value());
				float rate = std::stof(Prop_node->first_attribute("rate")->value());
				unsigned time = std::stoi(Prop_node->first_attribute("time")->value());
				Feintgine::F_oEvent::getInstance()->add([=] {
					e_darkeningScene(maxVal, rate);
				}, ENGINE_current_tick + time);

			}
		}

		if (t_type == "turnLight")
		{
			xml_node<> * Prop_node = nullptr;
			Prop_node = Event_node->first_node("Prop");
			if (Prop_node)
			{
				int turnLightVal = std::stoi(Prop_node->first_attribute("value")->value());
				unsigned time = std::stoi(Prop_node->first_attribute("time")->value());
				Feintgine::F_oEvent::getInstance()->add([=] {
					turnLight(turnLightVal);
				}, ENGINE_current_tick + time);

			}
		}
		if (t_type == "showBGM")
		{
			xml_node<> * Prop_node = nullptr;
			Prop_node = Event_node->first_node("Prop");
			if (Prop_node)
			{

				//std::string bgm = Prop_node->first_attribute("text")->value();
				std::wstring wbgm = feint_common::Instance()->convertStringtoWstring(Prop_node->first_attribute("text")->value());
				unsigned time = std::stoi(Prop_node->first_attribute("time")->value());
				m_bgmLabel.setText(wbgm, 0.0f);
				m_bgmLabel.setPos(glm::vec2(-400.0f, 700.0f));
				Feintgine::F_oEvent::getInstance()->add([=] {

					//LivingLabel *bgml = new BGMLabel();
					m_bgmLabel.setLifeTime(5.0f);
					//m_bgmLabel.set
// 		

				}, ENGINE_current_tick + time);
			}

		}
		if (t_type == "changeShaderValue")
		{
			
			xml_node<> * Prop_node = nullptr;
			Prop_node = Event_node->first_node("Prop");
			if (Prop_node)
			{
				
				//std::string bgm = Prop_node->first_attribute("text")->value();
				std::string type = Prop_node->first_attribute("type")->value();
				std::string name = Prop_node->first_attribute("name")->value();
			

				ShaderValueType tType = getShaderValueType(type);
				unsigned time = std::stoi(Prop_node->first_attribute("time")->value());
				switch (tType)
				{
				case T_Float:
				{
					std::string valueX = Prop_node->first_attribute("value")->value();
					float duration = std::stof(Prop_node->first_attribute("duration")->value());
					Feintgine::F_oEvent::getInstance()->add([=] {
						Feintgine::F_ShaderEventBase * tEvent = m_shaderEventHandler.getEventByName(name);
						if (tEvent)
						{
							tEvent->setEvent(std::stof(valueX), duration);
						}
						else
						{
							std::cout << "warning, the value shader " << name << " is null \n";
						}
					}, ENGINE_current_tick + time); 

				}
				break;
				case T_Vec3:
				{
					
					std::string valueX = Prop_node->first_attribute("valueX")->value();
					std::string valueY = Prop_node->first_attribute("valueY")->value();
					std::string valueZ = Prop_node->first_attribute("valueZ")->value();

					float duration = std::stof(Prop_node->first_attribute("duration")->value());

					Feintgine::F_oEvent::getInstance()->add([=] {
						Feintgine::F_ShaderEventBase * tEvent = m_shaderEventHandler.getEventByName(name);
						if (tEvent)
						{
							
							tEvent->setEvent(feint_common::Instance()->convertStringToVec3(valueX, valueY, valueZ) , duration);
						}
						else
						{
							std::cout << "warning, the value shader " << name << " is null \n";
						}


					}, ENGINE_current_tick + time);
					break;
				}

				default:
					break;
				}

				

			}

		}
		if (t_type == "showChapter")
		{
			xml_node<> * Prop_node = nullptr;
			Prop_node = Event_node->first_node("Prop");
			if (Prop_node)
			{

		
				std::wstring wbgm = feint_common::Instance()->convertStringtoWstring(Prop_node->first_attribute("text1")->value());
				std::wstring wbgm2 = feint_common::Instance()->convertStringtoWstring(Prop_node->first_attribute("text2")->value());
				unsigned time = std::stoi(Prop_node->first_attribute("time")->value());
				
				Feintgine::F_oEvent::getInstance()->add([=] {
					m_chapterLabel.setTextes(wbgm, wbgm2, 5.0f);
					//m_chapterLabel.setLifeTime(5.0f);

				}, ENGINE_current_tick + time);
			}

		}

		if (t_type == "spawnEnemy")
		{
			xml_node<> * Prop_node = nullptr;
			Prop_node = Event_node->first_node("Prop");

			if (Prop_node)
			{
				glm::vec2 pos = glm::vec2(std::stof(Prop_node->first_attribute("pX")->value()),
					std::stof(Prop_node->first_attribute("pY")->value()));

				glm::vec2 dim = glm::vec2(std::stof(Prop_node->first_attribute("w")->value()),
					std::stof(Prop_node->first_attribute("h")->value()));

				float heath = std::stof(Prop_node->first_attribute("health")->value());

				unsigned int time = std::stoi(Prop_node->first_attribute("time")->value());

				std::string state = Prop_node->first_attribute("state")->value();

				std::string asset = Prop_node->first_attribute("asset")->value();
				bool dropable = false;
				bool isGuardian = false;

				if (Prop_node->first_attribute("guardian"))
				{

					isGuardian = true;

					//enemy->initShield("Assets/F_AObjects/shield.xml", pos, 1.0f);
				}

				if (Prop_node->first_attribute("drop"))
				{
					dropable = true;
				}

				std::string dropType = "";
				if (dropable)
				{
					dropType = Prop_node->first_attribute("drop")->value();

				}



				bool hasLighting = false;

				if (Prop_node->first_attribute("lighting"))
				{
					hasLighting = true;
				}
				std::string lightingOption = "";
				if (hasLighting)
				{
					lightingOption = Prop_node->first_attribute("lighting")->value();

				}
				Feintgine::F_oEvent::getInstance()->add([=] {
					F_EnemyBasic*  enemy = new FairyBase();
					enemy->init(pos,
						dim, asset,
						heath);
					if (isGuardian)
					{
						enemy->initShield("Assets/F_AObjects/shield.xml", pos, .7f);
					}
					enemy->registerAudio(&m_audioEngine);
					enemy->loadState(state);
					//enemy->playAnim("idle");
					if (dropable)
					{

						enemy->setCollectableItem(dropType);

					}
					if (hasLighting)
					{
						enemy->loadLighting(lightingOption);
					}



					//enemy->registerWorld(m_world.get());
					m_enemies.push_back(enemy);
					//delete enemy;
				}, ENGINE_current_tick + time);

				continue;
			}
			else
			{
				std::cout << "Prop not OK \n";
			}

		}

		if (t_type == "spawnGuardian")
		{
			xml_node<> * Prop_node = nullptr;
			Prop_node = Event_node->first_node("Prop");

			if (Prop_node)
			{
				glm::vec2 pos = glm::vec2(std::stof(Prop_node->first_attribute("pX")->value()),
					std::stof(Prop_node->first_attribute("pY")->value()));

				glm::vec2 dim = glm::vec2(std::stof(Prop_node->first_attribute("w")->value()),
					std::stof(Prop_node->first_attribute("h")->value()));

				float heath = std::stof(Prop_node->first_attribute("health")->value());

				unsigned int time = std::stoi(Prop_node->first_attribute("time")->value());

				std::string state = Prop_node->first_attribute("state")->value();

				std::string asset = Prop_node->first_attribute("asset")->value();
				bool dropable = false;
				bool isGuardian = false;


				if (Prop_node->first_attribute("drop"))
				{
					dropable = true;
				}

				std::string dropType = "";
				if (dropable)
				{
					dropType = Prop_node->first_attribute("drop")->value();

				}

				bool hasLighting = false;

				if (Prop_node->first_attribute("lighting"))
				{
					hasLighting = true;
				}
				std::string lightingOption = "";
				if (hasLighting)
				{
					lightingOption = Prop_node->first_attribute("lighting")->value();

				}
				Feintgine::F_oEvent::getInstance()->add([=] {
					EnemyGuardian*  enemy = new EnemyGuardian();
					enemy->initShield("Assets/F_AObjects/shield.xml", pos, .7f);
					enemy->init(pos,
						dim, asset,
						heath);


					enemy->registerAudio(&m_audioEngine);
					enemy->loadState(state);
					//enemy->playAnim("idle");
					if (dropable)
					{

						enemy->setCollectableItem(dropType);

					}
					if (hasLighting)
					{
						enemy->loadLighting(lightingOption);
					}



					//enemy->registerWorld(m_world.get());
					m_guardians.push_back(enemy);
					//delete enemy;
				}, ENGINE_current_tick + time);

				continue;
			}
			else
			{
				std::cout << "Prop not OK \n";
			}

		}
		if (t_type == "spawnAmplifier")
		{
			xml_node<> * Prop_node = nullptr;
			Prop_node = Event_node->first_node("Prop");

			if (Prop_node)
			{
				glm::vec2 pos = glm::vec2(std::stof(Prop_node->first_attribute("pX")->value()),
					std::stof(Prop_node->first_attribute("pY")->value()));

				glm::vec2 dim = glm::vec2(std::stof(Prop_node->first_attribute("w")->value()),
					std::stof(Prop_node->first_attribute("h")->value()));

				float heath = std::stof(Prop_node->first_attribute("health")->value());

				unsigned int time = std::stoi(Prop_node->first_attribute("time")->value());

				std::string state = Prop_node->first_attribute("state")->value();

				std::string asset = Prop_node->first_attribute("asset")->value();
				bool dropable = false;
				bool isGuardian = false;
				if (Prop_node->first_attribute("drop"))
				{
					dropable = true;
				}

				std::string dropType = "";
				if (dropable)
				{
					dropType = Prop_node->first_attribute("drop")->value();

				}

				bool hasLighting = false;

				if (Prop_node->first_attribute("lighting"))
				{
					hasLighting = true;
				}
				std::string lightingOption = "";
				if (hasLighting)
				{
					lightingOption = Prop_node->first_attribute("lighting")->value();

				}
				Feintgine::F_oEvent::getInstance()->add([=] {
					EnemyAmplifier*  enemy = new EnemyAmplifier();
					enemy->init(pos,
						dim, asset,
						heath);

					//enemy->initShield("Assets/F_AObjects/shield.xml", pos, .7f);
					enemy->registerAudio(&m_audioEngine);
					enemy->loadState(state);
					//enemy->playAnim("idle");
					if (dropable)
					{
						enemy->setCollectableItem(dropType);
					}
					if (hasLighting)
					{
						enemy->loadLighting(lightingOption);
					}

					//enemy->registerWorld(m_world.get());
					m_amplifiers.push_back(enemy);
					//delete enemy;
				}, ENGINE_current_tick + time);

				continue;
			}
			else
			{
				std::cout << "Prop not OK \n";
			}

		}


		if (t_type == "spawnEnemyLine")
		{

			xml_node<> * Prop_node = nullptr;
			Prop_node = Event_node->first_node("Prop");

			if (Prop_node)
			{

				glm::vec2 pos = glm::vec2(std::stof(Prop_node->first_attribute("pX")->value()),
					std::stof(Prop_node->first_attribute("pY")->value()));

				glm::vec2 dim = glm::vec2(std::stof(Prop_node->first_attribute("w")->value()),
					std::stof(Prop_node->first_attribute("h")->value()));

				float heath = std::stof(Prop_node->first_attribute("health")->value());

				unsigned int time = std::stoi(Prop_node->first_attribute("time")->value());

				std::string state = Prop_node->first_attribute("state")->value();

				std::string asset = Prop_node->first_attribute("asset")->value();

				int number = std::stoi(Prop_node->first_attribute("number")->value());

				int interval = std::stoi(Prop_node->first_attribute("interval")->value());

				bool dropable = false;
				if (Prop_node->first_attribute("drop"))
				{
					dropable = true;
				}
				std::vector<int> dropInstace;
				std::string dropType = "";
				if (dropable)
				{
					dropType = Prop_node->first_attribute("drop")->value();
					std::string dropOn = Prop_node->first_attribute("drop_on")->value();
					getDropInstances(dropOn, dropInstace, number);
				}
				bool hasLighting = false;
				if (Prop_node->first_attribute("lighting"))
				{
					hasLighting = true;
				}
				std::string lightingOption = "";
				if (hasLighting)
				{
					lightingOption = Prop_node->first_attribute("lighting")->value();

				}

				for (int i = 0; i < number; i++)
				{
					Feintgine::F_oEvent::getInstance()->add([=]
					{
						FairyBase*  enemy = new FairyBase();
						enemy->init(pos,
							dim, asset,
							heath);
						enemy->registerAudio(&m_audioEngine);
						enemy->loadState(state);
						//enemy->playAnim("idle");

						if (dropable)
						{
							for (int f = 0; f < dropInstace.size(); f++)
							{
								if (dropInstace[f] == i)
								{
									//std::cout << "match " << i << " " << dropInstace[f] << "\n";
									enemy->setCollectableItem(dropType);
									//dropInstace.
								}
							}
						}
						if (hasLighting)
						{
							enemy->loadLighting(lightingOption);
						}
						//enemy->registerWorld(m_world.get());
						m_enemies.push_back(enemy);

						//delete enemy;
					}, ENGINE_current_tick + (time + (i * interval)));
				}

				continue;

			}
			else
			{
				std::cout << "Prop not OK \n";
			}
		}
	}

}

void Extra_DemoScreen::e_darkeningScene(float maxVal, float rate)
{
	m_lightMaxVal = maxVal;
	m_lightRate = rate;
	if (maxVal > dayLight)
	{
		lightPositive = true;
	}
	else
	{
		lightPositive = false;
	}
	lightChange = true;
}

void Extra_DemoScreen::getDropInstances(const std::string & value, std::vector<int> & data, int maxCount)
{
	data.clear();
	if (value == "all")
	{
		for (int i = 0; i < maxCount; i++)
		{
			data.push_back(i);
		}
		return;
	}
	else
	{
		std::stringstream ss(value);
		for (int i; ss >> i;)
		{
			data.push_back(i);
			if (ss.peek() == ',')
				ss.ignore();
		}
	}

}

void Extra_DemoScreen::turnLight(bool val)
{
	is_lightOn = val;
}

void Extra_DemoScreen::drawBackup()
{
	glm::mat4 projectionMatrix;
	GLint pUniform;
	if (m_foregroundShader)
	{
		m_foregroundShader->use();

		GLint textureUniform = m_foregroundShader->getUniformLocation("mySampler");
		glUniform1i(textureUniform, 0);
		glActiveTexture(GL_TEXTURE0);

		// Camera matrix
		projectionMatrix = m_camera.getCameraMatrix();
		pUniform = m_foregroundShader->getUniformLocation("P");
		glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

		
		GLint dayLightIndex = m_foregroundShader->getUniformLocation("dayLight");
		glUniform3f(dayLightIndex, dayLight, dayLight, dayLight);
		

		m_lightBatch.begin();

		if (is_lightOn)
		{
			m_player.drawLight(m_lightBatch);
			//m_particleEngine.
		
		}

		m_lightBatch.renderLight();

		m_spriteBatch.begin(Feintgine::GlyphSortType::FRONT_TO_BACK);

		if (m_pauseMenu.isPause())
		{
			m_pauseMenu.drawBG(m_spriteBatch);
		}
		m_player.draw(m_spriteBatch);
		m_bg.draw(m_spriteBatch);
		bg2.draw(m_spriteBatch);

		m_spriteBatch.end();
		m_spriteBatch.renderBatch();

		m_foregroundShader->unuse();

	}
}

void Extra_DemoScreen::toggleLightAE()
{
	
	if (dayLight <= 0.0f)
	{
		dayLight = 1.0f;
	}
	else
	{
		dayLight = -0.1f;
	}
	GlobalValueClass::Instance()->setAmbientLight(glm::vec3(dayLight));
	
}

void Extra_DemoScreen::drawHitboxes()
{
	m_linkCreator.drawDebug(m_debug);
	m_debug.end();
	m_debug.render(m_camera.getCameraMatrix(), 2.0f);
}

void Extra_DemoScreen::toggleBalanceLight()
{

	GlobalValueClass::Instance()->setLightBalance(!GlobalValueClass::Instance()->isLightBalance());

}

void Extra_DemoScreen::updateShaderCamera(float deltaTime)
{

	// ROTATION CONTROL
	
	m_shaderEventHandler.update(deltaTime);
	//m_shaderDirection.update(deltaTime);

	if (m_cloudCameraViewFlag & CLOUD_CAM_ROT_LEFT)
	{
		m_lookDir.z -= 0.01f * deltaTime;
	}
	if (m_cloudCameraViewFlag & CLOUD_CAM_ROT_RIGHT)
	{
		m_lookDir.z += 0.01f * deltaTime;
	}
	if (m_cloudCameraViewFlag & CLOUD_CAM_ROT_UP)
	{
		m_lookDir.y += 0.01f * deltaTime;
	}
	if (m_cloudCameraViewFlag & CLOUD_CAM_ROT_DOWN)
	{
		m_lookDir.y -= 0.01f * deltaTime;
	}

	//glm::rotate(m_camVel, m_lookDir);



	// MOVE CONTROL 

	glm::vec3 copyDir = m_lookDir;
	copyDir.x -= 1.0f;

 /*	m_forwardCamVel.x = cos(copyDir.z) * sin(copyDir.y) ;
 	m_forwardCamVel.y = -sin(copyDir.z);
 	m_forwardCamVel.z = cos(copyDir.z) * cos(copyDir.y);*/


	//m_forwardCamVel += glm::vec3(-3, 0, 0);
	//m_forwardCamVel.x = -m_forwardCamVel.x;
	//m_forwardCamVel.x = sin(m_lookDir.y);
	//m_forwardCamVel.y = -tan(m_lookDir.x);
	//m_forwardCamVel.z = cos(m_lookDir.y);


	//glm::vec3 dir;


	//dir.x = cos(copyDir.x) * cos(copyDir.y);

	//dir.y = sin(copyDir.x);

	//dir.z = cos(copyDir.x) * sin(copyDir.y);

	///*dir.x = cos(pitch) * cos(yaw);

	//dir.y = sin(pitch);

	//dir.z = cos(pitch) * sin(yaw);*/

	//dir = glm::normalize(dir);


	//m_forwardCamVel = dir;

	//m_forwardCamVel.y = 0.0f;
	//m_forwardCamVel.z = 0.0f;
	//m_forwardCamVel.x = -m_forwardCamVel.x;
	//m_forwardCamVel.z = -m_forwardCamVel.z;
	//std::cout << feint_common::Instance()->convertVec3toString(m_forwardCamVel) << "\n";

	//m_camVel = m_forwardCamVel;

	if (m_cloudCameraPosFlag & CLOUD_CAM_MOVE_UP)
	{
		
	}
	if (m_cloudCameraPosFlag & CLOUD_CAM_MOVE_DOWN)
	{
		//m_camVel = -m_forwardCamVel * speed;
	}

	//if (m_cloudCameraPosFlag & CLOUD_CAM_MOVE_LEFT)
	//{
	//	m_camVel.z -= 0.01f * deltaTime;
	//}
	//if (m_cloudCameraPosFlag & CLOUD_CAM_MOVE_RIGHT)
	//{
	//	m_camVel.z += 0.01f * deltaTime;
	//}
	//if (m_cloudCameraPosFlag & CLOUD_CAM_MOVE_UP)
	//{
	//	m_camVel.y += 0.01f * deltaTime;
	//}
	//if (m_cloudCameraPosFlag & CLOUD_CAM_MOVE_DOWN)
	//{
	//	m_camVel.y -= 0.01f * deltaTime;
	//}



}

void Extra_DemoScreen::toggleCTRL()
{
	if (isControlMode)
	{
		isControlMode = false;
	}
	else
	{
		isControlMode = true;
	}
}

