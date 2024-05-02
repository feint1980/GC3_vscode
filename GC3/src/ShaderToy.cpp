#include "ShaderToy.h"
#include <EngineSetting.h>


ShaderToy::ShaderToy()
{
	
}


ShaderToy::~ShaderToy()
{
}


ShaderToy::ShaderToy(Feintgine::Window * window)
{
	m_screenIndex = 1;
	std::cout << "number " << SHADER_TEST_MODE << "\n";
	m_window = window;
	m_alpha = 1;

	initShader();
	m_foregroundShader = &m_shader;
	m_backgroundShader = &m_whiteBlackShader;
	
	
}



int ShaderToy::getNextScreenIndex() const
{
	return 2;
}

int ShaderToy::getPreviousScreenIndex() const
{
	return 1;
}

void ShaderToy::build()
{

}

void ShaderToy::destroy()
{
	std::cout << "destroy screen \n";
	m_currentState = Feintgine::ScreenState::EXIT_APPLICATION;
	m_shader.dispose();
}

void ShaderToy::onEntry()
{
	
	m_debug.init();
	m_camera.init(720, 720,7);
	m_sideCam.init(1366, 768);

	m_camera.setScale(1.0f);
	m_camera.setPosition(glm::vec2(0));
	//Spider_lily
	bg.init(Feintgine::ResourceManager::getTexture("./Assets/Textures/Spider_lily_edited.png"), glm::vec2(0), glm::vec2(1366, 768),
		Feintgine::Color(255,255,255,255));
	bg1.init(Feintgine::ResourceManager::getTexture("./Assets/Textures/shadowing.png"), glm::vec2(0), glm::vec2(4000, 2000),
		Feintgine::Color(255, 255, 255, 0));
	bg2.init(Feintgine::ResourceManager::getTexture("./Assets/Textures/shadowing.png"), glm::vec2(0), glm::vec2(4000, 2000),
		Feintgine::Color(0, 0, 0, 40));
	m_camera.update();
	m_sideCam.update();
	m_spriteBatch.init();
	m_timerSpriteBatch.init();
	GlobalValueClass::Instance()->savedCamera = &m_camera;
	
	m_spriteFont = new Feintgine::SpriteFont("font/ARIALUNI.ttf", 30);
	m_audioEngine.init();

	//m_world = std::make_unique<b2World>(b2Vec2(0.0f, 0.0f));
//	m_world->SetContactListener(&m_contactListener);
	
	//m_player.registerBox2DWorld(m_world.get());
	GlobalValueClass::Instance()->setAmbientLight(glm::vec3(dayLight));
	SDL_GL_SetSwapInterval(1);
	//m_timer.start();
	//fcounter.start();

}

void ShaderToy::onExit()
{
	std::cout << "exit \n";
	m_enemies.clear();
	m_bullets.clear();
	m_currentState = Feintgine::ScreenState::NONE;
	//Feintgine::F_oEvent::getInstance()->clearEvent();
	m_audioEngine.destroy();

}

void ShaderToy::update(float deltaTime)
{

	
	//fcounter.update();
	//std::cout << "update \n";
	//SDL_DisplayMode current;
	//SDL_GetCurrentDisplayMode(), &current);
	//std::cout << "using " << SDL_GetWindowDisplayIndex(m_game->getWindow().getWindow()) << "\n";
	
	if (!loaded && !startLoad)
	{
		startLoad = true;
		firstCheckPoint();
 		//std::thread load(&ShaderToy::firstCheckPoint, this);
 		//load.join();c
		
		return;
	}
	m_camera.update();
	m_shaderTime += 0.01075f* deltaTime;
	if (loaded)
	{		
		m_player.update(deltaTime, m_enemies, m_bullets,m_guardians,m_amplifiers);
			
		m_bg.update(deltaTime);
		m_animatObj.update(deltaTime);
		if (!isDone)
		{
			if (!m_animatObj.isPlaying())
			{
				switchShader();
				isDone = true;
			}
			else
			{
				if (m_animatObj.getPos().y >= 10)
				{
					glm::vec2 pos = m_animatObj.getPos();
					pos.y -= 15.0f * deltaTime;
					m_animatObj.setPos(pos);
				}
			}
		}
		
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
				(*it)->update(deltaTime,m_enemies,m_amplifiers, m_player);

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

// 			for (int i = 0; i < m_guardians.size(); i++)
// 			{
// 				if (m_guardians[i]->m_bullets.size() > 0)
// 				{
// 					for (int c = 0; c < m_guardians[i]->m_bullets.size(); c++)
// 					{
// 						
// 						m_bullets.push_back(m_guardians[i]->m_bullets[c]);
// 					}
// 					m_guardians[i]->m_bullets.clear();
// 				}
// 			}
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
			
		}
		
		m_kanjiEffectManager.update(deltaTime);

		m_linkCreator.update(deltaTime, m_amplifiers, m_bullets,m_player);
		m_boss.update(deltaTime,m_player);

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
	
}





