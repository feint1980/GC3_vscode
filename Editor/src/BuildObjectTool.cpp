#include "BuildObjectTool.h"



BuildObjectTool::BuildObjectTool()
{
}


BuildObjectTool::~BuildObjectTool()
{
}

void BuildObjectTool::init(EditObject *object, Feintgine::GUI * gui, Feintgine::Camera2D * camera)
{
	m_object = object;
	m_gui = gui;

	m_camera = camera;

	m_dim = glm::vec2(m_camera->getScreenWidth(), m_camera->getScreenHeight());

	bg.init(Feintgine::ResourceManager::getTexture("Textures/shadowing.png"),
		glm::vec2(0, 0), glm::vec2(40000.0f, 40000.0f), Feintgine::Color(0, 0, 0, 255));
	bg.setDepth(-15);

	initTools();

}

void BuildObjectTool::loadObject(EditObject *object)
{
	m_object = object;
}

void BuildObjectTool::addSpriteToObject(Feintgine::F_Sprite t_sprite, glm::vec2 t_posOffset, glm::vec2 t_scaleOffset, Feintgine::Color t_color, float offsetAngle, float t_depth)
{
	int t_ID = spriteID_count;

	m_object->addSprite(t_sprite, glm::vec2(0), glm::vec2(1), Feintgine::Color(255, 255, 255, 255), 0.0f, 1.0f, t_ID);
	std::cout << "added sprite ID " << t_ID << "\n";
	//int i_layerDepth = layerDepth;
	CEGUI::ListboxTextItem * firstRowItem1 = new CEGUI::ListboxTextItem(t_sprite.getName().c_str());
	CEGUI::ListboxTextItem * firstRowItem2 = new CEGUI::ListboxTextItem("");
 	CEGUI::ListboxTextItem * firstRowItem3 = new CEGUI::ListboxTextItem(std::to_string(t_ID).c_str());



	firstRowItem1->setSelectionBrushImage("TaharezLook/ListboxSelectionBrush");
// 	firstRowItem2->setSelectionBrushImage("TaharezLook/ListboxSelectionBrush");
// 	firstRowItem3->setSelectionBrushImage("TaharezLook/ListboxSelectionBrush");

	CEGUI::uint firstRow = m_spriteList->addRow(firstRowItem1, 1);

	m_spriteList->setItem(firstRowItem2, 2, firstRow);
	m_spriteList->setItem(firstRowItem3, 3, firstRow);

	m_spriteList->getHorzScrollbar()->hide();
// 	m_layers->setItem(firstRowItem2, 2, firstRow);
// 	m_layers->setItem(firstRowItem3, 3, firstRow);

	spriteID_count++;

}

void BuildObjectTool::drawBoxes(Feintgine::DebugRender & renderer)
{
	if (m_selectedSprite)
	{		
		//m_editorCrosshair.drawBox(glm::vec4(0, -25, 0.25, 50), Feintgine::Color(240, 240, 240, 125), 0);
		glm::vec2 dim = glm::vec2(m_selectedSprite->scaleOffset.x * m_selectedSprite->sprite.getDim().x, m_selectedSprite->scaleOffset.y * m_selectedSprite->sprite.getDim().y);
	
		renderer.drawBox_center(glm::vec4(m_selectedSprite->posOffset, dim), Feintgine::Color(0, 240, 240, 125), m_selectedSprite->angleOffset);
	}
	if (currentLightIndex > -1)
	{
		float radius = 1.0f / m_object->m_lightListAttenuation[currentLightIndex].z;
		glm::vec2 dim = glm::vec2(radius);
		renderer.drawBox_center(glm::vec4(m_object->m_lightListPos[currentLightIndex], dim), Feintgine::Color(250, 0, 240, 125), 0);
	}
}



void BuildObjectTool::drawShadowing(Feintgine::SpriteBatch & spriteBatch)
{
	bg.draw(spriteBatch);
}

