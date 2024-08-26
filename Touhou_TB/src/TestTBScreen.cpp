#include "TestTBScreen.h"


TestTBScreen::TestTBScreen()
{

}


TestTBScreen::~TestTBScreen()
{

}

TestTBScreen::TestTBScreen(Feintgine::Window * window)
{
    m_alpha = 1.0;
    m_window = window;
    m_screenIndex = 12;

    initShader();
}

void TestTBScreen::initShader()
{
    //m_shader.compileShaders("Shaders/basic.vert", "Shaders/basic.frag");
	
    m_shader.compileShaders("Shaders/ShaderToy/normal.vert", "Shaders/ShaderToy/normal.frag");
    m_shader.addAttribute("vertexPosition");
	m_shader.addAttribute("vertexColor");
	m_shader.addAttribute("vertexUV");
	m_shader.linkShaders();
}
void TestTBScreen::onEntry()
{
    
	Feintgine::SpriteManager::Instance()->loadFromDirectory("Assets/", 0);
    m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight() , 7);
	

    m_camera.setPosition(glm::vec2(0, 0));
    //m_camera.setScale(1.5f);

    m_camera.update();

    m_spriteBatch.init();
    
    float tempScale = 0.85f;
	m_bg.init(Feintgine::ResourceManager::getTexture("./Assets/Textures/Palace_of_the_Earth_Spirits.png"),glm::vec2(0,100), glm::vec2(1280, 720),Feintgine::Color(255, 255, 255, 255));
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_battleScene.initTGUI(m_window->getWindow());
	m_battleScene.init(&m_camera);

}

void TestTBScreen::build()
{

	// build screen (unused)
}

void TestTBScreen::destroy()
{
    // unload screen (unused)
}

int TestTBScreen::getNextScreenIndex() const
{
    return -1;
}

int TestTBScreen::getPreviousScreenIndex() const
{
    return 0;
}

void TestTBScreen::onExit()
{
    // unload screen (unused)   
}


void TestTBScreen::update(float deltaTime)
{
    m_camera.update();
	m_battleScene.update(deltaTime);
}

void TestTBScreen::checkInput()
{
    
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{

		m_game->onSDLEvent(evnt);
		m_camera.handleInput(m_game->m_inputManager, evnt);

	}
	handleInput(m_game->m_inputManager);
}

void TestTBScreen::handleInput(Feintgine::InputManager & inputManager)
{
    if (inputManager.isKeyPressed(SDL_QUIT))
	{
		m_currentState = Feintgine::ScreenState::EXIT_APPLICATION;
	}
	m_battleScene.handleInput(inputManager);
}

void TestTBScreen::draw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	

	m_shader.use();

	// GLint alphaLocation = m_shader.getUniformLocation("time");
	// glUniform1f(alphaLocation, 1);
		
	// Upload texture uniform
	GLint textureUniform = m_shader.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	glActiveTexture(GL_TEXTURE0);

	GLint dayLightIndex = m_shader.getUniformLocation("dayLight");
	glUniform3f(dayLightIndex, 1, 1, 1);

	// Camera matrix
	glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
	GLint pUniform = m_shader.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	m_spriteBatch.begin(Feintgine::GlyphSortType::FRONT_TO_BACK);

    m_bg.draw(m_spriteBatch);
	m_battleScene.draw(m_spriteBatch);
	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_shader.unuse();
	

	drawGUI();
	SDL_GL_SetSwapInterval(1);	

}

void TestTBScreen::drawGameplay()
{

  //  glViewport(0, 0, m_window->getScreenWidth(), m_window->getScreenHeight());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    m_shader.use();

    glm::mat4 projectionMatrix;
	GLint pUniform;

    GLint textureUniform = m_shader.getUniformLocation("mySampler");
    glUniform1i(textureUniform, 0);
    glActiveTexture(GL_TEXTURE0);

    projectionMatrix =  m_camera.getCameraMatrix();
    pUniform = m_shader.getUniformLocation("P");

    glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

    m_spriteBatch.begin();
    m_bg.draw(m_spriteBatch);
    m_spriteBatch.end();
    m_spriteBatch.renderBatch();

    m_shader.unuse();




}


void TestTBScreen::drawGUI()
{

	m_battleScene.drawGUI();
}