void ShaderToy::drawTimer()
{

	glViewport(0, 0, 1366, 768);
	glm::mat4 projectionMatrix;
	GLint pUniform;

	
	
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

// 	GLint dayLightIndex = m_shader.getUniformLocation("dayLight");
// 	glUniform1f(dayLightIndex, 0.0f);

	

	char buffer[256];
	char buffer2[256];
	char buffer3[256];
	char buffer4[256];
	char buffer5[256];
	char buffer6[256];
	char buffer7[256];
	//char spellbuffer[256];
	t_duration = (SDL_GetTicks() - t_start) / (double)CLOCKS_PER_SEC;
	//sprintf_s(buffer, "Time : %.3lf", t_duration);
	sprintf_s(buffer, "Real time(s): %.2f", t_duration);


	sprintf_s(buffer3, "%d / %d", m_player.getGrazedPoint(),
		m_player.getSpellSelector().getSpellcards()[m_player.getSpellSelector().getCurrentSelection()]->getGrazeCost());

	sprintf_s(buffer4, "%d", m_player.getScore());
	
	sprintf_s(buffer2, "Fps: %.2f", m_game->getFps());
	sprintf_s(buffer6, "Logic fps: %.2f", ENGINE_targetFPS);
	sprintf_s(buffer7, "Event time: %.2f", ENGINE_current_tick);
// 	sprintf_s(spellbuffer, "%s %s ",
// 		m_player.getSpellSelector().getSpellcards()[m_player.getSpellSelector().getCurrentSelection()]->getSignName().c_str(),
// 		m_player.getSpellSelector().getSpellcards()[m_player.getSpellSelector().getCurrentSelection()]->getSpellName().c_str());

	m_timerSpriteBatch.begin(Feintgine::GlyphSortType::FRONT_TO_BACK);


	bg.draw(m_timerSpriteBatch);
	m_player.drawSpellSelector(m_timerSpriteBatch);


	m_timerSpriteBatch.end();
	m_timerSpriteBatch.renderBatch();
	//glEnable(GL_BLEND);

	m_shaderNormal.unuse();

	
	m_textRenderer.renderText(m_sideCam,feint_common::Instance()->convertStringtoWstring(buffer),
		glm::vec2(150, 300),
		Feintgine::Color(255, 255, 255, 255), 0.8, ALIGN_FT_LEFT);
	m_textRenderer.renderText(m_sideCam, feint_common::Instance()->convertStringtoWstring(buffer2),
		glm::vec2(150, -370),
		Feintgine::Color(255, 255, 255, 255), 0.6, ALIGN_FT_LEFT);
	m_textRenderer.renderText(m_sideCam, feint_common::Instance()->convertStringtoWstring(buffer3), 
		glm::vec2(300, 250),
		Feintgine::Color(255, 255, 255, 255), 0.75, ALIGN_FT_LEFT);
	m_textRenderer.renderText(m_sideCam, feint_common::Instance()->convertStringtoWstring(buffer4),
		glm::vec2(300, 200),
		Feintgine::Color(255, 255, 255, 255), 0.75, ALIGN_FT_LEFT);

	m_textRenderer.renderText(m_sideCam, feint_common::Instance()->convertStringtoWstring(buffer6),
		glm::vec2(150, -350),
		Feintgine::Color(255, 255, 255, 255), 0.6, ALIGN_FT_LEFT);

	m_textRenderer.renderText(m_sideCam, L"Graze", glm::vec2(150, 250),
		Feintgine::Color(255, 255, 255, 255), 0.8, ALIGN_FT_LEFT);
// 	m_textRenderer.renderText(m_sideCam, L"Score", glm::vec2(240, 200),
// 		Feintgine::Color(255, 255, 255, 255), 1.05, ALIGN_FT_CENTER);
	m_textRenderer.renderText(m_sideCam, L"Score", glm::vec2(150, 200),
		Feintgine::Color(255, 255, 255, 255), 0.8, ALIGN_FT_LEFT);

	m_textRenderer.renderText(m_sideCam, L"Spellcards", glm::vec2(240, 130),
		Feintgine::Color(255, 255, 255, 255), 0.8, ALIGN_FT_CENTER);

	m_textRenderer.renderText(m_sideCam, 
		m_player.getSpellSelector().getSpellcards()[m_player.getSpellSelector().getCurrentSelection()]->getSignName(),
		glm::vec2(240, -180),
		Feintgine::Color(255, 255, 255, 255), 0.83, ALIGN_FT_CENTER);
	m_textRenderer.renderText(m_sideCam,
		m_player.getSpellSelector().getSpellcards()[m_player.getSpellSelector().getCurrentSelection()]->getSpellName(),
		glm::vec2(240, -220),
		Feintgine::Color(255, 255, 255, 255), 0.65, ALIGN_FT_CENTER);

	m_textRenderer.renderText(m_sideCam, feint_common::Instance()->convertStringtoWstring(buffer7),
		glm::vec2(150, 350),
		Feintgine::Color(255, 255, 255, 255), 0.8, ALIGN_FT_LEFT);


	//drawLoadingScreen();
	//SDL_GL_SetSwapInterval(1);
}

