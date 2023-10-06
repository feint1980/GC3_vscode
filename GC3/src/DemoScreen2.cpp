#include "DemoScreen2.h"



DemoScreen2::DemoScreen2()
{
}

DemoScreen2::DemoScreen2(Feintgine::Window * window)
{
	m_window = window;
	m_screenIndex = SCREEN_INDEX_TEST_MODE_2;
	initShader();

}

DemoScreen2::~DemoScreen2()
{
}

int DemoScreen2::getNextScreenIndex() const
{
	return -1;
}

int DemoScreen2::getPreviousScreenIndex() const
{
	return -1;
}

void DemoScreen2::build()
{
	
}

void DemoScreen2::destroy()
{
	
}

void DemoScreen2::onEntry()
{
	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight(),7);
	bg.init(Feintgine::ResourceManager::getTexture("Textures/log.png"),
		glm::vec2(0, 0), glm::vec2(160.0f, 90.0f), Feintgine::Color(255, 255, 255, 255));
	std::string filePath = "Scence/testScene.fsc";
	//m_scene.loadSceneFromFile(filePath);

	m_spriteBatch.init();
	m_camera.setPosition(glm::vec2(0));
//	m_camera.setScale(4.0f);
	m_camera.update();

}

void DemoScreen2::onExit()
{
	m_shader.dispose();
}

void DemoScreen2::update(float deltaTime)
{
	
	checkInput();
	handleInput(m_game->m_inputManager);
	//m_camera.update();
	//std::cout << m_camera.getScale() << "\n";
}

void DemoScreen2::draw()
{

	//m_alpha = 1;
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

	// Camera matrix
	glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
	GLint pUniform = m_shader.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);
	m_spriteBatch.begin();
	bg.draw(m_spriteBatch);

	//m_scene.drawScene(m_spriteBatch);
	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_shader.unuse();


}

void DemoScreen2::initShader()
{
	m_shader.compileShaders("Shaders/editor.vert", "Shaders/editor.frag");
	m_shader.addAttribute("vertexPosition");
	m_shader.addAttribute("vertexColor");
	m_shader.addAttribute("vertexUV");
	m_shader.linkShaders();
}

void DemoScreen2::handleInput(Feintgine::InputManager & inputManager)
{
	if (inputManager.isKeyDown(SDL_QUIT))
	{
		m_currentState = Feintgine::ScreenState::EXIT_APPLICATION;
	}
}

void DemoScreen2::checkInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		m_game->onSDLEvent(evnt);
		m_camera.handleInput(m_game->m_inputManager,  evnt);
	}
}
