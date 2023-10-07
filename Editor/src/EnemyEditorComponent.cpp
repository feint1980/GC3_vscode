// #include "../../GC3/src/F_EnemyBasic.cpp"
// #include "../../GC3/src/FairyBase.cpp"
// #include "../../GC3/src/F_Player.cpp"
// #include "../../GC3/src/GlobalValueClass.cpp"
// #include "../../GC3/src/F_MarisaRocket_small.cpp"
// #include "../../GC3/src/F_BaseEnemy.cpp"

#include "F_EnemyBasic.cpp"

#include "EnemyEditorComponent.h"



EnemyEditorComponent::EnemyEditorComponent()
{
}


EnemyEditorComponent::~EnemyEditorComponent()
{
}


void EnemyEditorComponent::loadGUI(Feintgine::GUI * gui)
{
	m_gui = gui;

	m_enemyList = static_cast<CEGUI::Listbox*> (m_gui->createWidget("TaharezLook/Listbox",
		glm::vec4(0.55, 0.08, 0.25, 0.6), glm::vec4(0), "m_enemyList"));

	m_enemyList->subscribeEvent(CEGUI::Listbox::EventMouseDoubleClick,
		CEGUI::Event::Subscriber(&EnemyEditorComponent::pickEnemy, this));

}

void EnemyEditorComponent::init(const glm::vec4 &drawScreen, Feintgine::Camera2D * cam, const
	Feintgine::Camera2D & staticCam)
{
	m_drawScreen = drawScreen;
	m_cam = cam;
	m_staticCam = staticCam;

	bg.init(Feintgine::ResourceManager::getTexture("./Assets/Textures/__inubashiri_momiji_touhou_drawn_by_ryosios__a76f3b1a0e54bb60a93727e460fe5e60.png"), glm::vec2(0), glm::vec2(1366, 768),
		Feintgine::Color(255, 255, 255, 255));

	m_audioEngine.init();
	m_player.init("Assets/F_AObjects/reimu.xml","character/reimu_accessory_3.png");
	m_player.setInvinsible(true);


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GlobalValueClass::Instance()->savePlayer(&m_player);
	
}


void EnemyEditorComponent::loadShader(const std::string & vertexPath, const std::string &fragmentPath)
{
	m_shader.compileShaders(vertexPath, fragmentPath);
	m_shader.addAttribute("vertexPosition");
	m_shader.addAttribute("vertexColor");
	m_shader.addAttribute("vertexUV");
	m_shader.linkShaders();

	m_lightBatch.initShader(&m_shader);
}

void EnemyEditorComponent::draw(Feintgine::SpriteBatch & spriteBatch, 
	Feintgine::DebugRender & debug)
{
	glViewport(m_drawScreen.x, m_drawScreen.y, m_drawScreen.z, m_drawScreen.w);

	m_shader.use();

	GLint textureUniform = m_shader.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	glActiveTexture(GL_TEXTURE0);

	// Camera matrix
	glm::mat4 projectionMatrix = m_cam->getCameraMatrix();
	GLint pUniform = m_shader.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	GLint dayLightIndex = m_shader.getUniformLocation("dayLight");
	glUniform3f(dayLightIndex, 1.0f, 1.0f, 1.0f);

	m_lightBatch.begin();
	m_lightBatch.renderLight();

	spriteBatch.begin(Feintgine::GlyphSortType::FRONT_TO_BACK);


	for (int i = 0; i < m_enemyObjectList.size(); i++)
	{
		//std::cout << "drawing " << m_enemyObjectList.size() << "items \n";
		m_enemyObjectList[i]->draw(spriteBatch);
		m_enemyObjectList[i]->drawBullet(spriteBatch);
	}
	//m_player.draw(spriteBatch);
	//bg.draw(spriteBatch);
	spriteBatch.end();
	spriteBatch.renderBatch();

	m_shader.unuse();



	glm::mat4 Static_Edit_projectionMatrix = m_staticCam.getCameraMatrix();

	debug.drawBox(glm::vec4(-(m_drawScreen.z / 2.0f), -(m_drawScreen.w / 2.0f),
		m_drawScreen.z, m_drawScreen.w), Feintgine::Color(250, 250, 40, 255), 0);

	debug.end();
	debug.render(Static_Edit_projectionMatrix, 2.0f);
}