void ShaderToy::drawBackground()
{

	//glScalef(1.5f, 1.5f, 1.0f);
	glViewport(25, 0, 768, 768);
	//glViewport(0, 0, 1280, 720);
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


		m_spriteBatch.begin(Feintgine::GlyphSortType::FRONT_TO_BACK);
		m_bg.draw(m_spriteBatch);
		m_animatObj.draw(m_spriteBatch);

		m_spriteBatch.end();
		m_spriteBatch.renderBatch();


		m_backgroundShader->unuse();
	}
}

void ShaderToy::draw()
{

	if (!loaded)
	{
		drawLoadingScreen();
		return;
	}
	else
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glDisable(GL_BLEND);
		m_shaderTime = 54.0;
		if (m_shaderTime < 53.2)
		{
			drawCustomShader();
		}
		else
		{
			drawBackground();
		}
	
		
		glViewport(25, 0, 768, 768);

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

			
			if (m_animatObj.isPlaying())
			{
				m_animatObj.draw(m_spriteBatch);
			}
			
			bg2.draw(m_spriteBatch);
			m_player.draw(m_spriteBatch);
			m_boss.draw(m_spriteBatch);

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

			m_linkCreator.draw(m_spriteBatch);

			for (int i = 0; i < m_bullets.size(); i++)
			{
				m_bullets[i]->draw(m_spriteBatch);				
			}

			m_spriteBatch.end();
			m_spriteBatch.renderBatch();

			m_particleEngine.draw(&m_spriteBatch);

			m_foregroundShader->unuse();

			if (m_foregroundShader == &m_shader)
			{
				drawNoLight();
			}
			
		}
		if (m_showHitBox)
		{
			drawHitboxes();
		}
		for (int i = 0; i < m_labels.size(); i++)
		{	
			//std::cout << "size " << m_labels.size() << "\n";
			m_labels[i]->draw(&m_textRenderer);
		}
	
		m_player.drawScore(m_scoreRenderer, m_camera);
		m_player.drawText(m_textRenderer, m_camera);

		if (m_pauseMenu.isPause())
		{
			m_pauseMenu.drawContext(m_textRenderer, m_camera);
		}

		drawTimer();

		m_CEGUI_textRenderer.draw();
	}
}

