#include "EditorScreen.h"



EditorScreen::EditorScreen()
{
}

EditorScreen::EditorScreen(Feintgine::Window * window)
{
	m_screenIndex = 0;
	//m_sceneFilePath = "";
	m_window = window;
	//m_scene = new Feintgine::Fg_scene();
	initShader();

}

EditorScreen::~EditorScreen()
{

}

int EditorScreen::listdir(const char *name, int level)
{
	//std::cout << "scan on " << name << "\n";
	DIR *dir ;
	struct dirent *entry;

	if (!(dir = opendir(name)))
	{
		std::cout << "dir failed \n";
		return 0;
	}
		
	if (!(entry = readdir(dir)))
	{
		std::cout << "entry failed \n";
		return 0;
	}
		

	do {
		if (entry->d_type == DT_DIR) {
			char path[1024];
			int len = _snprintf_s(path, sizeof(path) - 1, "%s/%s", name, entry->d_name);
			path[len] = 0;
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
				continue;
		//	printf("%*s[%s]\n", level * 2, "", entry->d_name);
				listdir(path, level + 1);			
		}
		else
		{
			//printf("%*s- %s\n", level * 2, "", entry->d_name);
			std::string texturePath = name;
			texturePath.append("/");
			texturePath.append(entry->d_name);



			if (texturePath.find("Packets/") != std::string::npos)
			{
				if (texturePath.find(".xml") != std::string::npos)
				{
					// std::cout << "packet " << entry->d_name << " found \n";
					loadPacket(texturePath.c_str());
				}
			}		

			if (texturePath.find("F_AObjects/") != std::string::npos)
			{
				if (texturePath.find(".xml") != std::string::npos)
				{
					// std::cout << "packet " << entry->d_name << " found \n";
					const CEGUI::Image* sel_img = &CEGUI::ImageManager::getSingleton().get("TaharezLook/MultiListSelectionBrush");
					 
					CEGUI::ListboxTextItem * item;
				 	item = new CEGUI::ListboxTextItem(entry->d_name, animateCount++);
					item->setSelectionBrushImage(sel_img);
					m_AObjList->addItem(item);
				}
			}
						
		}
	} while (entry = readdir(dir));

	closedir(dir);
	return 0;

}


int EditorScreen::getNextScreenIndex() const
{
	return -1;
}

int EditorScreen::getPreviousScreenIndex() const
{
	return -1;
}

void EditorScreen::build()
{
	
}

void EditorScreen::destroy()
{
	m_debug.dispose();
	m_currentState = Feintgine::ScreenState::EXIT_APPLICATION;
	m_gui.destroy();
	m_editorCrosshair.dispose();
	m_coliderRenderer.dispose();
}


static void loadAsync()
{

}
void EditorScreen::onEntry()
{
	
	__int64 now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	std::cout << "Start loading " << now << "\n";
	Feintgine::SpriteManager::Instance()->loadFromDirectory("Assets/", 0);
	Feintgine::SpriteManager::Instance()->executeReadData();
	// tileset 
	m_tileset.initData(Feintgine::ResourceManager::getTexture("Assets/Tilesets/test.png"));
	m_tileset.loadData();

	// 

	m_debug.init();

	m_coliderRenderer.init();
	m_editorCrosshair.init();

	m_textRenderer.init(24,128, "font/ARIALUNI.ttf");
	m_sceneManager.loadIcons();
	

//	EditScreen = glm::vec4((float)m_window->getScreenWidth() / 4.57142857f, m_window->getScreenHeight()/18, m_window->getScreenWidth()/2, m_window->getScreenHeight()/1.125f);
//	SampleSceen = glm::vec4((float)m_window->getScreenWidth() / 1.32231404958, m_window->getScreenHeight() / 2.1686746f, m_window->getScreenWidth() / 10.666f, m_window->getScreenHeight() / 6);
//	ObjectsScreen = glm::vec4((float)m_window->getScreenWidth() / 160, m_window->getScreenHeight() / 1.6071428f, m_window->getScreenWidth() / 5.3333f, m_window->getScreenHeight() /3);
//	PreviewScreen = glm::vec4((float)m_window->getScreenWidth() / 32, m_window->getScreenHeight() / 6, m_window->getScreenWidth() / 7.27272f, m_window->getScreenHeight() / 4.090909);
 	
	SceneScreen = glm::vec4(350, 50, 800, 800);
	EditScreen = glm::vec4(350, 450,400,400);
	AnimateScreen = glm::vec4(225, 410, 450, 450);
 	SampleSceen = glm::vec4(970, 700, 150, 150);
	ObjectsScreen = glm::vec4(10, 560, 300, 300);
 	PreviewScreen = glm::vec4(50, 50, 220, 220);
	SpriteListScreen = glm::vec4(1160, 570, 300, 300);

	EditDamaku = glm::vec4(50, 50, 800, 800);

	EditEnemy = glm::vec4(50, 50, 800, 800);

	EditLua = glm::vec4(50, 50, 800, 800);

	//m_brushTest.init(Feintgine::ResourceManager::getTexture("./Assets/Brush/grass.png"),glm::vec2(0),glm::vec2(1250),glm::vec2(50),Feintgine::Color(255,255,255,255),-1);

	//m_brushTest.init(Feintgine::ResourceManager::getTexture("./Assets/Brush/grass.png"), glm::vec2(0), glm::vec2(32000), glm::vec2(500), Feintgine::Color(255, 255, 255, 255), -1);


	staticCam_Editing.init(EditScreen.z, EditScreen.w);
	staticCam_Editing.setPosition(glm::vec2(0));
	staticCam_Editing.setScale(1.0f);

	staticCam_Animating.init(AnimateScreen.z, AnimateScreen.w);
	staticCam_Animating.setPosition(glm::vec2(0));

	m_sampleCam.update();
	//staticCam_Editing.loadAspect(m_window->getAspect());

	m_fullCam.init(1600, 900);
	m_fullCam.setPosition(glm::vec2(0));

	m_fullCam.setScale(1.0f);
	m_fullCam.update();

	
	m_spriteListCamera.init(SpriteListScreen.z, SpriteListScreen.w);
	m_spriteListCamera.setScale(1.0f);

	m_spriteListCamera.setPosition(glm::vec2(0));

	//m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
	m_camera.init(EditScreen.z, EditScreen.w);
	m_camera.setScale(1.0f);

	m_animatingCamera.init(AnimateScreen.z, AnimateScreen.w);
	m_animatingCamera.setScale(2.0f);


	m_camera.setPosition(glm::vec2(0));
	//m_camera.loadAspect(m_window->getAspect());

	m_sceneCamera.init(SceneScreen.z, SceneScreen.w);
	m_sceneCamera.setScale(1.0f);
	
	m_sceneCamera.setPosition(glm::vec2(0));
	//m_sceneCamera.loadAspect(m_window->getAspect());
	m_sceneCamera.update();
	m_sceneCamera_static.init(SceneScreen.z, SceneScreen.w);
	m_sceneCamera_static.setScale(1.0f);

	m_sceneCamera_static.setPosition(glm::vec2(0));

	m_sceneCamera_static.update();

	m_editDamakuCamera.init(EditDamaku.z, EditDamaku.w);
	m_editDamakuCamera.setScale(1.0f);
	m_editDamakuCamera.setPosition(glm::vec2(0));

	m_editDamakuCamera_static.init(EditDamaku.z, EditDamaku.w);
	m_editDamakuCamera_static.setScale(1.0f);
	m_editDamakuCamera_static.setPosition(glm::vec2(0));
	m_editDamakuCamera_static.update();

	m_editEnemyCamera.init(EditEnemy.z, EditEnemy.w);
	m_editEnemyCamera.setScale(1.0f);
	m_editEnemyCamera.setPosition(glm::vec2(0));
	
	m_editEnemyCamera_static.init(EditEnemy.z, EditEnemy.w);
	m_editEnemyCamera_static.setScale(1.0f);
	m_editEnemyCamera_static.setPosition(glm::vec2(0));
	m_editEnemyCamera_static.update();


	m_editLuaCamera.init(EditLua.z, EditLua.w);
	m_editLuaCamera.setScale(1.0f);
	m_editLuaCamera.setPosition(glm::vec2(0));

	m_editLuaCamera_static.init(EditEnemy.z, EditEnemy.w);
	m_editLuaCamera_static.setScale(1.0f);
	m_editLuaCamera_static.setPosition(glm::vec2(0));
	m_editLuaCamera_static.update();


	m_sampleCam.init(SampleSceen.z, SampleSceen.w);
	m_sampleCam.setScale(1.0f);

	m_sampleCam.setPosition(glm::vec2(0));	
	//m_sampleCam.loadAspect(m_window->getAspect());
	m_sampleCam.update();

	m_previewCamera.init(PreviewScreen.z, PreviewScreen.w);
	m_previewCamera.setScale(1.0f);

	m_previewCamera.setPosition(glm::vec2(0));	
	//m_previewCamera.loadAspect(m_window->getAspect());
	m_previewCamera.update();

	m_previewCamera_static.init(PreviewScreen.z, PreviewScreen.w);
	m_previewCamera_static.setScale(1.0f);

	m_previewCamera_static.setPosition(glm::vec2(0));
	m_previewCamera_static.update();
	//m_previewCamera_static.loadAspect(m_window->getAspect());


	staticCam_Sample.init(SampleSceen.z, SampleSceen.w);
	staticCam_Sample.setScale(1.0f);

	staticCam_Sample.setPosition(glm::vec2(0));
//	staticCam_Sample.loadAspect(m_window->getAspect());
	staticCam_Sample.update();

	m_objectsCamera.init(ObjectsScreen.z, ObjectsScreen.w);
	m_objectsCamera.setScale(1.0f);

	m_objectsCamera.setPosition(glm::vec2(0));
//	m_objectsCamera.loadAspect(m_window->getAspect());
	m_objectsCamera.update();

	m_camera.update();
	m_camera.setScale(DEFAULT_OBJECT_CAM_SCALE);
	m_spriteListCamera.update();

	m_spriteBatch.init();
	
	m_camera.setPosition(glm::vec2(0));
	//readFile();
	initGUI();
	m_spriteListDisplayer.init(glm::vec2(0), glm::vec2(SpriteListScreen.z, SpriteListScreen.w), 5, 5, &m_gui);
	m_spriteListDisplayer.setClickSpriteEvent([&]() {
		eventSelectSprite();
	
		return true;
	});
	m_objectHolder.setClickObjectEvent([&]() {
	
			if (m_objectSelected)
			{
				//m_selectedObject.clearLightAfterward();
			}
			m_selectedObject  = m_objectHolder.getNonConstDisplaySample();
			m_selectedObject.setDepth(100);
			EditorProperty::Instance()->setCurrentEditObject(m_selectedObject);
			//m_selectedObject = *p_selectedObject;
			m_objectSelected = true;
		return true;
	});
	m_objectHolder.setOnCancelObject([&]() {

		m_selectedObject = m_objectHolder.getNonConstDisplaySample();
		m_selectedObject.setDepth(100);
		EditorProperty::Instance()->setCurrentEditObject(m_selectedObject);
		m_objectSelected = false;
		return true;
	});
	//initGUI();
	drawMode = edit_scene_mode;
	//hideObjectEditor();
	hideAnimateEditor();
	hideDamakuEditor();
	showSceneEditor();
	m_layers->show();
	m_addLayerButton->show();
	m_deleteLayerButton->show();

	refresh();
// 	initSlot();
// 	listdir("./Assets", 0);
// 	sortObject();
// 	updatePage();



	//Load Sprite Packets
	
	m_spriteListDisplayer.hide();
	m_buildObjectTool.init(&m_buildingObject,&m_gui,&m_camera);

	m_buildObjectTool.hide();

	m_objectHolder.init(glm::vec2(0), glm::vec2(ObjectsScreen.z, ObjectsScreen.w), 5, 5, &m_gui);
	
	m_sceneManager.init(&m_sceneCamera,&m_gui);

	m_tileStack.init(
		Feintgine::ResourceManager::getTexture("Assets/Tilesets/tileset_water.png")
		,32,24, &m_sceneCamera);
	m_tileStack.bindTileManager(&m_tileManager);

	m_enemyEditor.init(EditEnemy, &m_editEnemyCamera,
		m_editEnemyCamera_static);

	m_luaEditor.init(EditEnemy, &m_editLuaCamera,
		m_editLuaCamera_static);

	m_enemyEditor.loadGUI(&m_gui);
	m_enemyEditor.loadEnemies("./Data/stageData/enemyState/fairyState.est");
	//m_enemyEditor.loadEnemy("./Data/stageData/enemyState/fairyState.est");
	m_enemyEditor.showGUI(false);

	m_luaEditor.loadGUI(&m_gui);
	m_luaEditor.showGUI(false);

	m_luaEditor.loadBosses("Assets/LuaFiles/");

	
	__int64 end = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	std::cout << "End load " << end << std::endl;

	glEnable(GL_BLEND);
	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
	

	__int64 elapsed = end - now;
	std::cout << "total " << (float)elapsed / 1000.0f << "\n";



}

void EditorScreen::onExit()
{
	m_editObjectShader.dispose();
	//m_spriteListShader.dispose();
	//m_sceneShader.dispose();
	m_gui.destroy();
	
	
}



void EditorScreen::update(float deltaTime)
{
	//checkInput();
	
	m_camera.update();
	
	staticCam_Editing.update();
	staticCam_Animating.update();
	staticCam_Sample.update();
	m_sampleCam.update();
	m_animatingCamera.update();
	//m_objectsCamera.update();
	m_previewCamera.update();
	m_sceneCamera.update();
	m_spriteListCamera.update();
	m_editDamakuCamera_static.update();
	m_editDamakuCamera.update();
	m_editEnemyCamera.update();
	m_editLuaCamera.update();
	m_editLuaCamera_static.update();

	m_tileset.update(deltaTime);
	m_tileManager.update(deltaTime);
	m_tileStack.update(deltaTime);
	if (m_objectSelected && drawMode == T_EDIT_SCREEN_MODE)
	{
		if (m_sceneManager.isGrided())
		{
			glm::vec2 curMousePos = m_sceneCamera.convertScreenToWorld(m_game->getInputManager().getMouseCoords(),
				glm::vec2(SceneScreen.x, SceneScreen.y), glm::vec2(m_window->getScreenWidth(), m_window->getScreenHeight()));
			glm::vec2 SpacingOffset = EditorProperty::Instance()->getSpacingOffset();
			
			float xbalanceVal = 0.0f;
			float ybalanceVal = 0.0f;
			if (curMousePos.x < 0)
			{
				xbalanceVal = SpacingOffset.x;
			}
			if (curMousePos.y < 0)
			{
				ybalanceVal = SpacingOffset.y;
			}
			int xVal = (curMousePos.x - xbalanceVal) / SpacingOffset.x;
			int yVal = (curMousePos.y - ybalanceVal) / SpacingOffset.y;
			glm::vec2 gridedPos = glm::vec2((xVal* SpacingOffset.x) + 32, (yVal*SpacingOffset.y) + 32);
			m_selectedObject.setPos(gridedPos);
		}
		else
		{
			m_selectedObject.setPos(m_sceneCamera.convertScreenToWorld(m_game->getInputManager().getMouseCoords(),
				glm::vec2(SceneScreen.x, SceneScreen.y), glm::vec2(m_window->getScreenWidth(), m_window->getScreenHeight())));
		}
	
	}
	if (drawMode == edit_scene_mode)
	{
		m_sceneManager.update(m_sceneCamera.convertScreenToWorld(m_game->getInputManager().getMouseCoords(),
			glm::vec2(SceneScreen.x, SceneScreen.y), glm::vec2(m_window->getScreenWidth(), m_window->getScreenHeight())));
	}

	
	if (drawMode == edit_object_mode)
	{
		m_buildObjectTool.update();
		//m_camera.update();
	}

	if (m_fAnimatedObject.isInited())
	{
		m_fAnimatedObject.update(deltaTime);

		if(!m_fAnimatedObject.isPlaying())
		{
			m_isAnimationPlaying = false;
		}
		//m_animatedObject.update();
	}
	if (drawMode == edit_enemy_mode)
	{
		m_enemyEditor.update(deltaTime);
	}
	if (drawMode == edit_lua_mode)
	{
		m_luaEditor.update(deltaTime);
	}

	if (m_fAnimatedObject.getCurrentAnimation())
	{
		if (m_spriteListDisplayer.getDisplaySample())
		{
			animation_applySprite->setEnabled(true);
			
		}
		else
		{
			animation_applySprite->setEnabled(false);
			
		}
		animation_enableLoop_toggle->setEnabled(true);
		animation_isSpriteInverted->setEnabled(true);
		animation_markAsLoop_toggle->setEnabled(true);

		animation_anim_offset_textbox_x->setEnabled(true);
		animation_anim_offset_textbox_y->setEnabled(true);


		if (m_fAnimatedObject.getCurrentAnimation()->getCurrentAnim())
		{
			//std::cout << "offset is " << m_fAnimatedObject.getCurrentAnimation()->getCurrentAnim()->offset.x << "\n";

			//std::cout << m_fAnimatedObject.getCurrentAnimation()->getCurrentAnim()->sprite.getName() << " !!!!!\n";
			if (!animation_anim_offset_textbox_x->hasInputFocus())
			{
				
				animation_anim_offset_textbox_x->setText(
						feint_common::Instance()->convertPreciousFloatToString(
							m_fAnimatedObject.getCurrentAnimation()->getCurrentAnim()->offset.x));
			}
			if (!animation_anim_offset_textbox_y->hasInputFocus())
			{
				animation_anim_offset_textbox_y->setText(
					feint_common::Instance()->convertPreciousFloatToString(m_fAnimatedObject.getCurrentAnimation()->getCurrentAnim()->offset.y));
			}
		}
		else
		{
			animation_anim_offset_textbox_x->setText(
				feint_common::Instance()->convertPreciousFloatToString(0));

			animation_anim_offset_textbox_y->setText(
				feint_common::Instance()->convertPreciousFloatToString(0));
		
		}

	}
	else
	{
		animation_enableLoop_toggle->setEnabled(false);
		animation_isSpriteInverted->setEnabled(false);
		animation_markAsLoop_toggle->setEnabled(false);

		animation_anim_offset_textbox_x->setEnabled(false);
		animation_anim_offset_textbox_y->setEnabled(false);
	}

	if (m_actionList->getFirstSelectedItem())
	{

		animation_addAnim->setEnabled(true);
		animation_removeAnim->setEnabled(true);
	
		
	}
	else
	{
		animation_addAnim->setEnabled(false);
		animation_removeAnim->setEnabled(false);
		
	}
	updateAnimationLabel();
	if (drawMode == edit_damaku_mode)
	{
		m_paternEditor.update(deltaTime);
	}



	//
}

void EditorScreen::draw()
{
	// SpriteSheet / Map Editing Camera
	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	switch (objectiveMode)
	{
	case OBJECTIVE_OBJECT: 
		
		break;
	case OBJECTIVE_BRUSH:
		break;

	default:
		break;
	}
	if (m_currentMode == T_EDIT_OJECT_MODE || m_currentMode == T_EDIT_SCREEN_MODE)
	{
		drawPreviewScreen();
		drawObjectsScreen();
	}

	if (drawMode == edit_object_mode)
	{
		drawEditScreen();
		drawSampleScreen();
		drawSpriteList();
	}
	if (drawMode == edit_scene_mode)
	{
		drawSceneScreen();
	}
	if (drawMode == edit_animate_mode)
	{
		drawSpriteList();
		drawAnimateObject();
		drawSampleScreen();
	}
	if (drawMode == edit_damaku_mode)
	{
		drawDamaKuScreen();
		drawSpriteList();
		drawSampleScreen();
	}
	if (drawMode == edit_enemy_mode)
	{
		m_enemyEditor.draw(m_spriteBatch,m_debug);
	}
	if (drawMode == edit_lua_mode)
	{
		m_luaEditor.draw(m_spriteBatch, m_debug);
	}

	glViewport(0, 0, 1600, 900);
	m_spriteListShader.use();

	GLint textureUniform = m_spriteListShader.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	glActiveTexture(GL_TEXTURE0);

	GLint pUniform = m_spriteListShader.getUniformLocation("P");
	glm::mat4 previewMatrix = m_fullCam.getCameraMatrix();
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &previewMatrix[0][0]);

	m_spriteBatch.begin(Feintgine::GlyphSortType::FRONT_TO_BACK);
	if (drawMode == edit_scene_mode)
	{
		m_sceneManager.drawIcons(m_spriteBatch);
	}

	m_spriteBatch.end();
	m_spriteBatch.renderBatch();

	m_spriteListShader.unuse();
	

	if (drawMode == edit_scene_mode)
	{
		m_sceneManager.drawIconsBorder(m_debug);
	}
	m_debug.end();
	m_debug.render(previewMatrix, 2.0f);

	SDL_GL_SetSwapInterval(1);
	
	

	m_textRenderer.renderText(m_fullCam, 
		L"FPS :" + 
		feint_common::Instance()->convertStringtoWstring(feint_common::
			Instance()->convertPreciousFloatToString(m_game->getFps())),
		glm::vec2(720, -400), Feintgine::Color(255, 255, 255, 255), 1, ALIGN_FT_CENTER);

	glm::vec2 curPos = m_sceneCamera.convertScreenToWorld(m_game->getInputManager().getMouseCoords(),
		glm::vec2(SceneScreen.x, SceneScreen.y), glm::vec2(m_window->getScreenWidth(), m_window->getScreenHeight()));


	
	//std::string narrow = converter.to_bytes(wide_utf16_source_string);
	//feint_common::Instance()->con	
	//std::wstring l_x = feint_common::Instance()->convertStringtoWstring(feint_common::Instance()->convertPreciousFloatToString(curPos.x));
	//std::wstring l_y = feint_common::Instance()->convertStringtoWstring(feint_common::Instance()->convertPreciousFloatToString(curPos.y));

