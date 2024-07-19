#include "SceneManager.h"



SceneManager::SceneManager()
{
	 m_currentScene = nullptr;
}


SceneManager::~SceneManager()
{
}

bool SceneManager::createScene(const std::string & fileName)
{
	std::cout << "call scan \n";
	std::string fullType = fileName +".fsc";
	std::cout << "search for file " << fileName << "\n";
	if (listdir("./Scence", 0, fullType.c_str()) == -1)
	{
		return false;
	}
	if (!m_currentScene)
	{
		m_currentScene = new Feintgine::Fg_scene();
		m_currentScene->createNew(fileName);
	}
	else
	{
		if (feint_common::Instance()->showConfirmationBox("Scene Creation Confirmation", "there is a scene still open, you want to create a new one ? "))
		{
			std::cout << "Save the current Scene (" << m_currentScene->getName() << "), create new one (" << fileName << ") \n";
			m_currentScene->createNew(fileName);
		}
		else
		{
			std::cout << "Did not create new scene \n";			
		}

	}
	return true;
}

int SceneManager::listdir(const char *name, int level, const char *fileName)
{
	//std::cout << "scan on " << name << "\n";
	DIR *dir;
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
			listdir(path, level + 1, fileName);
		}
		else
		{
			printf(" >>>>> %*s- %s\n", level * 2, "", entry->d_name);
			std::cout << "compare name : " << fileName << " to " << entry->d_name << "\n";
			
			if (!std::strcmp(fileName, entry->d_name) )
			{
				std::cout << "found exist file \n";
				return -1;
			}

		}
	} while (entry = readdir(dir));
	std::cout << "no exist file found \n";

	closedir(dir);
	return 0;

}

void SceneManager::init(Feintgine::Camera2D * cam, Feintgine::GUI * gui)
{

	m_gui = gui;
	m_sceneCam = cam;
	EditorProperty::Instance()->setSpacingOffset(glm::vec2(64));
	gridOffset_label = static_cast<CEGUI::DefaultWindow*> (gui->createWidget("TaharezLook/Label", glm::vec4(0.86, 0.46, 0.08, 0.02), glm::vec4(0), "gridOffset_label"));
	gridOffset_label->setText("Grid offset");
	gridOffset_x = static_cast<CEGUI::Editbox*> (gui->createWidget("TaharezLook/Editbox", glm::vec4(0.85, 0.5, 0.04, 0.03), glm::vec4(0), "gridOffset_x"));
	gridOffset_y = static_cast<CEGUI::Editbox*> (gui->createWidget("TaharezLook/Editbox", glm::vec4(0.9, 0.5, 0.04, 0.03), glm::vec4(0), "gridOffset_y"));

	addBrushButton = static_cast<CEGUI::PushButton *>
		(gui->createWidget("TaharezLook/Button", glm::vec4(0.85, 0.62, 0.08, 0.04), glm::vec4(0), "addBrushButton"));
	addBrushButton->setText("Add Brush");

	//onAddBurshClick
	//addBrushButton

	gridOffset_x->setValidationString("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)");
	gridOffset_y->setValidationString("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)");
	updateSpacingOffset();
	//gridOffset_x->setText(feint_common::Instance()->convertPreciousFloatToString(spacingOffset.x,1).c_str());
	//gridOffset_y->setText(feint_common::Instance()->convertPreciousFloatToString(spacingOffset.y, 1).c_str());
	gridOffset_x->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&SceneManager::onSpacingXOffsetChanged, this));
	gridOffset_y->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&SceneManager::onSpacingYOffsetChanged, this));

	 
	gridApply = static_cast<CEGUI::PushButton *>
		(gui->createWidget("TaharezLook/Button", glm::vec4(0.85, 0.55, 0.12, 0.04), glm::vec4(0), "gridApply"));
	gridApply->setText("Apply Current Object");
	gridApply->subscribeEvent(CEGUI::PushButton::EventMouseClick, CEGUI::Event::Subscriber(&SceneManager::onApplyGridClick, this));
	addBrushButton->subscribeEvent(CEGUI::PushButton::EventMouseClick, CEGUI::Event::Subscriber(&SceneManager::onAddBurshClick, this));

	
		
}

