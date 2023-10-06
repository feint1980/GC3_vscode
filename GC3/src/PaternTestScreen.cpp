#include "PaternTestScreen.h"



PaternTestScreen::PaternTestScreen()
{
}

PaternTestScreen::PaternTestScreen(Feintgine::Window * window)
{
	m_screenIndex = 2;
	std::cout << "number " << 0 << "\n";
	m_window = window;
	m_alpha = 1;

	initShader();
	
}

PaternTestScreen::~PaternTestScreen()
{
}

int PaternTestScreen::getNextScreenIndex() const
{
	return -1;
}

int PaternTestScreen::getPreviousScreenIndex() const
{
	return 1;
}

void PaternTestScreen::build()
{
	
}

void PaternTestScreen::destroy()
{
	m_currentState = Feintgine::ScreenState::EXIT_APPLICATION;
	
}

void PaternTestScreen::onEntry()
{
	std::cout << "hey \n";
	bg.init(Feintgine::ResourceManager::getTexture("Textures/particle2.png"),
		glm::vec2(0, 0), glm::vec2(40.0f, 40.0f), Feintgine::Color(255, 255, 255, 255));
	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight(), 7);

	for (int i = 0; i < 1; i++)
	{
		Feintgine::F_oEvent::getInstance()->add([=] 
		{

			m_objects.push_back(bg);
			std::cout << "ho\n";
			
		}, ENGINE_current_tick  + (i * 1000));
	}

	
	m_camera.setPosition(glm::vec2(0));

	m_camera.update();
	m_spriteBatch.init();
}

void PaternTestScreen::onExit()
{
	

}

void PaternTestScreen::update(float deltaTime)
{
	checkInput();
	handleInput(m_game->m_inputManager);
	m_camera.update();


	for (int i = 0; i < m_objects.size(); i++)
	{
		m_objects[i].update(deltaTime);
	}
	ENGINE_current_tick += (ENGINE_tick_speed * deltaTime);
	Feintgine::F_oEvent::getInstance()->timer();
	//bg.setPos(calculate(m_t));
	//bg.setAngle(m_t);
	
}

void PaternTestScreen::draw()
{


	glViewport(0, 0, m_window->getScreenWidth(), m_window->getScreenHeight());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	m_shader.use();
	//glViewport(0, 600 / 2, 1000 / 2, 600 / 2);
	// Upload texture uniform
	GLint textureUniform = m_shader.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	glActiveTexture(GL_TEXTURE0);

	// Camera matrix
	glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
	GLint pUniform = m_shader.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	m_spriteBatch.begin(Feintgine::GlyphSortType::FRONT_TO_BACK);

	//bg.draw(m_spriteBatch);

	for (int i = 0; i < m_objects.size(); i++)
	{
		m_objects[i].draw(m_spriteBatch);
	}

	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_shader.unuse();

}

void PaternTestScreen::checkInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{
		m_game->onSDLEvent(evnt);
		m_camera.handleInput(m_game->m_inputManager, evnt);

	}

}

void PaternTestScreen::initShader()
{
	m_shader.compileShaders("Shaders/demo.vert", "Shaders/demo.frag");
	m_shader.addAttribute("vertexPosition");
	m_shader.addAttribute("vertexColor");
	m_shader.addAttribute("vertexUV");
	m_shader.linkShaders();
	m_alpha = 1.0f;

	std::cout << " init shader called \n";
}

void PaternTestScreen::handleInput(Feintgine::InputManager & inputManager)
{
	if (inputManager.isKeyDown(SDL_QUIT))
	{
		m_currentState = Feintgine::ScreenState::EXIT_APPLICATION;
	}

	if (inputManager.isKeyPressed(SDLK_PAGEUP))
	{

		m_currentState = Feintgine::ScreenState::CHANGE_PREVIOUS;
	}

	
}

