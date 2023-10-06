// #include "InGameScreen.h"
// #include <ResourceManager.h>
// #include <random>
// #include "Light.h"
// #include <iostream>
// #include <algorithm>



// InGameScreen::InGameScreen(Feintgine::Window * window)
// {
// 	m_screenIndex = SCREEN_INDEX_NULL;
// 	m_window = window;
// 	m_alpha = 0;
// 	initShader();

// 	//levelFile = file;
// }


// InGameScreen::~InGameScreen()
// {
// }

// int InGameScreen::getNextScreenIndex() const
// {
// 	return -1;
// }
// int InGameScreen::getPreviousScreenIndex() const
// {
// 	return SCREEN_INDEX_NULL;
// }

// void InGameScreen::build()
// {

// }
// void InGameScreen::destroy()
// {

// }
// void InGameScreen::loadLevel(const std::string & levelFile)
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
// // 					m_player.init(glm::vec2(x, y), glm::vec2(2.0f), glm::vec2(1.0f), Feintgine::Color(255, 255, 255, 255), m_game->getWindow(), m_camera, "yo");
// // 					if (m_gameState == GameState::TOWN)
// // 					{
// // 						TownTile mytile;
// // 						mytile.init(glm::vec2(x, y), glm::vec2(1.0f), tile_txt, Feintgine::Color(255, 255, 255, 255), glm::vec2(16, 12));
// // 						mytile.setTile(135);
// // 						mytile.touchable = false;
// // 						m_townTile.push_back(mytile);
// // 						centerPos = m_player.getPos();
// // 					}


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




// 				//if (tile == )


// 			}
// 		}
// 		height = m_levelData.size();
// 		width = m_levelData[0].size();
// 		if (m_gameState == GameState::PLAY)
// 		{


// 			for (int i = 0; i < m_levelData.size() - 1; i++)
// 			{
// 				for (int j = 0; j < m_levelData[i].size() - 1; j++)
// 				{

// 					Grid grid;
// 					grid.init(grids, glm::vec2(j, i), glm::vec2(1.0f), Feintgine::Color(255, 255, 255, 255));
// 					m_grids.push_back(grid);


// 				}
// 			}
// 		}


// 	}

// }
// void InGameScreen::onEntry()
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



// 	loadLevel("Levels/hakurei.txt");
// 	//init camera
// 	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
// 	m_camera.setScale(35.0f);
// 	m_camera.setPosition(glm::vec2(32,16));

// 	m_camera.update();

// 	m_guicamera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
// 	m_guicamera.setScale(35.0f);
// 	//m_guicamera.setPosition(centerPos);
// 	//init GUI;



// }
// void InGameScreen::onExit()
// {
// 	m_debugRender.dispose();
// }



// void InGameScreen::update()
// {
// 	m_camera.update();
// 	m_guicamera.update();

// 	startScreen();

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

// 			//m_player.handleInput(m_game->getInputManager());

// 			//grid rule
// 		//	m_player.update(m_grids, m_tiles, m_townTile);

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






// }
// void InGameScreen::draw()
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
// 	for (auto & m : m_monsters)
// 	{
// 		m.draw(m_spriteBatch);
// 	}
// 	for (auto & t : m_townTile)
// 	{
// 		t.draw(m_spriteBatch);
// 	}
// //	m_player.draw(m_spriteBatch);




// 	m_spriteBatch.end();
// 	m_spriteBatch.renderBatch();
// 	m_textureProgram.unuse();


// 	SDL_GL_SetSwapInterval(1);

// 	m_gui.draw();

// }
// void InGameScreen::handleInput(Feintgine::InputManager &inputManager)
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

// void InGameScreen::initGUI()
// {
// 	m_gui.init("GUI");
// 	m_gui.loadScheme("TaharezLook.scheme");
// 	m_gui.setFont("DejaVuSans-10");
// 	//CEGUI::PushButton* testButton = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button", glm::vec4(0.8f, 0.2f, 0.1f, 0.05f), glm::vec4(0.0f), "TestButton"));
// 	//testButton->setText("Hello World!");

// 	//testButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&InGameScreen::clickExit, this));

// 	//CEGUI::Editbox* TestCombobox = static_cast<CEGUI::Editbox*>(m_gui.createWidget("TaharezLook/Editbox", glm::vec4(0.2f, 0.2f, 0.5f, 0.05f), glm::vec4(0.0f), "TestCombobox"));

// 	m_gui.setMouseCursor("TaharezLook/MouseArrow");
// 	m_gui.showMouseCursor();
// 	SDL_ShowCursor(0);
// }
// void InGameScreen::setPause()
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

// bool InGameScreen::clickExit(const CEGUI::EventArgs & e)
// {
// 	m_currentState = Feintgine::ScreenState::EXIT_APPLICATION;
// 	return true;
// }
// void InGameScreen::setDebug()
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


// void InGameScreen::checkInput()
// {
// 	SDL_Event evnt;
// 	while (SDL_PollEvent(&evnt))
// 	{
// 		m_game->onSDLEvent(evnt);
// 		m_gui.onSDLEvent(evnt);
// 	}


// }

// void InGameScreen::setType(GameState gameState)
// {
// 	m_gameState = gameState;
// }

// void InGameScreen::initShader()
// {
// 	m_objectShader.compileShaders("Shaders/backup.vert", "Shaders/backup.frag");
// 	m_objectShader.addAttribute("vertexPosition");
// 	m_objectShader.addAttribute("vertexColor");
// 	m_objectShader.addAttribute("vertexUV");
// 	m_objectShader.addAttribute("spec");
// 	m_objectShader.linkShaders();

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
// }