void ShaderToy::handleInput(Feintgine::InputManager & inputManager)
{
	if (ENGINE_isGameRunning)
	{
		m_player.handleInput(inputManager);
	}
	if (inputManager.isKeyPressed(SDL_QUIT) )
	{
		m_currentState = Feintgine::ScreenState::EXIT_APPLICATION;
	}
	if (inputManager.isKeyPressed(SDLK_ESCAPE))
	{
		togglePause();
		m_pauseMenu.togglePause();
		togglePauseLogic();
	}
	if (inputManager.isKeyPressed(SDLK_HOME))
	{
		toggleLightAE();
	}
	
	if (inputManager.isKeyPressed(SDLK_PAGEDOWN))
	{
		m_currentState = Feintgine::ScreenState::CHANGE_NEXT;
	}

	if (inputManager.isKeyPressed(SDLK_SPACE))
	{
		m_animatObj.playAnimation("start", 1);
		isDone = false;
	
	}

	if (inputManager.isKeyPressed(SDLK_F3))
	{
		toggleLight();

	}
	if (inputManager.isKeyPressed(SDLK_f))
	{
		m_boss.startDialouge("first_encounter");
	}

	if (inputManager.isKeyDown(SDLK_UP))
	{
		ENGINE_targetFPS *= 1.01f;
	}
	if (inputManager.isKeyDown(SDLK_DOWN))
	{
		//std::cout << "slow \n";
		ENGINE_targetFPS *= 0.99f;
	}
	if (inputManager.isKeyPressed(SDLK_z))
	{
		ENGINE_targetFPS = 60.0f;
	}

	
	if (inputManager.isKeyDown(SDLK_LEFT))
	{
		dayLight -= 0.01f;
		GlobalValueClass::Instance()->setAmbientLight(glm::vec3(dayLight));
	}
	if (inputManager.isKeyDown(SDLK_RIGHT))
	{
		dayLight += 0.01f;
		GlobalValueClass::Instance()->setAmbientLight(glm::vec3(dayLight));
	}
	if (inputManager.isKeyPressed(SDLK_TAB))
	{

		switchShader();
	}
	if (inputManager.isKeyPressed(SDLK_BACKSPACE))
	{
		loaded = false;
		reloadLevel();
	}
	if (inputManager.isKeyPressed(SDLK_F2))
	{
		if (m_showHitBox)
		{
			m_showHitBox = false;
		}
		else
		{
			m_showHitBox = true;
		}
	}
	m_boss.handleInput(inputManager);
}

void ShaderToy::testFun()
{
	
}

