// #include "MainMenuScreen.h"
// #include <iostream>
// #include <ScreenList.h>
// #include <random>

// #pragma execution_character_set("utf-8")

// #include "Light.h"




// MainMenuScreen::MainMenuScreen(Feintgine::Window* window)
// {
	
// 	m_screenIndex = SCREEN_INDEX_MAINMENU;
// 	m_window = window;
// 	m_alpha = 0;
// 	current_slide_pos = MARK;
	
	
// 	if (SDLNet_Init() == -1)
// 	{
// 		std::cerr << "Failed to intialise SDL_net: " << SDLNet_GetError() << std::endl;

// 	}
// 	else
// 	{
// 		std::cout << "init SDL_net OK\n";
// 	}


// 	//ClientSocket::Instance()->init("127.0.0.1", 11111, 512);
// //	m_inputManager = m_game->getInputManager();
	
	
// }
// MainMenuScreen::~MainMenuScreen()
// {


// }

// int MainMenuScreen::getNextScreenIndex() const
// {
// 	return SCREEN_INDEX_SELECT;
// }

// int MainMenuScreen::getPreviousScreenIndex() const
// {
	
// 	return SCREEN_INDEX_NULL;
// }

// void MainMenuScreen::build()
// {
	
// }

// void MainMenuScreen::destroy()
// {
// 	m_debugRenderer.dispose();
// 	m_particles.clear();
// 	m_gui.destroy();
// }

// void MainMenuScreen::onEntry()
// {

// 	initShader();
// 	isConnected = false;


// 	hasClickLog = false;
	
	
// 	initWorld();
// 	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
// 	if (first)
// 	{
// 		m_camera.setScale(15.0f);
// 	}
// 	else
// 	{
		
// 		m_camera.setScale(7.0f);
// 		m_fixer = 0.9998f;
// 	}



// 	m_camera.setAngle(cam_angle);
// 	m_spriteBatch.init();
// 	m_hudSpriteBatch.init();
// 	m_debugRenderer.init();
// 	bg.init(Feintgine::ResourceManager::getTexture("Textures/log.png"), 
// 		glm::vec2(0,0), glm::vec2(160.0f, 90.0f), Feintgine::Color(255, 255, 255, 255));
	

// 	//m_player.init(bg.getPos(), glm::vec2(2.0f), glm::vec2(1.0f), Feintgine::Color(255, 255, 255, 255), m_game->getWindow(), m_camera);

// 	particle_Texture = Feintgine::ResourceManager::getTexture("Textures/particle.png");
// 	particle_Texture_2 = Feintgine::ResourceManager::getTexture("Textures/particle2.png");
// 	particle_Texture_3 = Feintgine::ResourceManager::getTexture("Textures/particle3.png");

// 	pop.init(Feintgine::ResourceManager::getTexture("Textures/pannel.png"),
// 		glm::vec2(-50, 0.5f), glm::vec2(0.0f, 90.0f), Feintgine::Color(255, 255, 255, 220));
// 	pop.setSPec(0.0f);

// 	//Load bg
	
// 	// Shaders 

// 	active_camera = true;

// 	std::srand(time(NULL));
// 	createParticle();

// 	initGUI();

// 	m_camera.setPosition(bg.getPos());

// 	m_fontRenderer = new Feintgine::SpriteFont("font/ARIALUNI.ttf", 64);
	
// }

// void MainMenuScreen::onExit()
// {
// 	m_gui.destroy();
// 	isExit = false;
// 	active_camera = false;
// 	m_fixer = 0.9988f;
// 	hide = true;
// 	pannelTurnoff = false;
// 	cam_angle = 0.0f;
// 	ui_alpha = 0;
// 	changeNext = false;
// 	changeBack = false;
// 	withDraw = 0;

// }

// void MainMenuScreen::update(float deltaTime)
// {

// 	//std::cout << deltaTime << "\n";
// 	m_world->Step(1.0f / 60.0f * deltaTime, 6, 20);
// 	m_fpsLimiter.begin();
// 	m_camera.update();
// 	handleInput(m_game->getInputManager());
// 	//_sleep(10);
// 	checkInput();

// 	//	testLabel->setWidth(testLabel->getWidth() + CEGUI::UDim(0.001f, 0.0f));
// 	m_fps = m_fpsLimiter.end();
// 	handleInput(m_game->getInputManager());

// 	static int counter = 0;
// 	counter++;
	
