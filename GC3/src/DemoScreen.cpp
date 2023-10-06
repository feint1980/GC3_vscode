#include "DemoScreen.h"



DemoScreen::DemoScreen()
{
}

DemoScreen::DemoScreen(Feintgine::Window * window)
{
	m_screenIndex = SCREEN_INDEX_TEST_MODE;
	std::cout << "number " << SCREEN_INDEX_TEST_MODE << "\n";
	m_window = window;
	m_alpha = 1;

}

DemoScreen::~DemoScreen()
{
}

int DemoScreen::getNextScreenIndex() const
{
	return -1;
}

int DemoScreen::getPreviousScreenIndex() const
{
	return -1;
}

void DemoScreen::build()
{
	
}

void DemoScreen::destroy()
{

	std::cout << "destroy screen \n";
	m_currentState = Feintgine::ScreenState::EXIT_APPLICATION;
	m_shader.dispose();
}

void DemoScreen::onEntry()
{
	std::string filePath = "Scence/testScene.fsc";
// 	std::thread t1(&DemoScreen::loadScreen, this, filePath);
// 	t1.join();
	loadScreen(filePath);
	__int64 start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	std::cout << "Start loading " << start << std::endl;
	initShader();
	//m_shader.dispose();
	//initShader();


	bg.init(Feintgine::ResourceManager::getTexture("Textures/log.png"),
		glm::vec2(0, 0), glm::vec2(160.0f, 90.0f), Feintgine::Color(255, 255, 255, 255));

	
	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight(),7);	
	//std::cout << m_window->getScreenWidth() << " sdsd " << m_window->getScreenHeight() << "\n";
	

		//loadScreen(filePath);
	//m_scene.updateScreenPriority();
	m_camera.setPosition(glm::vec2(0));
	//m_camera.setScale(m_camera.getScale() * m_window->getScreenWidth()/ m_window->getScreenWidth());

	m_camera.update();
	m_spriteBatch.init();


	
	__int64 end = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	std::cout << "End load " << end << std::endl;
	__int64 elapsed = end - start;
	std::cout << "total " << (float)elapsed / 1000.0f << "\n";
	
	
}

void DemoScreen::onExit()
{
	std::cout << "exit \n";

}

void DemoScreen::update(float deltaTime)
{	
	checkInput();
	handleInput(m_game->m_inputManager);
	m_camera.update();	
	
}

void DemoScreen::draw()
{
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
	
	//m_scene.drawScene(m_spriteBatch);

	//drawHUD();
	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_shader.unuse();


	//
	
}

void DemoScreen::handleInput(Feintgine::InputManager & inputManager)
{
	if (inputManager.isKeyDown(SDL_QUIT))
	{
		m_currentState = Feintgine::ScreenState::EXIT_APPLICATION;
	}
	
	if (inputManager.isKeyPressed(SDLK_RETURN))
	{
		switchScreen();
		//m_currentState = Feintgine::ScreenState::EXIT_APPLICATION;
	
		
		//m_game->exitGame();
		//m_game->run();
		//m_game->run();
	}
	


}

void DemoScreen::checkInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{	
		m_game->onSDLEvent(evnt);
		m_camera.handleInput(m_game->m_inputManager, evnt);
		
	}
}

void DemoScreen::initShader()
{
	m_shader.compileShaders("Shaders/demo.vert", "Shaders/demo.frag");
	m_shader.addAttribute("vertexPosition");
	m_shader.addAttribute("vertexColor");
	m_shader.addAttribute("vertexUV");
	m_shader.linkShaders();
	m_alpha = 1.0f;

	std::cout << " init shader called \n";
	
}

void DemoScreen::loadScreen(std::string & filePath)
{
	//m_scene.loadSceneFromFile(filePath);
}

void DemoScreen::switchScreen()
{
	if (!full)
	{
		//SDL_GLContext context = m_game->getWindow().getGLContext();
		m_game->configureScreen("Gensokyo Adventure", 1280, 720, 0x2,true);
		//m_game->getWindow().loadContext(context);
		full = true;
	}
	else
	{
	//	SDL_GLContext context = m_game->getWindow().getGLContext();
		m_game->configureScreen("Gensokyo Adventure", 1280, 720, 0,true);
	//	m_game->getWindow().loadContext(context);
		full = false;
	}
	
	m_window->storageCamPos(m_camera.getPosition());
	m_shader.dispose();
	
	onEntry();
	m_camera.setPosition(m_window->getStoragedCam());
}
