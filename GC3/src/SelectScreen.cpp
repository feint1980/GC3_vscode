// #include "SelectScreen.h"

// #pragma execution_character_set("utf-8")

// SelectScreen::SelectScreen()
// {


// }

// SelectScreen::SelectScreen(Feintgine::Window *window)
// {
	
// 	m_screenIndex = SCREEN_INDEX_SELECT;
// 	m_window = window;
// 	m_alpha = 0;

	

// 	//m_inputManager = m_game->getInputManager();



// }

// SelectScreen::~SelectScreen()
// {
// }

// int SelectScreen::getNextScreenIndex() const
// {
// 	return SCREEN_INDEX_MAINMENU;
// }

// int SelectScreen::getPreviousScreenIndex() const
// {
// 	return SCREEN_INDEX_MAINMENU;
// }

// void SelectScreen::build()
// {
		
// }

// void SelectScreen::destroy()
// {
	
// }

// void SelectScreen::onEntry()
// {
	
// 	initShader();
// 	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
// 	std::cout << " start send requset !\n";
	
// // 	Enet_UDP::Instance()->initEnet();
// // 	Enet_UDP::Instance()->createHost_Self();
// // 	Enet_UDP::Instance()->connectToServer("127.0..1", 11112);

// 	initGUI();
// 	MainGUI::Instance()->loadGUI();
// 	m_debugRender.init();

// 	//ClientSocket::Instance()->executeCommand("update_player_list");
// 	//updateSocket();
// //	SDL_ShowCursor(1);
	
// 	loadLevel("Levels/hakurei.txt");
	
// 	//m_player.init(glm::vec2(20, 15), glm::vec2(2.0f), glm::vec2(1.0f), Feintgine::Color(255, 255, 255, 255), m_game->getWindow(), m_camera);
// 	m_camera.setPosition(m_player.getPos());
// 	m_spriteBatch.init();
	
// 	m_camera.setScale(30.0f);
// 	m_camera.setAngle(0.01f);
// 	m_camera.update();
// 	//bg.init(Feintgine::ResourceManager::getTexture("Textures/bg.png"), glm::vec2(0, 0), glm::vec2(160, 90), Feintgine::Color(255, 255, 255, 255));
// 	m_player.init(glm::vec2(5), glm::vec2(2.0f), glm::vec2(1.0f), Feintgine::Color(255, 255, 255, 255), m_game->getWindow(), &m_camera, "Feint");
// 	m_player.loadGUI(m_gui);
// 	m_camera.setPosition(m_player.getPos());
	
// }

// void SelectScreen::onExit()
// {

// 	changeNext = false;
// 	changeBack = false;
// 	m_gui.destroy();
// 	MainGUI::Instance()->destroyGUI();
// }

// void SelectScreen::update(float deltaTime)
// {
// 	if (!changeBack)
// 	{
// 		if (m_alpha < 1)
// 		{
// 			m_alpha += FADE_SPEED;
// 		}
// 	}
// 	else
// 	{
// 		m_alpha -= FADE_SPEED * 2;
// 		if (m_alpha <= 0)
// 		{
// 			m_currentState = Feintgine::ScreenState::CHANGE_PREVIOUS;
// 		}
// 	}
	
	

// // 

// 	m_camera.update();


// /*	m_camera.update();*/

// 	checkInput();
// 	handleInput(m_game->getInputManager());
// 	if (m_player.getInit())
// 	{
// 		m_camera.setPosition(m_player.getPos());
// 		m_player.handleInput(m_game->getInputManager());

// 		//grid rule
// 		m_player.update(m_grids, m_tiles, m_townTile);
// 	}
// 	for (int i = 0; i < m_others.size(); i++)
// 	{
// 		m_others[i].update(m_player.getPos(),m_grids, m_tiles, m_townTile);
// 	}


// 	//updateSocket();

// // 	if (Enet_UDP::Instance()->getSentRequuest())
// // 	{
// // 		updateUDP();
// // 	}
// 	updateGUI();

// }

// void SelectScreen::draw()
// {
// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// 	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

// 	m_objectShader.use();