// 	if (isExit)
// 	{
	
// 		m_alpha -= FADE_SPEED*2 * deltaTime;
// 		ui_alpha -= FADE_SPEED *4 * deltaTime; 	
// 		if (m_alpha <= 0)
// 		{
// 			m_currentState = Feintgine::ScreenState::EXIT_APPLICATION;
// 		}
		
// 	}
// 	else
// 	{
// 		if (!changeNext)
// 		{
// 			if (m_alpha < 1)
// 			{
// 				m_alpha += FADE_SPEED * deltaTime;
// 			}
// 		}
// 		else
// 		{
// 			m_alpha -= FADE_SPEED * 2 * deltaTime;
// 			ui_alpha -= FADE_SPEED * 4 * deltaTime;
// 			destroyLoginPanel();
// 			if (m_alpha <= 0)
// 			{
// 				m_currentState = Feintgine::ScreenState::CHANGE_NEXT;
// 			}
// 		}
	
// 	}


	
// 	if (showTheLoginBox)
// 	{	
// 		if (loginPanel_alpha <= 1)
// 		{
// 			loginPanel->setAlpha(loginPanel_alpha);
// 			loginPanel_alpha += 0.05f * deltaTime;
// 		}
// 		else
// 		{
// 			isLoginPanelShowed = true;
// 		}
		
// 	}
// 	if (showTheRegisterBox)
// 	{
	
// 		if (!isRegisterPanelShowed)
// 		{
// 			if (registerPanel_alpha <= 1)
// 			{
// 				registerPanel->setAlpha(registerPanel_alpha);
// 				registerPanel_alpha += 0.05f * deltaTime;

// 			}
// 			else
// 			{
// 				isRegisterPanelShowed = true;
// 			}
// 		}

// 	}
// 	if (isLoginPanelShowed)
// 	{
// 		if (!showTheLoginBox)
// 		{
// 			if (loginPanel_alpha >= 0)
// 			{
// 				loginPanel->setAlpha(loginPanel_alpha);
// 				loginPanel_alpha -= 0.05f * deltaTime;
// 			}
// 			else
// 			{
// 				loginPanel->hide();
// 				isLoginPanelShowed = false;
// 			}
// 		}
// 	}

// 	if (isRegisterPanelShowed)
// 	{
// 		if (!showTheRegisterBox)
// 		{
// 			if (registerPanel_alpha >= 0)
// 			{
// 				registerPanel->setAlpha(registerPanel_alpha);
// 				registerPanel_alpha -= 0.05f * deltaTime;
// 			}
// 			else
// 			{
// 				registerPanel->hide();
// 				isRegisterPanelShowed = false;
// 			}
// 		}
// 	}

// 	if (login_fail != nullptr)
// 	{
// 		if (login_fail->onDestroy())
// 		{		
// 			delete login_fail;
// 			free(login_fail);
// 			login_fail = nullptr;
			
// 		}
// 		else
// 		{
// 			login_fail->update();
// 		}
		
// 	}



// 	if (active_camera)
// 	{


// 		if (m_camera.getScale() > 6.7f)
// 		{
// 			m_camera.setScale(m_camera.getScale() - 0.045f * deltaTime);
// 		}
		
// 		else
// 		{
// 		active_camera = false;
		
// 		}
	
// 	}
// 	else
// 	{	
// 		pop.expandingSize(glm::vec2(27.2f, 90.0f), glm::vec2(0.45f, 0.0f) * deltaTime );
// 		if (pop.getDimentions().x >= 27.0f)
// 		{
// 			if (pannelTurnoff)
// 			{
// 				pop.end_spec(0.75f, 0.085f * deltaTime);
// 				hide = false;
// 				clickable = true;
// 				if (withDraw <= 80)
// 				{
// 					credit->setWidth(credit->getWidth() + CEGUI::UDim::UDim(0.005f, 0.0f));
// 					withDraw++;
// 				}
// 			}
// 			else
// 			{
// 				pop.fayde_spec(0.0f, 3.4f, 0.085f * deltaTime, false);
// 				if (pop.getSpec() >= 3.4f)
// 				{
// 					pannelTurnoff = true;
					
// 				}
// 			}

// 		}
// 	}
// 	if (m_fixer <= 1.0f)
// 	{

// 		m_fixer += 0.0000045f  * deltaTime;
// 	}
	