// 	m_textRenderer.renderText(m_fullCam, L"X :" + l_x
// 		, glm::vec2(0, -430), Feintgine::Color(255, 255, 255, 255), 1, ALIGN_FT_LEFT);
// 
// 	m_textRenderer.renderText(m_fullCam, L"Y :" + l_y
// 		, glm::vec2(150, -430), Feintgine::Color(255, 255, 255, 255), 1, ALIGN_FT_LEFT);

	m_gui.draw();



	

}

void EditorScreen::initShader()
{
	m_editObjectShader.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
	m_editObjectShader.addAttribute("vertexPosition");
	m_editObjectShader.addAttribute("vertexColor");
	m_editObjectShader.addAttribute("vertexUV");
	m_editObjectShader.linkShaders();

	m_previewObjectShader.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
	m_previewObjectShader.addAttribute("vertexPosition");
	m_previewObjectShader.addAttribute("vertexColor");
	m_previewObjectShader.addAttribute("vertexUV");
	m_previewObjectShader.linkShaders();

	m_spriteListShader.compileShaders("Shaders/editor.vert", "Shaders/editor.frag");
	m_spriteListShader.addAttribute("vertexPosition");
	m_spriteListShader.addAttribute("vertexColor");
	m_spriteListShader.addAttribute("vertexUV");
	m_spriteListShader.linkShaders();

	m_lightBatch.initShader(&m_editObjectShader);

	m_editDamakuShader.compileShaders("Shaders/editor.vert", "Shaders/editor.frag");
	m_editDamakuShader.addAttribute("vertexPosition");
	m_editDamakuShader.addAttribute("vertexColor");
	m_editDamakuShader.addAttribute("vertexUV");
	m_editDamakuShader.linkShaders();

	m_enemyEditor.loadShader("Shaders/textureShading.vert", "Shaders/textureShading.frag");
	m_luaEditor.loadShader("Shaders/textureShading.vert", "Shaders/textureShading.frag");

// 	m_sceneShader.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
// 	m_sceneShader.addAttribute("vertexPosition");
// 	m_sceneShader.addAttribute("vertexColor");
// 	m_sceneShader.addAttribute("vertexUV");
// 	m_sceneShader.linkShaders();

	m_alpha = 1;
}

void EditorScreen::checkInput()
{
	
	//SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{
		m_gui.onSDLEvent(evnt);
		m_game->onSDLEvent(evnt);
			switch (evnt.type)
			{
			case SDL_MOUSEMOTION:
			{
				mouseMove = true;

				if (m_move)
				{
				
					if (currentCam)
					{
						if (currentCam != &m_objectsCamera)
						{
							currentCam->move(-glm::vec2(evnt.motion.xrel, -evnt.motion.yrel));
							currentCam->update();

						}
						
					}
									
				}
			}
			break;

			case SDL_MOUSEWHEEL:
			{
				if (currentCam && currentCam != &m_objectsCamera)
				{
					if (evnt.wheel.y > 0)
					{
						
						currentCam->setScale(currentCam->getScale() *1.1f);
					}
					else
					{
						currentCam->setScale(currentCam->getScale() *0.9f);

					}
				}
				if (currentCam)
				{
					currentCam->update();
				}
				
			}
			break;

			default:
				mouseMove = false;
				break;
			}
	}	
	handleInput(m_game->m_inputManager);
}

void EditorScreen::handleInput(Feintgine::InputManager & inputManager)
{
	m_luaEditor.handleInput(inputManager);
	m_tileStack.handleInput(inputManager);
	m_spriteListDisplayer.handleInput(inputManager, m_spriteListCamera.convertScreenToWorldViewPort(inputManager.getMouseCoords(),
		glm::vec2(SpriteListScreen.x, SpriteListScreen.y),glm::vec2(m_window->getScreenWidth(),m_window->getScreenHeight())));

	m_objectHolder.handleInput(inputManager, m_objectsCamera.convertScreenToWorldViewPort(inputManager.getMouseCoords(),
		glm::vec2(ObjectsScreen.x, ObjectsScreen.y), glm::vec2(m_window->getScreenWidth(), m_window->getScreenHeight())));

	m_buildObjectTool.handleInput(inputManager);
	// I don't understand this shit either
	//glm::vec2 offsetValue = glm::vec2(-1430, -10);
	//m_spriteListDisplayer.update(m_spriteListCamera.convertScreenToWorld(inputManager.getMouseCoords() + screen_offset));
	//m_spriteListDisplayer.update(m_spriteListCamera.converWorldToScreen(inputManager.getMouseCoords() + offsetValue));
	/*m_spriteListDisplayer.update(m_spriteListCamera.convertScreenToWorld(inputManager.getMouseCoords()));*/
	//glm::vec2 object_screen_offset = glm::vec2(-60, -60);

// 	if (inputManager.isKeyPressed(SDLK_TAB))
// 	{
// 		if (objectiveMode == OBJECTIVE_OBJECT)
// 		{
// 			objectiveMode = OBJECTIVE_BRUSH;
// 		}
// 		else
// 		{
// 			objectiveMode = OBJECTIVE_OBJECT;
// 		}
// 	}

	if (inputManager.isKeyPressed(SDLK_F5))
	{
		std::cout << "refresh \n";
		m_objectHolder.loadList();
		//m_buildingObject.loadFromFile("E:/template/my_last/GC3/Editor/Assets/F_Objects/demo.fob");
		//m_buildObjectTool.loadObject(&m_buildingObject);
	}

	if(drawMode == edit_animate_mode)
	{

		if (!animation_anim_offset_textbox_x->hasInputFocus() && !animation_anim_offset_textbox_y->hasInputFocus())
		{

			if (inputManager.isKeyPressed(SDLK_LEFT))
			{
				animation_slide->scrollBackwardsByStep();
			}
			if (inputManager.isKeyPressed(SDLK_RIGHT))
			{
				animation_slide->scrollForwardsByStep();
			}
		
			if(inputManager.isKeyPressed(SDLK_SPACE))
			{
				togglePlayAnimation();
			}
		}
	}
	if (inputManager.isKeyPressed(SDLK_TAB))
	{
		toggetDebugTiles();
		
	}

	//m_buildObjectTool.handleInput(inputManager, m_camera.convertScreenToWorld(inputManager.getMouseCoords()) + object_screen_offset);
	if (inputManager.isKeyDown(SDLK_LCTRL))
	{
		if (inputManager.isKeyPressed(SDLK_s))
		{
			save_wat();
		}
	}
	if (inputManager.isKeyDown(SDLK_LALT))
	{
		if (inputManager.isKeyPressed(SDLK_1))
		{
			switchScreen(T_EDIT_SCREEN_MODE);
		}
		if (inputManager.isKeyPressed(SDLK_2))
		{
			
			switchScreen(T_EDIT_OJECT_MODE);
		}
		if (inputManager.isKeyPressed(SDLK_3))
		{
			switchScreen(T_EDIT_ANIMATE_MODE);
		}
		if (inputManager.isKeyPressed(SDLK_4))
		{
			switchScreen(T_EDIT_DAMAKU_MODE);
		}
		if (inputManager.isKeyPressed(SDLK_5))
		{
			switchScreen(T_EDIT_ENEMY_MODE);
		}
		if (inputManager.isKeyPressed(SDLK_6))
		{
			switchScreen(T_EDIT_LUA_MODE);
		}

	}

	if (currentCam)
	{
			
			if (inputManager.isKeyPressed(SDLK_x))
			{
				//currentCam->setPosition(glm::vec2(0));
				if (currentCam == &m_camera)
				{
					currentCam->setScale(DEFAULT_OBJECT_CAM_SCALE);
				}
				else
				{
					currentCam->setScale(1.0f);
				}		
			}
	
			if (inputManager.isKeyPressed(SDLK_z))
			{
				currentCam->setPosition(glm::vec2(0));
			}
		
	}
	if (isInsideScreen(inputManager.getMouseCoords(), EditScreen) && drawMode == edit_object_mode)
	{
		//std::cout << "m_camera \n";
		currentCam = &m_camera;
	
		glm::vec2 converted;
		converted.x = currentCam->convertScreenToWorld(inputManager.getMouseCoords()).x - (EditScreen.x / currentCam->getScale());
		float invertY = m_window->getScreenHeight() - EditScreen.w - EditScreen.y;
		converted.y = (currentCam->convertScreenToWorld(inputManager.getMouseCoords()).y) + ((invertY) / currentCam->getScale());
		
	
	}
	else if (isInsideScreen(inputManager.getMouseCoords(), AnimateScreen) && drawMode == edit_animate_mode )
	{
		//std::cout << "m_animatingCamera \n";
		currentCam = &m_animatingCamera;

		//currentCam = &m_camera;
		glm::vec2 converted;
		converted.x = currentCam->convertScreenToWorld(inputManager.getMouseCoords()).x - (AnimateScreen.x / currentCam->getScale());
		float invertY = m_window->getScreenHeight() - AnimateScreen.w - AnimateScreen.y;
		converted.y = (currentCam->convertScreenToWorld(inputManager.getMouseCoords()).y) + ((invertY) / currentCam->getScale());
		

	}
	else if (isInsideScreen(inputManager.getMouseCoords(), EditLua) && drawMode == edit_lua_mode)
	{
		//std::cout << "m_animatingCamera \n";
		currentCam = &m_editLuaCamera;

		//currentCam = &m_camera;
		glm::vec2 converted;
		converted.x = currentCam->convertScreenToWorld(inputManager.getMouseCoords()).x - (AnimateScreen.x / currentCam->getScale());
		float invertY = m_window->getScreenHeight() - AnimateScreen.w - AnimateScreen.y;
		converted.y = (currentCam->convertScreenToWorld(inputManager.getMouseCoords()).y) + ((invertY) / currentCam->getScale());


	}
	else if (isInsideScreen(inputManager.getMouseCoords(), SampleSceen) )
	{
		//std::cout << "m_sampleCam \n";
		currentCam = &m_sampleCam;
		glm::vec2 converted;
		converted.x = currentCam->convertScreenToWorld(inputManager.getMouseCoords()).x - (SampleSceen.x / currentCam->getScale());
		float invertY = m_window->getScreenHeight() - SampleSceen.w - SampleSceen.y;
		converted.y = (currentCam->convertScreenToWorld(inputManager.getMouseCoords()).y) + ((invertY) / currentCam->getScale());
		bool isModify = false;
		//converted.y = SampleSceen.w - converted.y;

	

		//Delete Collider 
		if (inputManager.isKeyPressed(SDLK_DELETE))
		{
			if (m_currentCol)
			{
				
				DestroyColider();
			}
		}


		if (inputManager.isKeyPressed(SDL_BUTTON_LEFT))
		{
			
			
		
	
		}	
		if (inputManager.isKeyDown(SDL_BUTTON_LEFT))
		{
			
				
		}
		else
		{
	
		}
	
		
		
	}
	else if (isInsideScreen(inputManager.getMouseCoords(), ObjectsScreen) && drawMode == edit_scene_mode \
		|| isInsideScreen(inputManager.getMouseCoords(), ObjectsScreen) && drawMode == edit_object_mode)
	{
		//std::cout << "m_objectsCamera \n";
		currentCam = &m_objectsCamera;
		glm::vec2 converted;
		converted.x = currentCam->convertScreenToWorld(inputManager.getMouseCoords()).x - (ObjectsScreen.x / currentCam->getScale());
		float invertY = m_window->getScreenHeight() - ObjectsScreen.w - ObjectsScreen.y;
		converted.y = (currentCam->convertScreenToWorld(inputManager.getMouseCoords()).y) + ((invertY) / currentCam->getScale());

		for (int i = 0; i < m_slots.size(); i++)
		{
			if (m_slots[i].onHover(converted))
			{
				if (inputManager.isKeyPressed(SDL_BUTTON_LEFT))
				{
					selectItemFromTempalte(converted);
				}
			}

		}
		
	}
	else if(isInsideScreen(inputManager.getMouseCoords(), PreviewScreen) && drawMode == edit_scene_mode \
		|| isInsideScreen(inputManager.getMouseCoords(), PreviewScreen) && drawMode == edit_object_mode)
	{
		//std::cout << "m_previewCamera \n";
		currentCam = &m_previewCamera;
		glm::vec2 converted;
		converted.x = currentCam->convertScreenToWorld(inputManager.getMouseCoords()).x - (PreviewScreen.x / currentCam->getScale());
		float invertY = m_window->getScreenHeight() - PreviewScreen.w - PreviewScreen.y;
		converted.y = (currentCam->convertScreenToWorld(inputManager.getMouseCoords()).y) + ((invertY) / currentCam->getScale());
	}
	else if (isInsideScreen(inputManager.getMouseCoords(), EditDamaku) && drawMode == edit_damaku_mode)
	{

		//std::cout << "m_editDamakuCamera \n";
		currentCam = &m_editDamakuCamera;

		glm::vec2 converted;
		converted.x = currentCam->convertScreenToWorld(inputManager.getMouseCoords()).x - (EditDamaku.x / currentCam->getScale());
		float invertY = m_window->getScreenHeight() - EditDamaku.w - EditDamaku.y;
		converted.y = (currentCam->convertScreenToWorld(inputManager.getMouseCoords()).y) + ((invertY) / currentCam->getScale());
		
	}
	else if (isInsideScreen(inputManager.getMouseCoords(), EditEnemy) && drawMode == edit_enemy_mode)
	{
		currentCam = &m_editEnemyCamera;

		glm::vec2 converted;
		converted.x = currentCam->convertScreenToWorld(inputManager.getMouseCoords()).x - (EditEnemy.x / currentCam->getScale());
		float invertY = m_window->getScreenHeight() - EditEnemy.w - EditEnemy.y;
		converted.y = (currentCam->convertScreenToWorld(inputManager.getMouseCoords()).y) + ((invertY) / currentCam->getScale());

	}
	else
	{

		for (int i = 0; i < m_slots.size(); i++)
		{
			m_slots[i].onHover(glm::vec2(-1000, -1000));		
		}
		currentCam = nullptr;
		
	}

	if (inputManager.isKeyDown(SDL_BUTTON_RIGHT))
	{
		m_move = true;
	}
	else {
		m_move = false;
	}
		
	
	if (inputManager.isKeyPressed(SDL_QUIT))
	{
		m_currentState = Feintgine::ScreenState::EXIT_APPLICATION;
	}

	handleException(inputManager);
	handleEditScreen(inputManager);
	

	switch (drawMode)
	{
	case edit_enemy_mode:
		m_enemyEditor.handleInput(inputManager);
		break;
	default:
		break;
	}

	//specific screen
	m_paternEditor.handleInput(inputManager);

	//// EXECEPTION

	if (inputManager.isKeyDown(SDL_BUTTON_LEFT))
	{
		m_isMouseLeftHold = true;
	}
	else
	{ 
		m_isMouseLeftHold = false;
	}
	//

	
}

void EditorScreen::initGUI()
{
	m_gui.init("GUI");
	m_gui.loadScheme("TaharezLook.scheme");
	m_gui.loadScheme("VanillaSkin.scheme");
	m_gui.loadScheme("WindowsLook.scheme");
	m_gui.loadScheme("AlfiskoSkin.scheme");
	m_gui.setFont("DejaVuSans-8");
	

	//Load component

	
	initMenuBar();
	initTextureList();
	initEditTool();
	initFilters();
	initLayerList();
	initActionBar();
	initAObjList();
	initAmbientTool();
	
	m_paternEditor.init(&m_gui, &m_spriteListDisplayer);

	m_gui.setMouseCursor("AlfiskoSkin/MouseArrow");
	//m_gui.showMouseCursor();
	SDL_ShowCursor(0);
	hideObjectEditor();

	
	
}

bool EditorScreen::openScene(const CEGUI::EventArgs &e)
{
	
	showFilePicker();
	//m_MenuItem_File->a
	return true;
}

void EditorScreen::showFilePicker()
{
	char filename[MAX_PATH];

	OPENFILENAME ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
	ofn.lpstrFilter = "Feintgine Scene \0*.fsc\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Select the Scence !";
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

	if (GetOpenFileNameA(&ofn))
	{
		std::cout << "You chose the file \"" << filename << "\"\n";
		std::string c_filePath = filename;
		//std::cout << c_filePath.find("Editor") << " con \n";
		//m_scene.loadSceneFromFile(c_filePath);		
		for (int i = 0; i < m_scene->getLayers().size(); i++)
		{
			//addLayerFunc(m_scene.getLayers()[i].getName(), m_scene.getLayers()[i]. ());
		}

	}
	else
	{
		// All this stuff below is to tell you exactly how you messed up above. 
		// Once you've got that fixed, you can often (not always!) reduce it to a 'user cancelled' assumption.
		switch (CommDlgExtendedError())
		{
		case CDERR_DIALOGFAILURE: std::cout << "CDERR_DIALOGFAILURE\n";   break;
		case CDERR_FINDRESFAILURE: std::cout << "CDERR_FINDRESFAILURE\n";  break;
		case CDERR_INITIALIZATION: std::cout << "CDERR_INITIALIZATION\n";  break;
		case CDERR_LOADRESFAILURE: std::cout << "CDERR_LOADRESFAILURE\n";  break;
		case CDERR_LOADSTRFAILURE: std::cout << "CDERR_LOADSTRFAILURE\n";  break;
		case CDERR_LOCKRESFAILURE: std::cout << "CDERR_LOCKRESFAILURE\n";  break;
		case CDERR_MEMALLOCFAILURE: std::cout << "CDERR_MEMALLOCFAILURE\n"; break;
		case CDERR_MEMLOCKFAILURE: std::cout << "CDERR_MEMLOCKFAILURE\n";  break;
		case CDERR_NOHINSTANCE: std::cout << "CDERR_NOHINSTANCE\n";     break;
		case CDERR_NOHOOK: std::cout << "CDERR_NOHOOK\n";          break;
		case CDERR_NOTEMPLATE: std::cout << "CDERR_NOTEMPLATE\n";      break;
		case CDERR_STRUCTSIZE: std::cout << "CDERR_STRUCTSIZE\n";      break;
		case FNERR_BUFFERTOOSMALL: std::cout << "FNERR_BUFFERTOOSMALL\n";  break;
		case FNERR_INVALIDFILENAME: std::cout << "FNERR_INVALIDFILENAME\n"; break;
		case FNERR_SUBCLASSFAILURE: std::cout << "FNERR_SUBCLASSFAILURE\n"; break;
		default: std::cout << "You cancelled.\n";
		}
	}
}