// 	GLint textureUniform = m_objectShader.getUniformLocation("mySampler");
// 	glUniform1i(textureUniform, 0);
// 	glActiveTexture(GL_TEXTURE0);


// 	GLint alphaLocation = m_objectShader.getUniformLocation("fadeout");
// 	glUniform1f(alphaLocation, m_alpha);


// 	// Camera matrix
// 	glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
// 	GLint pUniform = m_objectShader.getUniformLocation("P");
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
// 	for (auto & m : m_monsters)
// 	{
// 		m.draw(m_spriteBatch);
// 	}
// 	for (auto & t : m_townTile)
// 	{
		
// 		t.draw(m_spriteBatch);
// 	}
// 	for (int i = 0; i < m_others.size(); i++)
// 	{
// 		m_others[i].draw(m_spriteBatch);
// 	}

// 	if (m_player.getInit())
// 	{
// 		m_player.draw(m_spriteBatch);
// 		m_player.drawChat(m_spriteBatch);
		
// 	}

	

	
		
	
// //
// 	m_spriteBatch.end();
// 	m_spriteBatch.renderBatch();
// 	m_objectShader.unuse();

// 	//m_debugRender.drawBox(glm::vec4(33, 16, 1, 1), Feintgine::Color(255, 255, 255, 255), 0);
// 	m_debugRender.end();
// 	m_debugRender.render(projectionMatrix, 2.0f);

// 	MainGUI::Instance()->drawGUI();
// 	m_gui.draw();
	
// }

// void SelectScreen::initShader()
// {
// 	m_objectShader.compileShaders("Shaders/backup.vert", "Shaders/backup.frag");
// 	m_objectShader.addAttribute("vertexPosition");
// 	m_objectShader.addAttribute("vertexColor");
// 	m_objectShader.addAttribute("vertexUV");
// 	m_objectShader.linkShaders();


// }

// void SelectScreen::handleInput(Feintgine::InputManager &inputManager)
// {



// 	if (inputManager.isKeyPressed(SDLK_ESCAPE))
// 	{
// 		m_currentState = Feintgine::ScreenState::EXIT_APPLICATION;

// 	}
// 	if (inputManager.isKeyPressed(SDLK_SPACE))
// 	{
// 		//changePrevScreen();
// 	}
// 	MainGUI::Instance()->handleKey(inputManager);
// }

// void SelectScreen::checkInput()
// {
// 	SDL_Event evnt;
// 	while (SDL_PollEvent(&evnt)) {
// 		m_game->onSDLEvent(evnt);
// 		m_gui.onSDLEvent(evnt);
// 		MainGUI::Instance()->getGUI().onSDLEvent(evnt);
// 	}
// }

// void SelectScreen::loadLevel(const std::string & levelFile)
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
  					
						
// 						TownTile mytile;
// 						mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 						mytile.setTile(135);
// 						mytile.touchable = false;
// 						m_townTile.push_back(mytile);
// 						centerPos = glm::vec2(x, y);
					


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

// 					centerPos = glm::vec2(x, y);

// 				}
// 				if (tile == 'D')
// 				{
// 					BasicMonster kl;
// 					kl.init(glm::vec2(x, y), glm::vec2(2.0f), glm::vec2(1.0f), Feintgine::Color(255, 255, 255, 255));
// 					m_monsters.push_back(kl);

// 				}
// 				if (tile == 'R')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(135);
// 					mytile.setDepth(5);
// 					mytile.touchable = false;
// 					m_townTile.push_back(mytile);
// 				}

// 				if (tile == '.')
// 				{
					
// 						TownTile mytile;
// 						mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 						mytile.setTile(181);
// 						mytile.setDepth(0.0f);
// 						mytile.touchable = false;
// 						m_townTile.push_back(mytile);
					

// 				}
// 				if (tile == '1')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(120);
// 					mytile.setDepth(5);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == '2')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(136);
// 					mytile.setDepth(5);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == '3')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(104);
// 					mytile.setDepth(5);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == '4')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(137);
// 					mytile.setDepth(5);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == '5')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(105);
// 					mytile.setDepth(5);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == '6')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(121);
// 					mytile.setDepth(5);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'T')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_tree, Feintgine::Color(255, 255, 255, 255), glm::vec2(7, 4));
// 					mytile.setTile(3);
// 					mytile.setDepth(5);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);


// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(181);
// 					mytile.setDepth(0);
// 					mytile.touchable = false;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'M')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(3.0f, 5.0f), shops, Feintgine::Color(255, 255, 255, 255), glm::vec2(4, 1));
// 					mytile.setTile(3);
// 					mytile.setDepth(5);
// 					mytile.touchable = true;
// 					mytile.interactable = true;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'a')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), create, Feintgine::Color(255, 255, 255, 255), glm::vec2(3, 2));
// 					mytile.setTile(0);
// 					mytile.setDepth(5);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'b')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), create, Feintgine::Color(255, 255, 255, 255), glm::vec2(3, 2));
// 					mytile.setTile(1);
// 					mytile.setDepth(5);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'c')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), create, Feintgine::Color(255, 255, 255, 255), glm::vec2(3, 2));
// 					mytile.setTile(2);
// 					mytile.setDepth(5);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'd')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), create, Feintgine::Color(255, 255, 255, 255), glm::vec2(3, 2));
// 					mytile.setTile(3);
// 					mytile.setDepth(5);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'e')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), create, Feintgine::Color(255, 255, 255, 255), glm::vec2(3, 2));
// 					mytile.setTile(4);
// 					mytile.setDepth(5);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'f')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), create, Feintgine::Color(255, 255, 255, 255), glm::vec2(3, 2));
// 					mytile.setTile(5);
// 					mytile.setDepth(5);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'm')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y - 0.5f), glm::vec2(1.0f), simple, Feintgine::Color(255, 255, 255, 255), glm::vec2(9, 20));
// 					mytile.setTile(15);
// 					mytile.setDepth(5);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);


// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(181);
// 					mytile.setDepth(0);
// 					mytile.touchable = false;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'v')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y - 0.5f), glm::vec2(1.0f), simple, Feintgine::Color(255, 255, 255, 255), glm::vec2(9, 20));
// 					mytile.setTile(15);
// 					mytile.setDepth(5);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);


// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(181);
// 					mytile.setDepth(0);
// 					mytile.touchable = false;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 's')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), simple, Feintgine::Color(255, 255, 255, 255), glm::vec2(9, 20));
// 					mytile.setTile(20);
// 					mytile.setDepth(5);
// 					mytile.touchable = true;
// 					mytile.interactable = true;
// 					m_townTile.push_back(mytile);


// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(181);
// 					mytile.setDepth(0);
// 					mytile.touchable = false;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'k')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), simple, Feintgine::Color(255, 255, 255, 255), glm::vec2(9, 19));
// 					mytile.setTile(0);
// 					mytile.setDepth(5);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);


// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(181);
// 					mytile.setDepth(0);
// 					mytile.touchable = false;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'l')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), simple, Feintgine::Color(255, 255, 255, 255), glm::vec2(9, 19));
// 					mytile.setTile(36);
// 					mytile.setDepth(5);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);


// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(181);
// 					mytile.setDepth(0);
// 					mytile.touchable = false;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'V')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(3.0f, 5.0f), shops, Feintgine::Color(255, 255, 255, 255), glm::vec2(4, 1));
// 					mytile.setTile(2);
// 					mytile.setDepth(0);
// 					mytile.touchable = true;
// 					mytile.interactable = true;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'N')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(0.7f, 1.0f), NPC, Feintgine::Color(255, 255, 255, 255), glm::vec2(1, 1));
// 					mytile.setTile(0);
// 					mytile.setDepth(5);
// 					mytile.touchable = true;
// 					mytile.interactable = true;
// 					m_townTile.push_back(mytile);


// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(181);
// 					mytile.setDepth(0);
// 					mytile.touchable = false;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'r')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), simple, Feintgine::Color(255, 255, 255, 255), glm::vec2(9, 19));
// 					mytile.setTile(117);
// 					mytile.setDepth(5);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);


// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(181); 
// 					mytile.setDepth(0);
// 					mytile.touchable = false;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 't')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), simple, Feintgine::Color(255, 255, 255, 255), glm::vec2(9, 19));
// 					mytile.setTile(118);
// 					mytile.setDepth(5);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);


// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(181);
// 					mytile.setDepth(0);
// 					mytile.touchable = false;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'y')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), simple, Feintgine::Color(255, 255, 255, 255), glm::vec2(9, 19));
// 					mytile.setTile(119);
// 					mytile.setDepth(5);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);


// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(181);
// 					mytile.setDepth(0);
// 					mytile.touchable = false;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'x')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), simple, Feintgine::Color(255, 255, 255, 255), glm::vec2(9, 19));
// 					mytile.setTile(56);
// 					mytile.setDepth(5);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);


// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(181);
// 					mytile.setDepth(0);
// 					mytile.touchable = false;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'o')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), simple, Feintgine::Color(255, 255, 255, 255), glm::vec2(9, 19));
// 					mytile.setTile(45);
// 					mytile.setDepth(5);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);


// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(181);
// 					mytile.setDepth(0);
// 					mytile.touchable = false;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'W')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(2.0f), well, Feintgine::Color(255, 255, 255, 255), glm::vec2(2, 1));
// 					mytile.setTile(0);
// 					mytile.setDepth(5);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);


// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(181);
// 					mytile.setDepth(0);
// 					mytile.touchable = false;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'w')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(2.0f), well, Feintgine::Color(255, 255, 255, 255), glm::vec2(2, 1));
// 					mytile.setTile(1);
// 					mytile.setDepth(5);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);


// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(181);
// 					mytile.setDepth(0);
// 					mytile.touchable = false;
// 					m_townTile.push_back(mytile);
// 				}


// 			}
// 		}




// 	}
// }

// void SelectScreen::updateGUI()
// {
// 	if (error_msgbox != nullptr)
// 	{
// 		if (error_msgbox->onDestroy())
// 		{
// 			delete error_msgbox;
// 			free(error_msgbox);
// 			error_msgbox = nullptr;

// 		}
// 		else
// 		{
// 			error_msgbox->update();
// 		}

// 	}
// 	MainGUI::Instance()->updataGUI();
// }

// void SelectScreen::initGUI()
// {
// 	m_gui.init("GUI");
// 	m_gui.loadScheme("TaharezLook.scheme");
// 	m_gui.loadScheme("VanillaSkin.scheme");
// 	m_gui.loadScheme("WindowsLook.scheme");

// 	m_gui.setFont("DejaVuSans-12");


// 	m_gui.setMouseCursor("TaharezLook/MouseArrow");
// 	//m_gui.showMouseCursor();
// 	SDL_ShowCursor(0);
// }

// void SelectScreen::updateSocket()
// {
// 	std::string r_data = ClientSocket::Instance()->checkForIncomingMessages();
// 	if (r_data == "@SHUTDOWN")
// 	{
// 		createMessageBox("Bị mất kết nối với server" ,[&](const CEGUI::EventArgs & e) {

// 			changePrevScreen();

// 			return true;
// 		});
// 		//std::cout << "disconnect di 3 \n";
// 		ClientSocket::Instance()->disconnect();
// 	}
// 	else
// 	{
// 		if (r_data.size() > 0)
// 		{
// 			TCP_msg recv_msg;
// 			recv_msg.ParseFromString(r_data);
// 			switch (recv_msg.type())
// 			{
// 			case LOGLIST:
// 			{
// 				std::cout << " log list here \n";

// 				std::cout << " found " << recv_msg.m_log_list().list_size() << "\n";
// 				for (int i = 0; i < recv_msg.m_log_list().list_size(); i++)
// 				{
// 					//std::cout << recv_msg.m_log_list().list(i).SerializeAsString() << "\n";

// 					CharacterLog currentLog = recv_msg.m_log_list().list(i);

// 						if (!m_player.getInit())
// 						{
// 							std::cout << "identify player \n";
// 							std::cout << " name : " << currentLog.name() << " pos x " << currentLog.x_pos() << " pos y " << currentLog.y_pos() << "\n";