void BuildObjectTool::handleInput(Feintgine::InputManager & inputManger)
{
	
	//glm::vec2 mousePos = m_camera->convertScreenToWorld(inputManger.getMouseCoords() + glm::vec2(350,450)) /*- ( object_screen_offset / m_camera->getScale())*/ ;
	glm::vec2 mousePos = m_camera->convertScreenToWorldViewPort(inputManger.getMouseCoords(),glm::vec2(350, 450),glm::vec2(1600,900));
// 	std::cout << feint_common::Instance()->convertVec2toString(m_sceneCamera.convertScreenToWorld(m_game->getInputManager().getMouseCoords(),
// 		glm::vec2(SceneScreen.x, SceneScreen.y), glm::vec2(m_window->getScreenWidth(), m_window->getScreenHeight()))) << "\n";
	//std::cout << "camera scale " << m_camera->getScale() << "\n";
	//mousePos /= m_camera->getScale();
	//std::cout << feint_common::Instance()->convertVec2toString(mousePos) << "\n";
	if (currentColiderIndex > -1)
	{
		if (inputManger.isKeyPressed(SDLK_DELETE))
		{
			m_object->deleteColiderByID(m_object->m_coliders[currentColiderIndex].getID());
			removeColiderInList();
			currentColiderIndex = -1;
			if (m_object->m_coliders.size() == 0)
			{
				coliderID_count = 1;
			}

		}
	}

	if (inputManger.isKeyPressed(SDLK_F5))
	{
		//m_object->
	}

	if (checkInside(mousePos))
	{
		if (currentLightIndex > -1)
		{
			if (checkInsideLight(mousePos))
			{

				if (inputManger.isKeyDown(SDL_BUTTON_LEFT))
				{


					if (!isDrag)
					{
						mouseOffset = mousePos - m_object->m_lightListPos[currentLightIndex];
						isDrag = true;
					}

					if (isDrag)
					{
						m_object->m_lightListPos[currentLightIndex] = (mousePos - mouseOffset);
					}

				}
				else
				{
					mouseOffset = glm::vec2(0);
					isDrag = false;
				}
			
			}
			else
			{
			
			}

			if (inputManger.isKeyPressed(SDLK_DELETE))
			{
				m_object->m_lightListAttenuation.erase(m_object->m_lightListAttenuation.begin() + currentLightIndex);
				m_object->m_lightListColor.erase(m_object->m_lightListColor.begin() + currentLightIndex);
				m_object->m_lightListPos.erase(m_object->m_lightListPos.begin() + currentLightIndex);
				m_object->m_lightListID.erase(m_object->m_lightListID.begin() + currentLightIndex);
				removeSelectedLightInList();
				if (m_object->m_lightListID.size() == 0)
				{
					lightID_count = 1;
				}
				currentLightIndex = -1;
			}
		}
		if (currentColiderIndex > -1)
		{
			if (m_object->m_coliders[currentColiderIndex].checkInside(mousePos))
			{
				if (inputManger.isKeyDown(SDL_BUTTON_LEFT))
				{


					if (!isDrag)
					{
						mouseOffset = mousePos - m_object->m_coliders[currentColiderIndex].getPos();
						isDrag = true;
					}

					if (isDrag)
					{
						m_object->m_coliders[currentColiderIndex].setPos(mousePos - mouseOffset);
					}

				}
				else
				{
					mouseOffset = glm::vec2(0);
					isDrag = false;
				}
				
			}
		}

		if (inputManger.isKeyPressed(SDLK_ESCAPE))
		{

			//m_selectedSprite = nullptr;
			if (currentLightIndex > -1)
			{
				currentLightIndex = -1;
			}
			if (m_lightList->getFirstSelectedItem())
			{
				m_lightList->setItemSelectState(m_lightList->getFirstSelectedItem(), false);
				
			}
			if (m_spriteList->getFirstSelectedItem())
			{
				m_selectedSprite = nullptr;
				m_spriteList->setItemSelectState(m_spriteList->getFirstSelectedItem(), false);
				
			}
			if (currentColiderIndex > -1)
			{
				m_object->m_coliders[currentColiderIndex].setSelected(false);
				currentColiderIndex = -1;
			}
			if (m_coliderList->getFirstSelectedItem())
			{
				m_coliderList->setItemSelectState(m_coliderList->getFirstSelectedItem(), false);
			}

		}		//std::cout << feint_common::Instance()->convertVec2toString(mousePos) << "\n";
		
	
		if (m_selectedSprite)
		{
			if (m_selectedSprite->sprite.isInverted())
			{
				m_isSpriteInverted->setSelected(true);
			}
			else
			{
				m_isSpriteInverted->setSelected(false);
			}
			if (m_selectedSprite->checkInside(mousePos))
			{
			//	std::cout << "hit \n";
			//	std::cout << "dim is " << feint_common::Instance()->convertVec2toString(m_selectedSprite->sprite.getDim()) << " \n";
				if (inputManger.isKeyDown(SDL_BUTTON_LEFT))
				{

					if (!isDrag)
					{
						mouseOffset = mousePos - m_selectedSprite->posOffset;
						isDrag = true;
					}

					if (isDrag)
					{
						m_selectedSprite->posOffset = (mousePos - mouseOffset);
					}

				}
				else
				{

					mouseOffset = glm::vec2(0);
					isDrag = false;
				}
				
			}
			else
			{

			}
			if (inputManger.isKeyPressed(SDLK_DELETE))
			{
				if (m_selectedSprite)
				{

					std::cout << "DEBUG 1 " << m_selectedSprite->m_ID << "\n";
					int kaka = m_selectedSprite->m_ID;
					m_object->deleteSpriteByID(kaka);
					std::cout << "DEBUG 2 " << m_selectedSprite->m_ID << "\n";
					removeSpriteInList(kaka);
					m_selectedSprite = nullptr;
					if (m_object->getSpriteList().size() == 0)
					{
						spriteID_count = 1;
					}
					
				}
			}
		}
		else
		{
			if (currentLightIndex < 0 && currentColiderIndex < 0)
			{
				if (inputManger.isKeyPressed(SDL_BUTTON_LEFT))
				{
					m_selectedSprite = m_object->getSpriteByPos(mousePos);
					if (m_selectedSprite)
					{
						if (m_lightList->getFirstSelectedItem())
						{
							m_lightList->setItemSelectState(m_lightList->getFirstSelectedItem(), false);
						}
						for (int i = 0; i < m_spriteList->getRowCount(); i++)
						{

							if (std::stoi(m_spriteList->getItemAtGridReference(CEGUI::MCLGridRef(i, 2))->getText().c_str()) == m_selectedSprite->m_ID)
							{
			
								m_spriteList->setItemSelectState(m_spriteList->getItemAtGridReference(CEGUI::MCLGridRef(i, 2)),true);
							}

						}
					}
					
					
				}
			}
		}
	}
}

void BuildObjectTool::selectASprite()
{

}