// 	if (hide)
// 	{
// 		if (ui_alpha > 0)
// 		{
// 			ui_alpha -= FADE_SPEED*2  * deltaTime;
// 		}
// 	}
// 	else
// 	{
// 		if (ui_alpha < 1.0f)
// 		{
// 			ui_alpha += FADE_SPEED*2 * deltaTime;
// 		}
// 	}

// 	//pop.setAlpha(ui_alpha);
// 	start.getButton()->setAlpha(ui_alpha);
// 	regis.getButton()->setAlpha(ui_alpha);
// 	exit.getButton()->setAlpha(ui_alpha);

// 	//_sleep(10);
// 	if (isConnected)
// 	{
// 		updateSocket();
// 	}
	
// }

// void MainMenuScreen::draw()
// {


// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// 	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


// 	m_blurShader.use();

// 	//glViewport(0, 600 / 2, 1000 / 2, 600 / 2);

// 	// Upload texture uniform
// 	GLint textureUniform = m_blurShader.getUniformLocation("mySampler");
// 	glUniform1i(textureUniform, 0);
// 	glActiveTexture(GL_TEXTURE0);


// 	GLint alphaLocation = m_blurShader.getUniformLocation("time");
// 	glUniform1f(alphaLocation, m_alpha);


// 	GLint fixer = m_blurShader.getUniformLocation("fixer");
// 	glUniform1f(fixer, m_fixer);

// 	// Camera matrix
// 	glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
// 	GLint pUniform = m_blurShader.getUniformLocation("P");
// 	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

// 	m_spriteBatch.begin();

// 	bg.draw(m_spriteBatch);
// 	//m_player.draw(m_spriteBatch);
	
// 	//drawHUD();
// 	m_spriteBatch.end();
// 	m_spriteBatch.renderBatch();
// 	m_blurShader.unuse();


// 	//glViewport(1000/2, 600 / 2, 1000 / 2, 600 / 2);

// 	m_textureProgram.use();
// 	//glBlendFunc(GL_DST_COLOR, GL_DST_ALPHA);

	


// 	alphaLocation = m_textureProgram.getUniformLocation("fadeout");
// 	glUniform1f(alphaLocation, m_alpha);
	

	

// 	// Upload texture uniform
// 	textureUniform = m_textureProgram.getUniformLocation("mySampler");
// 	glUniform1i(textureUniform, 0);
// 	glActiveTexture(GL_TEXTURE0);


// 	// Camera matrix
// 	projectionMatrix = m_camera.getCameraMatrix();
// 	pUniform = m_textureProgram.getUniformLocation("P");
// 	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

// 	m_spriteBatch.begin();

// 	pop.draw(m_spriteBatch);
// 	for (int i = 0; i < m_particles.size(); i++)
// 	{
// 		m_particles[i]->draw(m_spriteBatch);
// 		m_particles[i]->update(m_camera, active_camera);

// 	}

// 	m_spriteBatch.end();
// 	m_spriteBatch.renderBatch();
// 	m_textureProgram.unuse();

	


// 	m_lightProgram.use();
// 	pUniform = m_lightProgram.getUniformLocation("P");
// 	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

// 	// Additive blending
// 	glBlendEquation(GL_FUNC_ADD);
// 	glBlendFunc(GL_SRC_ALPHA, GL_ONE);


	
// 	//glBlendFunc(GL_SRC_ALPHA, GL_ZERO);
// 	m_spriteBatch.begin();



// 	//playerLight.draw(m_spriteBatch);
// 	//glColorMask(true, true, true, false);
// 	//mouseLight.draw(m_spriteBatch);
// 	//glColorMask(true, true, true, true);
// 	//los.draw(m_spriteBatch);
// 	m_spriteBatch.end();
// 	m_spriteBatch.renderBatch();

// 	m_lightProgram.unuse();

// 	// Reset to regular alpha blending
	



// 	m_gui.draw();
// 	credit->setAlpha(m_alpha);

// 	//
	

// 	SDL_GL_SetSwapInterval(1);
// 	//
// 	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

// }

// void MainMenuScreen::drawHUD()
// {
// 	char buffer[256];
// 	sprintf_s(buffer, "FPS %.2f", m_fps);
// 	//std::cout << m_fps << std::endl;
// 	m_fontRenderer->draw(m_spriteBatch,
// 	buffer, glm::vec2(-50, -30), glm::vec2(0.04f),
// 	0.0f, Feintgine::Color(255, 0, 0, 255));
// }