void SceneManager::loadIcons()
{
	m_selectIcon.init(Feintgine::ResourceManager::getTexture("./Assets/Lazy/select.png"), glm::vec2(450, 0),glm::vec2(44), Feintgine::Color(255, 255, 255, 255));
	m_moveIcon.init(Feintgine::ResourceManager::getTexture("./Assets/Lazy/move.png"), glm::vec2(520, 0), glm::vec2(44), Feintgine::Color(255, 255, 255, 255));
}

int SceneManager::browseScene(const char *name, int level, CEGUI::Listbox * listBox)
{
	//std::cout << "scan on " << name << "\n";
	DIR *dir;
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
			browseScene(path, level + 1, listBox);
		}
		else
		{
		
				
			std::cout << "scene " << entry->d_name << " found \n";
			CEGUI::ListboxTextItem * item  =new CEGUI::ListboxTextItem(entry->d_name, 0, 0, false, false);
			listBox->addItem(item);
			const CEGUI::Image* sel_img = &CEGUI::ImageManager::getSingleton().get("TaharezLook/MultiListSelectionBrush");

			item->setSelectionBrushImage(sel_img);
// 			if (texturePath.find("./Scene/") != std::string::npos)
// 			{
// 				
// 				
// 					
// 				
// 			}

		}
	} while (entry = readdir(dir));


	closedir(dir);
	return 0;

}

void SceneManager::closeCurrentScene()
{
	if (m_currentScene)
	{
		delete m_currentScene;
		m_currentScene = nullptr;
	}
}

void SceneManager::loadSceneFromFile(const std::string & filePath, CEGUI::MultiColumnList * list)
{
	if (!m_currentScene)
	{
		//createScene()
		m_currentScene = new Feintgine::Fg_scene();
		m_currentScene->loadSceneFromFile(filePath,list);

	}
	else
	{
		m_currentLayer = m_currentScene->getCurrentLayer();
		if (m_currentLayer)
		{
			 m_currentScene->findAndSetCurrentLayer(m_currentLayer->getName());
		}
		else
		{
			std::cout << "now no more selected layer \n";
		}

		std::cout << "reach here \n";
// 		for (int i = 0; i < m_currentScene->getLayers().size(); i++)
// 		{
// 			std::cout << "clear << " << i << "\n";
// 			m_currentScene->getLayers().erase(m_currentScene->getLayers().begin() + i);
// 		}
		
		
		std::cout << "reach after clear \n";
		m_currentScene->loadSceneFromFile(filePath,list);
	}
}

