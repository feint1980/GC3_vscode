#include "TestScreeb.h"



TestScreeb::TestScreeb(Feintgine::Window * window)
{
	m_alpha = 1;
	m_window = window;
	m_screenIndex = 0;
	initShader();
	std::cout << " init \n";
}

TestScreeb::TestScreeb()
{

}



TestScreeb::~TestScreeb()
{
}

int TestScreeb::getNextScreenIndex() const
{
	return -1;
}

int TestScreeb::getPreviousScreenIndex() const
{
	return -1;
}

void TestScreeb::build()
{
	
}

void TestScreeb::destroy()
{
	
}

void TestScreeb::onEntry()
{


	Feintgine::SpriteManager::Instance()->loadFromDirectory("Assets/", 0);
	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());

	std::cout << " init with " << m_window->getScreenWidth() << " and " << m_window->getScreenHeight() << "\n";
	m_camera.setScale(1.0f);
	m_spriteBatch.init();

	testObj.init(Feintgine::ResourceManager::getTexture("Textures/bg.png"), 
		glm::vec2(-10, 10), glm::vec2(80.0f, 100.0f), Feintgine::Color(255, 255, 255, 255));
	testObj.setSPec(1);
	//m_camera.setPosition(testObj.getPos());
	m_camera.update();

	std::cout << "camera pos is " << feint_common::Instance()->convertVec2toString(m_camera.getPosition()) << "\n";
	m_luaManager.init();
	//m_luaManager.readFile("Assets/Lua/test.lua");

	// m_luaObj.init(glm::vec2(0, 0), glm::vec2(1.0f, 1.0f), "Assets/F_AObjects/boss_komachi.xml", "name", 1, glm::vec2(0, 0));
	// m_anim.init("./Assets/F_AObjects/boss_komachi.xml");
	// m_anim.setPos(glm::vec2(0, 0));
	// m_anim.playAnimation("idle");
}

void TestScreeb::onExit()
{
	
}

void TestScreeb::update(float deltaTime)
{

	startScreen();
	m_camera.update();
	checkInput();
	handleInput(m_game->m_inputManager);

	m_anim.update(deltaTime);
	m_luaManager.update(deltaTime);
	//m_luaObj.update(deltaTime);
}

void TestScreeb::draw()
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

	m_spriteBatch.begin();

	m_luaManager.draw(m_spriteBatch);
	
	//m_luaObj.draw(m_spriteBatch);
	//m_anim.draw(m_spriteBatch);
	//testObj.draw(m_spriteBatch);
	//m_player.draw(m_spriteBatch);

	//drawHUD();
	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_shader.unuse();


	//SDL_GL_SetSwapInterval(1);
	//
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void TestScreeb::initShader()
{

	// m_shader.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
	// m_shader.addAttribute("vertexPosition");
	// m_shader.addAttribute("vertexColor");
	// m_shader.addAttribute("vertexUV");

	m_shader.compileShaders("Shaders/ShaderToy/normal.vert", "Shaders/ShaderToy/normal.frag");
	m_shader.addAttribute("vertexPosition");
	m_shader.addAttribute("vertexColor");
	m_shader.addAttribute("vertexUV");
	//m_shader.addAttribute("spec");
	m_shader.linkShaders();
}

void TestScreeb::handleInput(Feintgine::InputManager &inputManager)
{

	if (inputManager.isKeyPressed(SDLK_j))
	{
		std::cout << "something \n";
		m_currentState = Feintgine::ScreenState::EXIT_APPLICATION;
	//	exit(1);
		
	}
}

void TestScreeb::checkInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		m_game->onSDLEvent(evnt);
	}
}