// void MainMenuScreen::initGUI()
// {
// 	m_gui.init("GUI");
// 	m_gui.loadScheme("TaharezLook.scheme");
// 	m_gui.loadScheme("VanillaSkin.scheme");
// 	m_gui.loadScheme("WindowsLook.scheme");
// 	m_gui.loadScheme("Generic.scheme");

// 	m_gui.setFont("DejaVuSans-12");

// 	start.init("Đăng Nhập","startButton", m_gui, glm::vec4(0.12f, 0.2f, 0.1f, 0.05f), [&](const CEGUI::EventArgs & e){
	
// 		if (clickable)
// 		{
// 			hideSlice();
// 			showLoginPanel();
// 		}
	
// 		return true;
// 	});
// 	exit.init("Thoát", "exitButton",m_gui, glm::vec4(0.12f, 0.4f, 0.1f, 0.05f), [&](const CEGUI::EventArgs & e){
// 		if (clickable)
// 		{
			
// 			isExit = true;
// 			if (showTheLoginBox)
// 			{
// 				destroyLoginPanel();
// 			}
// 			if (showTheRegisterBox)
// 			{
// 				destroyRegisterPanel();
// 			}
// 		}
	
// 		return true;
// 	});
// 	regis.init("Đăng Ký", "registerButton", m_gui, glm::vec4(0.12f, 0.3f, 0.15f, 0.05f), [&](const CEGUI::EventArgs & e){

// 		if (clickable)
// 		{
// 			hideSlice();
// 			showRegisterPanel();
// 		}
	
		
// 		return true;
// 	});

// 	//testLabel->setProperty("HorzFormatting", "LeftAligned");
// 	//testLabel->setWidth(testLabel->getWidth() * 2);
// 	//testLabel->subscribeEvent(CEGUI::DefaultWindow::EventMouseClick, CEGUI::Event::Subscriber(&MainMenuScreen::onExitClicked, this));
// 	credit = static_cast<CEGUI::DefaultWindow*>(m_gui.createWidget("Generic/LabelWithOutline", glm::vec4(0.75, .865f, 0.0f, 0.2f), glm::vec4(0.0f), "credit"));
// 	std::string copyright = "Sản phẩm của team Blind Eye .";
// 	credit->setText((CEGUI::utf8*) copyright.c_str());
// //	credit->subscribeEvent(CEGUI::DefaultWindow::EventMouseLeavesSurface, CEGUI::Event::Subscriber(&MainMenuScreen::onNewGameClicked, this));
// 	credit->setProperty("HorzFormatting", "LeftAligned");
	

// 	background = static_cast<CEGUI::DefaultWindow*>(m_gui.createWidget("TaharezLook/StaticImage", glm::vec4(0.0, 0.0f, 1.0f, 1.0f), glm::vec4(0.0f), "popup"));
// 	background->setAlwaysOnTop(false);

// 	register_background = static_cast<CEGUI::DefaultWindow*>(m_gui.createWidget("TaharezLook/StaticImage", glm::vec4(0.0, 0.0f, 1.0f, 1.0f), glm::vec4(0.0f), "registerbg"));
// 	register_background->setAlwaysOnTop(false);

// 	//login panel
// 	loginPanel = static_cast<CEGUI::GroupBox *> (m_gui.createWidget(("TaharezLook/GroupBox"), glm::vec4(0.3, 0.25f, 0.4f, 0.4f), glm::vec4(0.0), "login_panel"));
// 	//loginPanel->setAlpha(0.0f);
// 	login_id = static_cast<CEGUI::Editbox *>(m_gui.createWidget(("TaharezLook/Editbox"), glm::vec4(0.35, 0.25f, 0.4f, 0.125f), glm::vec4(0.0), "login_id"));
// 	login_password = static_cast<CEGUI::Editbox *>(m_gui.createWidget(("TaharezLook/Editbox"), glm::vec4(0.35, 0.45f, 0.4f, 0.125f), glm::vec4(0.0), "login_password"));
// 	login_id_label = static_cast<CEGUI::DefaultWindow *> (m_gui.createWidget(("TaharezLook/Label"), glm::vec4(0.0, 0.25f, 0.4f, 0.125f), glm::vec4(0.0), "login_id_label"));
// 	login_password_label = static_cast<CEGUI::DefaultWindow *> (m_gui.createWidget(("TaharezLook/Label"), glm::vec4(0.0, 0.45f, 0.4f, 0.125f), glm::vec4(0.0), "login_password_label"));
// 	login_id_label->setText("ID :");
// 	login_id_label->setAlwaysOnTop(true);
// 	login_password_label->setText("Password :");
// 	login_password_label->setAlwaysOnTop(true);
// 	login_id->setAlwaysOnTop(true);
// 	login_password->setAlwaysOnTop(true);
// 	login_id->setText("feint");
// 	login_password->setText("admin");
	