void SceneManager::handleInput(Feintgine::InputManager & inputManager, bool isSelected, const Feintgine::F_Object &object, CEGUI::MultiColumnList * list)
{

	
	if (inputManager.isKeyPressed(SDLK_1))
	{
		m_currentMode = SELECT_MODE;
	}
	if (inputManager.isKeyPressed(SDLK_2))
	{
		m_currentMode = EDIT_MODE;
	}

	if (inputManager.isKeyPressed(SDLK_g))
	{
		if (isGrid)
		{
			isGrid = false;
		}
		else
		{
			isGrid = true;
		}
		
	}

	if (!m_currentScene)
	{
		return;
	}
	else
	{

		m_currentLayer = m_currentScene->getCurrentLayer();
		if (m_currentLayer)
		{
			if (inputManager.isKeyPressed(SDLK_ESCAPE))
			{
				m_currentLayer->clearAllSelectedObject();
			}
			if (m_currentMode == SELECT_MODE)
			{
				if (isSelected)
				{
					if (inputManager.isKeyPressed(SDL_BUTTON_LEFT))
					{

						m_currentLayer->addObjectToLayer(object);
						std::cout << "added " << object.getName() << " \n";
					}
					if (isGrid)
					{


						if (inputManager.isKeyDown(SDLK_LSHIFT))
						{
							if (inputManager.isKeyDown(SDL_BUTTON_LEFT))
							{
								
								if (savedPos != object.getPos())
								{
									m_currentLayer->addObjectToLayer(object);
									savedPos = object.getPos();
								}
								
								
							}
						}
					}

				}


				if (m_currentLayer)
				{

					if (inputManager.isKeyPressed(SDLK_DELETE))
					{
						m_currentLayer->removeSelectedObjects();

					}
					if (inputManager.isKeyDown(SDLK_LCTRL))
					{
						if (inputManager.isKeyPressed(SDL_BUTTON_LEFT))
						{
							m_currentLayer->handleDeselectObject();
						}
					}
					else
					{
						if (inputManager.isKeyPressed(SDL_BUTTON_LEFT))
						{
							m_currentLayer->handleSelectObject();
						}
					}
				}
				
			}
			if (m_currentMode == EDIT_MODE)
			{
				if (m_currentLayer)
				{
					if (inputManager.isKeyDown(SDL_BUTTON_LEFT))
					{
						if (!i_move)
						{
							i_move = true;
							firstClick = curMousePos;
							
							//std::cout << "get first click " << feint_common::Instance()->convertVec2toString(firstClick) << "\n";
							m_currentLayer->moveSelectedObject(firstClick, true);
							m_currentLayer->updateDepth();
						}
						if (i_move)
						{
							if (isGrid)
							{

								glm::vec2 SpacingOffset = EditorProperty::Instance()->getSpacingOffset();
								float standardX = 64.0f;
								float standardY = 64.0f;
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
								m_currentLayer->moveSelectedObject(gridedPos, false);
							}
							else
							{
								glm::vec2 secondClick = curMousePos;
								glm::vec2 offset = secondClick - firstClick;// -secondClick;
								glm::vec2 finalPos = secondClick + offset;
								m_currentLayer->moveSelectedObject(finalPos, false);
							}
							m_currentLayer->updateDepth();
							//i_move = false;
						}
					}
					else
					{
						i_move = false;
						m_currentLayer->clearObjectOffset();
					}
				}
			}
		}

		
	
	}
	
}



void SceneManager::update(const glm::vec2 & mousePos)
{
	if (m_currentScene)
	{
		//std::cout << "second  " << feint_common::Instance()->convertVec2toString(mousePos) << "\n";
		curMousePos = mousePos;
		m_currentScene->editorUpdate(mousePos);
		
	}
}

void SceneManager::drawBox(Feintgine::DebugRender & debugRenderer)
{
	if (m_currentScene)
	{
		m_currentScene->drawBox(debugRenderer);
	}
}

void SceneManager::selectCurrentLayer(const std::string & layerName)
{
	if (m_currentScene)
	{
		m_currentScene->findAndSetCurrentLayer(layerName);
	}
}


void SceneManager::draw(Feintgine::SpriteBatch & spriteBatch)
{
	if (m_currentScene)
	{
		m_currentScene->drawScene(spriteBatch);
	}
}

void SceneManager::showGUIcomponent(bool val)
{
	if (val)
	{
		gridOffset_label->show();
		gridOffset_x->show();
		gridOffset_y->show();
		gridApply->show();
		addBrushButton->show();
		
	}
	else
	{
		gridOffset_label->hide();
		gridOffset_x->hide();
		gridOffset_y->hide();
		gridApply->hide();
		addBrushButton->hide();
	}
}

void SceneManager::drawIcons(Feintgine::SpriteBatch & spriteBatch)
{
	
	m_selectIcon.draw(spriteBatch);
	m_moveIcon.draw(spriteBatch);
}