void EnemyEditorComponent::handleInput(Feintgine::InputManager & inputManager)
{
	if (inputManager.isKeyPressed(SDLK_F5))
	{
		loadEnemy(savedLocation);
	}
}

bool EnemyEditorComponent::pickEnemy(const CEGUI::EventArgs &e)
{
	std::cout << "called \n";
	if (m_enemyList->getSelectedCount() > 0)
	{
		//std::cout << "test \n";
		int selection = getEnemyNodeIndexByName(m_enemyList->getFirstSelectedItem()->getText().c_str());
		if (selection != -1)
		{
			std::cout << "valid data \n";
		}
		else
		{
			//std::cout << "invalid selected item \n";
		}
	}

	return true;
}

void EnemyEditorComponent::showGUI(bool value)
{

	if (value)
	{
		m_enemyList->show();
	}
	else
	{
		m_enemyList->hide();
	}

	m_enemyList->setVisible(value);
	
}

void EnemyEditorComponent::loadEnemy(const std::string & path)
{
	//enemyList.clear();
	savedLocation = path;
	m_enemyList->resetList();
	xml_document<> doc;

	std::ifstream  file(savedLocation);
	std::vector<char>buffer = std::vector<char>((std::istreambuf_iterator<char>(file)), \
		std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	//std::vector<char> buffer = Feintgine::ResourceManager::getPreloadedFile(savedLocation.c_str());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);

	xml_node<> * enemy_states_node;

	enemy_states_node = doc.first_node("EnemyStates");

	if (!enemy_states_node)
	{
		std::cout << "error parsing xml file, EnemyStates " << path.c_str() << "\n";
		return;
	}
	const CEGUI::Image* sel_img = &CEGUI::ImageManager::getSingleton().get("TaharezLook/MultiListSelectionBrush");
	for (xml_node<> * comboState_node = enemy_states_node->first_node("ComboState");
		comboState_node; comboState_node = comboState_node->next_sibling())
	{
		
		CEGUI::ListboxTextItem * item;
		item = new CEGUI::ListboxTextItem(comboState_node->first_attribute("name")->value());
		item->setSelectionBrushImage(sel_img);
		m_enemyList->addItem(item);
		//enemyDataList.push_back(comboState_node->value());
	}

}

int EnemyEditorComponent::getEnemyNodeIndexByName(const std::string & name)
{
	FairyBase * enemy = new FairyBase();
	enemy->init(glm::vec2(0,400), glm::vec2(24, 32), "./Assets/F_AObjects/fairy_enemy_normal_black.xml",10);
	//enemy->playAnim("idle");
	enemy->registerAudio(&m_audioEngine);
	//enemy->init(glm::vec2(0), glm::vec2(240, 320), Feintgine::ResourceManager::getTexture("./Assets/Textures/__inubashiri_momiji_touhou_drawn_by_ryosios__a76f3b1a0e54bb60a93727e460fe5e60.png"));
	enemy->loadState(name,false);
	m_enemyObjectList.push_back(enemy);
	return -1;
}

void EnemyEditorComponent::update(float deltaTime)	
{

	for (auto it = m_enemyObjectList.begin(); it != m_enemyObjectList.end(); )
	{
		(*it)->update(deltaTime);
		(*it)->updateBullet(deltaTime);
		//std::cout << "enemy size " << m_enemyObjectList.size() << "\n";
		if (!(*it)->isAlive())
		{
			delete * it;
			it = m_enemyObjectList.erase(it);
		}
		else
		{
			++it;
		}
	}

	//m_player.getAnimation().update(deltaTime);
	//m_player.
	//m_player.update(deltaTime, m_baseenemiesObjectList, m_enemiesbulletObjectList, m_enemyguardianObjectList, m_enemyamplifierObjectList);

	ENGINE_current_tick += (ENGINE_tick_speed * deltaTime);
	Feintgine::F_oEvent::getInstance()->timer();
}