void EditorScreen::initMenuBar()
{
	m_MenuBar = static_cast<CEGUI::Menubar*>(m_gui.createWidget("TaharezLook/Menubar", glm::vec4(0.2f, 0.01f, .5f, 0.03f), glm::vec4(0.0f), "MenuBar"));
	CEGUI::MenuItem *m_MenuItem_File = static_cast<CEGUI::MenuItem*>(m_gui.createWidget("TaharezLook/MenuItem", glm::vec4(0, 0, 0.4, .85f), glm::vec4(0.0f), "Menu_Item_File"));
	CEGUI::MenuItem *m_MenuItem_Edit = static_cast<CEGUI::MenuItem*>(m_gui.createWidget("TaharezLook/MenuItem", glm::vec4(0, 0, 0.4, .85f), glm::vec4(0.0f), "Menu_Item_Edit"));
	CEGUI::MenuItem *m_MenuItem_Object = static_cast<CEGUI::MenuItem*>(m_gui.createWidget("TaharezLook/MenuItem", glm::vec4(0, 0, 0.4, .85f), glm::vec4(0.0f), "Menu_Item_Object"));
	CEGUI::MenuItem *m_MenuItem_Animate = static_cast<CEGUI::MenuItem*>(m_gui.createWidget("TaharezLook/MenuItem", glm::vec4(0, 0, 0.4, .85f), glm::vec4(0.0f), "Menu_Item_Animate_Object"));
	File_Popup = static_cast<CEGUI::PopupMenu*>(m_gui.createWidget("TaharezLook/PopupMenu", glm::vec4(1), glm::vec4(0), "File_Popup"));
	Edit_Popup = static_cast<CEGUI::PopupMenu*>(m_gui.createWidget("TaharezLook/PopupMenu", glm::vec4(1), glm::vec4(0), "Edit_Popup"));
	Object_Popup = static_cast<CEGUI::PopupMenu*>(m_gui.createWidget("TaharezLook/PopupMenu", glm::vec4(1), glm::vec4(0), "Object_Popup"));
	Animate_Popup = static_cast<CEGUI::PopupMenu*>(m_gui.createWidget("TaharezLook/PopupMenu", glm::vec4(1), glm::vec4(0), "Animate_Popup"));
	
	//CEGUI::Window *myImageWindow = static_cast<CEGUI::Window*>(m_gui.createWidget("TaharezLook/StaticImage", glm::vec4(0.5, 0.5, 0.4, .85f), glm::vec4(0.0f),"PrettyWindow"));
	//File Menu======================

	//CEGUI::ImageManager::getSingleton().loadImageset("green.imageset");
	//myImageWindow->setProperty("Image", "green/cliff_big.png");
	CEGUI::MenuItem *new_scene = static_cast<CEGUI::MenuItem*> (CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/MenuItem", "File_Item_New"));
	new_scene->setText("New Scene");

	CEGUI::MenuItem *save_scence = static_cast<CEGUI::MenuItem*> (CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/MenuItem", "File_Item_Save"));
	save_scence->setText("Save");

	CEGUI::MenuItem *save_as = static_cast<CEGUI::MenuItem*> (CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/MenuItem", "File_Item_Save_As"));
	save_as->setText("Save As");

	CEGUI::MenuItem *open_scene = static_cast<CEGUI::MenuItem*> (CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/MenuItem", "File_Item_Open"));
	open_scene->setText("Open Scene");

	
	 CEGUI::MenuItem *exit_editor = static_cast<CEGUI::MenuItem*> (CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/MenuItem", "File_Exit"));
	exit_editor->setText("Exit");
	//-------------------------

	File_Popup->addItem(new_scene);
	File_Popup->addItem(open_scene);
	File_Popup->addItem(save_scence);
	File_Popup->addItem(save_as);
	File_Popup->addItem(exit_editor);

	//===============================

	//Edit Menu==============
	
	CEGUI::MenuItem *edit_scene = static_cast<CEGUI::MenuItem*> (CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/MenuItem", "Edit_Scene"));
	edit_scene->setText("Edit Scene");

	
	CEGUI::MenuItem * edit_object = static_cast<CEGUI::MenuItem*> (CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/MenuItem", "Edit_Object"));
	edit_object->setText("Edit Object");


	CEGUI::MenuItem * edit_animate = static_cast<CEGUI::MenuItem*> (CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/MenuItem", "Edit_Animate"));
	edit_animate->setText("Edit Animate Object");


	CEGUI::MenuItem * edit_danmaku = static_cast<CEGUI::MenuItem*> (CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/MenuItem", "Edit_Danmaku"));
	edit_danmaku->setText("Edit Danmaku");

	CEGUI::MenuItem * edit_enemies = static_cast<CEGUI::MenuItem*> (CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/MenuItem", "Edit_Enemies"));
	edit_enemies->setText("Edit Enemies");


	CEGUI::MenuItem * edit_lua_bosses = static_cast<CEGUI::MenuItem*> (CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/MenuItem", "Edit_Bosses"));
	edit_lua_bosses->setText("Edit Bosses");

	//------------------------

	Edit_Popup->addItem(edit_scene);
	Edit_Popup->addItem(edit_object);
	Edit_Popup->addItem(edit_animate);
	Edit_Popup->addItem(edit_danmaku);
	Edit_Popup->addItem(edit_enemies);
	Edit_Popup->addItem(edit_lua_bosses);
	
	//=======================

	//Object Menu 
	CEGUI::MenuItem *new_object = static_cast<CEGUI::MenuItem*> (CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/MenuItem", "Object_File_new"));
	new_object->setText("New Object");
	//---
	Object_Popup->addItem(new_object);

	//==========

	//Animate Object
	//==========
	CEGUI::MenuItem *new_animate_obj = static_cast<CEGUI::MenuItem*> (CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/MenuItem", "new_animate_obj"));
	new_animate_obj->setText("New Object");

	Animate_Popup->addItem(new_animate_obj);


	//==========

	m_MenuItem_File->setText("File");
	m_MenuItem_Edit->setText("Edit");
	m_MenuItem_Object->setText("Object");
	m_MenuItem_Animate->setText("Animated");

	//----------------------
	m_MenuItem_File->addChild(File_Popup);
	m_MenuItem_Edit->addChild(Edit_Popup);
	m_MenuItem_Object->addChild(Object_Popup);
	m_MenuItem_Animate->addChild(Animate_Popup);
	//------------
	m_MenuBar->addItem(m_MenuItem_File);
	m_MenuBar->addItem(m_MenuItem_Edit);
	m_MenuBar->addItem(m_MenuItem_Object);
	m_MenuBar->addItem(m_MenuItem_Animate);

	//-------------------------




	new_scene->subscribeEvent(CEGUI::DefaultWindow::EventMouseClick, CEGUI::Event::Subscriber(&EditorScreen::scene_create_protocol, this));
	open_scene->subscribeEvent(CEGUI::DefaultWindow::EventMouseClick, CEGUI::Event::Subscriber(&EditorScreen::scene_select_protocol, this));
	save_as->subscribeEvent(CEGUI::DefaultWindow::EventMouseClick, CEGUI::Event::Subscriber(&EditorScreen::save_as, this));
	save_scence->subscribeEvent(CEGUI::DefaultWindow::EventMouseClick, CEGUI::Event::Subscriber(&EditorScreen::save, this));
	exit_editor->subscribeEvent(CEGUI::DefaultWindow::EventMouseClick, CEGUI::Event::Subscriber(&EditorScreen::exitEditor, this));
	new_object->subscribeEvent(CEGUI::DefaultWindow::EventMouseClick, CEGUI::Event::Subscriber(&EditorScreen::createObject, this));

	edit_object->subscribeEvent(CEGUI::DefaultWindow::EventMouseClick, CEGUI::Event::Subscriber(&EditorScreen::changeToEditObject, this));
	edit_animate->subscribeEvent(CEGUI::DefaultWindow::EventMouseClick, CEGUI::Event::Subscriber(&EditorScreen::changeToEditAnimate, this));
	edit_scene->subscribeEvent(CEGUI::DefaultWindow::EventMouseClick, CEGUI::Event::Subscriber(&EditorScreen::changeToEditScene, this));
	edit_danmaku->subscribeEvent(CEGUI::DefaultWindow::EventMouseClick, CEGUI::Event::Subscriber(&EditorScreen::changeToEditDamaku, this));
	edit_enemies->subscribeEvent(CEGUI::DefaultWindow::EventMouseClick, CEGUI::Event::Subscriber(&EditorScreen::changeToEditEnemy, this));
	edit_lua_bosses->subscribeEvent(CEGUI::DefaultWindow::EventMouseClick, CEGUI::Event::Subscriber(&EditorScreen::changeToEditLua, this));



}

bool EditorScreen::exitEditor(const CEGUI::EventArgs &e)
{
	exit(1);
	return true;
}

void EditorScreen::readFile()
{
	DIR *pdir = NULL; // remember, it's good practice to initialise a pointer to NULL!
	pdir = opendir("./Assets"); // "." will refer to the current directory
	struct dirent *pent = NULL;

	// I used the current directory, since this is one which will apply to anyone reading
	// this tutorial~ If I said "C:\\" and you're on Linux, it may get a little confusing!
	if (pdir == NULL) // if pdir wasn't initialised correctly
	{ // print an error message and exit the program
		std::cout << "\nERROR! pdir could not be initialised correctly \n";
		exit(3);
	} // end if

	while (pent = readdir(pdir)) // while there is still something in the directory to list
	{
		if (pent == NULL) // if pent has not been initialised correctly
		{ // print an error message, and exit the program
			std::cout << "\nERROR! pent could not be initialised correctly \n";
			exit(3);
		}

		// otherwise, it was initialised correctly. Let's print it on the console:
		std::cout << pent->d_name << "\n";	
	}
	// finally, let's close the directory
	closedir(pdir);
}

void EditorScreen::initTextureList()
{
	listDes = static_cast<CEGUI::DefaultWindow *>(m_gui.createWidget("TaharezLook/Label", glm::vec4(0.33, 0.02f, 0.13, 0.1), glm::vec4(0), "ListLabel"));
}

void EditorScreen::initAObjList()
{
	m_AObjList = static_cast<CEGUI::Listbox*> (m_gui.createWidget("TaharezLook/Listbox",
		glm::vec4(0.01, 0.08, 0.12, 0.6), glm::vec4(0), "AObjList"));

	m_AObjList->subscribeEvent(CEGUI::Listbox::EventMouseDoubleClick,
		CEGUI::Event::Subscriber(&EditorScreen::pickAobj, this));

	m_AObjList->subscribeEvent(CEGUI::Listbox::EventMouseClick,
		CEGUI::Event::Subscriber(&EditorScreen::onAnimationListChange, this));

	m_actionList = static_cast<CEGUI::Listbox*> (m_gui.createWidget("TaharezLook/Listbox",
		glm::vec4(0.44, 0.07, 0.15, 0.55), glm::vec4(0), "ActionList"));

	m_actionList->subscribeEvent(CEGUI::Listbox::EventMouseDoubleClick, 
		CEGUI::Event::Subscriber(&EditorScreen::selectAction, this));
	m_actionList->subscribeEvent(CEGUI::Listbox::EventListContentsChanged,
		CEGUI::Event::Subscriber(&EditorScreen::onListActionChangedEvent, this));

	m_actionLabel = static_cast<CEGUI::DefaultWindow *>(m_gui.createWidget("TaharezLook/Label",
		glm::vec4(0.44, .033f, 0.14, 0.03), glm::vec4(0), "ActionList_Label"));
	m_actionLabel->setText("Action List");

	//Slide

	animation_addNewAnimation = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button",
		glm::vec4(0.015, 0.02, 0.095, 0.04), glm::vec4(0), "animation_addNewAnimation"));
	animation_addNewAnimation->setText("New Animation");


	animation_deleteAnimation = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button",
		glm::vec4(0.015, 0.7, 0.095, 0.04), glm::vec4(0), "animation_deleteAnimation"));
	animation_deleteAnimation->setText("Delete Animation");

	animation_slide = static_cast<CEGUI::Scrollbar *> (m_gui.createWidget("TaharezLook/HorizontalScrollbar",
		glm::vec4(0.16f, 0.75f, 0.2, 0.02), glm::vec4(0), "animation_slide"));
	
	playAnimation_button = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button",
		glm::vec4(0.17, 0.8, 0.04, 0.04), glm::vec4(0), "playAnimation_button"));
	playAnimation_button->setText("  >  ");
	
	pauseAnimation_button = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button", 
		glm::vec4(0.24, 0.8, 0.04, 0.04), glm::vec4(0), "pauseAnimation_button"));
	pauseAnimation_button->setText(" || ");

	stopAnimation_button = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button",
		glm::vec4(0.31, 0.8, 0.04, 0.04), glm::vec4(0), "stopAnimation_button"));
	stopAnimation_button->setText(" <> ");

	animation_addAnim = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button",
		glm::vec4(0.37, 0.73, 0.04, 0.04), glm::vec4(0), "animation_addAnim"));
	animation_addAnim->setText(" + ");

	animation_removeAnim = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button",
		glm::vec4(0.37, 0.78, 0.04, 0.04), glm::vec4(0), "animation_removeAnim"));
	animation_removeAnim->setText(" - ");

	animation_applySprite = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button",
		glm::vec4(0.615, 0.28, 0.07, 0.04), glm::vec4(0), "animation_applySprite"));
	animation_applySprite->setText("Apply to Anim");

	animation_saveAnimation = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button",
		glm::vec4(0.47, 0.71, 0.09, 0.04), glm::vec4(0), "animation_saveAnimation"));
	animation_saveAnimation->setText("Save to File");

	animation_newAction = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button",
		glm::vec4(0.43, 0.64, 0.08, 0.04), glm::vec4(0), "animation_newAction"));
	animation_newAction->setText("New Action");

	animation_deleteAction = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button",
		glm::vec4(0.52, 0.64, 0.08, 0.04), glm::vec4(0), "animation_deleteAction"));
	animation_deleteAction->setText("Delete Action");

	animation_index_label = static_cast<CEGUI::DefaultWindow *> (m_gui.createWidget("TaharezLook/Label",
		glm::vec4(0.21, 0.7, 0.12, 0.075), glm::vec4(0), "animation_index_label"));
	animation_index_label->setText("0/0");

	animation_tick_textbox = static_cast<CEGUI::Editbox *>(m_gui.createWidget("TaharezLook/Editbox",
		glm::vec4(0.17, 0.575, 0.05, 0.03), glm::vec4(0), "animation_tick_textbox"));
	animation_tick_textbox->setValidationString("^[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+){0,10}$");
	//^[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+){0,10}$
  	animation_tick_textbox->subscribeEvent(CEGUI::Editbox::EventDeactivated,
  		CEGUI::Event::Subscriber(&EditorScreen::recheckTick, this));

	animation_sprite_label = static_cast<CEGUI::DefaultWindow *> (m_gui.createWidget("TaharezLook/Label",
		glm::vec4(0.25, 0.55, 0.2, 0.075), glm::vec4(0), "animation_sprite_label"));
	animation_sprite_label->setText("None");

	animation_tick_textbox->subscribeEvent(CEGUI::Editbox::EventKeyUp,
		CEGUI::Event::Subscriber(&EditorScreen::updateAnimTick, this));

	animation_tick_label = static_cast<CEGUI::DefaultWindow *> (m_gui.createWidget("TaharezLook/Label",
		glm::vec4(0.13, 0.55, 0.05, 0.075), glm::vec4(0), "animation_tick_label"));
	animation_tick_label->setText("Tick");

	animation_slide->getDecreaseButton()->setWidth(CEGUI::UDim(0.05f, 1.0f));
	//someSlide->getDecreaseButton()->setXPosition(CEGUI::UDim(-0.01f, 1.0f));
	animation_slide->getIncreaseButton()->setWidth(CEGUI::UDim(0.05f, 1.0f));
	//someSlide->getIncreaseButton()->setXPosition(CEGUI::UDim(1.01f, 1.0f));
	playAnimation_button->subscribeEvent(CEGUI::PushButton::EventClicked, 
		CEGUI::Event::Subscriber(&EditorScreen::playAnimation, this));
	pauseAnimation_button->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&EditorScreen::pauseAnimation, this));
	stopAnimation_button->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&EditorScreen::stopAnimation, this));
	animation_slide->subscribeEvent(CEGUI::Scrollbar::EventThumbTrackEnded,
		CEGUI::Event::Subscriber(&EditorScreen::fixAnimationScroll, this));
	animation_slide->subscribeEvent(CEGUI::Scrollbar::EventScrollPositionChanged, 
		CEGUI::Event::Subscriber(&EditorScreen::updateAnimation, this));


	animation_saveAnimation->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&EditorScreen::saveAnimation, this));

	animation_newAction->subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&EditorScreen::action_new_protocol, this));


	animation_deleteAction->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&EditorScreen::onDeleteActionButtonClicked, this));

	animation_addAnim->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&EditorScreen::onAddAnimButtonClicked, this));

	animation_removeAnim->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&EditorScreen::onRemoveAnimButtonCLicked, this));

	animation_applySprite->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&EditorScreen::onApplyToCurrentAnimButtonCLicked, this));

	animation_addNewAnimation->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&EditorScreen::animation_new_protocol, this));

	animation_deleteAnimation->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&EditorScreen::onAnimationDeleteClick, this));
	
	animation_enableLoop_toggle = static_cast<CEGUI::ToggleButton *>
		(m_gui.createWidget("TaharezLook/Checkbox", glm::vec4(0.115, 0.775, 0.05, 0.05),
			glm::vec4(0), "enableLoop_toggle"));
	animation_enableLoop_toggle->subscribeEvent(CEGUI::ToggleButton::EventMouseClick, 
		CEGUI::Event::Subscriber(&EditorScreen::onLoopToggle, this));

	enableLoop_toggle_label = static_cast<CEGUI::DefaultWindow *>(m_gui.createWidget("TaharezLook/Label",
		glm::vec4(0.05, 0.75, 0.14, 0.03), glm::vec4(0), "enableLoop_toggle_label"));
	enableLoop_toggle_label->setText("Enable Loop");

	animation_markAsLoop_toggle = static_cast<CEGUI::ToggleButton *>
		(m_gui.createWidget("TaharezLook/Checkbox", glm::vec4(0.175, 0.645, 0.05, 0.05),
			glm::vec4(0), "animation_markAsLoop_toggle"));

	animation_markAsLoop_toggle->subscribeEvent(CEGUI::ToggleButton::EventMouseEntersSurface,
		CEGUI::Event::Subscriber(&EditorScreen::onMarkReady, this));

	animation_isSpriteInverted = static_cast<CEGUI::ToggleButton *>
		(m_gui.createWidget("TaharezLook/Checkbox", glm::vec4(0.35, 0.62, 0.1, 0.1), glm::vec4(0), "animation_isSpriteInverted"));
	animation_isSpriteInverted->subscribeEvent(CEGUI::ToggleButton::EventMouseClick, CEGUI::Event::Subscriber(&EditorScreen::onSpriteInvertToggleBoxClicked, this));
	animation_isSpriteInverted->setText("Is Inverted");


	animation_markAsLoop_toggle->subscribeEvent(CEGUI::ToggleButton::EventMouseLeavesSurface,
		CEGUI::Event::Subscriber(&EditorScreen::onMarkAsStop, this));

	animation_markAsLoop_toggle->subscribeEvent(CEGUI::ToggleButton::EventSelectStateChanged,
 		CEGUI::Event::Subscriber(&EditorScreen::onMarkAsLoopToggled, this));

	animation_markAsLoop_label = static_cast<CEGUI::DefaultWindow *>(m_gui.createWidget("TaharezLook/Label",
		glm::vec4(0.11, 0.62, 0.1, 0.03), glm::vec4(0), "animation_markAsLoop_label"));
	animation_markAsLoop_label->setText("Mark as loop");
	
	animation_applySprite->setEnabled(false);

	animation_deleteAnimation->setEnabled(false);

	animation_newAction->setEnabled(false);

	// Offset init 

	animation_anim_offset_label = static_cast<CEGUI::DefaultWindow *>(m_gui.createWidget("TaharezLook/Label",
		glm::vec4(0.63, 0.55, 0.07, 0.03), glm::vec4(0), "animation_anim_offset_label"));
	animation_anim_offset_label->setText("Offset Pos");

	animation_anim_offset_textbox_x = static_cast<CEGUI::Editbox *>(m_gui.createWidget("TaharezLook/Editbox",
		glm::vec4(0.7, 0.55, 0.05, 0.03), glm::vec4(0), "animation_anim_offset_textbox_x"));

	animation_anim_offset_textbox_y = static_cast<CEGUI::Editbox *>(m_gui.createWidget("TaharezLook/Editbox",
		glm::vec4(0.76, 0.55, 0.05, 0.03), glm::vec4(0), "animation_anim_offset_textbox_y"));

	animation_anim_offset_textbox_x->setText("0.0");
	animation_anim_offset_textbox_y->setText("0.0");

	animation_anim_offset_textbox_x->setValidationString("^[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+){0,10}$");
	animation_anim_offset_textbox_y->setValidationString("^[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+){0,10}$");

	animation_anim_offset_textbox_x->subscribeEvent(CEGUI::Editbox::EventTextChanged,
		CEGUI::Event::Subscriber(&EditorScreen::onOffsetAnimationChangedX, this));

	animation_anim_offset_textbox_y->subscribeEvent(CEGUI::Editbox::EventTextChanged,
		CEGUI::Event::Subscriber(&EditorScreen::onOffsetAnimationChangedY, this));

	animation_anim_offset_button_up = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button",
		glm::vec4(0.7, 0.63, 0.04, 0.04), glm::vec4(0), "animation_anim_offset_button_up"));
	animation_anim_offset_button_up->setText(feint_common::Instance()->WCharToUTF8(L"▲"));

	animation_anim_offset_button_down = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button",
		glm::vec4(0.7, 0.72, 0.04, 0.04), glm::vec4(0), "animation_anim_offset_button_down"));
	animation_anim_offset_button_down->setText(feint_common::Instance()->WCharToUTF8(L"▼"));

	animation_anim_offset_button_left = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button",
		glm::vec4(0.67, 0.675, 0.04, 0.04), glm::vec4(0), "animation_anim_offset_button_left"));

	animation_anim_offset_button_left->setText(feint_common::Instance()->WCharToUTF8(L"◄"));

	animation_anim_offset_button_right = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button",
		glm::vec4(0.73, 0.675, 0.04, 0.04), glm::vec4(0), "animation_anim_offset_button_right"));
	animation_anim_offset_button_right->setText(feint_common::Instance()->WCharToUTF8(L"►"));



	animation_anim_offset_button_up->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&EditorScreen::onOffsetPosChangedUp, this));

	animation_anim_offset_button_down->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&EditorScreen::onOffsetPosChangedDown, this));

	animation_anim_offset_button_left->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&EditorScreen::onOffsetPosChangedLeft, this));

	animation_anim_offset_button_right->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&EditorScreen::onOffsetPosChangedRight, this));

	//


}