void SceneManager::drawLight(Feintgine::LightBatch & lightBatch)
{
	if (m_currentScene)
	{
		m_currentScene->drawLight(lightBatch);
	}
}



void SceneManager::drawIconsBorder(Feintgine::DebugRender & debugRenderer)
{
	if (m_currentMode == SELECT_MODE)
	{
		m_selectIcon.drawBox(debugRenderer);
	}
	if (m_currentMode == EDIT_MODE)
	{
		m_moveIcon.drawBox(debugRenderer);
	}
	
}

bool SceneManager::onSpacingXOffsetChanged(const CEGUI::EventArgs &e)
{
	glm::vec2 originalSpacing = EditorProperty::Instance()->getSpacingOffset();
	if (std::stof(gridOffset_x->getText().c_str()) != NULL)
	{
		originalSpacing.x = std::stof(gridOffset_x->getText().c_str());
		EditorProperty::Instance()->setSpacingOffset(originalSpacing);
		//gridOffset_x->setText(feint_common::Instance()->convertPreciousFloatToString(originalSpacing.x, 1).c_str());
		//updateSpacingOffset();
	}
	
	
	
	return true;
}

bool SceneManager::onAddBurshClick(const CEGUI::EventArgs &e)
{
	if (m_currentScene)
	{


		if (m_currentLayer)
		{
			m_addBrushWindow = static_cast<CEGUI::Window*>
				(m_gui->createWidget("TaharezLook/FrameWindow", glm::vec4(0.5, 0.5, 0.4, 0.4), glm::vec4(0), "m_addBrushWindow"));

	 		CEGUI::PushButton * AcceptButton = static_cast<CEGUI::PushButton*>(m_gui->createWidget("TaharezLook/Button", glm::vec4(0.4, 0.8, 0.14, 0.08), glm::vec4(0), "OK_AddBrush_button"));
	 		AcceptButton->setText("Create");


			//AcceptButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&EditorScreen::addLayer, this));
			//m_addLayerWindow->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked, CEGUI::Event::Subscriber(&EditorScreen::destroyObjectPannel, this));
			m_addBrushWindow->setText("Add Brush");

	 		CEGUI::DefaultWindow * edit1_label = static_cast<CEGUI::DefaultWindow *> (m_gui->createWidget("TaharezLook/Label", glm::vec4(0.01, 0.1, 0.12, 0.1), glm::vec4(0), "addlayer_name_label"));
	 		edit1_label->setText("Name");
	 		CEGUI::DefaultWindow * edit2_label = static_cast<CEGUI::DefaultWindow *> (m_gui->createWidget("TaharezLook/Label", glm::vec4(0.01, 0.28, 0.12, 0.1), glm::vec4(0), "addbrush_depth_label"));
	 		edit2_label->setText("Depth");
			CEGUI::DefaultWindow * edit3_label = static_cast<CEGUI::DefaultWindow *> (m_gui->createWidget("TaharezLook/Label", glm::vec4(0.65, 0.04, 0.12, 0.1), glm::vec4(0), "addlayer_depth_label"));
			edit3_label->setText("Texture");
	// 
	// 
			texturePicker = static_cast<CEGUI::Combobox*>
				(m_gui->createWidget("TaharezLook/Combobox", glm::vec4(0.5, 0.12, 0.4, 0.22), glm::vec4(0), "texturePicker"));
	 		m_brushName = static_cast<CEGUI::Editbox *>(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.13, 0.1, 0.2, 0.08), glm::vec4(0), "edit_layerName"));
			m_brushDepth = static_cast<CEGUI::Editbox *>(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.13, 0.28, 0.2, 0.08), glm::vec4(0), "edit_layerDepth"));
	// 
			CEGUI::DefaultWindow * edit4_label = static_cast<CEGUI::DefaultWindow *> (m_gui->createWidget("TaharezLook/Label", glm::vec4(0.08, 0.43, 0.15, 0.1), glm::vec4(0), "edit4_label"));
			edit4_label->setText("UV Mode");
			brushUVMode = static_cast<CEGUI::ToggleButton*>
				(m_gui->createWidget("TaharezLook/RadioButton", glm::vec4(0.05, 0.45, 0.04, 0.04), glm::vec4(0), "brushDimMode"));
			brushUVMode->setSelected(true);

		
			m_brushCollum = static_cast<CEGUI::Editbox *>(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.63, 0.35, 0.2, 0.08), glm::vec4(0), "m_brushCollum"));
			m_brushRow = static_cast<CEGUI::Editbox *>(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.63, 0.45, 0.2, 0.08), glm::vec4(0), "m_brushRow"));

			m_brushPosX = static_cast<CEGUI::Editbox *>(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.3, 0.6, 0.2, 0.08), glm::vec4(0), "m_brushPosX"));
			m_brushPosY = static_cast<CEGUI::Editbox *>(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.52, 0.6, 0.2, 0.08), glm::vec4(0), "m_brushPosY"));
			m_brushPosX->setValidationString("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)");
			m_brushPosY->setValidationString("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)");
			m_brushPosX->setText("0.00");
			m_brushPosY->setText("0.00");
			m_brushCollum->setText("30");
			m_brushRow->setText("30");

 			CEGUI::DefaultWindow * edit5_label = static_cast<CEGUI::DefaultWindow *> (m_gui->createWidget("TaharezLook/Label", glm::vec4(0.48, 0.35, 0.15, 0.1), glm::vec4(0), "edit5_label"));
 			edit5_label->setText("Collumn");

			CEGUI::DefaultWindow * edit6_label = static_cast<CEGUI::DefaultWindow *> (m_gui->createWidget("TaharezLook/Label", glm::vec4(0.48, 0.45, 0.15, 0.1), glm::vec4(0), "edit6_label"));
			edit6_label->setText("Row");

			m_brushDepth->setValidationString("^-?\\d*");
			m_brushCollum->setValidationString("\\d*");
			m_brushRow->setValidationString("\\d*");