void BuildObjectTool::update()
{
	m_pos = m_camera->getPosition();
	m_currentDim = m_dim * m_camera->getScale();

	if (m_selectedSprite)
	{
		if (propertyDisableCounter == 0)
		{
			m_offsetPos_X->enable();
			m_offsetPos_Y->enable();
			m_offsetWidthScale->enable();
			m_offsetHeightScale->enable();
			m_ownColor_r->enable();
			m_ownColor_g->enable();
			m_ownColor_b->enable();
			m_ownColor_a->enable();
			m_dephValue->enable();
			m_angleValue->enable();
			m_isSpriteInverted->enable();
			propertyDisableCounter = 1;
		}
		
		if (m_offsetPos_X->isActive() || m_offsetPos_Y->isActive())
		{
			
		}
		else
		{
			std::stringstream stream;
			std::string str;
			stream << std::fixed << std::setprecision(2) << m_selectedSprite->posOffset.x;	
			str = stream.str();
			m_offsetPos_X->setText(str.c_str());
			stream.clear();
			stream.str(std::string());
			stream << std::fixed << std::setprecision(2) << m_selectedSprite->posOffset.y;
			str = stream.str();
			m_offsetPos_Y->setText(str.c_str());
		}

		if (m_offsetWidthScale->isActive() || m_offsetHeightScale->isActive())
		{

		}
		else
		{

			std::stringstream stream;
			std::string str;
			stream << std::fixed << std::setprecision(2) << m_selectedSprite->scaleOffset.x;
			str = stream.str();
			m_offsetWidthScale->setText(str.c_str());
			stream.clear();
			stream.str(std::string());
			stream << std::fixed << std::setprecision(2) << m_selectedSprite->scaleOffset.y;
			str = stream.str();
			m_offsetHeightScale->setText(str.c_str());

			//m_offsetWidthScale->setText(std::to_string(m_selectedSprite->scaleOffset.x).c_str());
			//m_offsetHeightScale->setText(std::to_string(m_selectedSprite->scaleOffset.y).c_str());


		}

		if (m_ownColor_r->isActive() || m_ownColor_b->isActive() || m_ownColor_g->isActive() || m_ownColor_a->isActive())
		{
			

		}
		else
		{

			std::stringstream stream;
			std::string str;
			stream << std::fixed << std::setprecision(2) << m_selectedSprite->color.r;
			str = stream.str();
			m_ownColor_r->setText(str.c_str());
			stream.clear();
			stream.str(std::string());
			stream << std::fixed << std::setprecision(2) << m_selectedSprite->color.g;
			str = stream.str();
			m_ownColor_g->setText(str.c_str());
			stream.clear();
			stream.str(std::string());
			stream << std::fixed << std::setprecision(2) << m_selectedSprite->color.b;
			str = stream.str();
			m_ownColor_b->setText(str.c_str());
			stream.clear();
			stream.str(std::string());
			stream << std::fixed << std::setprecision(2) << m_selectedSprite->color.a;
			str = stream.str();
			m_ownColor_a->setText(str.c_str());


// 			m_ownColor_r->setText(std::to_string(m_selectedSprite->color.r).c_str());
// 			m_ownColor_g->setText(std::to_string(m_selectedSprite->color.g).c_str());
// 			m_ownColor_b->setText(std::to_string(m_selectedSprite->color.b).c_str());
// 			m_ownColor_a->setText(std::to_string(m_selectedSprite->color.a).c_str());
		}
		if (m_dephValue->isActive())
		{

		}
		else
		{
			std::stringstream stream;
			std::string str;
			stream << std::fixed << std::setprecision(2) << m_selectedSprite->depth;
			str = stream.str();
			m_dephValue->setText(str.c_str());
			//m_dephValue->setText(std::to_string(m_selectedSprite->depth).c_str());
		}
		if (m_angleValue->isActive())
		{

		}
		else
		{
			std::stringstream stream;
			std::string str;
			stream << std::fixed << std::setprecision(2) << m_selectedSprite->angleOffset;
			str = stream.str();
			m_angleValue->setText(str.c_str());
			//m_angleValue->setText(std::to_string(m_selectedSprite->angleOffset).c_str());
		}
		
	}
	else
	{
		if (propertyDisableCounter != 0)
		{
			m_offsetPos_X->setText("");
			m_offsetPos_Y->setText("");
			m_offsetWidthScale->setText("");
			m_offsetHeightScale->setText("");
			m_ownColor_r->setText("");
			m_ownColor_g->setText("");
			m_ownColor_b->setText("");
			m_ownColor_a->setText("");
			m_dephValue->setText("");
			m_angleValue->setText("0");
			m_isSpriteInverted->setSelected(false);


			m_offsetPos_X->disable();
			m_offsetPos_Y->disable();
			m_offsetWidthScale->disable();
			m_offsetHeightScale->disable();
			m_ownColor_r->disable();
			m_ownColor_g->disable();
			m_ownColor_b->disable();
			m_ownColor_a->disable();
			m_dephValue->disable();
			m_angleValue->disable();
			m_isSpriteInverted->disable();

		
			

			propertyDisableCounter = 0;
		}
		

	}
	if (currentLightIndex > -1)
	{
		if (lightPropertyDisableCounter == 0)
		{
			m_lightPos_X->enable();
			m_lightPos_Y->enable();
			m_lightAtten_X->enable();
			m_lightAtten_Y->enable();
			m_lightAtten_Z->enable();
			m_lightColor_r->enable();
			m_lightColor_g->enable();
			m_lightColor_b->enable();
			m_lightColor_a->enable();

			lightPropertyDisableCounter = 1;
		}

		if (m_lightPos_X->isActive() || m_lightPos_Y->isActive())
		{

		}
		else
		{
			m_lightPos_X->setText(std::to_string(m_object->m_lightListPos[currentLightIndex].x).c_str());
			m_lightPos_Y->setText(std::to_string(m_object->m_lightListPos[currentLightIndex].y).c_str());
		}
		if (m_lightAtten_X->isActive() || m_lightAtten_Y->isActive() || m_lightAtten_Z->isActive())
		{


		}
		else
		{
			m_lightAtten_X->setText(std::to_string(1.0f/ m_object->m_lightListAttenuation[currentLightIndex].x).c_str());
			m_lightAtten_Y->setText(std::to_string(1.0f/ m_object->m_lightListAttenuation[currentLightIndex].y).c_str());
			m_lightAtten_Z->setText(std::to_string(1.0f/m_object->m_lightListAttenuation[currentLightIndex].z).c_str());
			
		}
		if (m_lightColor_r->isActive() || m_lightColor_g->isActive() || m_lightColor_b->isActive() || m_lightColor_a->isActive())
		{


		}
		else
		{
			m_lightColor_r->setText(std::to_string(m_object->m_lightListColor[currentLightIndex].r).c_str());
			m_lightColor_g->setText(std::to_string(m_object->m_lightListColor[currentLightIndex].g).c_str());
			m_lightColor_b->setText(std::to_string(m_object->m_lightListColor[currentLightIndex].b).c_str());
			m_lightColor_a->setText(std::to_string(m_object->m_lightListColor[currentLightIndex].a).c_str());

		}

	}
	else
	{
		if (lightPropertyDisableCounter != 0)
		{
			m_lightPos_X->disable();
			m_lightPos_Y->disable();
			m_lightAtten_X->disable();
			m_lightAtten_Y->disable();
			m_lightAtten_Z->disable();
			m_lightColor_r->disable();
			m_lightColor_g->disable();
			m_lightColor_b->disable();
			m_lightColor_a->disable();

			lightPropertyDisableCounter = 0;
		}
		
	}
	if (currentColiderIndex > -1)
	{
		if (coliderPropertyDisableCounter == 0)
		{
			m_coliderDim_X->enable();
			m_coliderDim_Y->enable();

			coliderPropertyDisableCounter = 1;
		}
		if (m_coliderDim_X->isActive() || m_coliderDim_Y->isActive())
		{


		}
		else
		{
			m_coliderDim_X->setText(std::to_string(m_object->m_coliders[currentColiderIndex].getDim().x).c_str());
			m_coliderDim_Y->setText(std::to_string(m_object->m_coliders[currentColiderIndex].getDim().y).c_str());
		
		}
	}
	else
	{
		if (coliderPropertyDisableCounter != 0)
		{
			m_coliderDim_X->disable();
			m_coliderDim_Y->disable();
			

			coliderPropertyDisableCounter = 0;
		}
	}

}

void BuildObjectTool::removeSpriteInList(int ID)
{ 
	if (m_spriteList->getRowCount() > 0)
	{
		for (int i = 0; i < m_spriteList->getRowCount(); i++)
		{		 
			if (std::stoi(m_spriteList->getItemAtGridReference(CEGUI::MCLGridRef(i, 2))->getText().c_str()) == ID)
			{				
				//std::cout << "supposed to remove " << ID; 
				//std::cout << "but removed " << m_spriteList->getItemAtGridReference(CEGUI::MCLGridRef(i, 2))->getText().c_str() << "\n";
			
				m_spriteList->removeRow(i);
			}
		}
	}
}

void BuildObjectTool::removeColiderInList()
{
	
	if (m_coliderList->getFirstSelectedItem())
	{
		m_coliderList->removeItem(m_coliderList->getFirstSelectedItem());
	}

	
}