void EditorScreen::refresh()
{
	//clear item from TextureList before refresh
	m_slots.clear();
	
	m_templateList.clear();
	m_AObjList->resetList();
	m_actionList->resetList();
	//=============================
	initSlot();

	//std::string refeshDir = ExePath();
	//refeshDir.append("/Editor/Assets");
	//listdir(refeshDir.c_str(), 0);
	listdir("./Assets", 0);
	//listDirver2();
	updateList();
	
	
}

bool EditorScreen::isInsideScreen(const glm::vec2 & pos, glm::vec4 t_sc)
{
	float py = m_window->getScreenHeight() - pos.y;
	if (pos.x > t_sc.x && pos.x < t_sc.x + t_sc.z && py> t_sc.y && py < t_sc.y + t_sc.w)
	{
		return true;
	}
	return false;
}

bool EditorScreen::layer_add_protocol(const CEGUI::EventArgs &e)
{
	if (m_sceneManager.getCurrentScene())
	{
		m_addLayerWindow = static_cast<CEGUI::Window*>
			(m_gui.createWidget("TaharezLook/FrameWindow", glm::vec4(0.7, 0.5, 0.3, 0.3), glm::vec4(0), "NewObeject_groupbox"));

		CEGUI::PushButton * AcceptButton = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button", glm::vec4(0.4, 0.8, 0.2, 0.14), glm::vec4(0), "OK_Addlayer_button"));
		AcceptButton->setText("Create");


		AcceptButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&EditorScreen::addLayer, this));
		m_addLayerWindow->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked, CEGUI::Event::Subscriber(&EditorScreen::destroyObjectPannel, this));
		m_addLayerWindow->setText("Add Layer");

		CEGUI::DefaultWindow * edit1_label = static_cast<CEGUI::DefaultWindow *> (m_gui.createWidget("TaharezLook/Label", glm::vec4(0.1, 0.1, 0.12, 0.1), glm::vec4(0), "addlayer_name_label"));
		edit1_label->setText("Name");
		CEGUI::DefaultWindow * edit2_label = static_cast<CEGUI::DefaultWindow *> (m_gui.createWidget("TaharezLook/Label", glm::vec4(0.1, 0.28, 0.12, 0.1), glm::vec4(0), "addlayer_depth_label"));
		edit2_label->setText("Depth");

		m_layerName = static_cast<CEGUI::Editbox *>(m_gui.createWidget("TaharezLook/Editbox", glm::vec4(0.3, 0.1, 0.4, 0.14), glm::vec4(0), "edit_layerName"));
		m_layerDepth = static_cast<CEGUI::Editbox *>(m_gui.createWidget("TaharezLook/Editbox", glm::vec4(0.3, 0.28, 0.4, 0.14), glm::vec4(0), "edit_layerDepth"));

		m_layerDepth->setValidationString("\\d*");

		m_addLayerWindow->addChild(m_layerName);
		m_addLayerWindow->addChild(m_layerDepth);
		m_addLayerWindow->addChild(AcceptButton);
		m_addLayerWindow->addChild(edit1_label);
		m_addLayerWindow->addChild(edit2_label);
	}
	else
	{
		feint_common::Instance()->showMessageBox("Error", "Create the Scene first");
	}
	return true;
}

void EditorScreen::initEditTool()
{

	m_addToObject = dynamic_cast<CEGUI::PushButton *>
		(m_gui.createWidget("TaharezLook/Button", glm::vec4(0.61, 0.28, 0.09, 0.04), glm::vec4(0), "m_addToObject"));
	//m_addToObject->setFont(CEGUI::FontManager::getSingleton().createFromFile("DejaVuSans-8.font").getName());
	m_addToObject->setText("Add to Object");
	m_addToObject->subscribeEvent(CEGUI::PushButton::EventMouseClick, CEGUI::Event::Subscriber(&EditorScreen::addSpriteToObject, this));

// 	name_label = static_cast<CEGUI::DefaultWindow*>
// 		(m_gui.createWidget("TaharezLook/Label", glm::vec4(0.72, 0.51, 0.1, 0.12), glm::vec4(0), "name_label"));
// 	name_label->setText("Object name");
// 	name_label->setProperty("HorzFormatting", "LeftAligned");
// 
// 	 type_label = static_cast<CEGUI::DefaultWindow*>
// 		(m_gui.createWidget("TaharezLook/Label", glm::vec4(0.875, 0.575, 0.1, 0.1), glm::vec4(0), "type_label"));
// 	type_label->setText("Object type");
// 	type_label->setProperty("HorzFormatting", "LeftAligned");
// 
// 
// 	 width_label = static_cast<CEGUI::DefaultWindow*>
// 		(m_gui.createWidget("TaharezLook/Label", glm::vec4(0.725, 0.565, 0.08, 0.12), glm::vec4(0), "width_label"));
// 	width_label->setText("Width");
// 	width_label->setProperty("HorzFormatting", "LeftAligned");
// 
// 
// 
// 	heigh_label = static_cast<CEGUI::DefaultWindow*>
// 		(m_gui.createWidget("TaharezLook/Label", glm::vec4(0.725, 0.615, 0.08, 0.12), glm::vec4(0), "heigh_label"));
// 	heigh_label->setText("Heigh");
// 	heigh_label->setProperty("HorzFormatting", "LeftAligned");

	

// 	 red_label = static_cast<CEGUI::DefaultWindow*>
// 		(m_gui.createWidget("TaharezLook/Label", glm::vec4(0.725, 0.86, 0.08, 0.12), glm::vec4(0), "red_label"));
// 	red_label->setText("Red");
// 	red_label->setProperty("HorzFormatting", "LeftAligned");



// 	green_label = static_cast<CEGUI::DefaultWindow*>
// 		(m_gui.createWidget("TaharezLook/Label", glm::vec4(0.725, 0.91, 0.08, 0.12), glm::vec4(0), "green_label"));
// 	green_label->setText("Green");
// 	green_label->setProperty("HorzFormatting", "LeftAligned");

	

// 	blue_label = static_cast<CEGUI::DefaultWindow*>
// 		(m_gui.createWidget("TaharezLook/Label", glm::vec4(0.81, 0.86, 0.08, 0.12), glm::vec4(0), "blue_label"));
// 	blue_label->setText("Blue");
// 	blue_label->setProperty("HorzFormatting", "LeftAligned");


// 
// 	alpha_label = static_cast<CEGUI::DefaultWindow*>
// 		(m_gui.createWidget("TaharezLook/Label", glm::vec4(0.81, 0.91, 0.08, 0.12), glm::vec4(0), "alpha_label"));
// 	alpha_label->setText("Alpha");
// 	alpha_label->setProperty("HorzFormatting", "LeftAligned");



// 	object_edit_name = static_cast<CEGUI::Editbox *>
// 		(m_gui.createWidget("TaharezLook/Editbox", glm::vec4(0.815, 0.55, 0.13, 0.04), glm::vec4(0), "name_edit"));
// 
// 	object_combo_type = static_cast<CEGUI::Combobox*>
// 		(m_gui.createWidget("TaharezLook/Combobox", glm::vec4(0.875, 0.655, 0.085, 0.18), glm::vec4(0), "type_combo"));
// 
// 	object_edit_width = static_cast<CEGUI::Editbox *>
// 		(m_gui.createWidget("TaharezLook/Editbox", glm::vec4(0.775, 0.605, 0.09, 0.04), glm::vec4(0), "width_edit"));
// 

// 
// 	object_edit_heigh = static_cast<CEGUI::Editbox *>
// 		(m_gui.createWidget("TaharezLook/Editbox", glm::vec4(0.775, 0.655, 0.09, 0.04), glm::vec4(0), "heigh_edit"));
// 
// 
// 
// 	object_button_create = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button", glm::vec4(0.895, 0.95, 0.1, 0.05), glm::vec4(0),
// 		"create_button"));
// 	object_button_create->setText("Save Object");
// 
// 	


// 	object_button_addColider = static_cast<CEGUI::PushButton*> (m_gui.createWidget("TaharezLook/Button", glm::vec4(0.895, 0.895, 0.1, 0.05), glm::vec4(0),
// 		"create_addColider"));
// 	object_button_addColider->setText("Add Colider");


// 
// 	color_red_value = static_cast<CEGUI::Editbox *>
// 		(m_gui.createWidget("TaharezLook/Editbox", glm::vec4(0.77, 0.895, 0.035, 0.04), glm::vec4(0), "color_red_value"));
// 	color_red_value->setMaxTextLength(3);
// 
	
// 
// 	color_green_value = static_cast<CEGUI::Editbox *>
// 		(m_gui.createWidget("TaharezLook/Editbox", glm::vec4(0.77, 0.945, 0.035, 0.04), glm::vec4(0), "color_green_value"));
// 	color_green_value->setMaxTextLength(3);
// 

// 	color_blue_value = static_cast<CEGUI::Editbox *>
// 		(m_gui.createWidget("TaharezLook/Editbox", glm::vec4(0.855, 0.895, 0.035, 0.04), glm::vec4(0), "color_blue_value"));
// 	color_blue_value->setMaxTextLength(3);
// 
// 	color_alpha_value = static_cast<CEGUI::Editbox *>
// 		(m_gui.createWidget("TaharezLook/Editbox", glm::vec4(0.855, 0.945, 0.035, 0.04), glm::vec4(0), "color_alpha_value"));
// 	color_alpha_value->setMaxTextLength(3);
// 
// 	color_red_value->setValidationString("\\d*");
// 	color_green_value->setValidationString("\\d*");
// 	color_blue_value->setValidationString("\\d*");
// 	color_alpha_value->setValidationString("\\d*");
// 

// 	cancelButton = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button", glm::vec4(0.6, 0.7, 0.3, 0.14), glm::vec4(0),
// 		"cancelButton"));
// 	cancelButton->setText("Cancel");

	//Combobox Item
	//type_combo->getEditbox()->disable();

// 	const CEGUI::Image* sel_img = &CEGUI::ImageManager::getSingleton().get("TaharezLook/MultiListSelectionBrush");
// 
// 	CEGUI::ListboxTextItem * item;
// 	item = new CEGUI::ListboxTextItem("Terrain", TYPE_TERRIAN);
// 	item->setSelectionBrushImage(sel_img);
// 	object_combo_type->addItem(item);
// 	item = new CEGUI::ListboxTextItem("Object", TYPE_OBJECT);
// 	item->setSelectionBrushImage(sel_img);
// 	object_combo_type->addItem(item);
// 	item = new CEGUI::ListboxTextItem("Tree", TYPE_TREE);
// 	item->setSelectionBrushImage(sel_img);
// 	object_combo_type->addItem(item);
// 	item = new CEGUI::ListboxTextItem("Plant", TYPE_PLANT);
// 	item->setSelectionBrushImage(sel_img);
// 	object_combo_type->addItem(item);
// 	item = new CEGUI::ListboxTextItem("Decal", TYPE_DECAL);
// 	item->setSelectionBrushImage(sel_img);
// 	object_combo_type->addItem(item);
// 	object_combo_type->setSortingEnabled(false);
// 	
// 	
// 	object_combo_type->setReadOnly(true);
// 	
// 	
// 
// 	if (CEGUI::ListboxItem* skinItem = object_combo_type->getListboxItemFromIndex(0))
// 	{
// 		object_combo_type->setItemSelectState(skinItem, true);
// 			
// 	}
// 
// // 
// 
// 	object_edit_width->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&EditorScreen::recalculateDimforSample, this));
// 	object_edit_heigh->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&EditorScreen::recalculateDimforSample, this));
// 	object_button_addColider->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&EditorScreen::createColider, this));
// 
// 	color_red_value->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&EditorScreen::updateColor, this));
// 	color_green_value->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&EditorScreen::updateColor, this));
// 	color_blue_value->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&EditorScreen::updateColor, this));
// 	color_alpha_value->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&EditorScreen::updateColor, this));
// 	object_button_create->subscribeEvent(CEGUI::FrameWindow::EventMouseClick, CEGUI::Event::Subscriber(&EditorScreen::writeFile, this));

}

bool EditorScreen::destroyObjectPannel(const CEGUI::EventArgs & e)
{

	m_addLayerWindow->destroy();
	return true;
}

bool EditorScreen::createObject(const CEGUI::EventArgs &e)
{
	glm::vec2 dim(30, 30);
	glm::vec2 pos(0, 0);

	if (m_currentTexture.isHasTexture())
	{
 		dim.x = m_currentTexture.getTexture().width / 10.0f;
 		dim.y = m_currentTexture.getTexture().height / 10.0f;

		pos.x = -(m_currentTexture.getTexture().width / 2.0f);
		pos.y = (m_currentTexture.getTexture().height / 2.0f);
	
	}

	//test.recalculateDim();

	color_red_value->setText("255");
	color_green_value->setText("255");
	color_blue_value->setText("255");
	color_alpha_value->setText("255");

	//new_object_dialog->destroy();

	return true;
}

void EditorScreen::drawEditScreen()
{
	
	//Sample Editting Camera
	glViewport(EditScreen.x, EditScreen.y, EditScreen.z, EditScreen.w);

	m_editObjectShader.use();

	GLint textureUniform = m_editObjectShader.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	glActiveTexture(GL_TEXTURE0);

	// Camera matrix
	glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
	GLint pUniform = m_editObjectShader.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	GLint dayLightIndex = m_editObjectShader.getUniformLocation("dayLight");
	//glUniform1f(dayLightIndex, m_buildObjectTool.getAmbientLight());
	glUniform3f(dayLightIndex, 1.0f, 1.0f, 1.0f);
	m_lightBatch.begin();

	m_buildingObject.drawLight(m_lightBatch);

	m_lightBatch.renderLight();
	m_spriteBatch.begin(Feintgine::GlyphSortType::FRONT_TO_BACK);
	
	m_buildObjectTool.drawShadowing(m_spriteBatch);
	m_buildingObject.draw(m_spriteBatch);

	m_spriteBatch.end();
	m_spriteBatch.renderBatch();

	m_editObjectShader.unuse();

	glm::mat4 Static_Edit_projectionMatrix = staticCam_Editing.getCameraMatrix();

	m_debug.drawBox(glm::vec4(-(EditScreen.z / 2.0f), -(EditScreen.w / 2.0f), EditScreen.z, EditScreen.w), Feintgine::Color(40, 110, 210, 255), 0);

	m_debug.end();
	m_debug.render(Static_Edit_projectionMatrix, 2.0f);

	m_editorCrosshair.drawBox(glm::vec4(-12.5, 0, 25, 0.25), Feintgine::Color(240, 240, 240, 125), 0);
	m_editorCrosshair.drawBox(glm::vec4(0, -12.5, 0.25, 25), Feintgine::Color(240, 240, 240, 125), 0);
	if (m_buildObjectTool.isShowColider())
	{
		m_buildingObject.drawColider(m_editorCrosshair);
	}	
	m_buildObjectTool.drawBoxes(m_editorCrosshair);
	m_editorCrosshair.end();
	m_editorCrosshair.render(projectionMatrix, 2.0f);
	
}

void EditorScreen::drawSampleScreen()
{
	
	glViewport(SampleSceen.x, SampleSceen.y, SampleSceen.z, SampleSceen.w);
	m_spriteListShader.use();

	GLint textureUniform = m_spriteListShader.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	glActiveTexture(GL_TEXTURE0);

	// Camera matrix

	GLint pUniform = m_spriteListShader.getUniformLocation("P");
	glm::mat4 sampleMatrix = m_sampleCam.getCameraMatrix();
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &sampleMatrix[0][0]);

	m_spriteBatch.begin(Feintgine::GlyphSortType::FRONT_TO_BACK);
	
	if (m_spriteListDisplayer.getDisplaySample())
	{
		m_spriteListDisplayer.getDisplaySample()->draw(m_spriteBatch);
	}
	
	//m_sample.draw(m_spriteBatch);
	
	m_spriteBatch.end();
	m_spriteBatch.renderBatch();

	m_spriteListShader.unuse();

	for (int i = 0; i < m_colider_boxes.size(); i++)
	{
		m_colider_boxes[i].draw(m_editorCrosshair);
	}
	//col.draw(m_uvrenderer);
	
	m_editorCrosshair.end();
	m_editorCrosshair.render(sampleMatrix, 2.0f);

	glm::mat4 Static_Sample_projectionMatrix = staticCam_Sample.getCameraMatrix();
	m_debug.drawBox(glm::vec4(-(SampleSceen.z / 2.0f) , -(SampleSceen.w / 2.0f), SampleSceen.z , SampleSceen.w), Feintgine::Color(40, 180, 160, 255), 0);

	m_debug.end();
	m_debug.render(Static_Sample_projectionMatrix, 2.0f);
	
}

bool EditorScreen::recalculateDimforSample(const CEGUI::EventArgs &e)
{
	if (object_edit_width->getText().size() > 0 && object_edit_heigh->getText().size())
	{

		if (std::stof(object_edit_width->getText().c_str()) != NULL && std::stof(object_edit_heigh->getText().c_str()) != NULL)
		{
			glm::vec2 t_dim;
			t_dim.x = std::stof(object_edit_width->getText().c_str());
			t_dim.y = std::stof(object_edit_heigh->getText().c_str());
	
		}
	}

	return true;
}

bool EditorScreen::createColider(const CEGUI::EventArgs &e)
{

	ColiderBox col;


	return true;
}

bool EditorScreen::updateColor(const CEGUI::EventArgs & e)
{

	if (color_red_value->getText().size() > 0 && color_green_value->getText().size() > 0 && color_blue_value->getText().size() >0 && color_alpha_value->getText().size() > 0)
	{
		
// 			m_sample.setColor(Feintgine::Color(std::stof(color_red_value->getText().c_str()), std::stof(color_green_value->getText().c_str()),
// 				std::stof(color_blue_value->getText().c_str()), std::stof(color_alpha_value->getText().c_str())));
// 		
	}
	return true;
}

void EditorScreen::DestroyColider()
{
// 	for (int i = 0; i < m_colider_boxes.size(); i++)
// 	{
// 		if (m_colider_boxes[i].isDestroyed())
// 		{
// 			m_colider_boxes.erase(m_colider_boxes.begin() + i);
// 		}
// 	}
}

bool EditorScreen::writeFile(const CEGUI::EventArgs &e)
{

	if (checkValid())
	{
	//	f_writeFile("Assets/Objects/");
	}
	else
	{
		std::cout << " not valid state \n";
	}
	
	return true;
}

// void EditorScreen::f_writeFile(const std::string & filePath)
// {
	
// 	f_object object;
// 	object.set_name(object_edit_name->getText().c_str());
// 	object.set_type(object_combo_type->getItemIndex(object_combo_type->getSelectedItem()));

