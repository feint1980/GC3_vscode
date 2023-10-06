// #include "GameTownScreen.h"
// #include <ResourceManager.h>
// #include <random>
// #include "Light.h"
// #include <iostream>
// #include <algorithm>



// GameTownScreen::GameTownScreen(Feintgine::Window * window, const std::string & file)
// {
// 	m_screenIndex = SCREEN_INDEX_TOWN;
// 	m_window = window;
// 	m_alpha = 0;
	
// 	levelFile = file;

// 	m_textureProgram.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
// 	m_textureProgram.addAttribute("vertexPosition");
// 	m_textureProgram.addAttribute("vertexColor");
// 	m_textureProgram.addAttribute("vertexUV");
// 	m_textureProgram.linkShaders();
// }


// GameTownScreen::~GameTownScreen()
// {
// }

// int GameTownScreen::getNextScreenIndex() const
// {
// 	return SCREEN_INDEX_GAMEPLAY;
// }
// int GameTownScreen::getPreviousScreenIndex() const
// {
// 	return SCREEN_INDEX_NULL;
// }

// void GameTownScreen::build()
// {

// }
// void GameTownScreen::destroy()
// {

// }
// void GameTownScreen::loadLevel(const std::string & levelFile)
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
// 					//m_player.init(glm::vec2(x, y), glm::vec2(2.0f), glm::vec2(1.0f), Feintgine::Color(255, 255, 255, 255), m_game->getWindow() , m_gui ,m_guicamera);
// 					if (m_gameState == GameState::TOWN)
// 					{
// 						TownTile mytile;
// 						mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 						mytile.setTile(135);
// 						mytile.touchable = false;
// 						m_townTile.push_back(mytile);
// 						centerPos = m_player.getPos();
// 					}


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
// 					mytile.touchable = false;
// 					m_townTile.push_back(mytile);
// 				}

// 				if (tile == '.')
// 				{
// 					if (m_gameState == GameState::TOWN)
// 					{
// 						TownTile mytile;
// 						mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 						mytile.setTile(181);
// 						mytile.touchable = false;
// 						m_townTile.push_back(mytile);
// 					}

// 				}
// 				if (tile == '1')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(120);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == '2')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(136);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == '3')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(104);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == '4')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(137);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == '5')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(105);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == '6')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(121);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'T')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_tree, Feintgine::Color(255, 255, 255, 255), glm::vec2(7, 4));
// 					mytile.setTile(3);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);


// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(181);
// 					mytile.touchable = false;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'M')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(3.0f, 5.0f), shops, Feintgine::Color(255, 255, 255, 255), glm::vec2(4, 1));
// 					mytile.setTile(3);
// 					mytile.touchable = true;
// 					mytile.interactable = true;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'a')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), create, Feintgine::Color(255, 255, 255, 255), glm::vec2(3, 2));
// 					mytile.setTile(0);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'b')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), create, Feintgine::Color(255, 255, 255, 255), glm::vec2(3, 2));
// 					mytile.setTile(1);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'c')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), create, Feintgine::Color(255, 255, 255, 255), glm::vec2(3, 2));
// 					mytile.setTile(2);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'd')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), create, Feintgine::Color(255, 255, 255, 255), glm::vec2(3, 2));
// 					mytile.setTile(3);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'e')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), create, Feintgine::Color(255, 255, 255, 255), glm::vec2(3, 2));
// 					mytile.setTile(4);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'f')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), create, Feintgine::Color(255, 255, 255, 255), glm::vec2(3, 2));
// 					mytile.setTile(5);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'm')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y - 0.5f), glm::vec2(1.0f), simple, Feintgine::Color(255, 255, 255, 255), glm::vec2(9, 20));
// 					mytile.setTile(15);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);


// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(181);
// 					mytile.touchable = false;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'v')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y - 0.5f), glm::vec2(1.0f), simple, Feintgine::Color(255, 255, 255, 255), glm::vec2(9, 20));
// 					mytile.setTile(15);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);


// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(181);
// 					mytile.touchable = false;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 's')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), simple, Feintgine::Color(255, 255, 255, 255), glm::vec2(9, 20));
// 					mytile.setTile(20);
// 					mytile.touchable = true;
// 					mytile.interactable = true;
// 					m_townTile.push_back(mytile);


// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(181);
// 					mytile.touchable = false;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'k')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), simple, Feintgine::Color(255, 255, 255, 255), glm::vec2(9, 19));
// 					mytile.setTile(0);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);


// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(181);
// 					mytile.touchable = false;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'l')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), simple, Feintgine::Color(255, 255, 255, 255), glm::vec2(9, 19));
// 					mytile.setTile(36);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);


// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(181);
// 					mytile.touchable = false;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'V')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(3.0f, 5.0f), shops, Feintgine::Color(255, 255, 255, 255), glm::vec2(4, 1));
// 					mytile.setTile(2);
// 					mytile.touchable = true;
// 					mytile.interactable = true;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'N')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(0.7f, 1.0f), NPC, Feintgine::Color(255, 255, 255, 255), glm::vec2(1, 1));
// 					mytile.setTile(0);
// 					mytile.touchable = true;
// 					mytile.interactable = true;
// 					m_townTile.push_back(mytile);


// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(181);
// 					mytile.touchable = false;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'r')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), simple, Feintgine::Color(255, 255, 255, 255), glm::vec2(9, 19));
// 					mytile.setTile(117);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);


// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(181);
// 					mytile.touchable = false;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 't')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), simple, Feintgine::Color(255, 255, 255, 255), glm::vec2(9, 19));
// 					mytile.setTile(118);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);


// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(181);
// 					mytile.touchable = false;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'y')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), simple, Feintgine::Color(255, 255, 255, 255), glm::vec2(9, 19));
// 					mytile.setTile(119);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);


// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(181);
// 					mytile.touchable = false;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'x')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), simple, Feintgine::Color(255, 255, 255, 255), glm::vec2(9, 19));
// 					mytile.setTile(56);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);


// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(181);
// 					mytile.touchable = false;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'o')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), simple, Feintgine::Color(255, 255, 255, 255), glm::vec2(9, 19));
// 					mytile.setTile(45);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);


// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(181);
// 					mytile.touchable = false;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'W')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(2.0f), well, Feintgine::Color(255, 255, 255, 255), glm::vec2(2, 1));
// 					mytile.setTile(0);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);


// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(181);
// 					mytile.touchable = false;
// 					m_townTile.push_back(mytile);
// 				}
// 				if (tile == 'w')
// 				{
// 					TownTile mytile;
// 					mytile.init(glm::vec2(x, y), glm::vec2(2.0f), well, Feintgine::Color(255, 255, 255, 255), glm::vec2(2, 1));
// 					mytile.setTile(1);
// 					mytile.touchable = true;
// 					m_townTile.push_back(mytile);


// 					mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// 					mytile.setTile(181);
// 					mytile.touchable = false;
// 					m_townTile.push_back(mytile);
// 				}


// 			}
// 		}
// 		height = m_levelData.size();
// 		width = m_levelData[0].size();



// 	}

// }
// void GameTownScreen::onEntry()
// {
// 	srand(time(NULL));
// 	//
// 	m_debugRender.init();

	

	
	
// 	// Create world 
// 	//	
// 	//Create boxes
// 	//m_gameState = GameState::PLAY;
// 	initGUI();
// 	//m_player.init(glm::vec2(1, 1), glm::vec2(2.0f), glm::vec2(1.0f), Feintgine::Color(255, 255, 255, 255));
	
// 	//	loadLevel("Levels/level1.txt");

	


// 	// init draw materials
// 	m_spriteBatch.init();
// 	m_guiSriteBatch.init();
// 	// Shaders 



// 	//load texture

// 	//compiling light shader


// 	loadLevel(levelFile);
// 	//init camera
// 	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
// 	m_camera.setScale(10.0f);
// 	m_camera.setPosition(m_player.getPos());


// 	m_guicamera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
// 	m_guicamera.setScale(35.0f);
// 	//m_guicamera.setPosition(centerPos);
// 	//init GUI;
	
	

// }
// void GameTownScreen::onExit()
// {
// 	m_debugRender.dispose();
// }



// void GameTownScreen::update(float deltaTime)
// {
// 	m_camera.update();
// 	m_guicamera.update();


	
	
	

// 	startScreen();
// //	m_alpha = 1.0f;
// 	if (startup)
// 	{
	


// 		checkInput();
// 		handleInput(m_game->getInputManager());
// 		if (!m_isPaused)
// 		{

// 			if (m_gameState == GameState::TOWN)
// 			{
// 				m_camera.setPosition(m_player.getPos());
// 			}


// 			//Update physics simulation 

// 			m_player.handleInput(m_game->getInputManager());

// 			//grid rule
// 			m_player.update(m_grids, m_tiles, m_townTile);

			
// 			for (int i = 0; i < m_monsters.size(); i++)
// 			{
// 				m_monsters[i].update(m_grids, m_tiles, m_outsideGrids, m_player);
// 				if (!m_monsters[i].getLife())
// 				{
// 					m_monsters.erase(m_monsters.begin() + i);
// 				}
// 			}

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
// 					m_tiles.erase(m_tiles.begin() + i);
// 				}