bool BuildObjectTool::onSpriteListDoubleClick(const CEGUI::EventArgs & e)
{
	if (m_spriteList->getFirstSelectedItem())
	{

		CEGUI::ListboxItem* t_listboxItem = m_spriteList->getFirstSelectedItem();

		// This one should not be delete, it goes 2 times
		t_listboxItem = m_spriteList->getNextSelected(t_listboxItem);
		t_listboxItem = m_spriteList->getNextSelected(t_listboxItem);

	
		std::cout << "selecting ID : " << t_listboxItem->getText().c_str() << "\n";
		int t_ID = std::stoi(t_listboxItem->getText().c_str());
		std::cout << "selecting " << t_ID << "\n";
		m_selectedSprite = m_object->getSpriteByID(t_ID);
		saved_SelectedID = t_ID;
		m_selectedSprite->m_ID = t_ID;
		
		//std::cout << "get from " << t_listboxItem->getText().c_str() << "\n";
		if (m_selectedSprite)
		{
			if (m_selectedSprite->sprite.isInverted())
			{
				m_isSpriteInverted->setSelected(true);
			}
			else
			{
				m_isSpriteInverted->setSelected(false);
			}
			currentLightIndex = -1;
			if (m_lightList->getFirstSelectedItem())
			{
				m_lightList->setItemSelectState(m_lightList->getFirstSelectedItem(), false);
			}
			if (currentColiderIndex > -1)
			{
				m_object->m_coliders[currentColiderIndex].setSelected(false);
			}
			currentColiderIndex = -1;
			if (m_coliderList->getFirstSelectedItem())
			{
				m_coliderList->setItemSelectState(m_coliderList->getFirstSelectedItem(), false);
			}
					
			//std::cout << "success \n";
		}
	}

	//m_selectedSprite = m_object->getSpriteByID()
	return true;
}

bool BuildObjectTool::onLightLiseDoubleClick(const CEGUI::EventArgs &e)
{
	if (m_lightList->getFirstSelectedItem())
	{
		currentLightIndex = m_object->getLightIndexByID(std::stoi(m_lightList->getFirstSelectedItem()->getText().c_str()));

	}
	if (currentLightIndex > -1)
	{
		m_selectedSprite = nullptr;
		if (m_spriteList->getFirstSelectedItem())
		{
			m_spriteList->setItemSelectState(m_spriteList->getFirstSelectedItem(), false);
		}		
	}
	return true;
}

bool BuildObjectTool::onColiderLiseDoubleClick(const CEGUI::EventArgs &e)
{

	if (currentColiderIndex > -1)
	{
		m_object->m_coliders[currentColiderIndex].setSelected(false);
	}
	if (m_coliderList->getFirstSelectedItem())
	{
		currentColiderIndex = m_object->getColiderIndexByID(std::stoi(m_coliderList->getFirstSelectedItem()->getText().c_str()));
		m_object->m_coliders[currentColiderIndex].setSelected(true);

	}
	if (currentColiderIndex > -1)
	{
		m_selectedSprite = nullptr;
		if (m_spriteList->getFirstSelectedItem())
		{
			m_spriteList->setItemSelectState(m_spriteList->getFirstSelectedItem(), false);
		}
		if (m_lightList->getFirstSelectedItem())
		{
			m_lightList->setItemSelectState(m_lightList->getFirstSelectedItem(), false);
		}
		currentLightIndex = -1;		
	}

	return true;
}

bool BuildObjectTool::addLightToObject(const CEGUI::EventArgs &e)
{
	//int t_lightID = getValidLightID();
	int t_lightID = lightID_count++;
	m_object->addLight(glm::vec2(0), glm::vec4(1), glm::vec3(0.075), t_lightID);
	CEGUI::ListboxTextItem * item;
	// 
	item = new CEGUI::ListboxTextItem(std::to_string(t_lightID), 0);
	item->setSelectionBrushImage("TaharezLook/ListboxSelectionBrush");
	m_lightList->addItem(item);

	return true;
}

bool BuildObjectTool::onPositionOffsetChanged(const CEGUI::EventArgs &e)
{
	if (m_offsetPos_X->isActive() || m_offsetPos_Y->isActive())
	{
		if (m_selectedSprite)
		{
			m_selectedSprite->posOffset.x = std::stof(m_offsetPos_X->getText().c_str());
			m_selectedSprite->posOffset.y = std::stof(m_offsetPos_Y->getText().c_str());
		}
	}


	return true;
}

bool BuildObjectTool::onScaleOffsetChanged(const CEGUI::EventArgs &e)
{

	if (m_offsetWidthScale->isActive() || m_offsetHeightScale->isActive())
	{
		if (m_selectedSprite)
		{
			m_selectedSprite->scaleOffset.x = std::stof(m_offsetWidthScale->getText().c_str());
			m_selectedSprite->scaleOffset.y = std::stof(m_offsetHeightScale->getText().c_str());
		}
	}
	return true;
}

bool BuildObjectTool::onColorValueChanged(const CEGUI::EventArgs &e)
{
	if (m_ownColor_r->isActive() || m_ownColor_b->isActive() || m_ownColor_g->isActive() || m_ownColor_a->isActive())
	{
		if (m_selectedSprite)
		{
			
			m_selectedSprite->color.r = (float)(std::stof(m_ownColor_r->getText().c_str()));
			m_selectedSprite->color.g = (float)(std::stof(m_ownColor_b->getText().c_str()));
			m_selectedSprite->color.b = (float)(std::stof(m_ownColor_g->getText().c_str()));
			m_selectedSprite->color.a = (float)(std::stof(m_ownColor_a->getText().c_str()));
		}
	}
	return true;
}

bool BuildObjectTool::onLightAttenuationValueChanged(const CEGUI::EventArgs &e)
{
	if (m_lightAtten_X->isActive() || m_lightAtten_Y->isActive() || m_lightAtten_Z->isActive() )
	{
		if (currentLightIndex > -1)
		{

			m_object->m_lightListAttenuation[currentLightIndex].x = 1.0f/ (float)(std::stof(m_lightAtten_X->getText().c_str()));
			m_object->m_lightListAttenuation[currentLightIndex].y = 1.0f / (float)(std::stof(m_lightAtten_Y->getText().c_str()));
			m_object->m_lightListAttenuation[currentLightIndex].z = 1.0f / (float)(std::stof(m_lightAtten_Z->getText().c_str()));

		}
	}
	return true;
}

bool BuildObjectTool::onLightPosValueChanged(const CEGUI::EventArgs &e)
{
	if (m_lightPos_X->isActive() || m_lightPos_Y->isActive() )
	{
		if (currentLightIndex > -1)
		{

			m_object->m_lightListPos[currentLightIndex].x = (float)(std::stof(m_lightPos_X->getText().c_str()));
			m_object->m_lightListPos[currentLightIndex].y = (float)(std::stof(m_lightPos_Y->getText().c_str()));
			
		}
	}
	return true;
}