// 	std::cout << " saved item is " << object_combo_type->getItemIndex(object_combo_type->getSelectedItem()) << "\n";

// 	object.set_texturepath(m_currentTexture.getFilePath().c_str());

// 	f_object_color f_color;
// 	f_color.set_color_r(std::stof(color_red_value->getText().c_str()));
// 	f_color.set_color_g(std::stof(color_green_value->getText().c_str()));
// 	f_color.set_color_b(std::stof(color_blue_value->getText().c_str()));
// 	f_color.set_color_a(std::stof(color_alpha_value->getText().c_str()));

// 	setColor(f_color, *object.mutable_color());

// 	for (int i = 0; i < m_colider_boxes.size(); i++)
// 	{
// 		//f_colider t_colider ;
// // 		f_vec2 pos;
// // 		pos.set_x(m_colider_boxes[i].getPos().x);
// // 		pos.set_y(m_colider_boxes[i].getPos().y);
// // 
// // 		f_vec2 dim;
// // 		dim.set_x(m_colider_boxes[i].getDim().x);
// // 		dim.set_y(m_colider_boxes[i].getDim().y);

// // 		setfVec2(pos, *t_colider.mutable_pos());
// // 		setfVec2(dim, *t_colider.mutable_dim());

// /*		setColider(t_colider, *object.add_coliderlist());*/
// 	}

// 	std::string destiny = filePath;
// 	std::string fileName = object.name().c_str();
// 	fileName += ".fob";
// 	destiny += fileName;

// 	std::fstream output(destiny.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
	
// 	if (!object.SerializeToOstream(&output)) {
// 		std::cout << "Failed to write obj.\n";
		
// 	}
// 	else
// 	{
// 		std::cout << "Write Object OK \n";
		
// 	}
// 	output.close();

// }

bool EditorScreen::checkValid()
{
	return object_edit_name->getText().size() > 0;
}

// void EditorScreen::setUV(f_object_uv &uv1, f_object_uv &uv2)
// {
// 	uv2 = uv1;
// }

// void EditorScreen::setColor(f_object_color &c1, f_object_color &c2)
// {
// 	c2 = c1;
// }

// void EditorScreen::setfVec2(f_vec2 &v1, f_vec2 &v2)
// {
// 	v2 = v1;
// }

// void EditorScreen::setColider(f_colider & c1, f_colider &c2)
// {
// 	c2 = c1;
// }

// void EditorScreen::loadObject(const std::string & filePath)
// {
// 	f_object object;
// 	std::fstream input(filePath.c_str(), std::ios::in | std::ios::binary);
// 	if (!object.ParseFromIstream(&input)) 
// 	{
// 		std::cout << "Failed to read  object.\n";
// 	}
// 	else
// 	{
		
// 		TemplateObject temp;

// 		temp.init(filePath);

// 		m_templateList.push_back(temp);

// 	}
// }



void EditorScreen::drawObjectsScreen()
{
	glViewport(ObjectsScreen.x, ObjectsScreen.y, ObjectsScreen.z, ObjectsScreen.w);
	m_spriteListShader.use();

	GLint textureUniform = m_spriteListShader.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	glActiveTexture(GL_TEXTURE0);
	// Camera matrix

	GLint pUniform = m_spriteListShader.getUniformLocation("P");
	glm::mat4 objectsMatrix = m_objectsCamera.getCameraMatrix();
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &objectsMatrix[0][0]);

	m_spriteBatch.begin(Feintgine::GlyphSortType::FRONT_TO_BACK);


	m_objectHolder.draw(m_spriteBatch);
	m_spriteBatch.end();
	m_spriteBatch.renderBatch();

	m_spriteListShader.unuse();

	m_debug.drawBox(glm::vec4(-(ObjectsScreen.z / 2.0f), -(ObjectsScreen.w / 2.0f), ObjectsScreen.z, ObjectsScreen.w), Feintgine::Color(40, 210, 210, 255), 0);

	
	m_objectHolder.drawBorder(m_debug);
// 	for (int i = 0; i < m_slots.size(); i++)
// 	{
// 		m_slots[i].draw(m_debug);
// 	}

	m_debug.end();
	m_debug.render(objectsMatrix,2.0f);
}

void EditorScreen::sortObject()
{
	
	
	for (int i = 0; i < m_filedList.size(); i++)
	{
		int k = getFirstFreeSlot();
		
		m_slots[k].addObject(m_filedList[i]);
	}
	
}

void EditorScreen::initObjectUI()
{

}

void EditorScreen::initSlot()
{
	glm::vec2 startPoint = glm::vec2(-ObjectsScreen.z / 2.0f, ObjectsScreen.w / 2.0f);

	glm::vec2 offset = glm::vec2(ObjectsScreen.z / 5.0f, ObjectsScreen.w / 5.0f);

	int row = 1;
	int colum = 0;

	for (int i = 0; i < 25; i++)
	{
		ObjectSlot slot;
		slot.init(glm::vec2(offset.x *colum + startPoint.x + 1, -offset.y *row + startPoint.y + 1), offset);
		m_slots.push_back(slot);
		colum++;
		if (colum >= 5)
		{
			row++;
			colum = 0;
		}
	}
}

int EditorScreen::getFirstFreeSlot()
{
	for (int i = 0; i < m_slots.size(); i++)
	{
		if (!m_slots[i].hasObject())
		{
			return i;
		}
	}
	return m_slots.size();
}

std::vector <TemplateObject > EditorScreen::getFiltedList(std::vector<TemplateObject > list)
{
	std::vector <TemplateObject > filtedList1;
	std::vector<TemplateObject> filtedList2;
	int current = current_page - 1;
		
	for (int i = 0; i < list.size(); i++)
	{	
		if (current_type == TYPE_ALL)
		{
			filtedList1.push_back(list[i]);
		}
		else
		{
			// if (list[i].getType() == current_type)
			// {
				
			// 	filtedList1.push_back(list[i]);
			// }
		}
	}
	int startIndex = m_slots.size() * current;
	int endIndex = m_slots.size() * current_page;
	if (endIndex > filtedList1.size())
	{
		endIndex = filtedList1.size();
	}

	for (int i = startIndex; i < endIndex; i++)
	{
		
		filtedList2.push_back(filtedList1[i]);
				
	}
	
	return filtedList2;
}

void EditorScreen::initFilters()
{

// 	filter_type = static_cast<CEGUI::Combobox*>
// 		(m_gui.createWidget("TaharezLook/Combobox", glm::vec4(0.085, 0.49, 0.1, 0.2), glm::vec4(0), "filter_type"));
// 
// 	const CEGUI::Image* sel_img = &CEGUI::ImageManager::getSingleton().get("TaharezLook/MultiListSelectionBrush");
// 	
// 	CEGUI::ListboxTextItem * item;
// 	item = new CEGUI::ListboxTextItem("All", TYPE_ALL);
// 	item->setSelectionBrushImage(sel_img);
// 	filter_type->addItem(item);
// 	item = new CEGUI::ListboxTextItem("Terrain", TYPE_TERRIAN);
// 	item->setSelectionBrushImage(sel_img);
// 	filter_type->addItem(item);
// 	item = new CEGUI::ListboxTextItem("Object", TYPE_OBJECT);
// 	item->setSelectionBrushImage(sel_img);
// 	filter_type->addItem(item);
// 	item = new CEGUI::ListboxTextItem("Tree", TYPE_TREE);
// 	item->setSelectionBrushImage(sel_img);
// 	filter_type->addItem(item);
// 	item = new CEGUI::ListboxTextItem("Plant", TYPE_PLANT);
// 	item->setSelectionBrushImage(sel_img);
// 	filter_type->addItem(item);
// 	item = new CEGUI::ListboxTextItem("Decal", TYPE_DECAL);
// 	item->setSelectionBrushImage(sel_img);
// 	filter_type->addItem(item);
// 	filter_type->setSortingEnabled(false);
// 
// 	current_type = TYPE_ALL;
// 
// 	filter_type->setReadOnly(true);
// 
// 
// 	if (CEGUI::ListboxItem* skinItem = filter_type->getListboxItemFromIndex(0))
// 	{
// 		filter_type->setItemSelectState(skinItem, true);
// 
// 	}
// 	CEGUI::DefaultWindow * type_label = static_cast<CEGUI::DefaultWindow*>
// 		(m_gui.createWidget("TaharezLook/Label", glm::vec4(0.1, 0.45, 0.1, 0.04), glm::vec4(0), "type_label_pick"));
// 	type_label->setText("Type");
// 	type_label->setProperty("HorzFormatting", "LeftAligned");

// 	filter_page = static_cast<CEGUI::Combobox*>
// 		(m_gui.createWidget("TaharezLook/Combobox", glm::vec4(0.01, 0.49, 0.05, 0.12), glm::vec4(0), "filter_page"));


// 	CEGUI::DefaultWindow * page_label = static_cast<CEGUI::DefaultWindow*>
// 		(m_gui.createWidget("TaharezLook/Label", glm::vec4(0.01, 0.45, 0.1, 0.04), glm::vec4(0), "page_label"));
// 	page_label->setText("Page");
// 	page_label->setProperty("HorzFormatting", "LeftAligned");


// 	CEGUI::DefaultWindow * filter_label = static_cast<CEGUI::DefaultWindow*>
// 		(m_gui.createWidget("TaharezLook/Label", glm::vec4(0.01, 0.36, 0.1, 0.12), glm::vec4(0), "filter_label"));
// 	filter_label->setText("Filter");
// 	filter_label->setProperty("HorzFormatting", "LeftAligned");

// 	filer_name = static_cast<CEGUI::Editbox *>
// 		(m_gui.createWidget("TaharezLook/Editbox", glm::vec4(0.06, 0.4, 0.13, 0.04), glm::vec4(0), "filer_name"));



	//filter_type->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted, CEGUI::Event::Subscriber(&EditorScreen::filterChanges, this));
	//filer_name->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&EditorScreen::filterChanges_name, this));
	
	
}

void EditorScreen::updatePage()
{
// 	filter_page->removeAllEvents();
// 
// 	
// 	const CEGUI::Image* sel_img = &CEGUI::ImageManager::getSingleton().get("TaharezLook/MultiListSelectionBrush");
// 	CEGUI::ListboxTextItem * item;
// 	filter_page->setReadOnly(true);
// 	filter_page->setSortingEnabled(false);
// 	int totalPage = m_filedList.size()/m_slots.size();
// 	totalPage++;
// 	std::cout << "total page is " << totalPage << "\n";
// 
// 	filter_page->resetList();
// 	for (int i = 1; i <= totalPage; i++)
// 	{
// 
// 		item = new CEGUI::ListboxTextItem(std::to_string(i).c_str(), i);
// 		item->setSelectionBrushImage(sel_img);
// 		filter_page->addItem(item);
// 
// 	}
// 	if (!alreadySet)
// 	{
// 
// 
// 		if (CEGUI::ListboxItem* skinItem = filter_page->getListboxItemFromIndex(0))
// 		{
// 			filter_page->setItemSelectState(skinItem, true);
// 
// 		}
// 		alreadySet = true;
// 	}
// 
// 
// 	
// 	filter_page->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted, CEGUI::Event::Subscriber(&EditorScreen::filterChanges_page, this));
}

bool EditorScreen::filterChanges(const CEGUI::EventArgs &e)
{

// 	if (filter_type->getSelectedItem())
// 	{
// 		
// 			
// 		if (filter_type->getSelectedItem()->getText() == "All")
// 		{
// 			current_type = TYPE_ALL;
// 		}
// 		if (filter_type->getSelectedItem()->getText() == "Terrain")
// 		{
// 			current_type = TYPE_TERRIAN;
// 		}
// 		if (filter_type->getSelectedItem()->getText() == "Object")
// 		{
// 			current_type = TYPE_OBJECT;
// 		}
// 		if (filter_type->getSelectedItem()->getText() == "Tree")
// 		{
// 			current_type = TYPE_TREE;
// 		}
// 		if (filter_type->getSelectedItem()->getText() == "Plant")
// 		{
// 			current_type = TYPE_PLANT;
// 		}
// 		if (filter_type->getSelectedItem()->getText() == "Decal")
// 		{
// 			current_type = TYPE_DECAL;
// 		}
// 
// 		std::cout << "current_type is " << current_type << "\n";
// 	
// 	}
 	
// 	updateList();
// 	
	
	return true;
}

bool EditorScreen::filterChanges_page(const CEGUI::EventArgs &e)
{

// 	if (filter_page->getSelectedItem())
// 	{
// 		current_page = filter_page->getSelectedItem()->getID();
// 	}
// 
// 	
// 	
// 	updateList();

	return true;
}

bool EditorScreen::filterChanges_name(const CEGUI::EventArgs &e)
{
	
		//t_filter_name = filer_name->getText().c_str();
	
		//updateList();
	

	return true;
}

void EditorScreen::refreshFiltedList(std::string name)
{
	m_filedList.clear();
	std::vector <TemplateObject> finalList;
	std::vector <TemplateObject> finalList2;
	finalList = m_templateList;// getFiltedList(page, type);

	if (name.size() > 0)
	{


		for (int i = 0; i < finalList.size(); i++)
		{
			// std::size_t found = finalList[i].getName().find(name);
			// if (found != std::string::npos)
			// {
			// 	std::cout << "FOUND \n";
			// 	finalList2.push_back(finalList[i]);
			// }
		}
	}
	else
	{
		finalList2 = finalList;
	}

	m_filedList = getFiltedList(finalList2);
	updatePage();
	

}

void EditorScreen::updateList()
{
	for (int i = 0; i < m_slots.size(); i++)
	{
		m_slots[i].clearObject();
	}
	updatePage();
	refreshFiltedList(t_filter_name);

	sortObject();
}

void EditorScreen::drawPreviewScreen()
{

	
	glViewport(PreviewScreen.x, PreviewScreen.y, PreviewScreen.z, PreviewScreen.w);
	m_previewObjectShader.use();

	GLint textureUniform = m_previewObjectShader.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	glActiveTexture(GL_TEXTURE0);


	// Camera matrix
	GLint pUniform = m_previewObjectShader.getUniformLocation("P");
	glm::mat4 previewMatrix = m_previewCamera.getCameraMatrix();
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &previewMatrix[0][0]);

	GLint dayLightIndex = m_previewObjectShader.getUniformLocation("dayLight");
	glUniform3f(dayLightIndex, 1.0,1.0,1.0);

	m_lightBatch.begin();

	if (m_objectHolder.getDisplaySample())
	{
		m_objectHolder.getDisplaySample()->drawLight(m_lightBatch);
	}
	else
	{
		fakeObject.drawLight(m_lightBatch);
	}
	
	m_lightBatch.renderLight();

	m_spriteBatch.begin(Feintgine::GlyphSortType::FRONT_TO_BACK);
	m_buildObjectTool.drawShadowing(m_spriteBatch);

	if (m_objectHolder.getDisplaySample())
	{
		
		m_objectHolder.getDisplaySample()->draw(m_spriteBatch);
	}
	
	m_spriteBatch.end();
	m_spriteBatch.renderBatch();



	m_previewObjectShader.unuse();
	
	if (m_objectHolder.getDisplaySample())
	{
		m_objectHolder.getDisplaySample()->drawColider(m_debug);
	
	}	
	m_debug.end();
	m_debug.render(previewMatrix, 2.0f);
	
	glm::mat4 staticView = m_previewCamera_static.getCameraMatrix();
	m_debug.drawBox(glm::vec4(-(PreviewScreen.z / 2.0f), -(PreviewScreen.w / 2.0f), PreviewScreen.z, PreviewScreen.w), Feintgine::Color(40, 180, 160, 255), 0);

	m_debug.end();
	m_debug.render(staticView, 2.0f);

}

void EditorScreen::selectItemFromTempalte(glm::vec2 mousePos)
{
	int k = getHoverIndex(mousePos);
	if (k != -1)
	{
		if (m_slots[k].getObject())
		{

			// std::string target = m_slots[k].getCopyObject().getPrefabFilePath();
			
			// previewObject.init(target);
			// previewObject.setPos(glm::vec2(0));
			// previewObject.setDim(previewObject.getActualDim());

			m_previewObject = &previewObject;
			
		}
	}


		if (m_previewObject)
		{
			
			// copy.init(previewObject.getPrefabFilePath());
			// m_placeObject = &copy;
			// m_placeObject->setDepth(100);
		}
	
}

int EditorScreen::getHoverIndex(glm::vec2 mousepos)
{
	for (int i = 0; i < m_slots.size(); i++)
	{
		if (m_slots[i].onHover(mousepos))
		{
			return i;
		}
	}
	return -1;
}

void EditorScreen::drawSceneScreen()
{
	glViewport(SceneScreen.x, SceneScreen.y, SceneScreen.z, SceneScreen.w);

	m_editObjectShader.use();

	GLint textureUniform = m_editObjectShader.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	glActiveTexture(GL_TEXTURE0);


	// Camera matrix

	GLint pUniform = m_editObjectShader.getUniformLocation("P");
	glm::mat4 previewMatrix = m_sceneCamera.getCameraMatrix();
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &previewMatrix[0][0]);

	GLint dayLightIndex = m_editObjectShader.getUniformLocation("dayLight");
	
	glUniform3f(dayLightIndex, m_ambientLight.x,m_ambientLight.y, m_ambientLight.z);
	m_lightBatch.begin();

	m_selectedObject.drawLight(m_lightBatch);
	m_sceneManager.drawLight(m_lightBatch);
	
	m_lightBatch.renderLight();
	


	m_spriteBatch.begin(Feintgine::GlyphSortType::FRONT_TO_BACK);
	m_brushTest.draw(m_spriteBatch);

	m_buildObjectTool.drawShadowing(m_spriteBatch);

	if (m_objectSelected)
	{
		
		m_selectedObject.draw(m_spriteBatch);
	}
	m_sceneManager.draw(m_spriteBatch);
	m_tileset.draw(m_spriteBatch);

	m_tileManager.draw(m_spriteBatch);
	

	m_spriteBatch.end();
	m_spriteBatch.renderBatch();

	m_editObjectShader.unuse();

	if (debugTiles)
	{
		m_tileManager.drawText(m_textRenderer, m_sceneCamera);
	}

	if (m_objectSelected)
	{
		m_selectedObject.drawColider(m_editorCrosshair);

	}
	m_tileStack.drawIndicatior(m_editorCrosshair);
	m_sceneManager.drawBox(m_editorCrosshair);

	m_editorCrosshair.end();
	m_editorCrosshair.render(previewMatrix, 2.0f);

	glm::mat4 Static_Edit_projectionMatrix = m_sceneCamera_static.getCameraMatrix();

	m_debug.drawBox(glm::vec4(-(SceneScreen.z / 2.0f), -(SceneScreen.w / 2.0f), SceneScreen.z, SceneScreen.w), Feintgine::Color(40, 210, 110, 255), 0);
	
	m_debug.end();
	m_debug.render(Static_Edit_projectionMatrix, 2.0f);


}

bool EditorScreen::changeToEditObject(const CEGUI::EventArgs &e)
{
	
	switchScreen(T_EDIT_OJECT_MODE);
	return true;
}

bool EditorScreen::changeToEditScene(const CEGUI::EventArgs & e)
{
	
	switchScreen(T_EDIT_SCREEN_MODE);

	return true;
}

bool EditorScreen::changeToEditDamaku(const CEGUI::EventArgs & e)
{
	
	switchScreen(T_EDIT_DAMAKU_MODE);
	return true;
}

bool EditorScreen::changeToEditEnemy(const CEGUI::EventArgs & e)
{
	
	switchScreen(T_EDIT_ENEMY_MODE);
	return true;
}

bool EditorScreen::changeToEditLua(const CEGUI::EventArgs & e)
{
	
	switchScreen(T_EDIT_LUA_MODE);
	return true;
}


int EditorScreen::getLastestPage()
{
// 	if (filter_page)
// 	{
// 
// 		if (filter_page->getChildCount() > 0)
// 		{
// 			return filter_page->getChildCount() - 1;
// 		}
// 	}
	
	return 0;	
}