// 	login_password->setTextMasked(true);
// 	loginPanel->addChild(login_id);
// 	loginPanel->addChild(login_password);
// 	loginPanel->addChild(login_id_label);
// 	loginPanel->addChild(login_password_label);
// 	loginPanel->addChild(background);
// 	loginPanel->hide();

	


// 	pannel_login.init("Login", "loginButton", m_gui, glm::vec4(0.25f, 0.7f, 0.1f, 0.1f), [&](const CEGUI::EventArgs & e){
		
	
// 			std::string id = login_id->getText().c_str();
// 			std::string passwod = login_password->getText().c_str();


// 			login(strdup(id.c_str()), strdup(passwod.c_str()));
			
		

// 		return true;
// 	});

// 	panel_cancel.init("Cancel", "cancelLoginButton", m_gui, glm::vec4(0.55f, 0.7f, 0.13f, 0.1f), [&](const CEGUI::EventArgs & e){

	
// 		if (clickable)
// 		{
// 			show();
// 			destroyLoginPanel();
// 			if (login_fail != nullptr)
// 			{
// 				login_fail->destroy();
// 			}

// 		}
		
	
// 		return true;
// 	});

// 	register_regis.init("Sign Up", "registing_button", m_gui, glm::vec4(0.25f, 0.8f, 0.13f, 0.1f), [&](const CEGUI::EventArgs & e){

// 		registing(strdup(register_id->getText().c_str()), strdup(register_password->getText().c_str()), strdup(register_confirm->getText().c_str()));
// 		return true;
// 	});

// 	register_cancel.init("Cancel", "cancelRegisterButton", m_gui, glm::vec4(0.55f, 0.8f, 0.13f, 0.1f), [&](const CEGUI::EventArgs & e){

// 		if (clickable)
// 		{
// 			show();
// 			register_confirm->setText("");
// 			register_password->setText("");
// 			register_id->setText("");
// 			destroyRegisterPanel();
// 		}
		
// 		return true;
// 	});


// 	loginPanel->addChild(panel_cancel.getButton());
// 	loginPanel->addChild(pannel_login.getButton());


// 	loginPanel->setAlpha(0.0);
// 	//
	
// 	//register pannel
// 	registerPanel = static_cast<CEGUI::GroupBox *> (m_gui.createWidget(("TaharezLook/GroupBox"), glm::vec4(0.3, 0.25f, 0.4f, 0.4f), glm::vec4(0.0), "register_panel"));
// 	//loginPanel->setAlpha(0.0f);
// 	register_id = static_cast<CEGUI::Editbox *>(m_gui.createWidget(("TaharezLook/Editbox"), glm::vec4(0.45, 0.15f, 0.4f, 0.125f), glm::vec4(0.0), "register_id"));
// 	register_password = static_cast<CEGUI::Editbox *>(m_gui.createWidget(("TaharezLook/Editbox"), glm::vec4(0.45, 0.35f, 0.4f, 0.125f), glm::vec4(0.0), "register_password"));
// 	register_confirm = static_cast<CEGUI::Editbox *>(m_gui.createWidget(("TaharezLook/Editbox"), glm::vec4(0.45, 0.55f, 0.4f, 0.125f), glm::vec4(0.0), "register_confirm"));
// 	register_id_label = static_cast<CEGUI::DefaultWindow *> (m_gui.createWidget(("TaharezLook/Label"), glm::vec4(0.0, 0.15f, 0.4f, 0.125f), glm::vec4(0.0), "register_id_label"));
// 	register_password_label = static_cast<CEGUI::DefaultWindow *> (m_gui.createWidget(("TaharezLook/Label"), glm::vec4(0.0, 0.35f, 0.4f, 0.125f), glm::vec4(0.0), "register_password_label"));
// 	register_confirm_label = static_cast<CEGUI::DefaultWindow *> (m_gui.createWidget(("TaharezLook/Label"), glm::vec4(0.0, 0.55f, 0.4f, 0.125f), glm::vec4(0.0), "register_confirm_label"));
// 	register_id_label->setText("ID :");
// 	register_id_label->setAlwaysOnTop(true);
// 	register_password_label->setText("Password :");
// 	register_password_label->setAlwaysOnTop(true);
// 	register_id->setAlwaysOnTop(true);
// 	register_password->setAlwaysOnTop(true);
// 	register_confirm->setAlwaysOnTop(true);
// 	register_confirm_label->setAlwaysOnTop(true);
// 	register_confirm_label->setText("Confirm Password :");