// 			brushCustomMode = static_cast<CEGUI::ToggleButton*>
// 				(m_gui->createWidget("TaharezLook/RadioButton", glm::vec4(0.05, 0.52, 0.04, 0.04), glm::vec4(0), "brushCustomMode"));;
// 			brushCustomMode->setDisabled(true);

	// 		m_layerDepth->setValidationString("\\d*");
			m_addBrushWindow->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked, CEGUI::Event::Subscriber(& SceneManager::onCloseBrushProtocol, this));
			AcceptButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&SceneManager::addBrushOnCurrentLayer, this));
			m_addBrushWindow->addChild(m_brushName);
			m_addBrushWindow->addChild(m_brushDepth);
			m_addBrushWindow->addChild(AcceptButton);
			m_addBrushWindow->addChild(edit1_label);
			m_addBrushWindow->addChild(edit2_label);
			m_addBrushWindow->addChild(edit3_label);
			m_addBrushWindow->addChild(texturePicker);
			m_addBrushWindow->addChild(brushUVMode);
			m_addBrushWindow->addChild(edit4_label);
			m_addBrushWindow->addChild(m_brushCollum);
			m_addBrushWindow->addChild(m_brushRow);
			m_addBrushWindow->addChild(edit5_label);
			m_addBrushWindow->addChild(edit6_label);
			m_addBrushWindow->addChild(m_brushPosX);
			m_addBrushWindow->addChild(m_brushPosY);


			listdir("./Assets", 0);


		}
		else
		{
			feint_common::Instance()->showMessageBox("Error", "Select the Layer first");
		}
	}
	else
	{
		feint_common::Instance()->showMessageBox("Error", "Create the scene first");
	}
	return true;
}


