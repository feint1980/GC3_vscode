// #include "TestScreen.h"
// #include <iostream>
// #include <stdlib.h>
// 
// TestScreen::TestScreen()
// {
// 
// 
// 
// }
// 
// TestScreen::TestScreen(Feintgine::Window * window)
// {
// 	m_window = window;
// 	m_screenIndex = 4;
// 	initShader();
// 	
// }
// 
// TestScreen::~TestScreen()
// {
// 	initShader();
// }
// 
// int TestScreen::getNextScreenIndex() const
// {
// 	return NULL;
// }
// 
// int TestScreen::getPreviousScreenIndex() const
// {
// 	return NULL;
// }
// 
// void TestScreen::build()
// {
// 	
// }
// 
// void TestScreen::destroy()
// {
// 	
// }
// 
// void TestScreen::onEntry()
// {
// 	
// 
// 	srand(time(NULL));
// 	initWOrld();
// 	m_alpha = 1;
// 
// 
// 
// 	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
// 	m_camera.setScale(7.5f);
// 	m_spriteBatch.init();
// //	bg.init(Feintgine::ResourceManager::getTexture("Textures/bg.png"), glm::vec2(-20,0), glm::vec2(13, 8), Feintgine::Color(255, 255, 255, 255));
// 
// 	//createTheBlocks(6);
// 	createBlocks();
// 
// 	m_patchy.onInit();
// 	m_patchy.init(glm::vec2(-10, 20), glm::vec2(10), Feintgine::ResourceManager::getTexture("Textures/bosses/patchouli/patchouli.png"), glm::vec2(12, 9), Feintgine::Color(255, 255, 255, 255), "patchouli_knowledge");
// 	bg.init(Feintgine::ResourceManager::getTexture("Textures/system/HUD.png"), glm::vec2(0, 0), glm::vec2(140, 84), Feintgine::Color(255, 255, 255, 255));
// 	m_patchy.setB2World(m_world);
// 	m_patchy.setBlocks(m_blocks);
// 
// 	//mouseLight.position = glm::vec2(20, 0);
// 	m_camera.convertScreenToWorld(m_game->getInputManager().getMouseCoords());
// 
// 	SDL_GL_SetSwapInterval(1);
// 
// }
// 
// void TestScreen::onExit()
// {
// 	
// }
// 
// void TestScreen::update(float deltaTime)
// {
// 	
// 	checkInput();
// 	handleInput(m_game->getInputManager());
// 	m_patchy.handleInput(m_game->getInputManager());
// 	m_camera.update();
// 
// 	m_patchy.update();
// 
// 	if (activePhysic)
// 	{
// 		m_world->Step(1.0f / 60.0f, 6, 20);
// 		if (isStahp)
// 		{
// 			stahp(.58f);
// 		}
// 	}
// 	if (!cheat_physic)
// 	{
// 		if (m_patchy.cheat_physic)
// 		{
// 			physicMode();
// 			cheat_physic = true;
// 		}
// 	}
// 	
// 	
// 	
// }
// 
// void TestScreen::draw()
// {
// 	
// 
// 	/* Draw Order
// 	1 - Light
// 	2 - Objects 
// 	3 - Shadow of object that cause by light ( sounds not so logic elelelelel) -> but it is
// 	
// 	*/
// 	
// 
// 	glm::mat4 projectionMatrix;
// 	GLint pUniform;
// 	GLint textureUniform;
// 
// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// 	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
// 
// 
// 	
// 
// 	//Draw Light here
// 	m_lighShader.use();
// 	projectionMatrix = m_camera.getCameraMatrix();
// 	pUniform = m_lighShader.getUniformLocation("P");
// 	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);
// 
// 	// Additive blending
// 	
// 	glBlendEquation(GL_FUNC_ADD);
// 	glBlendFunc(GL_SRC_ALPHA, GL_ZERO);
// 
// 	m_spriteBatch.begin();
// 
// 	//playerLight.draw(m_spriteBatch);
// 	glColorMask(true, true, true, false);
// 	/*mouseLight.draw(m_spriteBatch);*/
// 	m_patchy.drawLight(m_spriteBatch);
// 
// 
// 	m_spriteBatch.end();
// 	m_spriteBatch.renderBatch();
// 
// 	m_lighShader.unuse();
// 
// 
// 	
// 	//Draw Shadow Here
// 	m_shadowShader.use();
// 	projectionMatrix = m_camera.getCameraMatrix();
// 	pUniform = m_shadowShader.getUniformLocation("P");
// 	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);
// 	m_spriteBatch.begin();
// 
// 	
// 	
// 	
// 	//glColorMask(false, false, false, true);
// 	m_patchy.getLight().drawShadows(m_spriteBatch, m_blocks);
// 
// 	m_spriteBatch.end();
// 	m_spriteBatch.renderBatch();
// 	m_shadowShader.unuse();
// 
// 
// 	// Reset to regular alpha blending
// 	//glBlendFunc(GL_DST_COLOR, GL_DST_ALPHA);
// 
// 	//Draw Object here
// 	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
// 	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
// 	m_normalShader.use();
// 
// 
// 	 textureUniform = m_normalShader.getUniformLocation("mySampler");
// 	glUniform1i(textureUniform, 0);
// 	glActiveTexture(GL_TEXTURE0);
// 
// 
// 	projectionMatrix = m_camera.getCameraMatrix();
// 	pUniform = m_normalShader.getUniformLocation("P");
// 	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);
// 
// 
// 
// 	m_spriteBatch.begin();
// 
// 
// 	//bg.draw(m_spriteBatch);
// 
// 	for (int i = 0; i < m_blocks.size(); i++)
// 	{
// 		m_blocks[i].update();
// 		m_blocks[i].draw(m_spriteBatch);
// 	}
// 	
// 	//m_patchy.draw(m_spriteBatch);
// 
// 	m_spriteBatch.end();
// 	m_spriteBatch.renderBatch();
// 	m_normalShader.unuse();
// 
// 
// 	//glBlendFunc(GL_DST_ALPHA, GL_DST_COLOR);
// 	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
// 	m_normalShader.use();
// 
// 	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
// 	textureUniform = m_normalShader.getUniformLocation("mySampler");
// 	glUniform1i(textureUniform, 0);
// 	glActiveTexture(GL_TEXTURE0);
// 
// 
// 	projectionMatrix = m_camera.getCameraMatrix();
// 	pUniform = m_normalShader.getUniformLocation("P");
// 	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);
// 
// 	
// 
// 	m_spriteBatch.begin();
// 	
// 
// 	
// 	m_patchy.drawChildren(m_spriteBatch);
// 
// 	m_patchy.draw(m_spriteBatch);
// 	bg.draw(m_spriteBatch);
// 	m_spriteBatch.end();
// 	m_spriteBatch.renderBatch();
// 	m_normalShader.unuse();
// 
// 
// 	//m_shadowShader
// 
// 
// 	
// //	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
// 
// 
// 
// }
// 
// void TestScreen::initShader()
// {
// 	
// 
// 	m_normalShader.compileShaders("Shaders/texture.vert", "Shaders/texture.frag");
// 	m_normalShader.addAttribute("vertexPosition");
// 	m_normalShader.addAttribute("vertexColor");
// 	m_normalShader.addAttribute("vertexUV");
// 	m_normalShader.addAttribute("spec");
// 	m_normalShader.linkShaders();
// 
// 
// 	m_lighShader.compileShaders("Shaders/lightShading.vert", "Shaders/lightShading.frag");
// 	m_lighShader.addAttribute("vertexPosition");
// 	m_lighShader.addAttribute("vertexColor");
// 	m_lighShader.addAttribute("vertexUV");
// 	m_lighShader.linkShaders();
// 
// 	m_shadowShader.compileShaders("Shaders/lightShading.vert", "Shaders/lightShading.frag");
// 	m_shadowShader.addAttribute("vertexPosition");
// 	m_shadowShader.addAttribute("vertexColor");
// 	m_shadowShader.addAttribute("vertexUV");
// 	m_shadowShader.linkShaders();
// 
// 
// }
// 
// void TestScreen::checkInput()
// {
// 	SDL_Event evnt;
// 	while (SDL_PollEvent(&evnt)) {
// 		m_game->onSDLEvent(evnt);
// 	}
// }
// 
// void TestScreen::handleInput(Feintgine::InputManager &inputManager)
// {
// 	if (inputManager.isKeyDown(SDL_BUTTON_LEFT))
// 	{
// 		
// 		system("cls");
// 		//mouseLight.size += 2.5;
// 	}
// 	if (inputManager.isKeyPressed(SDL_BUTTON_RIGHT))
// 	{
// 		
// 		std::cout << "click \n";
// 		//mouseLight.size -= 2.5;
// 	}
// 
// 	if (inputManager.isKeyPressed(SDLK_SPACE))
// 	{
// 			physicMode();	
// 	}
// 
// 	if (inputManager.isKeyPressed(SDLK_v))
// 	{
// 		m_patchy.playAnimation("Summon_Bookshelf");
// 		summonBlock();
// 	}
// 
// 	if (inputManager.isKeyPressed(SDLK_ESCAPE))
// 	{
// 		m_currentState = Feintgine::ScreenState::EXIT_APPLICATION;
// 	}
// }
// 
// void TestScreen::initWOrld()
// {
// 
// 	b2Vec2 gravity(0, 0.0f);
// 	m_world = new b2World(gravity);
// 
// }
// 
// void TestScreen::physicMode()
// {
// 	if (!activePhysic)
// 	{
// 		activePhysic = true;
// 	}
// 	else
// 	{
// 		activePhysic = false;
// 	}
// }
// 
// void TestScreen::createTheWall()
// {
// 	
// 
// }
// 
// void TestScreen::createTheBlocks(int seed)
// {
// 	int a;
// 	for (int i = 0; i < seed; i++)
// 	{
// 		a = rand() % 5;
// 		initBlock(a);
// 		cout << a << "\n";
// 	}
// 
// 
// }
// 
// void TestScreen::summonBlock()
// {
// 	for (int i = 0; i < m_blocks.size(); i++)
// 	{
//  		m_blocks[i].getBody()->ApplyLinearImpulse(m_blocks[i].summonDirection(glm::vec2(m_patchy.getPos().x, -10)), m_blocks[i].getBody()->GetWorldCenter(), true);
// 		m_blocks[i].getBody()->SetAngularVelocity(4.7f);
// 	}
// 	
// 	physicMode();
// 	stahper = 0.0f;
// 	isStahp = true;
// 	
// }
// 
// void TestScreen::initBlock(int instance)
// {
// 	block a;
// 	switch (instance)
// 	{
// 	case 0 : 
// 		a.init(Feintgine::ResourceManager::getTexture("Textures/bookshelf/bookshelf_01.png"), glm::vec2(-1000, 50), glm::vec2(19.2, 6.2), Feintgine::Color(255, 255, 255, 255));
// 		a.update();
// 		m_blocks.push_back(a);
// 		break;
// 	case 1:
// 		a.init(Feintgine::ResourceManager::getTexture("Textures/bookshelf/bookshelf_02.png"), glm::vec2(-1000, 50), glm::vec2(9.7, 6.4), Feintgine::Color(255, 255, 255, 255));
// 		a.update();
// 		m_blocks.push_back(a);
// 		break;
// 	case 2:
// 		a.init(Feintgine::ResourceManager::getTexture("Textures/bookshelf/bookshelf_03.png"), glm::vec2(-1000, 50), glm::vec2(16.0, 6.4), Feintgine::Color(255, 255, 255, 255));
// 		a.update();
// 		m_blocks.push_back(a);
// 		break;
// 	case 3:
// 		a.init(Feintgine::ResourceManager::getTexture("Textures/bookshelf/bookshelf_04.png"), glm::vec2(-1000, 50), glm::vec2(12.8, 6.4), Feintgine::Color(255, 255, 255, 255));
// 		a.update();
// 		m_blocks.push_back(a);
// 		break;
// 	case 4:
// 		a.init(Feintgine::ResourceManager::getTexture("Textures/bookshelf/bookshelf_05.png"), glm::vec2(-1000, 50), glm::vec2(6.4, 6.5), Feintgine::Color(255, 255, 255, 255));
// 		a.update();
// 		m_blocks.push_back(a);
// 		break;
// 
// 	default:
// 		break;
// 	}
// }
// 
// void TestScreen::createBlocks()
// {
// 	block a;
// 	a.init(Feintgine::ResourceManager::getTexture("Textures/bookshelf/bookshelf_02.png"), glm::vec2(-78, 50), glm::vec2(9.7, 6.4), Feintgine::Color(255, 255, 255, 255));
// 	a.loadPhysic(m_world);
// 	a.update();	
// 	m_blocks.push_back(a);
// 
// 
// 	a.init(Feintgine::ResourceManager::getTexture("Textures/bookshelf/bookshelf_02.png"), glm::vec2(24, 50), glm::vec2(9.2, 6.2), Feintgine::Color(255, 255, 255, 255));
// 	a.loadPhysic(m_world);
// 	a.update();
// 	m_blocks.push_back(a);
// 
// 	a.init(Feintgine::ResourceManager::getTexture("Textures/bookshelf/bookshelf_05.png"), glm::vec2(24, -50), glm::vec2(6.4, 6.5), Feintgine::Color(255, 255, 255, 255));
// 	a.loadPhysic(m_world);
// 	a.update();
// 	m_blocks.push_back(a);
// 
// 	a.init(Feintgine::ResourceManager::getTexture("Textures/bookshelf/bookshelf_04.png"), glm::vec2(-78, -50), glm::vec2(12.8, 6.4), Feintgine::Color(255, 255, 255, 255));
// 	a.loadPhysic(m_world);
// 	a.update();
// 	m_blocks.push_back(a);
// 
// 	a.init(Feintgine::ResourceManager::getTexture("Textures/bookshelf/bookshelf_05.png"), glm::vec2(-12, -44), glm::vec2(6.4, 6.5), Feintgine::Color(255, 255, 255, 255));
// 	a.loadPhysic(m_world);
// 	a.update();
// 	m_blocks.push_back(a);
// 
// }
// 
// void TestScreen::stahp(float staph_man)
// {
// 	
// 		stahper += 0.01f;
// 		if (stahper >= staph_man)
// 		{
// 			isStahp = false;
// 			physicMode();
// 			m_patchy.playAnimation("Book");
// 		}
// 
// 	
// }
// 
