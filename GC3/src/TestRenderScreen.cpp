#include "TestRenderScreen.h"
#include <ft2build.h>

#pragma execution_character_set( "utf-8" )
TestRenderScreen::TestRenderScreen()
{
}

TestRenderScreen::TestRenderScreen(Feintgine::Window * window)
{
	m_dayLight = glm::vec3(1, 1, 1);
	m_window = window;
	m_screenIndex = 9;

	initShader();
}

TestRenderScreen::~TestRenderScreen()
{
}

void TestRenderScreen::build()
{
	
}

void TestRenderScreen::checkInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{
		m_gui.onSDLEvent(evnt);
		m_camera.handleInput(m_game->m_inputManager, evnt);
		m_game->onSDLEvent(evnt);
	}
	handleInput(m_game->m_inputManager);
}

void TestRenderScreen::destroy()
{
	
}

void TestRenderScreen::draw()
{
	
	glViewport(0, 0, 1600, 900);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	
	m_frameBuffer.bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawSample();

	m_frameBuffer.unbind();
	

	m_frameBufferScreen.use();
	
	t_time += 0.25f;
	//m_frameBufferScreen.setUniformFloat("time", t_time);
	//m_frameBufferScreen.setUniformVec3("daylight", glm::vec3(m_dayLight));
	//m_frameBufferScreen.setUniformVec2("ripplePos", glm::vec2(0));
	//m_frameBufferScreen.setUniformMat4("P",m_camera.getCameraMatrix());
	glm::vec2 ripplePos = m_camera.converWorldToScreen(m_object.getPos());// / glm::vec2(m_window->getScreenWidth(), m_window->getScreenHeight());// / glm::vec2(m_window->getScreenWidth(), m_window->getScreenHeight()));
	ripplePos.x = 1.0f - (ripplePos.x/ m_window->getScreenWidth());
	ripplePos.y = ripplePos.y / m_window->getScreenHeight();


	// Todo : create a class that store ripple then pass to shader


	//std::cout << feint_common::Instance()->convertVec2toString(ripplePos) << "\n";
	//m_frameBufferScreen.setUniformVec2("ripplePos", ripplePos);
	//m_frameBufferScreen.setUniformFloat("intensityEffect", 0.01f);
	//m_frameBufferScreen.setUniformFloat("speed", 1.0f);

	m_effectBatch.draw();

	m_frameBufferScreen.draw();
	m_frameBufferScreen.unuse();
	//m_textRenderer.renderText(m_camera, L"some text/ vài dòng chữ/めらみぽっぷ", m_camera.convertScreenToWorld(m_game->m_inputManager.getMouseCoords()), Feintgine::Color(255, 255, 255, 255), 1, ALIGN_FT_CENTER);


}

int TestRenderScreen::getNextScreenIndex() const
{
	return -1;
}

int TestRenderScreen::getPreviousScreenIndex() const
{
	return -1;
}

void TestRenderScreen::onEntry()
{
	
	m_spriteBatch.init();
	Feintgine::SpriteManager::Instance()->loadFromDirectory("Assets/", 0);
	//m_textRenderer.init(64,300, "font/ARIALUNI-V2.otf");

	m_camera.init(m_window->getScreenWidth() , m_window->getScreenHeight(),7);
	m_camera.setScale(1);
	m_camera.setPosition(glm::vec2(0));
	m_camera.update();
	bg.init(Feintgine::ResourceManager::getTexture("./Assets/Textures/ringed_city.png"),
		glm::vec2(0), glm::vec2(1920, 1080), Feintgine::Color(255, 255, 255, 255));

	m_object.init("./Assets/F_AObjects/fairy_enemy_elite_1.xml");

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	initGUI();

	m_effectBatch.initEffectBatch(&m_frameBufferScreen, &m_camera);

	float m_spine = 0.4;


}

void TestRenderScreen::onExit()
{
	m_shader.dispose();
	m_gui.destroy();
}

void TestRenderScreen::update(float deltaTime)
{
	m_camera.update();
	m_object.update(deltaTime);
	m_gui.update();
	m_effectBatch.update(deltaTime);
}

void TestRenderScreen::initGUI()
{
	m_gui.init("GUI");
	
	m_gui.loadScheme("TaharezLook.scheme");
	m_gui.loadScheme("AlfiskoSkin.scheme");
	m_gui.loadScheme("OgreTray.scheme");
	m_gui.loadScheme("Golden.scheme");
	m_gui.setFont("DejaVuSans-12");
}

void TestRenderScreen::initShader()
{
	m_shader.compileShaders("Shaders/TestRender/normalshader.vert", "Shaders/TestRender/normalshader.frag");
	m_shader.addAttribute("vertexPosition");
	m_shader.addAttribute("vertexColor");
	m_shader.addAttribute("vertexUV");
	m_shader.linkShaders();
	m_alpha = 1;



	GLuint tex_fb = m_frameBuffer.init(m_window->getScreenWidth(), m_window->getScreenHeight());

	m_frameBufferScreen.initShader("Shaders/FBO/defaultshader_FBO.vert", "Shaders/FBO/defaultshader_FBO.frag");

	m_frameBufferScreen.initFrameTexture(tex_fb, m_window->getScreenWidth(), m_window->getScreenHeight());

	m_lightBatch.initShader(&m_shader);
}

void TestRenderScreen::handleInput(Feintgine::InputManager & inputManager)
{
	if (inputManager.isKeyPressed(SDLK_ESCAPE))
	{
		m_currentState = Feintgine::ScreenState::EXIT_APPLICATION;
	}
	if (inputManager.isKeyPressed(SDLK_SPACE))
	{
		//t_time = 0.0f;
		m_effectBatch.addRippleEffect(m_object.getPos(), 0.5f, 3.5f, 0.0f, 0.0f ,0.0f);
	}

	if (inputManager.isKeyDown(SDLK_DOWN))
	{
		m_dayLight *= 0.95f;
	}
	if (inputManager.isKeyDown(SDLK_UP))
	{
		m_dayLight *= 1.05f;
	}

	if (inputManager.isKeyPressed(SDL_BUTTON_LEFT))
	{
		m_effectBatch.addRippleEffect(m_camera.convertScreenToWorld(inputManager.getMouseCoords()) , 0.5f, 3.5f, 0.0f, 0.0f, 0.0f);
	}

	m_object.handleInput(inputManager);
}

void TestRenderScreen::drawSample()
{

	

	glm::mat4 projectionMatrix;
	GLint pUniform;

	m_shader.use();

	GLint textureUniform = m_shader.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	glActiveTexture(GL_TEXTURE0);

	pUniform = m_shader.getUniformLocation("P");
	projectionMatrix = m_camera.getCameraMatrix();
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	GLint dayLightIndex = m_shader.getUniformLocation("dayLight");
	glUniform3f(dayLightIndex, .0f, .0f, .0f);

	m_lightBatch.begin();

	m_object.drawLight(m_lightBatch);

	m_lightBatch.renderLight();


	m_spriteBatch.begin(Feintgine::GlyphSortType::FRONT_TO_BACK);

	
	m_object.draw(m_spriteBatch);
	bg.draw(m_spriteBatch);
	m_spriteBatch.end();
	m_spriteBatch.renderBatch();

	m_shader.unuse();
}

