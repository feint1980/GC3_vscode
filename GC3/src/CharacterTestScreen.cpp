#include "CharacterTestScreen.h"



CharacterTestScreen::CharacterTestScreen()
{
}

CharacterTestScreen::CharacterTestScreen(Feintgine::Window * window)
{
	initShader();

	m_screenIndex = 15;
	
}

CharacterTestScreen::~CharacterTestScreen()
{
}

int CharacterTestScreen::getNextScreenIndex() const
{
	return -1;
}

int CharacterTestScreen::getPreviousScreenIndex() const
{
	return 1;
}

void CharacterTestScreen::build()
{

}

void CharacterTestScreen::destroy()
{

}

void CharacterTestScreen::onEntry()
{

	m_CEGUI_textRenderer.addFont("DejaVuSans-14");
// 	m_CEGUI_textRenderer.addTextObject("Score",
// 		glm::vec2(0.6, 0.2), glm::vec2(0.4, 0.1), L"[colour='FF51F0FF'] Thật không thể tin được\
// 		[colour='FFFF0000'] \" Kinh đấy \"");

	m_scoreRenderer.init(24, 128, "font/ARIALUNI.ttf");
	m_camera.init(1366, 768,7);
	m_camera.setScale(1.0f);
	m_camera.setPosition(glm::vec2(0));
	m_camera.savePos();
	m_camera.update();

	m_timerSpriteBatch.init();

	m_spriteFont = new Feintgine::SpriteFont("font/ARIALUNI.ttf", 30);


}

void CharacterTestScreen::onExit()
{
	m_audioEngine.destroy();
}