bool BuildObjectTool::onLightColorValueChanged(const CEGUI::EventArgs &e)
{
	if (m_lightColor_r->isActive() || m_lightColor_g->isActive() || m_lightColor_b->isActive() || m_lightColor_a->isActive())
	{
		if (currentLightIndex > -1)
		{
			m_object->m_lightListColor[currentLightIndex].r = (float)(std::stof(m_lightColor_r->getText().c_str()));
			m_object->m_lightListColor[currentLightIndex].g = (float)(std::stof(m_lightColor_g->getText().c_str()));
			m_object->m_lightListColor[currentLightIndex].b = (float)(std::stof(m_lightColor_b->getText().c_str()));
			m_object->m_lightListColor[currentLightIndex].a = (float)(std::stof(m_lightColor_a->getText().c_str()));
		}
	}
	return true;


}

bool BuildObjectTool::onAmbientLightValueChanged(const CEGUI::EventArgs &e)
{

	
	m_ambLight = std::stof(m_ambientLight->getText().c_str());
		
	if (m_ambLight > 1.0f)
	{
		m_ambLight = 1.0f;
	}
	if (m_ambLight < 0.0f)
	{
		m_ambLight = 0.0f;
	}
		
	return true;
}

bool BuildObjectTool::onDepthValueChanged(const CEGUI::EventArgs &e)
{

	if (m_dephValue->isActive() )
	{
		if (m_selectedSprite)
		{

			m_selectedSprite->depth = std::stof(m_dephValue->getText().c_str());

		}
	}

	return true;
}

bool BuildObjectTool::onAddColiderClick(const CEGUI::EventArgs &e)
{
	glm::vec2 defaultDim = glm::vec2(50);
	if (m_selectedSprite)
	{
		defaultDim = m_selectedSprite->sprite.getDim() + glm::vec2(-1);
	}
	int t_coliderID = coliderID_count++;

	m_object->addColider(glm::vec2(0), defaultDim, t_coliderID);

	CEGUI::ListboxTextItem * item;
	// 
	item = new CEGUI::ListboxTextItem(std::to_string(t_coliderID), 0);
	item->setSelectionBrushImage("TaharezLook/ListboxSelectionBrush");
	m_coliderList->addItem(item);
	return true;
}

bool BuildObjectTool::onColiderDimValueChanged(const CEGUI::EventArgs &e)
{
	if (m_coliderDim_X->isActive() || m_coliderDim_Y->isActive())
	{
		if (currentColiderIndex > -1)
		{

			m_object->m_coliders[currentColiderIndex].setDim(glm::vec2(std::stof(m_coliderDim_X->getText().c_str()), std::stof(m_coliderDim_Y->getText().c_str())));

		}
	}

	return true;
}

bool BuildObjectTool::onAngleValueChanged(const CEGUI::EventArgs &e)
{

	float angle = std::stof(m_angleValue->getText().c_str());
	angle /= 57.2957795;
	if (m_angleValue->isActive())
	{
		if (m_selectedSprite)
		{
			m_selectedSprite->angleOffset = angle;
			
		}
	}
	return true;
}

bool BuildObjectTool::onSaveObjectClicked(const CEGUI::EventArgs &e)
{
	if (m_object)
	{
		if (m_objectName->getText().c_str() != "")
		{
			m_object->saveToFile(m_objectName->getText().c_str(), "./Assets/F_Objects/");
		}
		else
		{
			std::cout << "ERROR : File name is Empty !!!!!!!!! \n";
		}
		
	}

	return true;
}

bool BuildObjectTool::onColiderToggleBoxClicked(const CEGUI::EventArgs &e)
{

	if (m_showColiderButton->isSelected())
	{
		m_showColider = true;
	}
	else
	{
		m_showColider = false;
	}

	return true;
}


bool BuildObjectTool::onSpriteInvertToggleBoxClicked(const CEGUI::EventArgs &e)
{
	if (m_selectedSprite)
	{
		m_selectedSprite->sprite.setInvert(m_isSpriteInverted->isSelected());
	}

	return true;
}

