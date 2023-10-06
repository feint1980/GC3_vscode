// #include "GameplayScreen.h"
// #include <ResourceManager.h>
// #include <random>
// #include "Light.h"
// #include <iostream>
// #include <algorithm>
// #include "MonManager.h"



// GameplayScreen::GameplayScreen(Feintgine::Window * window, const std::string & file)
// {
// 	m_screenIndex = SCREEN_INDEX_GAMEPLAY;
// 	m_window = window;
// 	m_alpha = 0;
	
// 	levelFile = file;
// }


// GameplayScreen::~GameplayScreen()
// {
// }

// int GameplayScreen::getNextScreenIndex() const
// {
// 	return SCREEN_INDEX_MAINMENU;
// }
// int GameplayScreen::getPreviousScreenIndex() const
// {
// 	return SCREEN_INDEX_NULL;
// }

// void GameplayScreen::build()
// {

// }
// void GameplayScreen::destroy()
// {

// }
// void GameplayScreen::loadLevel(const std::string & levelFile)
// {

// 	m_levelData.clear();
// 	Feintgine::GLTexture grids = Feintgine::ResourceManager::getTexture("Textures/grid.png");
// 	Feintgine::GLTexture bg = Feintgine::ResourceManager::getTexture("Textures/brick.png");
// 	Feintgine::GLTexture tiles = Feintgine::ResourceManager::getTexture("Textures/tiles.png");
// 	Feintgine::GLTexture outsideGridTexture = Feintgine::ResourceManager::getTexture("Textures/outsideGrid.png");
// 	Feintgine::GLTexture dino = Feintgine::ResourceManager::getTexture("Textures/kl.png");
// 	Feintgine::GLTexture tile_txt = Feintgine::ResourceManager::getTexture("Textures/terra.png");
// 	Feintgine::GLTexture tile_tree = Feintgine::ResourceManager::getTexture("Textures/tree.png");
// 	Feintgine::GLTexture shops = Feintgine::ResourceManager::getTexture("Textures/shopslol.png");
// 	Feintgine::GLTexture create = Feintgine::ResourceManager::getTexture("Textures/crate.png");
// 	Feintgine::GLTexture simple = Feintgine::ResourceManager::getTexture("Textures/simple.png");
// 	Feintgine::GLTexture NPC = Feintgine::ResourceManager::getTexture("Textures/lumber.png");
// 	Feintgine::GLTexture well = Feintgine::ResourceManager::getTexture("Textures/well.png");
// 	std::ifstream file;
// 	file.open(levelFile);
// 	if (file.fail())
// 	{
// 		std::cout << "didn't find it , bitch ! " + levelFile;
// 	}
// 	else
// 	{
// 		std::string tmp;

		
// 		while (std::getline(file, tmp))
// 		{
// 			m_levelData.push_back(tmp);
			
// 		}
// 		std::reverse(m_levelData.begin(), m_levelData.end());


// 		for (int y = 0; y < m_levelData.size(); y++)
// 		{
// 			for (int x = 0; x < m_levelData[y].size(); x++)
// 			{

// 				char tile = m_levelData[y][x];
// 				if (tile == '@')
// 				{
// 					//m_player.init(glm::vec2(x, y), glm::vec2(2.0f), glm::vec2(1.0f), Feintgine::Color(255, 255, 255, 255), m_game->getWindow() ,m_gui, m_guiCamera);
				
// 				}
// 				if (tile == 'P')
// 				{

// 					PushableObject obj;
// 					obj.init(glm::vec2(x, y), glm::vec2(1.0f), tiles, Feintgine::Color(255, 255, 255, 255), glm::vec2(3, 5));
// 					obj.setTile(9);
// 					m_tiles.push_back(obj);
// 				}
// 				if (tile == 'O')
// 				{
// 					OutsideGrid outsideGrid;
// 					outsideGrid.init(outsideGridTexture, glm::vec2(x, y), glm::vec2(1.0f), Feintgine::Color(255, 255, 255, 255));
// 					m_outsideGrids.push_back(outsideGrid);
// 				}
// 				if (tile == 'X')
// 				{
				
// 						centerPos = glm::vec2(x, y);
				
// 				}
// // 				if (tile == 'D')
// // 				{
// // 					BasicMonster kl;
// // 					kl.init(glm::vec2(x, y), glm::vec2(2.0f), glm::vec2(1.0f), Feintgine::Color(255, 255, 255, 255));
// // 					m_monsters.push_back(kl);
// // 
// // 				}


// 			}
// 		}
// 		height = m_levelData.size();
// 		width = m_levelData[0].size();
	
// 			for (int i = 0; i < m_levelData.size() - 1; i++)
// 			{
// 				for (int j = 0; j < m_levelData[i].size() - 1; j++)
// 				{

// 					Grid grid;
// 					grid.init(grids, glm::vec2(j, i), glm::vec2(1.0f), Feintgine::Color(255, 255, 255, 255));
// 					m_grids.push_back(grid);


// 				}
// 			}
		

			
// 	}

