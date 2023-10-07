#include "LuaObjectEditorComponent.h"



LuaObjectEditorComponent::LuaObjectEditorComponent()
{
	ENGINE_current_tick = 0;
}


LuaObjectEditorComponent::~LuaObjectEditorComponent()
{
}

void LuaObjectEditorComponent::loadGUI(Feintgine::GUI * gui)
{
	m_gui = gui;

	m_bulletCount = static_cast<CEGUI::DefaultWindow*> (m_gui->createWidget("TaharezLook/Label",
		glm::vec4(0.75, 0.8, 0.1, 0.1), glm::vec4(0), "m_bulletCount"));


	m_movesetList = static_cast<CEGUI::Listbox*> (m_gui->createWidget("TaharezLook/Listbox",
		glm::vec4(0.55, 0.08, 0.25, 0.6), glm::vec4(0), "movesetList"));

	m_toggleUpdate = static_cast<CEGUI::PushButton*>(m_gui->createWidget("TaharezLook/Button",
		glm::vec4(0.75, 0.7, 0.04, 0.04), glm::vec4(0), "m_toggleUpdate"));
	m_toggleUpdate->setText("  >  ");

	m_clearButton = static_cast<CEGUI::PushButton*>(m_gui->createWidget("TaharezLook/Button",
		glm::vec4(0.8, 0.7, 0.04, 0.04), glm::vec4(0), "m_clearButton"));
	m_clearButton->setText("Reset");



	m_clearBullets = static_cast<CEGUI::PushButton*>(m_gui->createWidget("TaharezLook/Button",
			glm::vec4(0.85, 0.7, 0.1, 0.04), glm::vec4(0), "m_clearBullets"));
	m_clearBullets->setText("Clear Bullets");

	m_toggleUpdate->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&LuaObjectEditorComponent::toggleUpdate, this));

	m_clearButton->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&LuaObjectEditorComponent::resetEvent, this));

	m_clearBullets->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&LuaObjectEditorComponent::clearBullets, this));

	m_movesetList->subscribeEvent(CEGUI::Listbox::EventMouseDoubleClick,
		CEGUI::Event::Subscriber(&LuaObjectEditorComponent::pickMoveset, this));

}

void LuaObjectEditorComponent::init(const glm::vec4 &drawScreen, Feintgine::Camera2D * cam, const Feintgine::Camera2D & staticCam)
{
	m_drawScreen = drawScreen;
	m_cam = cam;
	m_staticCam = staticCam;

	m_audioEngine.init();

	//m_luaObjectManager.loadLuaFile("Assets/LuaFiles/test.lua");
	//m_luaObjectManager.callLuaFunction("Assets/LuaFiles/test.lua","TestFunc");
	m_luaObjectManager.callCreateFromLua("Assets/LuaFiles/test.lua", "CreateFromLua");
	//m_luaObjectManager.
	//loadMoveset("Assets/LuaFiles/test.lua");
	//m_luaObjectManager.callLuaFunction("Assets/LuaFiles/test.lua", "CreateFromLua");
	//m_luaObjectManager.initDummy();

	bg.init(Feintgine::ResourceManager::getTexture("./Assets/Textures/__inubashiri_momiji_touhou_drawn_by_ryosios__a76f3b1a0e54bb60a93727e460fe5e60.png"), glm::vec2(0), glm::vec2(1366, 768),
		Feintgine::Color(255, 255, 255, 255));
	update(1);
	//loadMoveset("");

}

void LuaObjectEditorComponent::loadShader(const std::string & vertexPath, const std::string &fragmentPath)
{
	m_shader.compileShaders(vertexPath, fragmentPath);
	m_shader.addAttribute("vertexPosition");
	m_shader.addAttribute("vertexColor");
	m_shader.addAttribute("vertexUV");
	m_shader.linkShaders();

	m_lightBatch.initShader(&m_shader);
}