// 	register_password->setTextMasked(true);
// 	register_confirm->setTextMasked(true);
	
// 	registerPanel->addChild(register_id);
// 	registerPanel->addChild(register_password);
// 	registerPanel->addChild(register_id_label);
// 	registerPanel->addChild(register_password_label);
// 	registerPanel->addChild(register_background);
// 	registerPanel->addChild(register_confirm);
// 	registerPanel->addChild(register_confirm_label);
// 	registerPanel->addChild(register_regis.getButton());
// 	registerPanel->addChild(register_cancel.getButton());
// 	registerPanel->hide();
// 	registerPanel->setAlpha(0.0f);


// 	m_gui.setMouseCursor("TaharezLook/MouseArrow");
// 	//m_gui.showMouseCursor();
// 	SDL_ShowCursor(0);
	

// 	//
// }
// void MainMenuScreen::checkInput()
// {
// 	SDL_Event evnt;
// 	while (SDL_PollEvent(&evnt)) {
// 		m_gui.onSDLEvent(evnt);
// 		m_game->onSDLEvent(evnt);
// 	}
	
// }

// void MainMenuScreen::handleInput(Feintgine::InputManager &inputManager)
// {
// 	if (inputManager.isKeyPressed(SDLK_ESCAPE))
// 	{
// 		m_currentState = Feintgine::ScreenState::EXIT_APPLICATION;

// 	}
// 	if (inputManager.isKeyPressed(SDL_QUIT))
// 	{
// 		m_currentState = Feintgine::ScreenState::EXIT_APPLICATION;
// 	}


	

	
// }

// void MainMenuScreen::show()
// {
// 	hide = false;

// 	clickable = false;
	
// }

// void MainMenuScreen::hideSlice()
// {
// 	hide = true;

// 	clickable = false;
// }

// void MainMenuScreen::showLoginPanel()
// {
// 	loginPanel->show();
// 	if (showTheRegisterBox)
// 	{
// 		destroyRegisterPanel();
// 	}
// 	showTheLoginBox = true;

// }

// void MainMenuScreen::destroyLoginPanel()
// {
// 	showTheLoginBox = false;
	
// }



// void MainMenuScreen::login( char * id,  char * password)
// {
// 	if (!hasClickLog)
// 	{

// 		hasClickLog = true;
// 		// if (ClientSocket::Instance()->connectToServer())
// 		// {
// 		// 	std::cout << "connect OK \n";
// 		// 	isConnected = true;
// 		// 	ClientSocket::Instance()->logIn(id, password);
// 		// }
// 		// else
// 		// {
// 		// 	createMessageBox("Không có kết nối !");
// 		// 	isConnected = false;
// 		// 	hasClickLog = false;
			
// 		// }
		
// 	}


// // 	if (ClientSys::Instance()->connectTo())
// // 	{
// // 		std::cout << "connect OK \n";
// // 		is_sock_init = true;
// // 	
// // 	}
// // 	else {
// // 		std::cout << "connect not OK \n";
// // 		createMessageBox("Không có kết nối !");
// // 		isConnected = false;
// // 	}
// // 	
// // 

// 		//std::cout << "check packet before sending : " << m_packetData->packetSize << " bytes \n";
// 		//testingData *testBrah = new testingData();

// // 		testBrah->f = 300; 
// // 		testBrah->y = 222;
// // 		std::cout << m_packetData->flag << "\n";
// // 		std::cout << m_packetData->id << "\n";
// // 		std::cout << m_packetData->password << "\n";

// 		//ClientSocket::Instance()->sendData(m_packetData);
		

	
// // 	std::string condition = "SELECT ID from account WHERE ID ='";
// // 	condition.append(id);
// // 	condition.append("' and password = '");
// // 	condition.append(password);
// // 	condition.append("'");