// }
// void GameplayScreen::onEntry()
// {
// 	srand(time(NULL));
// 	//
// 	m_debugRender.init();
// 	//m_dropItem.clear();

// 	initGUI();

// 	//	loadLevel("Levels/level1.txt");

// 	loadLevel(levelFile);

// 	// init draw materials
// 	m_spriteBatch.init();
// 	m_guispriteBatch.init();
// 	// Shaders 

// 	m_textureProgram.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
// 	m_textureProgram.addAttribute("vertexPosition");
// 	m_textureProgram.addAttribute("vertexColor");
// 	m_textureProgram.addAttribute("vertexUV");
// 	m_textureProgram.linkShaders();

// 	//load texture
	
// 	//compiling light shader
// 	m_lightProgram.compileShaders("Shaders/lightShading.vert", "Shaders/lightShading.frag");
// 	m_lightProgram.addAttribute("vertexPosition");
// 	m_lightProgram.addAttribute("vertexColor");
// 	m_lightProgram.addAttribute("vertexUV");
// 	m_lightProgram.linkShaders();
	

// 	//init camera
// 	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
// 	m_camera.setScale(35.0f);
// 	m_camera.setPosition(centerPos);

// 	m_guiCamera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
// 	m_guiCamera.setScale(35.0f);

// 	//init GUI;
	

// }
// void GameplayScreen::onExit()
// {
// 	m_debugRender.dispose();
// }



// void GameplayScreen::update(float deltaTime)
// {
// 	m_camera.update();
// 	m_guiCamera.update();

// 	startScreen();

	


// 	if (startup)
// 	{
	
// 		checkInput();
// 		handleInput(m_game->m_inputManager);
// 		if (!m_isPaused)
// 		{

// 			if (m_gameState == GameState::TOWN)
// 			{
// 				m_camera.setPosition(m_player.getPos());
// 			}
			
// // 			for (int i = 0; i < m_dropItem.size(); i++)
// // 			{
// // 				m_dropItem[i]->update(m_player);
// // 				if (m_dropItem[i]->collected)
// // 				{
// // 					m_player.m_inventory.refreshItem();
// // 					m_dropItem.erase(m_dropItem.begin() + i);
// // 					
// // 					
// // 				}
// // 			}
		
// 			//Update physics simulation 

// 			m_player.handleInput(m_game->m_inputManager);

// 			//grid rule
// 			m_player.update(m_grids, m_tiles, m_townTile);

			

// // 			for (int i = 0; i < m_monsters.size(); i++)
// // 			{
// // 				m_monsters[i].update(m_grids, m_tiles, m_outsideGrids, m_player);
// // 				if (!m_monsters[i].getLife())
// // 				{
// // 					m_monsters.erase(m_monsters.begin() + i);
// // 					//m_player.addMon(1);
// // 				}
// // 			}

// 			for (int i = 0; i < m_tiles.size(); i++)
// 			{
// 				std::vector<PushableObject> m_culledTiles;
// 				m_tiles[i].update();
// 				m_tiles[i].checkOuter(m_grids);
// 				for (int j = 0; j < m_tiles.size(); j++)
// 				{

// 					if (j != i)
// 					{

// 						m_culledTiles.push_back(m_tiles[j]);

// 					}
// 				}

// 				m_tiles[i].checkCollide(m_culledTiles, m_outsideGrids);
// 				if (m_tiles[i].isDestroyed())
// 				{
					
// // 					rate = rand() % 100 + 1;
// // 					//std::cout << rate <<"\n"; 
// // 					if (rate >= 20 && rate <= 40)
// // 					{
// // 						DropIcon * di = new DropIcon();
// // 						di->init(m_tiles[i].getPos(), m_tiles[i].getDims(), "1");
// // 						
// // 						m_dropItem.push_back(di);
// // 					}
// // 					if (rate >= 41 && rate <= 60)
// // 					{
// // 						DropIcon * di = new DropIcon();
// // 						di->init(m_tiles[i].getPos(), m_tiles[i].getDims(), "2");
// // 						m_dropItem.push_back(di);
// // 					}

// 					m_tiles.erase(m_tiles.begin() + i);
					
// 				}

// 			}

// 		}
// 	}

	
	
	


// }
// void GameplayScreen::draw()
// {
// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// 	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

// 	m_textureProgram.use();

// 	// Upload texture uniform
// 	GLint textureUniform = m_textureProgram.getUniformLocation("mySampler");
// 	glUniform1i(textureUniform, 0);
// 	glActiveTexture(GL_TEXTURE0);

// 	GLint alphaLocation = m_textureProgram.getUniformLocation("time");
// 	glUniform1f(alphaLocation, m_alpha);

// 	// Camera matrix
// 	glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
// 	GLint pUniform = m_textureProgram.getUniformLocation("P");
// 	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

// 	m_spriteBatch.begin();

	