int SceneManager::listdir(const char *name, int level)
{
	//std::cout << "scan on " << name << "\n";
	DIR *dir;
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



			if (texturePath.find("Brush/") != std::string::npos)
			{
				if (texturePath.find(".png") != std::string::npos)
				{
					std::cout << "png " << entry->d_name << " found \n";
					loadBrushTexture(texturePicker, entry->d_name);
				}
			}

		}
	} while (entry = readdir(dir));

	closedir(dir);
	return 0;

}

bool SceneManager::onSpacingYOffsetChanged(const CEGUI::EventArgs &e)
{
	glm::vec2 originalSpacing = EditorProperty::Instance()->getSpacingOffset();
	if (std::stof(gridOffset_y->getText().c_str()) != NULL)
	{
		originalSpacing.y = std::stof(gridOffset_y->getText().c_str());
		EditorProperty::Instance()->setSpacingOffset(originalSpacing);
		//gridOffset_y->setText(feint_common::Instance()->convertPreciousFloatToString(originalSpacing.y, 1).c_str());
		//updateSpacingOffset();
	}	
	return true;
}

bool SceneManager::onApplyGridClick(const CEGUI::EventArgs & e)
{
	EditorProperty::Instance()->setSpacingOffset(EditorProperty::Instance()->getCurrentEditObject().getFullDimObject());
	updateSpacingOffset();

	return true;
}

bool SceneManager::onCloseBrushProtocol(const CEGUI::EventArgs &e)
{

	if (m_addBrushWindow)
	{
		m_addBrushWindow->destroy();
	}

	return true;
}

bool SceneManager::addBrushOnCurrentLayer(const CEGUI::EventArgs &e)
{
	m_currentLayer = m_currentScene->getCurrentLayer();
	if (m_currentLayer)
	{

		Feintgine::Brush brush;
		std::string destination = "./Assets/Brush/";
		destination.append(texturePicker->getText().c_str());
		glm::vec2 pos = glm::vec2(std::stof(m_brushPosX->getText().c_str()), std::stof(m_brushPosY->getText().c_str()));
		int collum = std::stoi(m_brushCollum->getText().c_str());
		int row = std::stoi(m_brushRow->getText().c_str());

		Feintgine::GLTexture texture = Feintgine::ResourceManager::getTexture(destination);
		//glm::vec2 textureDim = texture.g


		brush.init(destination, pos, glm::vec2(texture.width * collum, texture.height * row), glm::vec2(collum,row),
			Feintgine::Color(255, 255, 255, 255), std::stoi(m_brushDepth->getText().c_str()));

		m_currentLayer->addBrush(brush);
		if (m_addBrushWindow)
		{
			m_addBrushWindow->destroy();
		}

	}

	return true;
}

void SceneManager::updateSpacingOffset()
{
	glm::vec2 originalSpacing = EditorProperty::Instance()->getSpacingOffset();
	gridOffset_x->setText(feint_common::Instance()->convertPreciousFloatToString(originalSpacing.x, 1).c_str());
	gridOffset_y->setText(feint_common::Instance()->convertPreciousFloatToString(originalSpacing.y, 1).c_str());
	//
}

void SceneManager::loadBrushTexture(CEGUI::Combobox * list, const std::string & itemName)
{
	if (list)
	{	
			const CEGUI::Image* sel_img = &CEGUI::ImageManager::getSingleton().get("TaharezLook/MultiListSelectionBrush");
			CEGUI::ListboxItem * item = new CEGUI::ListboxTextItem(itemName.c_str(), m_itemCount++);
			item->setSelectionBrushImage(sel_img);
			list->addItem(item);		
	}
}

void SceneManager::switchMode(int BrushMode)
{
	switch (BrushMode)
	{
	
	default:
		break;
	}
}

void SceneManager::saveScene()
{
	if (m_currentScene)
	{
		
		m_currentScene->saveScene("./Scence/");
		m_currentScene = nullptr;
	}
	else
	{
		feint_common::Instance()->showMessageBox("Erorr", "No scene created !!!");
	}
}