void EditorScreen::handleEditScreen(Feintgine::InputManager & inputManager)
{
	if (inputManager.isKeyPressed(SDLK_ESCAPE))
	{
		
		m_objectHolder.clearCurrentObject();
		//m_sceneManager.getCurrentScene()->deselectCurrentLayer();
	
		//drawEditScreen();
	}
	
	if (inputManager.isKeyDown(SDLK_LCTRL))
	{
		is_hold_CTRL = true;
	}
	else
	{
		is_hold_CTRL = false;
	}


		if (isInsideScreen(inputManager.getMouseCoords(), SceneScreen) && drawMode == edit_scene_mode)
		{
			m_sceneManager.handleInput(inputManager, m_objectSelected,m_selectedObject,m_layers);

			currentCam = &m_sceneCamera;

			if (!is_ObjectInside)
			{
				is_ObjectInside = true;
			}
					
			glm::vec2 converted;
			converted.x = currentCam->convertScreenToWorld(inputManager.getMouseCoords()).x - (EditScreen.x / currentCam->getScale());
			float invertY = m_window->getScreenHeight() - EditScreen.w - EditScreen.y;
			converted.y = (currentCam->convertScreenToWorld(inputManager.getMouseCoords()).y) + ((invertY) / currentCam->getScale());

			//Editing start 
			if (m_actionCombo)
			{
				//Place Mode =================================================
// 				if (m_actionCombo->getSelectedItem()->getID() == PLACE_MODE)
// 				{
// 					if (m_placeObject && m_previewObject)
// 					{
// 						// Defocus selected object (ESC)
// 						
// 
// 						// Terrain create (f5)
// 						if (inputManager.isKeyPressed(SDLK_F5))
// 						{
// 							Layout_auto_protocol();
// 						}
// 					}
// 
// 					if (m_placeObject)
// 					{
// 						if (is_gridMode)
// 						{
// 							float standard = 64.0f;
// 							glm::vec2 currentMousePos = converted;
// 							float xbalanceVal = 0.0f;
// 							float ybalanceVal = 0.0f;
// 							if (currentMousePos.x < 0 )
// 							{
// 								xbalanceVal = 64.0f;
// 							}
// 							if (currentMousePos.y < 0)
// 							{
// 								ybalanceVal = 64.0f;
// 							}
// 
// 							int xVal = (currentMousePos.x - xbalanceVal) / standard;
// 							int yVal = (currentMousePos.y - ybalanceVal) / standard ;
// 							glm::vec2 gridedPos = glm::vec2((xVal* standard) +32, (yVal*standard)+32);
// 							m_placeObject->setPos(gridedPos);
// 
// 						
// 						}
// 						else
// 						{
// 							m_placeObject->setPos(converted);
// 						}
// 					
// 						if (m_scene.getCurrentLayer())
// 						{
// 
// 						}
// 					}
// 				}


				//SELECT Mode =================================================
// 				if (m_actionCombo->getSelectedItem()->getID() == SELECT_MODE)
// 				{
// 					//Update current layer if there is any
// 					if (m_scene.getCurrentLayer())
// 					{
// 						if (inputManager.isKeyPressed(SDL_BUTTON_LEFT))
// 						{
// 							m_scene.getCurrentLayer()->selectObjects(is_hold_CTRL);
// 						}
// 						if (inputManager.isKeyPressed(SDLK_ESCAPE))
// 						{
// 							m_scene.getCurrentLayer()->deselectObjects();
// 						}
// 						if (inputManager.isKeyPressed(SDLK_DELETE))
// 						{
// 							m_scene.getCurrentLayer()->deleteSelected();
// 						}
// 
// 						m_scene.getCurrentLayer()->update(converted);
// 					}
// 					
// 
// 				}
				//EDIT MODE ===================================
				if (m_actionCombo->getSelectedItem()->getID() == EDIT_MODE)
				{
					if (m_scene->getCurrentLayer())
					{
						
				
											
					}
				}

			}

			//Editing end 
			//Update current layer end

		}
		else
		{
			if (is_ObjectInside)
			{
				is_ObjectInside = false;
			}
		}
		
	
	

		if (drawMode == edit_scene_mode)
		{

			//Show Colider ( F1)
			if (inputManager.isKeyPressed(SDLK_F1))
			{
				if (!showColider)
				{
					showColider = true;
				}
				else
				{
					showColider = false;
				}
			}
			if (inputManager.isKeyPressed(SDLK_g))
			{
				toggleGridMode();
			}
			// Toggle Hide/Show layer (H)
			if (inputManager.isKeyPressed(SDLK_h))
			{
				toggleHide_ShowLayer();
			}

			//Switch MODE

// 			if (inputManager.isKeyPressed(SDLK_1))
// 			{
// 				switchEditingMode(EDIT_MODE);
// 			}
// 			if (inputManager.isKeyPressed(SDLK_2))
// 			{
// 				switchEditingMode(PLACE_MODE);
// 			}
// 			if (inputManager.isKeyPressed(SDLK_3))
// 			{
// 				switchEditingMode(SELECT_MODE);
// 			}
					
		}
			
		
	

}

void EditorScreen::initLayerList()
{
	m_addLayerButton = static_cast<CEGUI::PushButton *> (m_gui.createWidget("TaharezLook/Button", glm::vec4(0.75, 0.4, 0.1, 0.04), glm::vec4(0), "add_layer"));
	m_deleteLayerButton = static_cast<CEGUI::PushButton *> (m_gui.createWidget("TaharezLook/Button", glm::vec4(0.88, 0.4, 0.1, 0.04), glm::vec4(0) ,"delete_layer"));
	m_addLayerButton->setText("Add Layer");
	m_deleteLayerButton->setText("Delete Layer");

	m_layers = static_cast<CEGUI::MultiColumnList *> (m_gui.createWidget("TaharezLook/MultiColumnList", glm::vec4(0.72, 0.04, 0.27, 0.32), glm::vec4(0), "layers"));

	m_layers->hide();
	m_addLayerButton->hide();
	m_deleteLayerButton->hide();
	m_layers->addColumn("Name", 1, cegui_reldim(0.5f));
	m_layers->addColumn("Depth", 2, cegui_reldim(0.3f));
	m_layers->addColumn("Show", 3, cegui_reldim(0.2f));

	m_addLayerButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&EditorScreen::layer_add_protocol, this));
	m_deleteLayerButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&EditorScreen::layer_delete_protocol, this));
	m_layers->subscribeEvent(CEGUI::MultiColumnList::EventMouseDoubleClick, CEGUI::Event::Subscriber(&EditorScreen::selectCurrentLayer, this));

	

}

bool EditorScreen::addLayer(const CEGUI::EventArgs &e)
{
	
	addLayerFunc(m_layerName->getText().c_str(),std::stof(m_layerDepth->getText().c_str()));
	if (m_layers->getFirstSelectedItem())
	{
		//m_layers->getFirstSelectedItem()->setSelected(false);
		CEGUI::uint index = m_layers->getItemRowIndex(m_layers->getFirstSelectedItem());
		for (int i = 0; i < 3; i++)
		{
			m_layers->getItemAtGridReference(CEGUI::MCLGridRef(index, i))->setSelected(false);
		}
		
	}

	Feintgine::Fg_layer layer;
	layer.create(m_layerName->getText().c_str(), std::stof(m_layerDepth->getText().c_str()));
	m_sceneManager.getCurrentScene()->addLayer(layer);

	m_addLayerWindow->destroy();
	
	return true;
}

void EditorScreen::handleException(Feintgine::InputManager & inputManager)
{
	if (m_gui.getWindow()->getActiveChild())
	{
	
		if (m_gui.getWindow()->getActiveChild()->getType() == "TaharezLook/Editbox")
		{
			pointerEdit = (CEGUI::Editbox*)m_gui.getWindow()->getActiveChild();
			
		}
		else
		{
			
			pointerEdit = nullptr;
		}
	}
	if (pointerEdit)
	{
		if (inputManager.isKeyPressed(SDL_BUTTON_LEFT))
		{
			if (!pointerEdit->isMouseContainedInArea())
			{
				pointerEdit->deactivate();
				pointerEdit = nullptr;
			}
		}
	}
}



bool EditorScreen::createScene(const CEGUI::EventArgs &e)
{
	
	if (m_sceneManager.createScene(scene_edit_name->getText().c_str()))
	{
		destroySceneCreator();		
	}
	else
	{
		feint_common::Instance()->showMessageBox("error", "this scene already exist ");
	}	
	return true;
}

bool EditorScreen::save(const CEGUI::EventArgs &e)
{

	save_wat();
	return true;
}

bool EditorScreen::save_as(const CEGUI::EventArgs &e)
{
	feint_common::Instance()->showMessageBox("Error =-=","cai nay chua lam");

	return true;
}



void EditorScreen::save_wat()
{
// 	if (m_scene.getCurrentLayer())
// 	{
// 
// 
// 		if (m_sceneManager.getCurrentScene()->getName() == "")
// 		{
// 			std::cout << " no project was opened or created !";
// 			return;
// 		}
// 	}
	m_sceneManager.saveScene();
}

bool EditorScreen::selectCurrentLayer(const CEGUI::EventArgs &e)
{
	
	if (m_layers->getFirstSelectedItem())
	{
		m_sceneManager.selectCurrentLayer(m_layers->getFirstSelectedItem()->getText().c_str());
		//m_scene.findAndSetCurrentLayer(m_layers->getFirstSelectedItem()->getText().c_str());
	}
	return true;
}

void EditorScreen::updateListedLayer()
{

}

void EditorScreen::addLayerFunc(const std::string &layerName, float layerDepth)
{

	int i_layerDepth = layerDepth;
	CEGUI::ListboxTextItem * firstRowItem1 = new CEGUI::ListboxTextItem(layerName);
	CEGUI::ListboxTextItem * firstRowItem2 = new CEGUI::ListboxTextItem(std::to_string(i_layerDepth).c_str());
	CEGUI::ListboxTextItem * firstRowItem3 = new CEGUI::ListboxTextItem("v");


	firstRowItem1->setSelectionBrushImage("TaharezLook/ListboxSelectionBrush");
	firstRowItem2->setSelectionBrushImage("TaharezLook/ListboxSelectionBrush");
	firstRowItem3->setSelectionBrushImage("TaharezLook/ListboxSelectionBrush");

	CEGUI::uint firstRow = m_layers->addRow(firstRowItem1, 1);
	m_layers->setItem(firstRowItem2, 2, firstRow);
	m_layers->setItem(firstRowItem3, 3, firstRow);

}

void EditorScreen::listDirver2()
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	//std::tr2::sys::current_path().assign();
	//std::tr2::sys::absolute(ExePath().c_str());
	
	// std::tr2::sys::path a(ExePath());

	// std::cout << a << "\n";
	// for (std::tr2::sys::recursive_directory_iterator i("."), end; i != end; ++i)
	// 	if (!is_directory(i->path()))
	// 	{
	// 		std::wstring ts = i->path().c_str();
	// 		//std::wcout << ts << "\n";
	// 		std::string texturePath = converter.to_bytes(ts);
	// 		//std::cout << texturePath << "\n";
	// 		if (texturePath.find("\\Textures\\") != std::string::npos)
	// 		{
	// 			std::cout << "texture found : " << i->path().filename() << "\n";
	// 			CEGUI::ListboxTextItem * item;
	// 			// 
	// 			std::wstring itemname = i->path().filename().c_str();
	// 			item = new CEGUI::ListboxTextItem(feint_common::Instance()->convertWstringToString(itemname).c_str(), 0);
	// 			item->setSelectionBrushImage("TaharezLook/ListboxSelectionBrush");
			
	// 		}
	// 		if (texturePath.find("\\Objects\\") != std::string::npos)
	// 		{
	// 			std::cout << "object found : " << i->path().filename() << "\n";
	// 			std::wstring addOn = L"Assets/Objects/";
	// 			addOn.append(i->path().filename().c_str());
	// 			//loadObject(feint_common::Instance()->convertWstringToString(addOn));
				
	// 		}
	// 	}
}

void EditorScreen::initSceneBrowse()
{

}

bool EditorScreen::scene_create_protocol(const CEGUI::EventArgs &e)
{

		m_newSceneWindow = static_cast<CEGUI::Window*>
			(m_gui.createWidget("TaharezLook/FrameWindow", glm::vec4(0.3, 0.2, 0.4, 0.4), glm::vec4(0), "new_Scene_window"));

		CEGUI::PushButton * AcceptButton = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button", glm::vec4(0.4, 0.8, 0.2, 0.14), glm::vec4(0), "createSceneButton"));
		AcceptButton->setText("Create");

		scene_edit_name = static_cast<CEGUI::Editbox*>(m_gui.createWidget("TaharezLook/Editbox", glm::vec4(0.4, 0.4, 0.4, 0.1), glm::vec4(0), "scene_name"));

		CEGUI::DefaultWindow * scnene_edit_name_lb = static_cast<CEGUI::DefaultWindow*>(m_gui.createWidget("TaharezLook/Label", glm::vec4(0.05, 0.4, 0.4, 0.08), glm::vec4(0), "scene_name_lb"));
		scnene_edit_name_lb->setText("Scene name");

 		AcceptButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&EditorScreen::createScene, this));
		m_newSceneWindow->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked, CEGUI::Event::Subscriber(&EditorScreen::destroyCreateSceneWindow, this));
// 		m_addLayerWindow->setText("Add Layer");
// 
// 
// 		m_layerName = static_cast<CEGUI::Editbox *>(m_gui.createWidget("TaharezLook/Editbox", glm::vec4(0.3, 0.1, 0.4, 0.14), glm::vec4(0), "edit_layerName"));
// 		m_layerDepth = static_cast<CEGUI::Editbox *>(m_gui.createWidget("TaharezLook/Editbox", glm::vec4(0.3, 0.28, 0.4, 0.14), glm::vec4(0), "edit_layerDepth"));
// 
// 		m_layerDepth->setValidationString("\\d*");
// 
// 		m_addLayerWindow->addChild(m_layerName);
		m_newSceneWindow->addChild(scnene_edit_name_lb);
		m_newSceneWindow->addChild(scene_edit_name);
		m_newSceneWindow->addChild(AcceptButton);
	
		//feint_common::Instance()->showMessageBox("Error", "Create the Scene first");
	return true;
}

bool EditorScreen::destroyCreateSceneWindow(const CEGUI::EventArgs &e)
{
	destroySceneCreator();

	return true;
}

int EditorScreen::scanScene(const std::string & fileName)
{
	m_sceneFileName = fileName ;
	return listdir("./Scence", 0);

}

void EditorScreen::destroySceneCreator()
{
	if (m_newSceneWindow)
	{
		m_newSceneWindow->destroy();
	}
}

bool EditorScreen::scene_select_protocol(const CEGUI::EventArgs &e)
{
	m_selectSceneWindow = static_cast<CEGUI::Window*>
		(m_gui.createWidget("TaharezLook/FrameWindow", glm::vec4(0.3, 0.2, 0.4, 0.4), glm::vec4(0), "Select_Scene_window"));

	m_sceneList = static_cast<CEGUI::Listbox*> (m_gui.createWidget("TaharezLook/Listbox", glm::vec4(0.1, 0.1, 0.8, 0.8), glm::vec4(0), "Scene_List"));

	m_sceneList->subscribeEvent(CEGUI::Listbox::EventMouseDoubleClick, CEGUI::Event::Subscriber(&EditorScreen::selectScene, this));

	std::cout << "select protocol called \n";
	m_sceneManager.browseScene("./Scence/",0,m_sceneList);
	m_selectSceneWindow->addChild(m_sceneList);
	m_selectSceneWindow->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked, CEGUI::Event::Subscriber(&EditorScreen::destroySelecrSceen, this));
	
	return true;
}

void EditorScreen::closeSelectSceen()
{
	if (m_selectSceneWindow)
	{
		m_selectSceneWindow->destroy();
	}
}

bool EditorScreen::destroySelecrSceen(const CEGUI::EventArgs &e)
{

	closeSelectSceen();
	return true;
}

bool EditorScreen::selectScene(const CEGUI::EventArgs &e)
{
	
	
	if (m_sceneList)
	{
		if (m_sceneList->getFirstSelectedItem())
		{
			std::cout << m_sceneList->getFirstSelectedItem()->getText() << "\n";
			std::string t_path = "./Scence/";
			t_path += m_sceneList->getFirstSelectedItem()->getText().c_str();
			//clearLayer();
			std::cout << "load scene from file " << t_path << "\n";
			m_sceneManager.loadSceneFromFile(t_path,m_layers);
			//m_scene.loadSceneFromFile(t_path);
	
	
// 			for (int i = 0; i < m_sceneManager.getCurrentScene()->getLayers().size(); i++)
// 			{
// 				addLayerFunc(m_sceneManager.getCurrentScene()->getLayers()[i].getName(), (float)m_sceneManager.getCurrentScene()->getLayers()[i].getDepth());
// 			}
			closeSelectSceen();
		}
	}
	

	return true;
}

void EditorScreen::pushMassive(int col, int row)
{
	if (m_previewObject)
	{
		// glm::vec2 offset = m_previewObject->getDim();

		// float start_pos_x = -(offset.x * col)/2;
		// float start_pos_y = -(offset.y * row) / 2;

		// if (m_scene->getCurrentLayer())
		// {
		// 	for (int i = 0; i < col; i++)
		// 	{
		// 		for (int j = 0; j < row; j++)
		// 		{
		// 			//std::cout << feint_common::Instance()->convertVec2toString(glm::vec2(start_pos_x + (offset.x * i), start_pos_y + (offset.y * j))) << "\n";
		// 			//m_scene.getCurrentLayer()->addObject(m_previewObject->getPrefabFilePath(), glm::vec2(start_pos_x + (offset.x * i) , start_pos_y + (offset.y * j)));
		// 		}
		// 	}
			


		// }
	}
}

void EditorScreen::toggleHide_ShowLayer()
{
	if (m_scene->getCurrentLayer())
	{
// 		if (m_scene.getCurrentLayer()->isHidden())
// 		{
// 			//m_scene.getCurrentLayer()->setHide(false);
// 		}
// 		else
// 		{
// 			//m_scene.getCurrentLayer()->setHide(true);
// 		}
	}
}

void EditorScreen::toggleGridMode()
{
	if (is_gridMode)
	{
		std::cout << "grid mode off \n";
		is_gridMode = false;
	}
	else
	{
		std::cout << "grid mode on \n";
		is_gridMode = true;
	}
}

void EditorScreen::initActionBar()
{

}

void EditorScreen::switchEditingMode(int mode)
{
	if (m_actionCombo)
	{
		if (m_actionCombo->getListboxItemFromIndex(mode))
		{
			if (CEGUI::ListboxItem* skinItem = m_actionCombo->getListboxItemFromIndex(mode))
			{
				m_actionCombo->setItemSelectState(skinItem, true);
			}
		}
	}
}

void EditorScreen::Layout_auto_protocol()
{
	m_autolayoutWindow = static_cast<CEGUI::Window*>
		(m_gui.createWidget("TaharezLook/FrameWindow", glm::vec4(0.7, 0.5, 0.3, 0.3), glm::vec4(0), "layout_window"));

	CEGUI::PushButton * AcceptButton = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button", glm::vec4(0.4, 0.8, 0.2, 0.14), glm::vec4(0), "start_layout"));
	AcceptButton->setText("Create");


	AcceptButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&EditorScreen::layout, this));
	m_autolayoutWindow->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked, CEGUI::Event::Subscriber(&EditorScreen::destroyAutoLayout, this));
	//m_addLayerWindow->setText("Add Layer");

	CEGUI::DefaultWindow * edit1_label = static_cast<CEGUI::DefaultWindow *> (m_gui.createWidget("TaharezLook/Label", glm::vec4(0.1, 0.1, 0.12, 0.1), glm::vec4(0), "row_label"));
	edit1_label->setText("Row");
	CEGUI::DefaultWindow * edit2_label = static_cast<CEGUI::DefaultWindow *> (m_gui.createWidget("TaharezLook/Label", glm::vec4(0.1, 0.28, 0.12, 0.1), glm::vec4(0), "Col_label"));
	edit2_label->setText("Col");
 	m_layoutRow = static_cast<CEGUI::Editbox *>(m_gui.createWidget("TaharezLook/Editbox", glm::vec4(0.3, 0.1, 0.4, 0.14), glm::vec4(0), "edit_Row"));
 	m_layoutCol = static_cast<CEGUI::Editbox *>(m_gui.createWidget("TaharezLook/Editbox", glm::vec4(0.3, 0.28, 0.4, 0.14), glm::vec4(0), "edit_Col"));

	m_layoutRow->setValidationString("\\d*");
	m_layoutCol->setValidationString("\\d*");

	m_autolayoutWindow->addChild(AcceptButton);
	m_autolayoutWindow->addChild(edit1_label);
	m_autolayoutWindow->addChild(edit2_label);
	m_autolayoutWindow->addChild(m_layoutRow);
	m_autolayoutWindow->addChild(m_layoutCol);

}