void BuildObjectTool::initTools()
{
	if (m_gui)
	{
		m_spriteList = static_cast<CEGUI::MultiColumnList*> (m_gui->createWidget("TaharezLook/MultiColumnList", glm::vec4(0.22, 0.555, 0.2, 0.2), glm::vec4(0), "m_spriteList"));
		m_spriteList->addColumn("Name", 1, cegui_reldim(0.7f));
		m_spriteList->addColumn("", 2, cegui_reldim(0.01f));
		m_spriteList->addColumn("ID", 3, cegui_reldim(0.29f));
		m_spriteList->subscribeEvent(CEGUI::MultiColumnList::EventMouseClick, CEGUI::Event::Subscriber(&BuildObjectTool::onSpriteListDoubleClick, this));
		m_spriteList->getHorzScrollbar()->hide();
		//m_spriteList->setSelectionMode(CEGUI::MultiColumnList::RowMultiple);
		
		m_spriteListDesc_label = static_cast<CEGUI::DefaultWindow*>
		 		(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.22, 0.51, 0.1, 0.05), glm::vec4(0), "m_spriteListDesc_label"));
		m_spriteListDesc_label->setText("Sprite List");
		m_spriteListDesc_label->setProperty("HorzFormatting", "LeftAligned");


		m_offsetPos_label = static_cast<CEGUI::DefaultWindow*>
			(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.22, 0.77, 0.08, 0.05), glm::vec4(0), "m_offsetPos_label"));
		m_offsetPos_label->setText("Offset Pos");
		m_offsetPos_label->setProperty("HorzFormatting", "LeftAligned");

		m_offsetPos_X = static_cast<CEGUI::Editbox *>
			 (m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.27, 0.78, 0.05, 0.03), glm::vec4(0), "m_offsetPos_X"));
		m_offsetPos_X->setValidationString("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)");
		m_offsetPos_X->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&BuildObjectTool::onPositionOffsetChanged, this));
		m_offsetPos_Y = static_cast<CEGUI::Editbox *>
			(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.33, 0.78, 0.05, 0.03), glm::vec4(0), "m_offsetPos_Y"));
		m_offsetPos_Y->setValidationString("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)");
		m_offsetPos_Y->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&BuildObjectTool::onPositionOffsetChanged, this));

		m_offsetScale_label = static_cast<CEGUI::DefaultWindow*>
			(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.22, 0.81, 0.08, 0.05), glm::vec4(0), "m_offsetScale_label"));
		m_offsetScale_label->setText("Scale");
		m_offsetScale_label->setProperty("HorzFormatting", "LeftAligned");

		m_offsetWidthScale = static_cast<CEGUI::Editbox *>
			(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.27, 0.82, 0.05, 0.03), glm::vec4(0), "m_offsetWidthScale"));
		m_offsetWidthScale->setValidationString("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)");
		m_offsetWidthScale->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&BuildObjectTool::onScaleOffsetChanged, this));
		m_offsetHeightScale = static_cast<CEGUI::Editbox *>
			(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.33, 0.82, 0.05, 0.03), glm::vec4(0), "m_offsetHeightScale"));
		m_offsetHeightScale->setValidationString("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)");
		m_offsetHeightScale->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&BuildObjectTool::onScaleOffsetChanged, this));

		m_colorRGBA_label = static_cast<CEGUI::DefaultWindow*>
			(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.22, 0.85, 0.08, 0.05), glm::vec4(0), "m_colorRGBA_label"));
		m_colorRGBA_label->setText("Color RGBA");
		m_colorRGBA_label->setProperty("HorzFormatting", "LeftAligned");

		m_dephValue_label = static_cast<CEGUI::DefaultWindow*>
			(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.22, 0.9, 0.08, 0.05), glm::vec4(0), "m_dephValue_label"));
		m_dephValue_label->setText("Depth");
		m_dephValue_label->setProperty("HorzFormatting", "LeftAligned");

		m_dephValue = static_cast<CEGUI::Editbox *>
			(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.275, 0.91, 0.045, 0.03), glm::vec4(0), "m_dephValue"));
		m_dephValue->setValidationString("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)");
		m_dephValue->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&BuildObjectTool::onDepthValueChanged, this));

		m_angleValue_label = static_cast<CEGUI::DefaultWindow*>
			(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.35, 0.9, 0.08, 0.05), glm::vec4(0), "m_angleValue_label"));
		m_angleValue_label->setText("Angle");
		m_angleValue_label->setProperty("HorzFormatting", "LeftAligned");

		m_angleValue = static_cast<CEGUI::Editbox *>
			(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.385, 0.91, 0.045, 0.03), glm::vec4(0), "m_angleValue"));
		m_angleValue->setValidationString("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)");
		m_angleValue->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&BuildObjectTool::onAngleValueChanged, this));



		m_ownColor_r = static_cast<CEGUI::Editbox *>
			(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.275, 0.86, 0.045, 0.03), glm::vec4(0), "m_ownColor_r"));
		
		m_ownColor_r->setValidationString("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)");
		m_ownColor_r->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&BuildObjectTool::onColorValueChanged, this));

		m_ownColor_g = static_cast<CEGUI::Editbox *>
			(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.321, 0.86, 0.045, 0.03), glm::vec4(0), "m_ownColor_g"));
		
		m_ownColor_g->setValidationString("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)");
		m_ownColor_g->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&BuildObjectTool::onColorValueChanged, this));

		m_ownColor_b = static_cast<CEGUI::Editbox *>
			(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.367, 0.86, 0.045, 0.03), glm::vec4(0), "m_ownColor_b"));
		
		m_ownColor_b->setValidationString("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)");
		m_ownColor_b->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&BuildObjectTool::onColorValueChanged, this));

		m_ownColor_a = static_cast<CEGUI::Editbox *>
			(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.413, 0.86, 0.045, 0.03), glm::vec4(0), "m_ownColor_a"));
		m_ownColor_a->setValidationString("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)");
		m_ownColor_a->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&BuildObjectTool::onColorValueChanged, this));

		m_addLightButton = static_cast<CEGUI::PushButton *>
			(m_gui->createWidget("TaharezLook/Button", glm::vec4(0.61, 0.36, 0.08, 0.04), glm::vec4(0), "m_addLightButton"));
		m_addLightButton->setText("Add Light");
		m_addLightButton->subscribeEvent(CEGUI::PushButton::EventMouseClick, CEGUI::Event::Subscriber(&BuildObjectTool::addLightToObject, this));


		
		m_lightListDesc_label = static_cast<CEGUI::DefaultWindow*>
			(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.485, 0.035, 0.08, 0.05), glm::vec4(0), "m_lightListDesc_label"));
		m_lightListDesc_label->setText("Light ID");
		m_lightListDesc_label->setProperty("HorzFormatting", "LeftAligned");

		m_lightList = static_cast<CEGUI::Listbox*> (m_gui->createWidget("TaharezLook/Listbox", glm::vec4(0.475, 0.08, 0.125, 0.25), glm::vec4(0), "m_lightList"));
		m_lightList->subscribeEvent(CEGUI::Listbox::EventMouseDoubleClick, CEGUI::Event::Subscriber(&BuildObjectTool::onLightLiseDoubleClick, this));

		m_lightPos_label = static_cast<CEGUI::DefaultWindow*>
			(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.48, 0.42, 0.08, 0.05), glm::vec4(0), "m_lightPos_label"));
		m_lightPos_label->setText("Offset Pos");
		m_lightPos_label->setProperty("HorzFormatting", "LeftAligned");

		m_lightPos_X = static_cast<CEGUI::Editbox *>
			(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.53, 0.43, 0.05, 0.03), glm::vec4(0), "m_lightPos_X"));
		m_lightPos_X->setValidationString("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)");
		m_lightPos_X->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&BuildObjectTool::onLightPosValueChanged, this));
		m_lightPos_Y = static_cast<CEGUI::Editbox *>
			(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.59, 0.43, 0.05, 0.03), glm::vec4(0), "m_lightPos_Y"));
		m_lightPos_Y->setValidationString("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)");
		m_lightPos_Y->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&BuildObjectTool::onLightPosValueChanged, this));

		

		m_lightAttenuation_label = static_cast<CEGUI::DefaultWindow*>
			(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.475, 0.47, 0.08, 0.05), glm::vec4(0), "m_lightAttenuation_label"));
		m_lightAttenuation_label->setText("Attenuation");
		m_lightAttenuation_label->setProperty("HorzFormatting", "LeftAligned");

		m_lightAtten_X = static_cast<CEGUI::Editbox *>
			(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.53, 0.48, 0.05, 0.03), glm::vec4(0), "m_lightAtten_X"));
		m_lightAtten_X->setValidationString("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)");
		m_lightAtten_X->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&BuildObjectTool::onLightAttenuationValueChanged, this));
		m_lightAtten_Y = static_cast<CEGUI::Editbox *>
			(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.585, 0.48, 0.05, 0.03), glm::vec4(0), "m_lightAtten_Y"));
		m_lightAtten_Y->setValidationString("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)");
		m_lightAtten_Y->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&BuildObjectTool::onLightAttenuationValueChanged, this));
		m_lightAtten_Z = static_cast<CEGUI::Editbox *>
			(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.64, 0.48, 0.05, 0.03), glm::vec4(0), "m_lightAtten_Z"));
		m_lightAtten_Z->setValidationString("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)");
		m_lightAtten_Z->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&BuildObjectTool::onLightAttenuationValueChanged, this));

		m_lightcolorRGBA_label = static_cast<CEGUI::DefaultWindow*>
			(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.475, 0.52, 0.08, 0.05), glm::vec4(0), "m_lightcolorRGBA_label"));
		m_lightcolorRGBA_label->setText("Color");
		m_lightcolorRGBA_label->setProperty("HorzFormatting", "LeftAligned");


		

		m_lightColor_r = static_cast<CEGUI::Editbox *>
			(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.53, 0.53, 0.05, 0.03), glm::vec4(0), "m_lightColor_r"));
		m_lightColor_r->setValidationString("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)");
		m_lightColor_r->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&BuildObjectTool::onLightColorValueChanged, this));
		m_lightColor_g = static_cast<CEGUI::Editbox *>
			(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.585, 0.53, 0.05, 0.03), glm::vec4(0), "m_lightColor_g"));
		m_lightColor_g->setValidationString("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)");
		m_lightColor_g->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&BuildObjectTool::onLightColorValueChanged, this));
		m_lightColor_b = static_cast<CEGUI::Editbox *>
			(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.64, 0.53, 0.05, 0.03), glm::vec4(0), "m_lightColor_b"));
		m_lightColor_b->setValidationString("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)");
		m_lightColor_b->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&BuildObjectTool::onLightColorValueChanged, this));
		m_lightColor_a = static_cast<CEGUI::Editbox *>
			(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.695, 0.53, 0.05, 0.03), glm::vec4(0), "m_lightColor_a"));
		m_lightColor_a->setValidationString("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)");
		m_lightColor_a->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&BuildObjectTool::onLightColorValueChanged, this));

		m_ambientLight_label = static_cast<CEGUI::DefaultWindow*>
			(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.475, 0.57, 0.08, 0.05), glm::vec4(0), "m_ambientLight_label"));
		m_ambientLight_label->setText("Ambient Light");
		m_ambientLight_label->setProperty("HorzFormatting", "LeftAligned");

		m_ambientLight = static_cast<CEGUI::Editbox *>
			(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.55, 0.58, 0.05, 0.03), glm::vec4(0), "m_ambientLight"));
		m_ambientLight->setValidationString("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)");
		std::stringstream stream;
		std::string str;
		stream << std::fixed << std::setprecision(2) << m_ambLight;
		str = stream.str();
		m_ambientLight->setText(str.c_str());
		//m_ambientLight->setText(std::to_string(m_ambLight).c_str());
		m_ambientLight->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&BuildObjectTool::onAmbientLightValueChanged, this));
		

		m_coliderList_label = static_cast<CEGUI::DefaultWindow*>
			(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.865, 0.54, 0.08, 0.05), glm::vec4(0), "m_coliderList_label"));
		m_coliderList_label->setText("Colider List");
		m_coliderList_label->setProperty("HorzFormatting", "LeftAligned");

		m_coliderList = static_cast<CEGUI::Listbox*> (m_gui->createWidget("TaharezLook/Listbox", glm::vec4(0.85, 0.58, 0.125, 0.25), glm::vec4(0), "m_coliderList"));
		m_coliderList->subscribeEvent(CEGUI::Listbox::EventMouseDoubleClick, CEGUI::Event::Subscriber(&BuildObjectTool::onColiderLiseDoubleClick, this));


		m_addColiderButton = static_cast<CEGUI::PushButton *>
			(m_gui->createWidget("TaharezLook/Button", glm::vec4(0.87, 0.835, 0.08, 0.04), glm::vec4(0), "m_addColiderButton"));
		m_addColiderButton->setText("Add Colider");
		m_addColiderButton->subscribeEvent(CEGUI::PushButton::EventMouseClick, CEGUI::Event::Subscriber(&BuildObjectTool::onAddColiderClick, this));

 		m_coliderDim_label = static_cast<CEGUI::DefaultWindow*>
 			(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.75, 0.84, 0.08, 0.05), glm::vec4(0), "m_coliderOffsetPos_label"));
 		m_coliderDim_label->setText("Width/Height");
		m_coliderDim_label->setProperty("HorzFormatting", "LeftAligned");

		m_coliderDim_X = static_cast<CEGUI::Editbox *>
			(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.72, 0.89, 0.05, 0.03), glm::vec4(0), "m_coliderOffsetPos_X"));
		m_coliderDim_X->setValidationString("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)");
		m_coliderDim_X->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&BuildObjectTool::onColiderDimValueChanged, this));


		m_coliderDim_Y = static_cast<CEGUI::Editbox *>
			(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.78, 0.89, 0.05, 0.03), glm::vec4(0), "m_coliderOffsetPos_Y"));
		m_coliderDim_Y->setValidationString("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)");
		m_coliderDim_Y->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&BuildObjectTool::onColiderDimValueChanged, this));

		m_objectName_label = static_cast<CEGUI::DefaultWindow*>
			(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.48, 0.68, 0.08, 0.05), glm::vec4(0), "m_objectName_label"));
		m_objectName_label->setText("Object Name");
		m_objectName_label->setProperty("HorzFormatting", "LeftAligned");

		m_objectName = static_cast<CEGUI::Editbox *>
			(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.54, 0.69, 0.1, 0.03), glm::vec4(0), "m_objectName"));
		
		m_saveObjetButton = static_cast<CEGUI::PushButton *>
			(m_gui->createWidget("TaharezLook/Button", glm::vec4(0.55, 0.74, 0.08, 0.04), glm::vec4(0), "m_saveObjetButton"));
		m_saveObjetButton->setText("Save Object");
		m_saveObjetButton->subscribeEvent(CEGUI::PushButton::EventMouseClick, CEGUI::Event::Subscriber(&BuildObjectTool::onSaveObjectClicked, this));