void CharacterTestScreen::update(float deltaTime)
{
	//checkInput();
	if (!isLoaded && !startLoad)
	{
		startLoad = true;
		firstCheckpoint();
		//std::thread load(&ShaderToy::firstCheckPoint, this);
		//load.join();c

		return;
	}
	if (isLoaded)
	{


		m_player.update(deltaTime, m_enemies, m_bullets,m_guardians, m_amplifiers);
		m_bg.update(deltaTime);
		m_camera.update();
		m_particleEngine.update(deltaTime);
		for (int i = 0; i < m_enemies.size(); i++)
		{
			m_enemies[i]->update(deltaTime);
			if (m_enemies[i]->m_bullets.size() > 0)
			{
				for (int c = 0; c < m_enemies[i]->m_bullets.size(); c++)
				{

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

		m_kanjiEffectManager.update(deltaTime);

	}

}

void CharacterTestScreen::draw()
{

	if (!isLoaded)
	{
		drawLoadingScreen();
		return;
	}
	else
	{


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		m_shader.use();
		// Upload texture uniform
		GLint textureUniform = m_shader.getUniformLocation("mySampler");
		glUniform1i(textureUniform, 0);
		glActiveTexture(GL_TEXTURE0);

		// 	GLint alphaLocation = m_shader.getUniformLocation("fadeout");
		// 	glUniform1f(alphaLocation, m_alpha);


		GLint dayLightIndex = m_shader.getUniformLocation("dayLight");
		glUniform3f(dayLightIndex, m_ambientLightR, m_ambientLightG, m_ambientLightB);



		// Camera matrix
		glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
		GLint pUniform = m_shader.getUniformLocation("P");
		glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

		m_lightBatch.begin();


		m_player.drawLight(m_lightBatch);
		m_particleEngine.drawLight(m_lightBatch);
		// 	for (auto i = 0; i < m_enemies.size(); i++)
		// 	{
		// 		m_enemies[i]->drawLight(m_lightBatch);
		// 	}
		// 	

		m_lightBatch.renderLight();



		m_spriteBatch.begin(Feintgine::GlyphSortType::FRONT_TO_BACK);
		m_tbg.draw(m_spriteBatch);
		m_bg.draw(m_spriteBatch);

		m_player.draw(m_spriteBatch);


		for (int i = 0; i < m_enemies.size(); i++)
		{
			m_enemies[i]->draw(m_spriteBatch);

		}

		for (int i = 0; i < m_exlosions.size(); i++)
		{
			m_exlosions[i].draw(m_spriteBatch);

		}

		m_kanjiEffectManager.draw(m_spriteBatch);

		m_spriteBatch.end();
		m_spriteBatch.renderBatch();
		m_shader.unuse();

		m_gui_shader.use();
		// Upload texture uniform
		textureUniform = m_gui_shader.getUniformLocation("mySampler");
		glUniform1i(textureUniform, 0);
		glActiveTexture(GL_TEXTURE0);


		// Camera matrix
		projectionMatrix = m_camera_static.getCameraMatrix();
		pUniform = m_gui_shader.getUniformLocation("P");
		glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

		m_spriteBatch.begin(Feintgine::GlyphSortType::FRONT_TO_BACK);

		m_player.drawSpellSelector(m_spriteBatch);

		m_spriteBatch.end();
		m_spriteBatch.renderBatch();

		m_particleEngine.draw(&m_spriteBatch);

		m_gui_shader.unuse();


		m_player.drawScore(m_scoreRenderer, m_camera_static);
		m_player.drawText(m_scoreRenderer, m_camera_static);


		m_CEGUI_textRenderer.draw();
	}
}

void CharacterTestScreen::checkInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		m_game->onSDLEvent(evnt);
		m_camera.handleInput( m_game->m_inputManager, evnt);
		
	}
	handleInput(m_game->m_inputManager);
}

void CharacterTestScreen::initShader()
{
	m_shader.compileShaders("Shaders/ShaderToy/normal.vert", "Shaders/ShaderToy/normal.frag");
	m_shader.addAttribute("vertexPosition");
	m_shader.addAttribute("vertexColor");
	m_shader.addAttribute("vertexUV");
	m_shader.linkShaders();

	m_gui_shader.compileShaders("Shaders/ShaderToy/texture.vert", "Shaders/ShaderToy/texture.frag");
	m_gui_shader.addAttribute("vertexPosition");
	m_gui_shader.addAttribute("vertexColor");
	m_gui_shader.addAttribute("vertexUV");
	m_gui_shader.linkShaders();

	m_shaderNormal.compileShaders("Shaders/ShaderToy/texture.vert", "Shaders/ShaderToy/texture.frag");
	m_shaderNormal.addAttribute("vertexPosition");
	m_shaderNormal.addAttribute("vertexColor");
	m_shaderNormal.addAttribute("vertexUV");
	m_shaderNormal.linkShaders();


}

void CharacterTestScreen::handleInput(Feintgine::InputManager & inputManager)
{
	m_player.handleInput(inputManager);
// 	for (int i = 0; i < m_players.size(); i++)
// 	{
// 		//m_players[i].handleInput(inputManager);
// 	}

	if (inputManager.isKeyPressed(SDLK_ESCAPE))
	{
		m_currentState = Feintgine::ScreenState::EXIT_APPLICATION;
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
		m_ambientLightR *= 0.95f;
		m_ambientLightG *= 0.95f;
		m_ambientLightB *= 0.95f;
	}
	if (inputManager.isKeyDown(SDLK_RIGHT))
	{
		m_ambientLightR *= 1.05f;
		m_ambientLightG *= 1.05f;
		m_ambientLightB *= 1.05f;
	}
	if (inputManager.isKeyPressed(SDLK_TAB))
	{
		spawnEnemy();
	}

}

void CharacterTestScreen::spawnEnemy()
{
	FairyBase*  enemy = new FairyBase();
	enemy->init(glm::vec2(0, 200),
		glm::vec2(24), "Assets/F_AObjects/fairy_enemy_normal_black.xml",
		100);
	enemy->registerAudio(&m_audioEngine);
	enemy->playAnim("idle");
	enemy->initSound();
	//enemy->registerAudio(&m_audioEngine);
	//enemy->setVel(glm::vec2(0, -4));
	//enemy->loadState("Test_enemy");
	//enemy->playAnim("idle");


	m_enemies.push_back(enemy);

}

void CharacterTestScreen::addExplosion(const Feintgine::F_Sprite & sprite, 
	const glm::vec2 & pos, const glm::vec2 & scale, 
	const glm::vec2 & explosionRate,
	const Feintgine::Color & color, float depth, float liveRate /*= 0.1f*/)
{
	//std::cout << "call \n";
	m_exlosions.emplace_back(sprite, pos, scale, explosionRate, color, depth, liveRate);
}

void CharacterTestScreen::firstCheckpoint()
{
	m_bg.init(Feintgine::ResourceManager::getTexture("Assets/Lazy/bg.png"),
		glm::vec2(0), glm::vec2(720, 720));

	m_tbg.init(Feintgine::ResourceManager::getTexture("Assets/Lazy/outline.png"), glm::vec2(0),
		glm::vec2(1800, 1800), Feintgine::Color(1, 1, 1, 255));
	//m_bg.setColor(Feintgine::Color(0, 0, 0, 255));

	m_spriteBatch.init();
	Feintgine::SpriteManager::Instance()->loadFromDirectory("Assets/", 0);

	m_player.init("Assets/F_AObjects/reimu.xml", "character/marisa_accessory_3.png");
	m_player.setPrimaryShot(true, "Assets/F_AObjects/reimu_normal_projectile.xml", 5.0f, 90.0f);
	m_player.setAccessoryShot(1);
	m_player.setSpellPos(glm::vec2(500, 0));

	m_lightBatch.initShader(&m_shader);
	m_player.registerLogicCamera(&m_camera);
//	m_player.registerTextCEGUI(m_CEGUI_textRenderer.m_gui);

	m_camera_static = m_camera;
	m_camera_static.update();

	m_player.setDepth(10);


	m_audioEngine.init();

	m_player.registerAudioEngine(&m_audioEngine);
	m_player.initSound();


	m_particleEngine.addParticleBatch(m_player.getHitParticle());
	m_particleEngine.addParticleBatch(m_player.getLeftAccessosry().getParticleBatch());
	m_particleEngine.addParticleBatch(m_player.getRightAccesory().getParticleBatch());

	m_player.setDeathCallback([&] {
		addExplosion(
			Feintgine::SpriteManager::Instance()->getSprite("projectile/death_anim_2.png"),
			m_player.getPos(), glm::vec2(1), glm::vec2(0.56), Feintgine::Color(255, 255, 255, 255), 4, 0.02f);
	});

	m_player.registerExplosionRing(&m_exlosions);
	m_player.registerKanjiEffect(&m_kanjiEffectManager);

	isLoaded = true;

}

void CharacterTestScreen::drawLoadingScreen()
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