// 	for (auto& b : m_grids) {
// 		b.draw(m_spriteBatch);
// 	}
// 	for (auto& o : m_outsideGrids) {
// 		o.draw(m_spriteBatch);
// 	}
// 	for (auto & t : m_tiles)
// 	{
// 		t.draw(m_spriteBatch);
// 	}
// // 	for (auto & m : m_monsters)
// // 	{
// // 		m.draw(m_spriteBatch);
// // 	}
// 	for (auto & t : m_townTile)
// 	{
// 		t.draw(m_spriteBatch);
// 	}
// // 	for (auto & i : m_dropItem)
// // 	{
// // 		i->draw(m_spriteBatch);
// // 	}
// 	// Draw all the boxes


// 	m_player.draw(m_spriteBatch);
	
// 	m_spriteBatch.end();
// 	m_spriteBatch.renderBatch();

// 	glm::mat4 cameraMatrix = m_guiCamera.getCameraMatrix();
// 	GLint pLocation = m_textureProgram.getUniformLocation("P");
// 	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

// 	m_guispriteBatch.begin();
// 	m_player.drawGUI(m_guispriteBatch);
// 	m_guispriteBatch.end();
// 	m_guispriteBatch.renderBatch();
// 	m_textureProgram.unuse();
// 	//Debug Rendering

// 	if (m_debugMode)
// 	{
		
// 		glm::vec4 playerDesRect;

// 		playerDesRect.z = 0.1f;
// 		playerDesRect.w = 0.1f;
// 		m_player.drawDebug(m_debugRender);
		
// 		for (auto & g : m_grids)
// 		{
			
// 			g.drawCenter(m_debugRender);
// 		}
// // 		for (auto & m : m_monsters)
// // 		{
// // 			m.drawDebug(m_debugRender);
// // 		}

// 		for (auto & t : m_tiles)
// 		{
// 			t.drawDebug(m_debugRender);
// 		}
// 		m_debugRender.end();
// 		m_debugRender.render(projectionMatrix, 2.0f);
// 	}

// 	Light playerLight;
// 	playerLight.color = Feintgine::Color(200, 200, 255, 225);
	
// 	playerLight.size = 40.0f;

// 	Light mouseLight;
// 	mouseLight.color = Feintgine::Color(255, 0, 255, 150);
// 	mouseLight.position = m_camera.convertScreenToWorld(m_game->m_inputManager.getMouseCoords());
// 	mouseLight.size = 45.0f;

// 	m_lightProgram.use();
// 	pUniform = m_textureProgram.getUniformLocation("P");
// 	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

// 	// Additive blending
// 	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

// 	m_spriteBatch.begin();

// 	//playerLight.draw(m_spriteBatch);
// 	//mouseLight.draw(m_spriteBatch);
	
// 	m_spriteBatch.end();
// 	m_spriteBatch.renderBatch();

// 	m_lightProgram.unuse();

// 	// Reset to regular alpha blending
// 	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

// 	SDL_GL_SetSwapInterval(1);

// 	m_gui.draw();

// }
// void GameplayScreen::handleInput(Feintgine::InputManager &inputManager)
// {
// 	if (inputManager.isKeyPressed(SDLK_F9))
// 	{
// 		setDebug();
// 	}
// 	if (inputManager.isKeyPressed(SDLK_F1))
// 	{
// 		int a = 1;
// 		std::cout << a; 
// 		setPause();
// 	}

// }

// void GameplayScreen::initGUI()
// {
// 	m_gui.init("GUI");
// 	m_gui.loadScheme("TaharezLook.scheme");
// 	m_gui.setFont("DejaVuSans-10");
// 	//CEGUI::PushButton* testButton = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button", glm::vec4(0.8f, 0.2f, 0.1f, 0.05f), glm::vec4(0.0f), "TestButton"));
// 	//testButton->setText("Hello World!");

// 	//testButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GameplayScreen::clickExit, this));

// 	//CEGUI::Editbox* TestCombobox = static_cast<CEGUI::Editbox*>(m_gui.createWidget("TaharezLook/Editbox", glm::vec4(0.2f, 0.2f, 0.5f, 0.05f), glm::vec4(0.0f), "TestCombobox"));

// 	m_gui.setMouseCursor("TaharezLook/MouseArrow");
// 	m_gui.showMouseCursor();
// 	SDL_ShowCursor(0);
// }
// void GameplayScreen::setPause()
// {
// 	if (m_isPaused)
// 	{
// 		m_isPaused = false;
// 	}
// 	else
// 	{
// 		m_isPaused = true;
// 	}
// }

// bool GameplayScreen::clickExit(const CEGUI::EventArgs & e)
// {
// 	m_currentState = Feintgine::ScreenState::EXIT_APPLICATION;
// 	return true;
// }
// void GameplayScreen::setDebug()
// {
// 	if (m_debugMode)
// 	{
// 		m_debugMode = false;
// 	}
// 	else
// 	{
// 		m_debugMode = true;
// 	}
// }


// void GameplayScreen::checkInput()
// {
// 	SDL_Event evnt;
// 	while (SDL_PollEvent(&evnt))
// 	{
// 		m_game->onSDLEvent(evnt );
// 		m_gui.onSDLEvent(evnt);
// 	}
	

// }

// void GameplayScreen::setType(GameState gameState)
// {
// 	m_gameState = gameState;
// }