// 							//m_player.init(glm::vec2(currentLog.x_pos(), currentLog.y_pos()), glm::vec2(2.0f), glm::vec2(1.0f), Feintgine::Color(255, 255, 255, 255), m_game->getWindow(), &m_camera , currentLog.name());
							

// 						}
						
					
					
			
// 				}
// // 				if (m_player.getInit())
// // 				{
// // 					for (int i = 0; i < recv_msg.m_log_list().list_size(); i++)
// // 					{
// // 						CharacterLog currentLog = recv_msg.m_log_list().list(i);
// // 						if (currentLog.name() != Profile::Instance()->getName())
// // 						{
// // 							if (getOtherPlayerIndex(currentLog.name()) == -1)
// // 							{
// // 
// // 								std::cout << " attemp to parse camera \n";
// // 								std::cout << feint_common::Instance()->convertVec2toString(m_camera.getPosition()) << "\n";
// // 								OtherPlayer temp;
// // 								temp.init(glm::vec2(currentLog.x_pos(), currentLog.y_pos()), glm::vec2(2.0f), glm::vec2(1.0f), Feintgine::Color(255, 255, 255, 255), m_game->getWindow(), &m_camera, currentLog.name());
// // 								temp.loadGUI(m_gui);
// // 								m_others.push_back(temp);
// // 							}
// // 						}
// // 						
// // 					}
// // 				}
// 			}		
// 			break;
// // 
// // 			case PLAYERMSG: 
// // 			{
// // 				if (recv_msg.m_playermsg().name() == Profile::Instance()->getName())
// // 				{
// // 					m_player.say(recv_msg.m_playermsg().msg());
// // 				}
// // 				else if(getOtherPlayerIndex(recv_msg.m_playermsg().name()) != -1)
// // 				{
// // 					int target = getOtherPlayerIndex(recv_msg.m_playermsg().name());
// // 					m_others[target].say(recv_msg.m_playermsg().msg());
// // 					
// // 				}
// // 				MainGUI::Instance()->addTextToChatLog(recv_msg.m_playermsg().name() , recv_msg.m_playermsg().msg());
// // 
// // 			}
// // 			break;

// // 			case PLAYERSTATE : 
// // 			{
// // 				if (recv_msg.m_playerstate().name() == Profile::Instance()->getName())
// // 				{
// // 					switch (recv_msg.m_playerstate().action())
// // 					{
// // 					case MOVELEFT :
// // 					{
// // 						m_player.moveLeft();
// // 					}
// // 					break;
// // 					case MOVERIGHT:
// // 					{
// // 						m_player.moveRight();
// // 					}
// // 					break;
// // 					case MOVEUP:
// // 					{
// // 						m_player.moveUp();
// // 					}
// // 					break;
// // 					case MOVEDOWN:
// // 					{
// // 						m_player.moveDown();
// // 					}
// // 					break;
// // 					default:
// // 						break;
// // 					}
// // 				}
// // 				else if (getOtherPlayerIndex(recv_msg.m_playerstate().name()) != -1)
// // 				{
// // 					
// // 					std::cout << " other player " << recv_msg.m_playerstate().name() << " detected \n";
// // 					std::cout << " slot " << target << " detected \n";
// // 					switch (recv_msg.m_playerstate().action())
// // 					{
// // 					case MOVELEFT:
// // 					{
// // 						m_others[target].moveLeft();
// // 					}
// // 					break;
// // 					case MOVERIGHT:
// // 					{
// // 						m_others[target].moveRight();
// // 					}
// // 					break;
// // 					case MOVEUP:
// // 					{
// // 						m_others[target].moveUp();
// // 					}
// // 					break;
// // 					case MOVEDOWN:
// // 					{
// // 						m_others[target].moveDown();
// // 					}
// // 					default:
// // 						break;
// // 					}
// // 					
// // 				}
// //				
// //			}

// //			break;
// 			default:
	
// 				break;
// 			}
// 		}
// 		else
// 		{
// 			m_player.stahp();
// 			for (int i = 0; i < m_others.size(); i++)
// 			{
// 				m_others[i].stahp();
// 			}
// 		}
	
			
		
// 	}

// }