// /*	std::vector<std::string> t_acc;*/

// //	changeNextScreen();
// 	//first = false;

// // 	if (t_acc.size() > 0)
// // 	{
// // 		condition = "SELECT currency from character_currency WHERE character_id = '";
// // 		condition.append(id);
// // 		condition.append("'");
// // 		
// // 		
// // 		
// // 		
// // 	
// // 		
// // 	
// // 	}
// // 	else
// // 	{
// // 		loged_in = false;
// // 		if (login_fail == nullptr)
// // 		{
// // 
// // 			std::string tmp1 = "log_fail_border";
// // 			tmp1.append(std::to_string(attemp));
// // 			std::string tmp2 = "log_fail_text";
// // 			tmp2.append(std::to_string(attemp));
// // 			std::string tmp3 = "log_fail_bg";
// // 			tmp3.append(std::to_string(attemp));
// // 			std::string tmp4 = "log_fail_button";
// // 			tmp4.append(std::to_string(attemp));
// // 
// // 			login_fail = new CustomMessageBox(m_gui, tmp1, tmp2, tmp3, tmp4,
// // 				"ID or password is invalid ! ",
// // 				glm::vec4(0.35f, 0.3f, 0.3f, 0.3f));
// // 
// // 			attemp++;
// // 		}
// // 
// // 
// // 	}

	
// }

// void MainMenuScreen::showRegisterPanel()
// {
// 	registerPanel->show();
// 	if (showTheLoginBox)
// 	{
// 		destroyLoginPanel();
// 	}
// 	showTheRegisterBox = true;
// }

// void MainMenuScreen::destroyRegisterPanel()
// {
// 	showTheRegisterBox = false;
// }

// void MainMenuScreen::registing(char * id, char * password, char * confirm)
// {
// 	std::string test = id;
// 	std::string test2 = password;


// 	if (test.size() == 0 || test2.size() ==0)
// 	{

// 		createMessageBox("Thiệt luôn ?");
// 	}
// 	else if (std::strcmp(password, confirm))
// 	{

// 		createMessageBox("Xác nhận mật khẩu sai !");

// 	}
		
// 	else
// 	{

// 		// if (ClientSocket::Instance()->connectToServer())
// 		// {
// 		// 	std::cout << "connect OK \n";
// 		// 	isConnected = true;
// 		// 	ClientSocket::Instance()->t_register(id, password);
// 		// }
// 		// else
// 		// {
// 		// 	createMessageBox("Không có kết nối !");
// 		// 	isConnected = false;
// 		// }
		
							
// 	}
		
	
// }

// void MainMenuScreen::createParticle()
// {
// 	m_particles.clear();
// 	std::mt19937 randGenerator;
// 	std::uniform_int_distribution<int> choice(0,2);

// 	std::mt19937 posRand;
// 	std::uniform_real_distribution<float> posX(-80.0f, 80.0f);
// 	std::uniform_real_distribution<float> posY(-50.0f, 50.0f);

// 	std::uniform_real_distribution<float> radius(0.9f, 1.8f);
// 	for (int i = 0; i < MAX_PARTICLE; i++)
// 	{ 
// 		Feintgine::GLTexture texture;
		
// 		Droping_Particle *temp = new Droping_Particle();

// 		switch (choice(randGenerator))
// 		{
// 		case 0:
// 			texture = particle_Texture;
// 			break;
// 		case 1:
// 			texture = particle_Texture_2;
// 			break;
// 		case 2:
// 			texture = particle_Texture_3;
// 			break;
// 		default:
// 			break;
// 		}
// 		temp->init(texture, glm::vec2(posX(posRand), posY(posRand)), glm::vec2(radius(posRand)), Feintgine::Color(255, 255, 255, 255));
// 		temp->loadPhysic(m_world);
// 		temp->setSPec(5);
	
		
// 		m_particles.push_back(temp);
// 	}
	
// }

// void MainMenuScreen::initShader()
// {
// 	m_textureProgram.compileShaders("Shaders/backup.vert", "Shaders/backup.frag");
// 	m_textureProgram.addAttribute("vertexPosition");
// 	m_textureProgram.addAttribute("vertexColor");
// 	m_textureProgram.addAttribute("vertexUV");
// 	//m_textureProgram.addAttribute("spec");
// 	m_textureProgram.linkShaders();

