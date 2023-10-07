#include "NewRenderModel.h"
#include <ft2build.h>

#pragma execution_character_set( "utf-8" )
NewRenderModel::NewRenderModel()
{
}

NewRenderModel::NewRenderModel(Feintgine::Window * window)
{
	m_window = window;
	m_screenIndex = 9;
}

NewRenderModel::~NewRenderModel()
{
}

void NewRenderModel::build()
{
	
}

void NewRenderModel::checkInput()
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

void NewRenderModel::destroy()
{
	
}

void NewRenderModel::draw()
{
	
	glViewport(0, 0, 1600, 900);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	
	
	m_shader.use();

	GLint textureUniform = m_shader.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	glActiveTexture(GL_TEXTURE0);

	// Camera matrix

	GLint pUniform = m_shader.getUniformLocation("P");
	glm::mat4 objectsMatrix = m_camera.getCameraMatrix();
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &objectsMatrix[0][0]);

	m_spriteBatch.begin();
	//m_currentTexture.draw(m_spriteBatch);
	//testObject.draw(m_spriteBatch);
	bg.draw(m_spriteBatch);
	m_spriteBatch.end();
	m_spriteBatch.renderBatch();

	m_shader.unuse();
		
	glDisable(GL_SCISSOR_TEST);
	m_textRenderer.renderText(m_camera, L"some text/ vài dòng chữ/めらみぽっぷ", m_camera.convertScreenToWorld(m_game->getInputManager().getMouseCoords()), Feintgine::Color(255, 255, 255, 255), 1, ALIGN_FT_CENTER);


}

int NewRenderModel::getNextScreenIndex() const
{
	return -1;
}

int NewRenderModel::getPreviousScreenIndex() const
{
	return -1;
}

void NewRenderModel::onEntry()
{
	
	m_spriteBatch.init();

	m_textRenderer.init(64,300, "font/ARIALUNI-V2.otf");

	m_camera.init(m_window->getScreenWidth() , m_window->getScreenHeight(),7);
	m_camera.setScale(1);
	m_camera.setPosition(glm::vec2(0));
	m_camera.update();
	bg.init(Feintgine::ResourceManager::getTexture("./Textures/ringed_city.png"), glm::vec2(0), glm::vec2(1600, 900), Feintgine::Color(255, 255, 255, 255));
	//std::cout << "testing service " << feint_common::Instance()->getFileNameFromPath("E:/template/my_last/GC3/Editor/Assets") << "\n";
	//Feintgine::SpriteManager::Instance()->loadFromDirectory("E:/template/my_last/GC3/Editor/Assets",0);


	//Feintgine::SpriteManager::Instance()->printPacketList();
	//testObject.init(Feintgine::SpriteManager::Instance()->getSprite("green.xml/system_02.png"), glm::vec2(0), glm::vec2(1), Feintgine::Color(255, 255, 255, 255));


	std::cout << "check property of F_EmptyObject\n";

//	Feintgine::SpriteManager::Instance()->getSpritePacketByName("Golden.xml").writeToImageset("Golden.imageset");
	


	

	//std::cout << "UV -> " << glm::to_string(testObject.getSprite().getUV()) << "\n";
	initGUI();
	initShader();
	
	//calculate round shape for 16x9 9/16 = 0.5625
	float m_spine = 0.4;
	//m_spriteDisplayer.init(&m_gui, glm::vec2(0.01), glm::vec2(m_spine*0.5625,m_spine),4,4);

	//m_spriteDisplayer.loadTotalList();


	
	Feintgine::SpriteManager::Instance()->printPacketList();


	
}

void NewRenderModel::onExit()
{
	m_shader.dispose();
	m_gui.destroy();
}

void NewRenderModel::update(float deltaTime)
{
	m_camera.update();
	
	m_gui.update();
}

void NewRenderModel::initGUI()
{
	m_gui.init("GUI");

	
	
	m_gui.loadScheme("TaharezLook.scheme");
	m_gui.loadScheme("AlfiskoSkin.scheme");
	m_gui.loadScheme("OgreTray.scheme");
	m_gui.loadScheme("Golden.scheme");
	m_gui.setFont("DejaVuSans-12");

	//m_gui.setMouseCursor("AlfiskoSkin/MouseArrow");

	initSpriteList();


	m_button  = static_cast<CEGUI::PushButton*>(m_gui.createWidget("Golden/Button", glm::vec4(0.4, 0.8, 0.175, 0.05), glm::vec4(0), "OK_Addlayer_button"));
	m_checkbox = static_cast<CEGUI::ToggleButton*>(m_gui.createWidget("Golden/RadioButton", glm::vec4(0.3, 0.8, 0.025, 0.025), glm::vec4(0), "m_checkbox"));
	m_fwnd = static_cast<CEGUI::FrameWindow*>(m_gui.createWidget("Golden/FrameWindow", glm::vec4(0.1, 0.1, 0.25, 0.4), glm::vec4(0), "asee"));
	m_button->setText("Create");
	m_fwnd->getTitlebar()->setText("This is a title");
	//m_gui.showMouseCursor();
	//SDL_ShowCursor(1);
}

void NewRenderModel::initShader()
{
	m_shader.compileShaders("Shaders/editor.vert", "Shaders/editor.frag");
	m_shader.addAttribute("vertexPosition");
	m_shader.addAttribute("vertexColor");
	m_shader.addAttribute("vertexUV");
	m_shader.linkShaders();
	m_alpha = 1;
}

void NewRenderModel::handleInput(Feintgine::InputManager & inputManager)
{
	if (inputManager.isKeyPressed(SDLK_ESCAPE))
	{
		m_currentState = Feintgine::ScreenState::EXIT_APPLICATION;
	}
}

void NewRenderModel::initSpriteList()
{
	
	//std::wstring itemname = "Blabla";

// 	CEGUI::Window *myImageWindow = static_cast<CEGUI::Window*>(m_gui.createWidget("TaharezLook/StaticImage", glm::vec4(0.5, 0.5, 0.4, .4f), glm::vec4(0.0f), "PrettyWindow"));
// 
// 	m_listBox->addChild(myImageWindow);
	//m_listBox->addItem(item);
}