// void SelectScreen::createMessageBox(const std::string & message, std::function<bool(const CEGUI::EventArgs & e)> setOnClick /*= nullptr*/)
// {
// 	float width = (message.size() * 0.009f) + 0.02f;

// 	std::string tmp1 = "regis_fail_border";
// 	tmp1.append(std::to_string(attemp));
// 	std::string tmp2 = "regis_fail_text";
// 	tmp2.append(std::to_string(attemp));
// 	std::string tmp3 = "regis_fail_bg";
// 	tmp3.append(std::to_string(attemp));
// 	std::string tmp4 = "regis_fail_button";
// 	tmp4.append(std::to_string(attemp));
// 	error_msgbox = new CustomMessageBox(m_gui, tmp1, tmp2, tmp3, tmp4,
// 		message,
// 		glm::vec4((1.0f - width) / 2.0f, 0.32, width, 0.3f));

// 	if (setOnClick != nullptr)
// 	{
// 		error_msgbox->addEvent(setOnClick);
// 	}

// 	attemp++;
// }

// int SelectScreen::getOtherPlayerIndex(const std::string & target)
// {
// 	for (int i = 0; i < m_others.size(); i++)
// 	{
// 		if (m_others[i].getName() == target)
// 		{
// 			return i;
// 		}
// 	}

// 	std::cout << "not found other player name " << target <<"\n";
// 	return -1;
// }

// void SelectScreen::updateUDP()
// {
// 	if (!Enet_UDP::Instance()->getConnectionState())
// 	{
// 		Enet_UDP::Instance()->getConnectionResponse();
// 	}
// 	else
// 	{
// 		checkPosTimeStack++;
// 	//	Enet_UDP::Instance()->updateUDP();
// 		std::string data = Enet_UDP::Instance()->checkForIncomingMessages();

// 		if (data != "")
// 		{
// 			UDP_msg msg;
// 			msg.ParseFromString(data);
// 			switch (msg.type())
// 			{
// 			case UDP_PLAYERSTATE:
// 			{

// 				//std::cout << "detect something"
// 				if (msg.m_playerstate().name() == Profile::Instance()->getName())
// 				{
					
// // 					switch (msg.m_playerstate().action())
// // 					{
// // 					case MOVELEFT:
// // 					{
// // 						//m_player.moveLeft();
// // 					//	m_player.setPos(glm::vec2(msg.m_playerstate().x_pos(), msg.m_playerstate().y_pos()));
// // 					}
// // 					break;
// // 					case MOVERIGHT:
// // 					{
// // 						//m_player.moveRight();
// // 					//	m_player.setPos(glm::vec2(msg.m_playerstate().x_pos(), msg.m_playerstate().y_pos()));
// // 					}
// // 					break;
// // 					case MOVEUP:
// // 					{
// // 						m_player.moveUp();
// // 						//m_player.setPos(glm::vec2(msg.m_playerstate().x_pos(), msg.m_playerstate().y_pos()));
// // 					}
// // 					break;
// // 					case MOVEDOWN:
// // 					{
// // 						m_player.moveDown();
// // 						
// // 					}
// // 					break;
// 					if (checkPosTimeStack > 100)
// 					{
// 						m_player.setPos(glm::vec2(msg.m_playerstate().x_pos(), msg.m_playerstate().y_pos()));
// 						checkPosTimeStack = 0;
// 					}
						
// 						//checkPosTimeStack = 0;
					
				

// // 					default:
// // 						
// // 						break;
// // 					}
					
// 				}
// 				else if (getOtherPlayerIndex(msg.m_playerstate().name()) != -1)
// 				{

// 					int target = getOtherPlayerIndex(msg.m_playerstate().name());
					
// 					//std::cout << " other player " << msg.m_playerstate().name() << " detected \n";
// 					//std::cout << " slot " << target << " detected \n";
				
			
// 						m_others[target].setFacing(msg.m_playerstate().action());
// 						m_others[target].setPos(glm::vec2(msg.m_playerstate().x_pos(), msg.m_playerstate().y_pos()));
// 						//checkPosTimeStack = 0;
					
				
					

// 				}
			

// 			}
// 			break;
// 			default:
// 				break;
// 			}
// 		}




// 	}
	
// }