// 		m_coliderList_label = static_cast<CEGUI::DefaultWindow*>
// 			(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.48, 0.68, 0.08, 0.05), glm::vec4(0), "m_coliderList_label"));
// 		m_coliderList_label->setText("Object Name");
// 		m_coliderList_label->setProperty("HorzFormatting", "LeftAligned");

		m_showColiderButton = static_cast<CEGUI::ToggleButton *>
			(m_gui->createWidget("TaharezLook/Checkbox", glm::vec4(0.755, 0.66, 0.1, 0.1), glm::vec4(0), "m_showColiderButton"));
		m_showColiderButton->subscribeEvent(CEGUI::ToggleButton::EventMouseClick, CEGUI::Event::Subscriber(&BuildObjectTool::onColiderToggleBoxClicked, this));
		m_showColiderButton->setText("Show Colider");
		m_showColiderButton->setSelected(true);

		m_isSpriteInverted = static_cast<CEGUI::ToggleButton *>
			(m_gui->createWidget("TaharezLook/Checkbox", glm::vec4(0.4, 0.74, 0.1, 0.1), glm::vec4(0), "m_isSpriteInverted"));
		m_isSpriteInverted->subscribeEvent(CEGUI::ToggleButton::EventMouseClick, CEGUI::Event::Subscriber(&BuildObjectTool::onSpriteInvertToggleBoxClicked, this));
		m_isSpriteInverted->setText("Is Inverted");
		//m_isSpriteInverted->setSelected(true);
		//m_showColiderButton->setLookNFeel("TaharezLook/Checkbox");
	}

}