void EditorScreen::closeAutoLayout()
{
	if (m_autolayoutWindow)
	{
		m_autolayoutWindow->destroy();
	}
}

bool EditorScreen::destroyAutoLayout(const CEGUI::EventArgs & e)
{
	closeAutoLayout();
	return true;
}

bool EditorScreen::layout(const CEGUI::EventArgs &e)
{

	if (m_layoutCol->getText().size() > 0 && m_layoutRow->getText().size() > 0)
	{
		pushMassive(std::stoi(m_layoutCol->getText().c_str()), std::stoi(m_layoutRow->getText().c_str()));
	}

	closeAutoLayout();
	return true;
}

void EditorScreen::drawAnimateObject()
{
	glViewport(AnimateScreen.x, AnimateScreen.y, AnimateScreen.z, AnimateScreen.w);

	m_spriteListShader.use();

	GLint textureUniform = m_spriteListShader.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	glActiveTexture(GL_TEXTURE0);

	// Camera matrix
	glm::mat4 projectionMatrix = m_animatingCamera.getCameraMatrix();
	GLint pUniform = m_spriteListShader.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	m_spriteBatch.begin(Feintgine::GlyphSortType::FRONT_TO_BACK);

	if (m_fAnimatedObject.isInited())
	{
		if (m_fAnimatedObject.getCurrentAnimation())
		{
			if (m_fAnimatedObject.isVisible())
			{
				
				m_fAnimatedObject.draw(m_spriteBatch);
				
			}
		}
		
		//m_animatedObject.update();
	}
	
	m_spriteBatch.end();
	m_spriteBatch.renderBatch();

	m_spriteListShader.unuse();

	m_editorCrosshair.end();
	m_editorCrosshair.render(projectionMatrix, 2.0f);

	glm::mat4 Static_Edit_projectionMatrix = staticCam_Animating.getCameraMatrix();

	m_debug.drawBox(glm::vec4(-(AnimateScreen.z / 2.0f), -(AnimateScreen.w / 2.0f), AnimateScreen.z, AnimateScreen.w), Feintgine::Color(110, 22, 110, 255), 0);

	m_debug.end();
	m_debug.render(Static_Edit_projectionMatrix, 2.0f);
}

bool EditorScreen::changeToEditAnimate(const CEGUI::EventArgs &e)
{
	switchScreen(T_EDIT_ANIMATE_MODE);
	return true;
}

void EditorScreen::hideObjectEditor()
{
	m_spriteListDisplayer.hide();
	m_buildObjectTool.hide();
	m_addToObject->hide();
	m_objectHolder.hide();
// 	object_edit_name->hide();
// 	object_combo_type->hide();
// 	object_edit_width->hide();
// 	object_edit_heigh->hide();
// 	color_red_value->hide();
// 	color_green_value->hide();
// 	color_blue_value->hide();
// 	color_alpha_value->hide();
// 	object_button_create->hide();
// 	object_button_addColider->hide();
	// 	filter_type ->hide();
	// 	filter_page ->hide();
	// 	filer_name ->hide();
// 	listDes->hide();
// 	type_label->hide();
// 	name_label->hide();
// 	width_label->hide();
// 	heigh_label->hide();
// 	red_label->hide();
// 	green_label->hide();
// 	blue_label->hide();
// 	alpha_label->hide();



}

void EditorScreen::showObjectEditor()
{
	m_spriteListDisplayer.show();
	m_addToObject->show();
	m_buildObjectTool.show();
	m_objectHolder.show();
// 	object_edit_name->show();
// 	object_combo_type->show();
// 	object_edit_width->show();
// 	object_edit_heigh->show();
// 	color_red_value->show();
// 	color_green_value->show();
// 	color_blue_value->show();
// 	color_alpha_value->show();
// 	object_button_create->show();
// 	object_button_addColider->show();
	// 	filter_type->show();
	// 	filter_page->show();
	// 	filer_name->show();
// 	listDes->show();
// 	type_label->show();
// 	name_label->show();
// 	width_label->show();
// 	heigh_label->show();
// 	red_label->show();
// 	green_label->show();
// 	blue_label->show();
// 	alpha_label->show();
//	listDes->setText("Sprite List");
	m_spriteListDisplayer.show();

}

void EditorScreen::showSceneEditor()
{
	//m_actionCombo->show();

	m_ambientColorR->show();
	m_ambientColorG->show();
	m_ambientColorB->show();
	m_ambientColor_label->show();
	m_objectHolder.show();

}

void EditorScreen::hideSceneEditor()
{
	//m_actionCombo->hide();
	m_ambientColorR->hide();
	m_ambientColorG->hide();
	m_ambientColorB->hide();
	m_ambientColor_label->hide();
	m_objectHolder.hide();

}

void EditorScreen::showAnimateEditor()
{
	//listDes->show();
	m_spriteListDisplayer.show();
	//listDes->setText("F_AnimObj List");
	m_AObjList->show();
	m_actionList->show();
	m_actionLabel->show();
	animation_slide->show();
	playAnimation_button->show();
	pauseAnimation_button->show();
	animation_index_label->show();
	stopAnimation_button->show();
	enableLoop_toggle_label->show();
	animation_enableLoop_toggle->show();
	animation_tick_textbox->show();
	animation_saveAnimation->show();
	animation_tick_label->show();
	animation_sprite_label->show();
	animation_removeAnim->show();
	animation_addAnim->show();
	animation_markAsLoop_toggle->show();
	animation_markAsLoop_label->show();
	animation_applySprite->show();
	animation_addNewAnimation->show();
	animation_deleteAnimation->show();
	animation_newAction->show();
	animation_deleteAction->show();
	animation_isSpriteInverted->show();


	animation_anim_offset_label->show();
	animation_anim_offset_textbox_x->show();
	animation_anim_offset_textbox_y->show();
	animation_anim_offset_button_up->show();
	animation_anim_offset_button_down->show();
	animation_anim_offset_button_left->show();
	animation_anim_offset_button_right->show();
	m_spriteListDisplayer.show();


}

void EditorScreen::hideAnimateEditor()
{
	listDes->hide();
	m_spriteListDisplayer.hide();
	m_AObjList->hide();
	animation_slide->hide();
	m_actionList->hide();
	m_actionLabel->hide();
	playAnimation_button->hide();
	pauseAnimation_button->hide();
	animation_index_label->hide();
	stopAnimation_button->hide();	
	enableLoop_toggle_label->hide();
	animation_enableLoop_toggle->hide();
	animation_tick_textbox->hide();
	animation_saveAnimation->hide();
	animation_tick_label->hide();
	animation_sprite_label->hide();
	animation_removeAnim->hide();
	animation_addAnim->hide();
	animation_markAsLoop_toggle->hide();
	animation_markAsLoop_label->hide();
	animation_applySprite->hide();
	animation_addNewAnimation->hide();
	animation_deleteAnimation->hide();
	animation_newAction->hide();
	animation_deleteAction->hide();
	animation_isSpriteInverted->hide();

	animation_anim_offset_label->hide();
	animation_anim_offset_label->hide();
	animation_anim_offset_textbox_x->hide();
	animation_anim_offset_textbox_y->hide();
	animation_anim_offset_button_up->hide();
	animation_anim_offset_button_down->hide();
	animation_anim_offset_button_left->hide();
	animation_anim_offset_button_right->hide();
}

bool EditorScreen::pickAobj(const CEGUI::EventArgs &e)
{
	if (m_AObjList->getSelectedCount() > 0)
	{
		std::string fullPath = "Assets/F_AObjects/";
		fullPath += m_AObjList->getFirstSelectedItem()->getText().c_str();
		m_fAnimatedObject.init(fullPath);
		
		m_actionList->resetList();
		animation_sprite_label->setText("None");
		animation_tick_textbox->setText("0.0");
		std::map<std::string , Feintgine::F_Animation> animationMap = m_fAnimatedObject.getMap();
		
		for (std::map<std::string, Feintgine::F_Animation>::iterator it = animationMap.begin(); it != animationMap.end(); it++)
		{
			CEGUI::ListboxTextItem * item;
			// 
			item = new CEGUI::ListboxTextItem(it->first, 0);
			item->setSelectionBrushImage("TaharezLook/ListboxSelectionBrush");
			m_actionList->addItem(item);
		}
		m_hasSelectAnimation = true;
		animation_newAction->setEnabled(true);
	
		//m_animatedObject.setPlaying(true);
	}
	return true;
}
// Select an action on action list 
bool EditorScreen::selectAction(const CEGUI::EventArgs &e)
{
	if (m_actionList->getFirstSelectedItem() )
	{
		if (m_actionList->getFirstSelectedItem())
		{
			animation_slide->setScrollPosition(0);
			m_fAnimatedObject.setAnimation(m_actionList->getFirstSelectedItem()->getText().c_str());
			//std::cout << "set animation to " << m_actionList->getFirstSelectedItem()->getText().c_str() << "\n";
			if (m_fAnimatedObject.getCurrentAnimation())
			{
				//m_fAnimatedObject.getCurrentAnimation()->resetAnim();
				//std::cout << "reset anim \n";
				if (m_fAnimatedObject.getCurrentAnimation()->getSize() > 0)
				{
					animation_slide->setStepSize(1.0f / (float)m_fAnimatedObject.getCurrentAnimation()->getSize());

					animation_slide->getDecreaseButton()->setWidth(CEGUI::UDim(0.05f, 1.0f));
					//someSlide->getDecreaseButton()->setXPosition(CEGUI::UDim(-0.01f, 1.0f));
					animation_slide->getIncreaseButton()->setWidth(CEGUI::UDim(0.05f, 1.0f));

					updateAnimationLabel();
					updateAnimation(e);
				}
			}

		}
		onListActionChangedEvent(e);
	}
	return true;
}

void EditorScreen::clearLayer()
{
	std::cout << "row is " << m_layers->getRowCount();
	while (m_layers->getRowCount() > 0)
	{
		m_layers->removeRow(0);
	}
}

bool EditorScreen::layer_delete_protocol(const CEGUI::EventArgs & e)
{
	
	if (m_layers->getFirstSelectedItem())
	{

		if (m_sceneManager.getCurrentScene()->getCurrentLayer())
		{
			m_sceneManager.getCurrentScene()->removeCurrentLayer();
			//m_sceneManager.getCurrentScene()->getCurrentLayer()->clearObject();
			//m_sceneManager.getCurrentScene()->deselectCurrentLayer();
		}

		//deleteCurrentLayer();
		m_layers->removeRow(m_layers->getItemRowIndex(m_layers->getFirstSelectedItem()));
		std::cout << "protocol claled \n";
	
	}
	
	return true;
}

void EditorScreen::loadPacket(const std::string & file)
{
	

}

void EditorScreen::drawSpriteList()
{
	glViewport(SpriteListScreen.x, SpriteListScreen.y, SpriteListScreen.z, SpriteListScreen.w);
	m_spriteListShader.use();

	GLint textureUniform = m_spriteListShader.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	glActiveTexture(GL_TEXTURE0);

	// Camera matrix

	GLint pUniform = m_spriteListShader.getUniformLocation("P");
	glm::mat4 objectsMatrix = m_spriteListCamera.getCameraMatrix();
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &objectsMatrix[0][0]);

	m_spriteBatch.begin();

	m_spriteListDisplayer.draw(m_spriteBatch);

	//m_currentTexture.draw(m_spriteBatch);
// 	for (int i = 0; i < m_slots.size(); i++)
// 	{
// 		m_slots[i].drawObject(m_spriteBatch);
// 	}

	m_spriteBatch.end();
	m_spriteBatch.renderBatch();

	m_spriteListShader.unuse();
	m_spriteListDisplayer.drawBorder(m_debug);

	m_debug.drawBox(glm::vec4(-(SpriteListScreen.z / 2.0f), -(SpriteListScreen.w / 2.0f), SpriteListScreen.z, SpriteListScreen.w), Feintgine::Color(40, 210, 210, 255), 0);


// 	for (int i = 0; i < m_slots.size(); i++)
// 	{
// 		m_slots[i].draw(m_debug);
// 	}
	

	m_debug.end();
	m_debug.render(objectsMatrix, 2.0f);
}

void EditorScreen::switchScreen(int flag)
{
	m_currentMode = flag;
	switch (m_currentMode)
	{
	case T_EDIT_OJECT_MODE:
		drawMode = edit_object_mode;
		hideSceneEditor();
		hideAnimateEditor();
		hideDamakuEditor();
		showObjectEditor();
		m_layers->hide();
		m_addLayerButton->hide();
		m_deleteLayerButton->hide();
		m_sceneManager.showGUIcomponent(false);
		m_enemyEditor.showGUI(false);
		m_luaEditor.showGUI(false);
		break;
	case T_EDIT_SCREEN_MODE:
		m_sceneManager.showGUIcomponent(true);
		drawMode = edit_scene_mode;
		hideObjectEditor();
		hideAnimateEditor();
		hideDamakuEditor();
		showSceneEditor();
		m_layers->show();
		m_addLayerButton->show();
		m_deleteLayerButton->show();
		m_enemyEditor.showGUI(false);
		m_luaEditor.showGUI(false);
		 break;
	case T_EDIT_ANIMATE_MODE:
		std::cout << "edit animate mode \n";
		drawMode = edit_animate_mode;
		m_layers->hide();
		m_addLayerButton->hide();
		m_deleteLayerButton->hide();
		m_sceneManager.showGUIcomponent(false);
		hideObjectEditor();
		hideSceneEditor();
		hideDamakuEditor();
		showAnimateEditor();
		m_enemyEditor.showGUI(false);
		m_luaEditor.showGUI(false);
		std::cout << "edit animate mode end \n";
		break;
	case T_EDIT_DAMAKU_MODE:
		drawMode = edit_damaku_mode;
		m_layers->hide();
		m_addLayerButton->hide();
		m_deleteLayerButton->hide();
		m_sceneManager.showGUIcomponent(false);
		hideObjectEditor();
		hideSceneEditor();
		hideAnimateEditor();
		showDamakuEditor();
		m_enemyEditor.showGUI(false);
		m_luaEditor.showGUI(false);

		break;
	case T_EDIT_ENEMY_MODE:
		drawMode = edit_enemy_mode;
		m_layers->hide();
		m_addLayerButton->hide();
		m_deleteLayerButton->hide();
		m_sceneManager.showGUIcomponent(false);
		hideObjectEditor();
		hideSceneEditor();
		hideAnimateEditor();
		hideDamakuEditor();
		m_enemyEditor.showGUI(true);
		m_luaEditor.showGUI(false);
		break;

	case T_EDIT_LUA_MODE:
		drawMode = edit_lua_mode;
		m_layers->hide();
		m_addLayerButton->hide();
		m_deleteLayerButton->hide();
		m_sceneManager.showGUIcomponent(false);
		hideObjectEditor();
		hideSceneEditor();
		hideAnimateEditor();
		hideDamakuEditor();
		m_enemyEditor.showGUI(false);
		m_luaEditor.showGUI(true);
		break;

	default:

		break;
	}
}

bool EditorScreen::eventSelectSprite()
{

	m_sampleCam.setScale(1.0f);
	m_sampleCam.setPosition(glm::vec2(0));

	return true;
}

bool EditorScreen::addSpriteToObject(const CEGUI::EventArgs &e)
{
	if (m_spriteListDisplayer.getDisplaySample())
	{
		//m_buildObjectTool.addSpriteToObject(m_buildObjectTool.getSelectedSprite(), glm::vec2(0), glm::vec2(1), Feintgine::Color(255, 255, 255, 255), 0.0f, 1.0f);
		m_buildObjectTool.addSpriteToObject(m_spriteListDisplayer.getDisplaySample()->getSprite(), glm::vec2(0), glm::vec2(1),Feintgine::Color(255,255,255,255),0.0f,1.0f);
	}
	
	return true;
}

void EditorScreen::deleteCurrentLayer()
{
	m_scene->removeLayerByName(m_layers->getFirstSelectedItem()->getText().c_str());
}

void EditorScreen::initAmbientTool()
{

	m_ambientColorR  = static_cast<CEGUI::Editbox*> (m_gui.createWidget("TaharezLook/Editbox", 
		glm::vec4(0.8, 0.8, 0.04, 0.03), glm::vec4(0), "m_ambientColorR"));
	m_ambientColorG  = static_cast<CEGUI::Editbox*> (m_gui.createWidget("TaharezLook/Editbox",
		glm::vec4(0.85, 0.8, 0.04, 0.03), glm::vec4(0), "m_ambientColorG"));
	m_ambientColorB = static_cast<CEGUI::Editbox*> (m_gui.createWidget("TaharezLook/Editbox",
		glm::vec4(0.9, 0.8, 0.04, 0.03), glm::vec4(0), "m_ambientColorB"));

	m_ambientColorR->setText(feint_common::Instance()->convertPreciousFloatToString(m_ambientLight.r));
	m_ambientColorG->setText(feint_common::Instance()->convertPreciousFloatToString(m_ambientLight.g));
	m_ambientColorB->setText(feint_common::Instance()->convertPreciousFloatToString(m_ambientLight.b));
	//^[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+){0,10}$
	m_ambientColorR->setValidationString("^[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+){0,10}$");
	m_ambientColorG->setValidationString("^[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+){0,10}$");
	m_ambientColorB->setValidationString("^[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+){0,10}$");

	m_ambientColor_label = static_cast<CEGUI::DefaultWindow *> (m_gui.createWidget("TaharezLook/Label",
		glm::vec4(0.825, 0.745, 0.08, 0.05), glm::vec4(0), "m_ambientColor_label"));
	m_ambientColor_label->setText("Ambient Color");

	m_ambientColorR->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&EditorScreen::onAmbientLightChanged, this));
	m_ambientColorG->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&EditorScreen::onAmbientLightChanged, this));
	m_ambientColorB->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&EditorScreen::onAmbientLightChanged, this));
}

bool EditorScreen::onAmbientLightChanged(const CEGUI::EventArgs &e)
{
	if (m_ambientColorR->getText().size() == 0)
	{
		m_ambientColorR->setText("0.0");
	}
	if (m_ambientColorG->getText().size() == 0)
	{
		m_ambientColorG->setText("0.0");
	}
	if (m_ambientColorB->getText().size() == 0)
	{
		m_ambientColorB->setText("0.0");
	}

	glm::vec3 color = glm::vec3(std::stof(m_ambientColorR->getText().c_str()),
		std::stof(m_ambientColorG->getText().c_str()), std::stof(m_ambientColorB->getText().c_str()));
	m_ambientLight = color;


	return true;
}

bool EditorScreen::fixAnimationScroll(const CEGUI::EventArgs &e)
{
	//std::cout << someSlide->getScrollPosition() << " <<<<<< ---- page size\n";
	float tata = fmod(animation_slide->getScrollPosition(), (1.0f / 200.0f));
	//std::cout << " tata " << tata << "\n";
	if (tata > 0.0f)
	{
	float ff = animation_slide->getScrollPosition();
	animation_slide->setScrollPosition(ff - tata);
	}

	//std::cout << someSlide->getScrollPosition() << " <<<<<< fixx page size\n";

	return true;
}