// 	m_lightProgram.compileShaders("Shaders/lightShading.vert", "Shaders/lightShading.frag");
// 	m_lightProgram.addAttribute("vertexPosition");
// 	m_lightProgram.addAttribute("vertexColor");
// 	m_lightProgram.addAttribute("vertexUV");
// 	m_lightProgram.linkShaders();

// 	m_blurShader.compileShaders("Shaders/blurShading.vert", "Shaders/blurShading.frag");
// 	m_blurShader.addAttribute("vertexPosition");
// 	m_blurShader.addAttribute("vertexColor");
// 	m_blurShader.addAttribute("vertexUV");
// 	m_blurShader.linkShaders();


// }

// void MainMenuScreen::expandPannel()
// {

// }

// void MainMenuScreen::initWorld()
// {
// 	b2Vec2 gravity(0, -1.3f);

// 	m_world = new b2World(gravity);

// 	//b2Body * worldDef


// }

// void MainMenuScreen::createMessageBox(const std::string & message , std::function<bool(const CEGUI::EventArgs & e)> setOnClick)
// {
	
// 	float width = (message.size() * 0.009f) + 0.02f;

// 	std::string tmp1 = "regis_fail_border";
// 	tmp1.append(std::to_string(attemp));
// 	std::string tmp2 = "regis_fail_text";
// 	tmp2.append(std::to_string(attemp));
//  	std::string tmp3 = "regis_fail_bg";
// 	tmp3.append(std::to_string(attemp));
// 	std::string tmp4 = "regis_fail_button";
// 	tmp4.append(std::to_string(attemp));
// 	login_fail = new CustomMessageBox(m_gui, tmp1, tmp2, tmp3, tmp4,
// 		message,
// 		glm::vec4((1.0f-width)/2.0f, 0.32, width, 0.3f));
	
// 	if (setOnClick != nullptr)
// 	{
// 		login_fail->addEvent(setOnClick);
// 	}

// 	attemp++;
// }

// void MainMenuScreen::updateSocket()
// {

// 	std::string r_data =  ClientSocket::Instance()->checkForIncomingMessages();
// 	if (r_data == "@SHUTDOWN")
// 	{
// 		createMessageBox("Bị mất kết nối với server");
// 	}
// 	else
// 	{
// 		if (r_data.size() > 0)
// 		{
// 			TCP_msg recv_msg;
// 			recv_msg.ParseFromString(r_data);
// 			switch (recv_msg.type())
// 			{	



// 			case LOGIN_INFO:
// 			{
// 				std::cout << "log info here \n";		
// 				Profile::Instance()->setPlayerIDSession(recv_msg.m_log_info().id());
// 				changeNextScreen();
// 			}
// 				break;
			
// 			case T_ERROR:
// 				if (recv_msg.m_error().des() == "log_failed")
// 				{
// 					createMessageBox("Tài khoản hoặc mật khẩu sai !");
// 					isConnected = false;
// 					ClientSocket::Instance()->disconnect();
// 				}
// 				else if (recv_msg.m_error().des() == "account_exist")
// 				{
// 					createMessageBox("Tài khoản này đã tồn tại !");
// 					isConnected = false;
// 					ClientSocket::Instance()->disconnect();
// 				}
// 				else if (recv_msg.m_error().des() == "register_success")
// 				{
// 					createMessageBox("Đăng ký thành công !", [&](const CEGUI::EventArgs &e) {
// 						destroyRegisterPanel();
// 						//showLoginPanel();
// 						return true;
// 					});
// 					isConnected = false;
// 					ClientSocket::Instance()->disconnect();
// 				}
// 				else if (recv_msg.m_error().des() == "register_failed")
// 				{
// 					createMessageBox("Đăng ký thất bại !");
// 					isConnected = false;
// 					ClientSocket::Instance()->disconnect();
// 				}
// 				else
// 				{
// 					createMessageBox("??????");
// 					ClientSocket::Instance()->disconnect();
// 				}
// 				break;
// 			default:
// 				break;
// 			}
// 		}
// 	}


	
// }

// // int MainMenuScreen::recvTCP(const std::string &data)
// // {
// // 	TCP_clientSide t_data;
// // 
// // 	t_data.ParseFromString(data);
// // 
// // 
// // 	if (t_data.has_characterlog())
// // 	{
// // 		return 1;
// // 	}
// // 
// // 	if (t_data.has_t_error())
// // 	{
// // 		return 2;
// // 	}
// // 
// // 	return -1;
// // }