void LuaObjectEditorComponent::draw(Feintgine::SpriteBatch & spriteBatch, Feintgine::DebugRender & debug)
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

	m_luaObjectManager.draw(spriteBatch);
	//bg.draw(spriteBatch);

	spriteBatch.end();
	spriteBatch.renderBatch();

	m_shader.unuse();

	glm::mat4 Static_Edit_projectionMatrix = m_staticCam.getCameraMatrix();

	debug.drawBox(glm::vec4(-(m_drawScreen.z / 2.0f), -(m_drawScreen.w / 2.0f),
		m_drawScreen.z, m_drawScreen.w), Feintgine::Color(100, 250, 100, 255), 0);

	debug.end();
	debug.render(Static_Edit_projectionMatrix, 2.0f);
}

bool LuaObjectEditorComponent::toggleUpdate(const CEGUI::EventArgs &e)
{
	
	if (m_isUpdate)
	{
		
		m_isUpdate = false;
		m_toggleUpdate->setText("  >  ");
		//std::cout << "started \n";
	}
	else
	{
		m_isUpdate = true;	
		m_toggleUpdate->setText("  ||  ");
		//std::cout << "started \n";
	}


	return true;
}

bool LuaObjectEditorComponent::resetEvent(const CEGUI::EventArgs &e)
{


	m_movesetList->clearAllSelections();
	m_luaObjectManager.resetEvent();
	update(1.0f);
	if (m_isUpdate)
	{
		
		toggleUpdate(e);
	}
	
	return true;
}

bool LuaObjectEditorComponent::clearBullets(const CEGUI::EventArgs &e)
{
	m_luaObjectManager.clearBullets();

	return true;
}

void LuaObjectEditorComponent::handleInput(Feintgine::InputManager & inputManager)
{

}

void LuaObjectEditorComponent::showGUI(bool value)
{
	if (value)
	{
		
		m_bulletCount->show();
		m_toggleUpdate->show();
		m_movesetList->show();
		m_clearButton->show();
		m_clearBullets->show();
	}
	else
	{
		m_bulletCount->hide();
		m_toggleUpdate->hide();
		m_movesetList->hide();
		m_clearButton->hide();
		m_clearBullets->hide();
	}

	m_bulletCount->setVisible(value);
	m_toggleUpdate->setVisible(value);
	m_movesetList->setVisible(value);
	m_clearButton->setVisible(value);
	m_clearBullets->setVisible(value);

}

void LuaObjectEditorComponent::update(float deltaTime)
{
	if (m_isUpdate)
	{

		m_luaObjectManager.update(deltaTime);

		ENGINE_current_tick += (ENGINE_tick_speed * deltaTime);

		m_bulletCount->setText("bullet(s) : " + std::to_string(m_luaObjectManager.getTotalBullets()));
	}
}

void LuaObjectEditorComponent::loadMoveset(const std::string & path)
{
	std::fstream t_file;
	t_file.open(path.c_str(), std::ios::in);
	if (t_file.is_open())
	{
		std::string t_line;
		while (std::getline(t_file, t_line))
		{
			m_lines.push_back(t_line);
			//std::cout << t_line << "\n";
		}
		t_file.close();
	}


	for (int i = 0; i < m_lines.size(); i++)
	{
		if (m_lines[i].find("function moveset_") != std::string::npos)
		{
			const CEGUI::Image* sel_img = &CEGUI::ImageManager::getSingleton().get("TaharezLook/MultiListSelectionBrush");
			

				CEGUI::ListboxTextItem * item;
				// strip functions
				int tFound = m_lines[i].find("(");
				//std::cout << "found " << tFound << "\n";
				std::string stripStr = m_lines[i].substr(17, tFound - 17);
				//
				item = new CEGUI::ListboxTextItem(stripStr);
				item->setSelectionBrushImage(sel_img);
				m_movesetList->addItem(item);
			
		}
	}
}

bool LuaObjectEditorComponent::pickMoveset(const CEGUI::EventArgs &e)
{
	
	//m_luaObjectManager.callFunctionFromLua("resetFunction");
	if (m_movesetList->getSelectedCount() > 0)
	{
		std::string functionName = "moveset_";
		functionName += m_movesetList->getFirstSelectedItem()->getText().c_str(); 
		m_luaObjectManager.callFunctionFromLua(functionName);
	}

	return true;
}