// 			}

// 		}
// 	}

// 	updateGui();


// 		updateSocket();
	


// }
// void GameTownScreen::draw()
// {

// 	//std::cout << "draw \n";
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
// 	for (auto & m : m_monsters)
// 	{
// 		m.draw(m_spriteBatch);
// 	}
// 	for (auto & t : m_townTile)
// 	{
// 		t.draw(m_spriteBatch);
// 	}
// 	m_player.draw(m_spriteBatch);




// 	m_spriteBatch.end();
// 	m_spriteBatch.renderBatch();

// 	glm::mat4 cameraMatrix = m_guicamera.getCameraMatrix();
// 	GLint pLocation = m_textureProgram.getUniformLocation("P");
// 	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

// 	m_guiSriteBatch.begin();
// 	m_player.drawGUI(m_guiSriteBatch);
// 	m_guiSriteBatch.end();
// 	m_guiSriteBatch.renderBatch();

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
// 		for (auto & m : m_monsters)
// 		{
// 			m.drawDebug(m_debugRender);
// 		}

// 		for (auto & t : m_tiles)
// 		{
// 			t.drawDebug(m_debugRender);
// 		}
// 		m_debugRender.end();
// 		m_debugRender.render(projectionMatrix, 2.0f);
// 	}



	
// 	// Reset to regular alpha blending
// 	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

// 	SDL_GL_SetSwapInterval(1);

// 	m_gui.draw();

// }
// void GameTownScreen::handleInput(Feintgine::InputManager &inputManager)
// {
// 	if (inputManager.isKeyPressed(SDLK_F9))
// 	{
// 		setDebug();
// 	}
// 	if (inputManager.isKeyPressed(SDLK_F1))
// 	{
	
// 		setPause();
// 	}
// 	if (inputManager.isKeyPressed(SDLK_F2))
// 	{
// 		changeNextScreen();
// 	}

// }

// void GameTownScreen::initGUI()
// {
// 	m_gui.init("GUI");
// 	m_gui.loadScheme("TaharezLook.scheme");
// 	m_gui.setFont("DejaVuSans-10");
// 	//CEGUI::PushButton* testButton = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button", glm::vec4(0.8f, 0.2f, 0.1f, 0.05f), glm::vec4(0.0f), "TestButton"));
// 	//testButton->setText("Hello World!");

// 	//testButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GameTownScreen::clickExit, this));

// 	//CEGUI::Editbox* TestCombobox = static_cast<CEGUI::Editbox*>(m_gui.createWidget("TaharezLook/Editbox", glm::vec4(0.2f, 0.2f, 0.5f, 0.05f), glm::vec4(0.0f), "TestCombobox"));

// 	m_gui.setMouseCursor("TaharezLook/MouseArrow");
// 	m_gui.showMouseCursor();
// 	SDL_ShowCursor(0);
// }
// void GameTownScreen::setPause()
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

// bool GameTownScreen::clickExit(const CEGUI::EventArgs & e)
// {
// 	m_currentState = Feintgine::ScreenState::EXIT_APPLICATION;
// 	return true;
// }
// void GameTownScreen::setDebug()
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


// void GameTownScreen::checkInput()
// {
// 	SDL_Event evnt;
// 	while (SDL_PollEvent(&evnt))
// 	{
// 		m_game->onSDLEvent(evnt);
// 		m_gui.onSDLEvent(evnt);
// 	}


// }

// void GameTownScreen::setType(GameState gameState)
// {
// 	m_gameState = gameState;
// }

// void GameTownScreen::updateSocket()
// {

// 	std::cout << " update socket \n";
// 	std::string r_data = ClientSocket::Instance()->checkForIncomingMessages();

// 	if (r_data == "@SHUTDOWN")
// 	{
// 		createMessageBox("Bị mất kết nối với server", [&](const CEGUI::EventArgs &e) {
		
// 			changePrevScreen();
// 			return true;
// 		});
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
// 				for (int i = 0; i < recv_msg.m_log_list().list_size(); i++)
// 				{
// 					std::cout << recv_msg.m_log_list().list(i).SerializeAsString() << "\n";

// 				}
// 			}
// 			break;

// 			default:
// 				break;
// 			}
// 		}
// 	}
// }

// void GameTownScreen::createMessageBox(const std::string & message, std::function<bool(const CEGUI::EventArgs & e)> setOnClick /*= nullptr*/)
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

// void GameTownScreen::updateGui()
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
// }