int BuildObjectTool::getValidSpriteID()
{
	int searchValue = 1;
	//int isValid = 1;
	for (int i = 0 ; i < m_object->getSpriteList().size(); i++)
	{
		if (searchValue == m_object->getSpriteList()[i].m_ID)
		{
			searchValue++;
		}
		else
		{
			return searchValue;
		}
			
	}
	return searchValue;
	
}

int BuildObjectTool::getValidLightID()
{
	int searchValue = 1;
	for (int i = 0; i < m_object->m_lightListID.size(); i++)
	{
		if (searchValue < m_object->m_lightListID[i])
		{
			return searchValue;
		}
		else
		{
			searchValue++;
		}
	}
	return searchValue;
}

int BuildObjectTool::getValidColiderID()
{
	int searchValue = 1;
	for (int i = 0; i < m_object->m_coliders.size(); i++)
	{
		if (searchValue < m_object->m_coliders[i].getID())
		{
			return searchValue;
		}
		else
		{
			searchValue++;
		}
	}
	return searchValue;
}

bool BuildObjectTool::checkInsideLight(glm::vec2 mousePos)
{
	if (currentLightIndex > -1)
	{
		float radius = 1.0f / m_object->m_lightListAttenuation[currentLightIndex].z;
		if (mousePos.x > m_object->m_lightListPos[currentLightIndex].x - radius / 2.0f && mousePos.x < m_object->m_lightListPos[currentLightIndex].x + radius / 2.0f &&
			mousePos.y > m_object->m_lightListPos[currentLightIndex].y - radius / 2.0f && mousePos.y < m_object->m_lightListPos[currentLightIndex].y + radius / 2.0f)
		{

			return true;
		}
		return false;
		
	}
}

void BuildObjectTool::toggleShowColider()
{
	if (m_showColider)
	{
		m_showColider = false;
		m_showColiderButton->setSelected(false);
	}
	else
	{
		m_showColider = true;
		m_showColiderButton->setSelected(true);
	}
}

void BuildObjectTool::removeSelectedLightInList()
{
	if (m_lightList->getFirstSelectedItem())
	{
		m_lightList->removeItem(m_lightList->getFirstSelectedItem());
	}
	
}

void BuildObjectTool::show()
{
	if (m_spriteList)
	{
		m_spriteList->show();
		m_spriteListDesc_label->show();
		m_offsetPos_Y->show();
		m_offsetPos_X->show();
		m_offsetPos_label->show();
		m_offsetScale_label->show();
		m_offsetWidthScale->show();
		m_offsetHeightScale->show();
		m_colorRGBA_label->show();
		m_ownColor_r->show();
		m_ownColor_g->show();
		m_ownColor_b->show();
		m_ownColor_a->show();
		m_addLightButton->show();
		m_lightList->show();
		m_lightListDesc_label->show();
		m_lightPos_label->show();
		m_lightPos_X->show();
		m_lightPos_Y->show();
		m_lightAttenuation_label->show();
		m_lightAtten_X->show();
		m_lightAtten_Y->show();
		m_lightAtten_Z->show();

		m_lightcolorRGBA_label->show();
		m_lightColor_r->show();
		m_lightColor_g->show();
		m_lightColor_b->show();
		m_lightColor_a->show();
		m_ambientLight->show();
		m_ambientLight_label->show();

		m_coliderList_label->show();
		m_coliderList->show();
		m_addColiderButton->show();
		m_dephValue_label->show();
		m_dephValue->show();


		m_coliderDim_label->show();
		m_coliderDim_X->show();
		m_coliderDim_Y->show();
		m_angleValue_label->show();
		m_angleValue->show();
		m_objectName_label->show();
		m_objectName->show();
		m_saveObjetButton->show();
		m_showColiderButton->show();

		m_isSpriteInverted->show();
	}
	
}

void BuildObjectTool::hide()
{
	if (m_spriteList)
	{
		m_spriteList->hide();
		m_spriteListDesc_label->hide();
		m_offsetPos_Y->hide();
		m_offsetPos_X->hide();
		m_offsetPos_label->hide();
		m_offsetScale_label->hide();
		m_offsetWidthScale->hide();
		m_offsetHeightScale->hide();
		m_colorRGBA_label->hide();
		m_ownColor_r->hide();
		m_ownColor_g->hide();
		m_ownColor_b->hide();
		m_ownColor_a->hide();
		m_addLightButton->hide();
		m_lightList->hide();
		m_lightListDesc_label->hide();
		m_lightPos_label->hide();
		m_lightPos_X->hide();
		m_lightPos_Y->hide();
		m_lightAttenuation_label->hide();
		m_lightAtten_X->hide();
		m_lightAtten_Y->hide();
		m_lightAtten_Z->hide();

		m_lightcolorRGBA_label->hide();
		m_lightColor_r->hide();
		m_lightColor_g->hide();
		m_lightColor_b->hide();
		m_lightColor_a->hide();
		m_ambientLight->hide();
		m_ambientLight_label->hide();

		m_coliderList_label->hide();
		m_coliderList->hide();

		m_addColiderButton->hide();
		m_dephValue_label->hide();
		m_dephValue->hide();

		m_coliderDim_label->hide();
		m_coliderDim_X->hide();
		m_coliderDim_Y->hide();
		m_angleValue_label->hide();
		m_angleValue->hide();

		m_objectName_label->hide();
		m_objectName->hide();
		m_saveObjetButton->hide();
		m_showColiderButton->hide();

		m_isSpriteInverted->hide();
	}
}

bool BuildObjectTool::checkInside(glm::vec2 mousePos)
{
	if (mousePos.x > m_pos.x - m_currentDim.x / 2.0f && mousePos.x < m_pos.x + m_currentDim.x / 2.0f &&
		mousePos.y > m_pos.y - m_currentDim.y / 2.0f && mousePos.y < m_pos.y + m_currentDim.y / 2.0f)
	{

		return true;
	}
	return false;
}