bool EditorScreen::updateAnimation(const CEGUI::EventArgs &e)
{
	if (m_fAnimatedObject.getCurrentAnimation())
	{
		if (m_fAnimatedObject.getCurrentAnimation()->getSize() > 0)
		{
			//std::cout << "ScrollPosition " << animation_slide->getScrollPosition() << "\n";
			//std::cout << "CurrentAnimation" << m_fAnimatedObject.getCurrentAnimation()->getSize() << "\n";
			//std::cout << "Result " << (float)(animation_slide->getScrollPosition() * m_fAnimatedObject.getCurrentAnimation()->getSize()) << "\n";


			// This would resolve the animation bug in the editor but, I really don't know why it does that, 
			// you may think that because of the convert from float to int, but it only need to run once, if 
			// there is a bug, add +0.99999f and then comment it again will fix the bug
			int result = (animation_slide->getScrollPosition() * m_fAnimatedObject.getCurrentAnimation()->getSize()) + 0.99999f;

			//std::cout << "reinforce " << result << "\n";
			m_fAnimatedObject.getCurrentAnimation()->setAnimIndex(result);
			animation_tick_textbox->setText(
				feint_common::Instance()->convertPreciousFloatToString(
					m_fAnimatedObject.getCurrentAnimation()->getCurrentAnim()->time));
			animation_isSpriteInverted->setSelected(m_fAnimatedObject.getCurrentAnimation()->getCurrentAnim()->sprite.isInverted());
			if (m_fAnimatedObject.getCurrentAnimation()->getCurrentIndex() < m_fAnimatedObject.getCurrentAnimation()->getSize())
			{
				animation_sprite_label->setText(m_fAnimatedObject.getCurrentAnimation()->getCurrentAnim()->sprite.getFullPacket());

				if (m_fAnimatedObject.getCurrentAnimation()->getCurrentIndex() == 0
					&& m_fAnimatedObject.getCurrentAnimation()->getLoopAnim() == 0)
				{
					animation_markAsLoop_toggle->disable();
				}
				else
				{
					animation_markAsLoop_toggle->enable();
				}

				if (m_fAnimatedObject.getCurrentAnimation()->getCurrentIndex() == m_fAnimatedObject.getCurrentAnimation()->getLoopAnim())
				{
					animation_markAsLoop_toggle->setSelected(true);
				}
				else
				{
					animation_markAsLoop_toggle->setSelected(false);
				}
				m_fAnimatedObject.setVisisble(true);
			}
		}
		if (m_fAnimatedObject.getCurrentAnimation()->getCurrentIndex() == m_fAnimatedObject.getCurrentAnimation()->getSize())
		{
			m_fAnimatedObject.getCurrentAnimation()->setAnimIndex(m_fAnimatedObject.getCurrentAnimation()->getCurrentIndex() - 1);
		}
		//std::cout << "index " << m_fAnimatedObject.getCurrentAnimation()->getCurrentIndex() << "/" << m_fAnimatedObject.getCurrentAnimation()->getSize() <<" \n";
		//std::cout << "scroll " << animation_slide->getScrollPosition() * m_fAnimatedObject.getCurrentAnimation()->getSize() << "\n";
	}
	else
	{
		animation_tick_textbox->setText("0.0");
		animation_sprite_label->setText("End");
		m_fAnimatedObject.setVisisble(false);

	}
	return true;
}

bool EditorScreen::playAnimation(const CEGUI::EventArgs &e)
{
	
	if (m_fAnimatedObject.getCurrentAnimation())
	{
		m_fAnimatedObject.getCurrentAnimation()->playAnimation(loopCount,m_fAnimatedObject.getCurrentAnimation()->getCurrentIndex());
		updateAnimation(e);
	}
	m_isAnimationPlaying = true;
	return true;
}

std::string EditorScreen::getFrameDataFromAnim(const Feintgine::F_AnimatedObject & obj)
{
	std::string value = "0/0";
	if (obj.getCurrentAnimation())
	{
		if (obj.getCurrentAnimation()->getSize() == 0)
		{
			return value;
		}
		value = std::to_string(obj.getCurrentAnimation()->getCurrentIndex());
		value += "/";
		value += std::to_string(obj.getCurrentAnimation()->getSize());
	}

	return value;
}

void EditorScreen::updateAnimationLabel()
{
	animation_index_label->setText(getFrameDataFromAnim(m_fAnimatedObject).c_str());
	if (!m_isMouseLeftHold)
	{
		if (m_fAnimatedObject.getCurrentAnimation())
		{

			animation_slide->setScrollPosition((1.0f / (float)m_fAnimatedObject.getCurrentAnimation()->getSize()) *
				(float)m_fAnimatedObject.getCurrentAnimation()->getCurrentIndex());
		}
	}

}

bool EditorScreen::pauseAnimation(const CEGUI::EventArgs &e)
{
	if (m_fAnimatedObject.getCurrentAnimation())
	{
		m_fAnimatedObject.getCurrentAnimation()->stop();
	}
	m_isAnimationPlaying = false;
	return true;
}

void EditorScreen::togglePlayAnimation()
{
	
	CEGUI::EventArgs e;
	m_isAnimationPlaying = !m_isAnimationPlaying;

	if(m_isAnimationPlaying)
	{	
		playAnimation(e);
	}
	else
	{
		pauseAnimation(e);
	
	}
}


bool EditorScreen::stopAnimation(const CEGUI::EventArgs &e)
{

	if (m_fAnimatedObject.getCurrentAnimation())
	{
		m_fAnimatedObject.getCurrentAnimation()->setAnimIndex(0);
		m_fAnimatedObject.getCurrentAnimation()->stop();
	}
	return true;
}

bool EditorScreen::onLoopToggle(const CEGUI::EventArgs &e)
{
	if (animation_enableLoop_toggle->isSelected())
	{
		loopCount = -1;
	}
	else
	{
		loopCount = 1;
	}
	return true;
}

bool EditorScreen::recheckTick(const CEGUI::EventArgs &e)
{
	if (animation_tick_textbox->getText().size() == 0)
	{
		animation_tick_textbox->setText("0");	
	}
	return true;
}

bool EditorScreen::updateAnimTick(const CEGUI::EventArgs &e)
{

	if (m_fAnimatedObject.getCurrentAnimation())
	{
		m_fAnimatedObject.getCurrentAnimation()->setCurrentAnimTime(std::stof(animation_tick_textbox->getText().c_str()));
	}
	return true;
}

bool EditorScreen::saveAnimation(const CEGUI::EventArgs &e)
{

	m_fAnimatedObject.saveToFile(m_fAnimatedObject.getName());
	
	return true;
}

bool EditorScreen::onMarkAsLoopToggled(const CEGUI::EventArgs &e)
{
	
	if (m_markable)
	{
		if (animation_markAsLoop_toggle->isSelected())
		{
			m_fAnimatedObject.getCurrentAnimation()->setLoopAnim(m_fAnimatedObject.getCurrentAnimation()->getCurrentIndex());
			//animation_markAsLoop_toggle->setSelected(false);
		}
		else
		{
			//animation_markAsLoop_toggle->setSelected(true);
			m_fAnimatedObject.getCurrentAnimation()->setLoopAnim(0);
		}
	}
	return true;
}

bool EditorScreen::onMarkReady(const CEGUI::EventArgs &e)
{
	
	m_markable = true;
	return true;
}

bool EditorScreen::onMarkAsStop(const CEGUI::EventArgs &e)
{
	m_markable = false;	
	return true;
}

bool EditorScreen::onAddAnimButtonClicked(const CEGUI::EventArgs &e)
{
	
	if (m_fAnimatedObject.getCurrentAnimation())
	{
		if (m_fAnimatedObject.getCurrentAnimation()->getSize() == 0)
		{
			Feintgine::f_anim nAnim;
			m_fAnimatedObject.getCurrentAnimation()->addAnim(nAnim,true);
			animation_slide->setStepSize(1.0f / (float)m_fAnimatedObject.getCurrentAnimation()->getSize());
			std::cout << "hit \n";
		}
		else
		{
			m_fAnimatedObject.getCurrentAnimation()->insertAnim();
			animation_slide->setStepSize(1.0f / (float)m_fAnimatedObject.getCurrentAnimation()->getSize());
			animation_slide->scrollForwardsByStep();
			animation_tick_textbox->setText("0");

			
		}
		updateAnimation(e);
		updateAnimationLabel();
		
		
	}
	
	return true;
}

bool EditorScreen::onRemoveAnimButtonCLicked(const CEGUI::EventArgs &e)
{
	if (m_fAnimatedObject.getCurrentAnimation())
	{
		if (m_fAnimatedObject.getCurrentAnimation()->getSize() > 0)
		{
			m_fAnimatedObject.getCurrentAnimation()->removeAnimAt(m_fAnimatedObject.getCurrentAnimation()->getCurrentIndex());
			animation_slide->setStepSize(1.0f / (float)m_fAnimatedObject.getCurrentAnimation()->getSize());
			updateAnimation(e);
		}
	}
	return true;
}

bool EditorScreen::onApplyToCurrentAnimButtonCLicked(const CEGUI::EventArgs &e)
{

	if (m_fAnimatedObject.getCurrentAnimation())
	{
		if (m_fAnimatedObject.getCurrentAnimation()->getSize() > 0)
		{
			if (m_fAnimatedObject.getCurrentAnimation()->getAnims().size() > 0)
			{

				m_fAnimatedObject.getCurrentAnimation()->assignSpriteToCurrentAnim(m_spriteListDisplayer.getDisplaySample()->getSprite());
				updateAnimation(e);
			}
		}
		
	}
	return true;
}

bool EditorScreen::destroyNewAnimationScreen(const CEGUI::EventArgs &e)
{
	if (animation_newAnimationWindow)
	{
		animation_newAnimationWindow->destroy();
	}	
	return true;
}

bool EditorScreen::animation_new_protocol(const CEGUI::EventArgs &e)
{
	animation_newAnimationWindow = static_cast<CEGUI::Window*>
		(m_gui.createWidget("TaharezLook/FrameWindow", glm::vec4(0.3, 0.2, 0.25, 0.25), glm::vec4(0), "animation_newAnimationWindow"));
	animation_newAnimationWindow->setText("Animation Creation");
	animation_addNewAnimation_sub = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button",
		glm::vec4(0.4, 0.65, 0.2, 0.15), glm::vec4(0), "animation_addNewAnimation_sub"));
	animation_addNewAnimation_sub->setText("Create");

	animation_addNewAnimation_textBox = static_cast<CEGUI::Editbox *>(m_gui.createWidget("TaharezLook/Editbox",
		glm::vec4(0.22, 0.4, 0.55, 0.15), glm::vec4(0), "animation_addNewAnimation_textBox"));

	animation_addNewAnimation_sub_label =  static_cast<CEGUI::DefaultWindow *> (m_gui.createWidget("TaharezLook/Label",
		glm::vec4(0.3, 0.2, 0.35, 0.2), glm::vec4(0), "animation_addNewAnimation_sub_label"));
	animation_addNewAnimation_sub_label->setText("Animation Name");

	animation_newAnimationWindow->addChild(animation_addNewAnimation_sub);
	animation_newAnimationWindow->addChild(animation_addNewAnimation_textBox);
	animation_newAnimationWindow->addChild(animation_addNewAnimation_sub_label);

	animation_addNewAnimation_sub->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&EditorScreen::createAnimation, this));

	animation_newAnimationWindow->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked, CEGUI::Event::Subscriber(&EditorScreen::destroyNewAnimationScreen, this));
	
	return true;
}

bool EditorScreen::createAnimation(const CEGUI::EventArgs &e)
{

	if (animation_addNewAnimation_textBox->getText() == "")
	{
		feint_common::Instance()->showMessageBox("Create Animation Failed", "Name must not be empty !");
	}
	else
	{		
		std::string animationName = animation_addNewAnimation_textBox->getText().c_str();
		
		Feintgine::F_AnimatedObject animation;	
		animation.saveToFile(animationName);
		refresh();
		destroyNewAnimationScreen(e);
	}
	
	return true;
}


bool EditorScreen::onAnimationListChange(const CEGUI::EventArgs &e)
{

	if (m_AObjList->getSelectedCount() > 0)
	{
		animation_deleteAnimation->setEnabled(true);
	}
	else
	{
		animation_deleteAnimation->setEnabled(false);
	}

	return true;
}

bool EditorScreen::onAnimationDeleteClick(const CEGUI::EventArgs &e)
{	
	std::string animationName = m_AObjList->getFirstSelectedItem()->getText().c_str();
	std::string fullPath = "./Assets/F_AObjects/" + animationName;
	std::cout << "Deleting " << fullPath << "\n";
	if (remove(fullPath.c_str()) != 0)
	{
		std::cout << "delete file not OK  \n";
	}
	else
	{
		std::cout << "delete file successfully \n";
	}
	Feintgine::F_AnimatedObject fresh;
	m_fAnimatedObject = fresh;
	m_AObjList->removeItem(m_AObjList->getFirstSelectedItem());

	for (int i = 0; i < m_actionList->getItemCount(); i++)
	{
		m_actionList->removeItem(m_actionList->getListboxItemFromIndex(i));
	}
	if (m_actionList->getFirstSelectedItem())
	{
		m_actionList->removeItem(m_actionList->getFirstSelectedItem());
	}
	m_hasSelectAnimation = false;
	animation_newAction->setEnabled(false);
	onAnimationListChange(e);
	return true;
}

bool EditorScreen::action_new_protocol(const CEGUI::EventArgs &e)
{
	action_newAnimationWindow = static_cast<CEGUI::Window*>
		(m_gui.createWidget("TaharezLook/FrameWindow", glm::vec4(0.3, 0.2, 0.25, 0.25), glm::vec4(0), "action_newAnimationWindow"));
	action_newAnimationWindow->setText("Animation Creation");
	animation_addNewAction_sub = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button",
		glm::vec4(0.4, 0.65, 0.2, 0.15), glm::vec4(0), "animation_addNewAction_sub"));
	animation_addNewAction_sub->setText("Create");

	animation_addNewAction_textBox = static_cast<CEGUI::Editbox *>(m_gui.createWidget("TaharezLook/Editbox",
		glm::vec4(0.22, 0.4, 0.55, 0.15), glm::vec4(0), "animation_addNewAction_textBox"));

	animation_addNewAction_sub_label = static_cast<CEGUI::DefaultWindow *> (m_gui.createWidget("TaharezLook/Label",
		glm::vec4(0.3, 0.2, 0.35, 0.2), glm::vec4(0), "animation_addNewAction_sub_label"));
	animation_addNewAction_sub_label->setText("Action Name");

	action_newAnimationWindow->addChild(animation_addNewAction_sub);
	action_newAnimationWindow->addChild(animation_addNewAction_textBox);
	action_newAnimationWindow->addChild(animation_addNewAction_sub_label);

	animation_addNewAction_sub->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&EditorScreen::createAction, this));

	action_newAnimationWindow->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked,
		CEGUI::Event::Subscriber(&EditorScreen::destroyNewActionScreen, this));

	return true;
}

bool EditorScreen::destroyNewActionScreen(const CEGUI::EventArgs &e)
{
	if (action_newAnimationWindow)
	{
		action_newAnimationWindow->destroy();
	}
	return true;
}

bool EditorScreen::createAction(const CEGUI::EventArgs &e)
{

	if (animation_addNewAction_textBox->getText() == "")
	{
		feint_common::Instance()->showMessageBox("Create Animation Failed", "Name must not be empty !");
	}
	else
	{
		m_fAnimatedObject.addNewAnimation(animation_addNewAction_textBox->getText().c_str());
 		CEGUI::ListboxTextItem * item;
 		item = new CEGUI::ListboxTextItem(animation_addNewAction_textBox->getText().c_str(), 0);
 		item->setSelectionBrushImage("TaharezLook/ListboxSelectionBrush");
 		m_actionList->addItem(item);
 		
 		destroyNewActionScreen(e);
	}
	return true;
}

bool EditorScreen::onDeleteActionButtonClicked(const CEGUI::EventArgs &e)
{
	if (m_actionList->getFirstSelectedItem())
	{
		m_fAnimatedObject.removeAnimation(m_actionList->getFirstSelectedItem()->getText().c_str());
		m_actionList->removeItem(m_actionList->getFirstSelectedItem());
		
	}

	return true;
}

bool EditorScreen::onListActionChangedEvent(const CEGUI::EventArgs &e)
{
	if (m_actionList->getFirstSelectedItem())
	{
		animation_deleteAction->setEnabled(true);
	}
	else
	{
		animation_deleteAction->setEnabled(false);
	}

	return true;
}

bool EditorScreen::onSpriteInvertToggleBoxClicked(const CEGUI::EventArgs &e)
{
	if (m_fAnimatedObject.getCurrentAnimation())
	{
		m_fAnimatedObject.getCurrentAnimation()->getCurrentAnim()->sprite.setInvert(animation_isSpriteInverted->isSelected());
	}

	return true;
}

bool EditorScreen::onOffsetAnimationChangedX(const CEGUI::EventArgs &e)
{
	glm::vec2 offsetPos;
	if (animation_anim_offset_textbox_x->getText().size() > 0 )
	{
		if (m_fAnimatedObject.getCurrentAnimation()->getCurrentAnim())
		{


			offsetPos = glm::vec2(std::stof(animation_anim_offset_textbox_x->getText().c_str()),
				m_fAnimatedObject.getCurrentAnimation()->getCurrentAnim()->offset.y);
		}
	}

	if (m_fAnimatedObject.getCurrentAnimation()->getCurrentAnim() )
	{
		m_fAnimatedObject.getCurrentAnimation()->getCurrentAnim()->offset = offsetPos;
	}
	return true;
}

bool EditorScreen::onOffsetAnimationChangedY(const CEGUI::EventArgs &e)
{
	glm::vec2 offsetPos;

	if (animation_anim_offset_textbox_y->getText().size() > 0)
	{
		if (m_fAnimatedObject.getCurrentAnimation()->getCurrentAnim())
		{


			offsetPos = glm::vec2(m_fAnimatedObject.getCurrentAnimation()->getCurrentAnim()->offset.x,
				std::stof(animation_anim_offset_textbox_y->getText().c_str()));
		}
	}

	if (m_fAnimatedObject.getCurrentAnimation()->getCurrentAnim())
	{
		m_fAnimatedObject.getCurrentAnimation()->getCurrentAnim()->offset = offsetPos;
	}
	return true;
}

bool EditorScreen::onOffsetPosChangedLeft(const CEGUI::EventArgs &e)
{
	float x_val = std::stof(animation_anim_offset_textbox_x->getText().c_str());
	x_val -= 1.0f;
	animation_anim_offset_textbox_x->setText(feint_common::Instance()->convertPreciousFloatToString(x_val));
	


	return true;
}

bool EditorScreen::onOffsetPosChangedRight(const CEGUI::EventArgs &e)
{
	float x_val = std::stof(animation_anim_offset_textbox_x->getText().c_str());
	x_val += 1.0f;
	animation_anim_offset_textbox_x->setText(feint_common::Instance()->convertPreciousFloatToString(x_val));

	//glm::vec2 offsetPos(x_val, m_fAnimatedObject.getCurrentAnimation()->getCurrentAnim()->offset.y);
	
	return true;
}

bool EditorScreen::onOffsetPosChangedUp(const CEGUI::EventArgs &e)
{
	float y_val = std::stof(animation_anim_offset_textbox_y->getText().c_str());
	y_val += 1.0f;
	animation_anim_offset_textbox_y->setText(feint_common::Instance()->convertPreciousFloatToString(y_val));

	//glm::vec2 offsetPos(m_fAnimatedObject.getCurrentAnimation()->getCurrentAnim()->offset.x, y_val);
	
	return true;
}

bool EditorScreen::onOffsetPosChangedDown(const CEGUI::EventArgs &e)
{
	float y_val = std::stof(animation_anim_offset_textbox_y->getText().c_str());
	y_val -= 1.0f;
	animation_anim_offset_textbox_y->setText(feint_common::Instance()->convertPreciousFloatToString(y_val));
	//glm::vec2 offsetPos(m_fAnimatedObject.getCurrentAnimation()->getCurrentAnim()->offset.x, y_val);
	
	return true;
}

void EditorScreen::drawDamaKuScreen()
{
	glViewport(EditDamaku.x, EditDamaku.y, EditDamaku.z, EditDamaku.w);

	m_editDamakuShader.use();

	GLint textureUniform = m_editDamakuShader.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	glActiveTexture(GL_TEXTURE0);
	// Camera matrix

	GLint pUniform = m_editDamakuShader.getUniformLocation("P");
	glm::mat4 objectsMatrix = m_editDamakuCamera.getCameraMatrix();
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &objectsMatrix[0][0]);

	m_spriteBatch.begin();

	m_paternEditor.draw(m_spriteBatch);

	m_spriteBatch.end();
	m_spriteBatch.renderBatch();

	m_editDamakuShader.unuse();

	m_debug.drawBox(glm::vec4(-(EditDamaku.z / 2.0f), -(EditDamaku.w / 2.0f), EditDamaku.z, EditDamaku.w), Feintgine::Color(210, 0, 0, 255), 0);

	objectsMatrix = m_editDamakuCamera_static.getCameraMatrix();
	m_debug.end();
	m_debug.render(objectsMatrix, 2.0f);
}

void EditorScreen::hideDamakuEditor()
{
	m_spriteListDisplayer.hide();
	m_paternEditor.show(false);
}

void EditorScreen::showDamakuEditor()
{
	m_spriteListDisplayer.show();
	m_paternEditor.show(true);
}

void EditorScreen::toggetDebugTiles()
{
	if (debugTiles)
	{
		debugTiles = false;
	}
	else
	{
		debugTiles = true;
	}
}

void EditorScreen::showEditEnemyEditor()
{

}

void EditorScreen::hideEditEnemyEditor()
{

}

  