void ShaderToy::loadLevel(const std::string & levelPath)
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
				}, ENGINE_current_tick+ time);
				
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

				std::string bgm = Prop_node->first_attribute("text")->value();

				char *str = Prop_node->first_attribute("text")->value();
				// work out the size
				int size = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);

				// allocate a vector for that size
				std::vector<wchar_t> wide(size);

				// do the conversion
				MultiByteToWideChar(CP_UTF8, 0, str, -1, &wide[0], size);

				std::wstring wbgm = wide.data();
				unsigned time = std::stoi(Prop_node->first_attribute("time")->value());

				Feintgine::F_oEvent::getInstance()->add([=] {
					
					LivingLabel *bgml = new BGMLabel();
				
					bgml->create(wbgm, glm::vec2(-800, -350), glm::vec2(0), Feintgine::Color(255, 255, 255, 255));
					m_labels.push_back(bgml);
					
				}, ENGINE_current_tick + time);
			}

		}
		if (t_type == "showChapter")
		{
			xml_node<> * Prop_node = nullptr;
			Prop_node = Event_node->first_node("Prop");
			if (Prop_node)
			{

				//std::string bgm = Prop_node->first_attribute("text1")->value();

				char *str = Prop_node->first_attribute("text1")->value();
				
				int size = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
				std::vector<wchar_t> wide(size);
				MultiByteToWideChar(CP_UTF8, 0, str, -1, &wide[0], size);
				std::wstring wbgm = wide.data();
				
				char *str2 = Prop_node->first_attribute("text2")->value();				
				int size2 = MultiByteToWideChar(CP_UTF8, 0, str2, -1, NULL, 0);
				std::vector<wchar_t> wide2(size2);
				MultiByteToWideChar(CP_UTF8, 0, str2, -1, &wide2[0], size2);
				std::wstring wbgm2 = wide2.data();
				unsigned time = std::stoi(Prop_node->first_attribute("time")->value());

				Feintgine::F_oEvent::getInstance()->add([=] {

					TitleLabel *bgml = new TitleLabel();

					//bgml->create(wbgm, glm::vec2(0, 0), glm::vec2(0), Feintgine::Color(255, 255, 255, 255));
					bgml->init(glm::vec2(0, 0), wbgm, wbgm2, Feintgine::Color(208, 219, 37, 255),Feintgine::Color(255,255,255,255));
					//bgml->setLifeTime(4.0f);
					m_labels.push_back(bgml);

					std::cout << "should have seen something \n";

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
				FairyBase *  enemy = new FairyBase();
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
					getDropInstances(dropOn, dropInstace,number);
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
	
void ShaderToy::switchShader()
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

void ShaderToy::checkInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{
		
		m_game->onSDLEvent(evnt);
		m_camera.handleInput(m_game->m_inputManager,evnt);
		
	}
	handleInput(m_game->m_inputManager);
	
}

void ShaderToy::initShader()
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

	m_magicalShader.compileShaders("Shaders/MagicalShader/star.vert", "Shaders/MagicalShader/star.frag");
	m_magicalShader.addAttribute("vertexPosition");
	m_magicalShader.addAttribute("vertexColor");
	m_magicalShader.addAttribute("vertexUV");
	m_magicalShader.linkShaders();

	m_crystalShader.compileShaders("Shaders/MagicalShader/crystal.vert", "Shaders/MagicalShader/crystal.frag");
	m_crystalShader.addAttribute("vertexPosition");
	m_crystalShader.addAttribute("vertexColor");
	m_crystalShader.addAttribute("vertexUV");
	m_crystalShader.linkShaders();


	// m_glitchShader.compileShaders("Shaders/MagicalShader/glitch.vert", "Shaders/MagicalShader/glitch.frag");
	// m_glitchShader.addAttribute("vertexPosition");
	// m_glitchShader.addAttribute("vertexColor");
	// m_glitchShader.addAttribute("vertexUV");
	// m_glitchShader.linkShaders();

	m_lightBatch.initShader(&m_shader);

	std::cout << " init shader called \n";

}

void ShaderToy::randomLight()
{

}

void ShaderToy::drawLoadingScreen()
{
//	m_currentState = Feintgine::ScreenState::RUNNING;

		//glViewport(25, 0, 720, 720);
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
		projectionMatrix = m_sideCam.getCameraMatrix();
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

void ShaderToy::firstCheckPoint()
{
	m_textRenderer.init(36,40000, "font/ARIALUNI.ttf");
	m_scoreRenderer.init(14,128, "font/ARIALUNI.ttf");
	Feintgine::SpriteManager::Instance()->loadFromDirectory("Assets/", 0);

	m_animatObj.init("Assets/F_AObjects/shiki.xml", glm::vec2(2.0f));
	m_animatObj.setPos(glm::vec2(25, 720));

	
	//m_player.init("Assets/F_AObjects/reimu.xml","character/reimu_accessory_3.png");
	m_player.init("Assets/F_AObjects/Marisa_own.xml", "character/marisa_accessory_3.png");
	//m_player.setsc
	//m_player.setPrimaryShot(true, "Assets/F_AObjects/reimu_normal_projectile.xml", 5.0f, 90.0f);
	m_player.setPrimaryShot(true, "Assets/F_AObjects/marisa_normal_projectile.xml", 5.0f, 90.0f);

	m_player.setAccessoryShot(2);
	//glm::vec2(720, 720)
	m_bg.init(Feintgine::ResourceManager::getTexture(
		"Assets/Lazy/bg.png"), glm::vec2(0), glm::vec2(720, 720));
	//bg3

	m_player.setDeathCallback([&] {
		addExplosion(
			Feintgine::SpriteManager::Instance()->getSprite("projectile/death_anim_2.png"),
			m_player.getPos(), glm::vec2(1), glm::vec2(0.56), Feintgine::Color(255, 255, 255, 255), 4,0.02f);
	});

	
	GlobalValueClass::Instance()->savePlayer(&m_player);
	m_player.registerExplosionRing(&m_exlosions);
	m_particleEngine.addParticleBatch(m_player.getHitParticle());
	m_particleEngine.addParticleBatch(m_player.getLeftAccessosry().getParticleBatch());
	m_particleEngine.addParticleBatch(m_player.getRightAccesory().getParticleBatch());

	m_player.registerLogicCamera(&m_camera);
	
	m_player.registerKanjiEffect(&m_kanjiEffectManager);
	m_player.registerAudioEngine(&m_audioEngine);
	m_player.initSound();
	// m_player.setOffsetNoLight(glm::vec2(-262, 3));


	m_music = m_audioEngine.loadMusic("Sounds/bgm/f1_modify.mp3");
			
	switchShader();
	//m_music.play(1);

	//m_sdlTextrenderer.init("font/ARIALUNI.ttf", 30);
	m_pauseMenu.init();
 	m_CEGUI_textRenderer.addFont("DejaVuSans-12_a");
//  	m_CEGUI_textRenderer.addTextObject("Score",
//  		glm::vec2(0.6, 0.2), glm::vec2(0.4,0.1), L"[colour='FF51F0FF'] Thật không thể tin được");


//	m_player.registerTextCEGUI(m_CEGUI_textRenderer.m_gui);
	
// 	m_boss.init("Assets/F_AObjects/boss_eiki.xml", "", "Data/stageData/dialouges/testDialouge.dlg");
// 	m_boss.registerTextGUI(m_CEGUI_textRenderer.m_gui, "m_bosssadsadasdasd",
// 		glm::vec2(glm::vec2(-1.0f, -1.0f)), glm::vec2(0.4, 0.1));

	reloadLevel();

}


void ShaderToy::addExplosion(const Feintgine::F_Sprite & sprite,
	const glm::vec2 & pos, const glm::vec2 & scale, 
	const glm::vec2 & explosionRate, 
	const Feintgine::Color & color, float depth, float liveRate)
{
	//std::cout << "call \n";
	m_exlosions.emplace_back(sprite, pos, scale, explosionRate, color, depth, liveRate);
}

void ShaderToy::addBullet(EnemyBulletBase * bullet)
{
	m_bullets.push_back(bullet);
}

void ShaderToy::drawHitboxes()
{
	
// 	for (int i = 0; i < m_bullets.size(); i++)
// 	{
// 		m_bullets[i]->drawHitbox(m_debug);
// 	}
	m_player.drawHitbox(m_debug);
	m_debug.end();
	m_debug.render(m_camera.getCameraMatrix(), 2.0f);
}

void ShaderToy::drawCustomShader()
{
	//glViewport(0, 0, 1366, 768);
	glViewport(25, 0, 768, 768);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	GLuint timeLoc;
	GLuint resLoc;

	m_currentEffect = & m_blackWhiteShader; // no longer use glitch shader //&m_glitchShader;
	   
	glm::mat4 projectionMatrix;
	GLint pUniform;

	m_currentEffect->use();

	// Camera matrix

	timeLoc = m_currentEffect->getUniformLocation("time");
	glUniform1f(timeLoc, m_shaderTime);

	resLoc = m_currentEffect->getUniformLocation("resolution");
	glUniform2f(resLoc, 1366, 768);

	projectionMatrix = m_sideCam.getCameraMatrix();
	pUniform = m_currentEffect->getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	m_spriteBatch.begin();

	bg1.draw(m_spriteBatch);
	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_currentEffect->unuse();

}


void ShaderToy::getDropInstances(const std::string & value, std::vector<int> & data, int maxCount)
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
	//std::cout << "check data \n";
// 	for (int i = 0; i < data.size(); i++)
// 	{
// 		std::cout << "!!!! " << data[i] << " !!!! \n";
// 	}
	
	
}

void ShaderToy::reloadLevel()
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

	loadLevel("Data/stageData/levelState/testLvl.lvl");
	
	dayLight = 1.0f;
	loaded = true;
	ENGINE_current_tick = 0.0;

	auto now = std::chrono::system_clock::now();
	Feintgine::F_Event::Instance()->add([=] {
		startCount = true;
		t_start = SDL_GetTicks();
	}, now + std::chrono::milliseconds(100));
	m_player.setPos(glm::vec2(25, -100));
	m_player.reset();
	m_bg.resetUV();
	m_music.stahp();
	//m_music.play(1);
	isDone = true;
	m_animatObj.setPos(glm::vec2(25, 720));
	//m_shaderTime =  54.0;
	m_shaderTime = 0.0;
	m_showHitBox = false;
	is_lightOn = true;
	
}

void ShaderToy::togglePauseLogic()
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


void ShaderToy::e_darkeningScene(float maxVal, float rate)
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

void ShaderToy::turnLight(bool val)
{
	is_lightOn = val;
}

void ShaderToy::toggleLight()
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

void ShaderToy::drawNoLight()
{
	glViewport(25, 0, 768, 768);
	glm::mat4 projectionMatrix;
	GLint pUniform;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	m_shaderNormal.use();

	GLint textureUniform = m_shaderNormal.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	glActiveTexture(GL_TEXTURE0);

	// Camera matrix
	projectionMatrix = m_camera.getCameraMatrix();
	pUniform = m_shaderNormal.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	// 	GLint dayLightIndex = m_shader.getUniformLocation("dayLight");
	// 	glUniform1f(dayLightIndex, 0.0f);


	m_spriteBatch.begin(Feintgine::GlyphSortType::FRONT_TO_BACK);


	//bg.draw(m_timerSpriteBatch);
	m_player.drawNoLight(m_spriteBatch);


	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	//glEnable(GL_BLEND);

	m_shaderNormal.unuse();



}

void ShaderToy::toggleLightAE()
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

