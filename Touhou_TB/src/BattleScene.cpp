
#include "BattleScene.h"


int lua_CreateEntity(lua_State * L)
{
	if (lua_gettop(L) < 3 ||  lua_gettop(L) > 7)
	{
		std::cout << "gettop failed (lua_CreateFromLua) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}
	std::cout << "[C++] lua_CreateEntity called \n";
	glm::vec2 pos(0);
	
	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));
	std::string animationPath = lua_tostring(L, 2);
	Slot * slot = static_cast<Slot*>(lua_touserdata(L, 3));
	int side = 1;
	glm::vec2 scale = glm::vec2(1.0f, 1.0f);
	std::string portraitPath = "";
	if(lua_gettop(L) >= 4)
	{
		portraitPath = lua_tostring(L, 4);
	}

	if(lua_gettop(L) >= 5)
	{
		side = (int)lua_tonumber(L, 5);
	}

	if(lua_gettop(L) >= 6)
	{
		float t_scale = (float)lua_tonumber(L, 6);
		scale = glm::vec2(t_scale, t_scale);

	}
	if(lua_gettop(L) >= 7)
	{
		float t_scale_x = (float)lua_tonumber(L, 6);
		float t_scale_y = (float)lua_tonumber(L, 7);
		scale = glm::vec2(t_scale_x, t_scale_y);
	}
	
	F_Lua_BaseEntity * object = battleScene->addEntity(slot, animationPath, portraitPath, scale);
	object->setSide(side);

	lua_pushlightuserdata(L, object);
	return 1; // this host function return 1 number 
}

int lua_SetAtrribute(lua_State * L)
{
	if (lua_gettop(L) != 3)
	{
		std::cout << "gettop failed (lua_SetAtrribute) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}
	F_Lua_BaseEntity * object = static_cast<F_Lua_BaseEntity*>(lua_touserdata(L, 1));

	std::string attributeName = lua_tostring(L, 2);

	float value = (float)lua_tonumber(L, 3);

	object->setAttribute(attributeName, value);

	return 0;
}
int lua_SetStrAtrribute(lua_State * L)
{
if (lua_gettop(L) != 3)
	{
		std::cout << "gettop failed (lua_SetAtrribute) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}
	F_Lua_BaseEntity * object = static_cast<F_Lua_BaseEntity*>(lua_touserdata(L, 1));

	std::string attributeName = lua_tostring(L, 2);

	std::string value = lua_tostring(L, 3);

	object->setAttribute(attributeName, value);

	return 0;
}
F_Lua_BaseEntity * BattleScene::addEntity(Slot * slot, const std::string & animationPath,const std::string & portraitPath , const glm::vec2 & scale)
{

	F_Lua_BaseEntity * object = new F_Lua_BaseEntity();
	object->init(slot, animationPath,portraitPath, scale);
	m_entities.push_back(object);
	return object;
}



int lua_CreateSlot(lua_State * L)
{
	if (lua_gettop(L) != 4)
	{
		std::cout << "gettop failed (lua_CreateSlot) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}
	std::cout << "[C++] lua_CreateSlot called \n";
	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));
	int row = (int)lua_tonumber(L, 2);
	int colum = (int)lua_tonumber(L, 3);
	int side = (int)lua_tonumber(L, 4);
	Slot * slot = battleScene->addSlot(row, colum, side);
	lua_pushlightuserdata(L, slot);
	return 1;
} 

int lua_PickActiveEntity(lua_State * L)
{
	if (lua_gettop(L) != 2)
	{
		std::cout << "gettop failed (lua_PickActiveEntity) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));
	F_Lua_BaseEntity * object = static_cast<F_Lua_BaseEntity*>(lua_touserdata(L, 2));
	battleScene->pickActiveEntity(object);
}

int lua_GetSlotCol(lua_State * L)
{
	if (lua_gettop(L) != 1)
	{
		std::cout << "gettop failed (lua_GetSlotCol) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}
	Slot * slot = static_cast<Slot*>(lua_touserdata(L, 1));
	int col = slot->getIndex().x;
	lua_pushnumber(L, col);
	return 1;
}

int lua_GetSlotRow(lua_State * L)
{
	if (lua_gettop(L) != 1)
	{
		std::cout << "gettop failed (lua_GetSlotRow) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}
	Slot * slot = static_cast<Slot*>(lua_touserdata(L, 1));
	int row = slot->getIndex().y;
	lua_pushnumber(L, row);
	return 1;
}

int lua_GetEntitySlot(lua_State * L)
{
	if (lua_gettop(L) != 1)
	{
		std::cout << "gettop failed (lua_GetEntitySlot) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	F_Lua_BaseEntity * object = static_cast<F_Lua_BaseEntity*>(lua_touserdata(L, 1));
	Slot * slot = object->getCurrentSlot();
	lua_pushlightuserdata(L, slot);

	return 1;
}

int lua_EntityPlayAnimation(lua_State * L)
{

	if (lua_gettop(L) < 4 || lua_gettop(L) > 6)
	{
		std::cout << "gettop failed (lua_EntityPlayAnimation) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));
	F_Lua_BaseEntity * object = static_cast<F_Lua_BaseEntity*>(lua_touserdata(L, 2));
	std::string animationName = lua_tostring(L, 3);

	bool isWait = false;
	isWait = lua_toboolean(L, 4);
	

	int time = 0;
	if (lua_gettop(L) >= 5)
	{
		time = (int)lua_tonumber(L, 5);
	}
	float duration = 500.0f;
	if(lua_gettop(L) == 6)
	{
		
		duration = (float)lua_tonumber(L, 6);
		std::cout << " has duration " << duration << "\n";
	}
	

	F_Lua_EntityManipulator * manipulator = new F_Lua_EntityManipulator();

	manipulator->playAnimation(object, animationName, time, duration);

	//battleScene->addEntityManipulator(manipulator);

	if(isWait)
	{
		battleScene->addEntityManipulator(manipulator);
	}
	else
	{
		battleScene->addNonWaitEntityManipulator(manipulator);
	}

	return 0;
}

int lua_EntityMoveToSlot(lua_State * L)
{

	if (lua_gettop(L) != 4)
	{
		std::cout << "gettop failed (lua_EntityMoveToSlot) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));
	F_Lua_BaseEntity * object = static_cast<F_Lua_BaseEntity*>(lua_touserdata(L, 2));
	Slot * slot = static_cast<Slot*>(lua_touserdata(L, 3));
	float time = (float)lua_tonumber(L, 4);

	F_Lua_EntityManipulator * manipulator = new F_Lua_EntityManipulator();

	manipulator->moveToSlot(object, slot, time);

	battleScene->addEntityManipulator(manipulator);	

	return 0;
}

void BattleScene::addEntityManipulator(F_Lua_EntityManipulator * entityManipulator)
{

	m_entityManipulators.push_back(entityManipulator);
}

void BattleScene::addNonWaitEntityManipulator(F_Lua_EntityManipulator * entityManipulator)
{

	m_nonWaitManipulators.push_back(entityManipulator);

}


int lua_EntityGetTargetSlot(lua_State * L)
{
	if (lua_gettop(L) != 1)
	{
		std::cout << "gettop failed (lua_EntityGetTargetSlot) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	F_Lua_BaseEntity * object = static_cast<F_Lua_BaseEntity*>(lua_touserdata(L, 1));

	Slot * slot = object->getTargetSlot();

	lua_pushlightuserdata(L, slot);
	return 1;	

}

int lua_CreateGUIHandler(lua_State * L)
{

	if (lua_gettop(L) != 4)
	{
		std::cout << "gettop failed (lua_CreateGUIHandler) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));
	std::string selectionTexturePath = lua_tostring(L, 2);
	glm::vec2 dim = glm::vec2(0);

	dim.x = (float)lua_tonumber(L, 3);
	dim.y = (float)lua_tonumber(L, 4);

	GUI_handler * handler =  battleScene->createGUIHandler(selectionTexturePath, dim);

	lua_pushlightuserdata(L, handler);

	return 1;
}


GUI_handler * BattleScene::createGUIHandler(const std::string & selectionTexturePath, const glm::vec2 & dim)
{

	if(m_guiHandler == nullptr)
	{
		m_guiHandler = new GUI_handler();	
		m_guiHandler->init(selectionTexturePath, dim);
		m_guiHandler->registerBattleScene(this);
		m_guiHandler->registerCamera(m_camera);

	}
	
	return m_guiHandler;
}


int lua_CreateSlotHandler(lua_State * L)
{

	if (lua_gettop(L) != 1)
	{
		std::cout << "gettop failed (lua_CreateSlotHandler) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));
	SlotHandler * slotHandler =  battleScene->createSlotHandler();

	lua_pushlightuserdata(L, slotHandler);

	return 1;
}

SlotHandler * BattleScene::createSlotHandler()
{

	if(m_slotHandler == nullptr)
	{
		m_slotHandler = new SlotHandler();
		m_slotHandler->init(this, m_camera);
	}

	return m_slotHandler;
}


int lua_CreateIcon(lua_State * L)
{

	if (lua_gettop(L) < 10 || lua_gettop(L) > 11)
	{
		std::cout << "gettop failed (lua_CreateIcon) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));
	std::string texturePath = lua_tostring(L, 2);
	glm::vec2 dim = glm::vec2(0);

	dim.x = (float)lua_tonumber(L, 3);
	dim.y = (float)lua_tonumber(L, 4);
	std::string name = lua_tostring(L, 5);
	std::string description = lua_tostring(L, 6);
	float turnCost = (float)lua_tonumber(L, 7);
	float manaCost = (float)lua_tonumber(L, 8);
	std::string turnCostStr = lua_tostring(L, 9);
	std::string manaCostStr = lua_tostring(L, 10);


	unsigned int specialID = 0;
	if(lua_gettop(L) == 11)
	{
		specialID = (unsigned int)lua_tonumber(L, 11);
	}

	GUI_icon * icon =  battleScene->createIcon(texturePath,glm::vec2(0), dim);
	icon->setName(name);
	icon->setDescription(description);
	icon->setTurnCost(turnCost);
	icon->setSpecialID(specialID);
	icon->setManaCost(manaCost);
	icon->setTurnCostString(turnCostStr);
	icon->setManaCostString(manaCostStr);

	lua_pushlightuserdata(L, icon);

	std::cout << "Add icon called OK \n";
	return 1;

}

GUI_icon * BattleScene::createIcon(const std::string & texturePath, const glm::vec2 & pos, const glm::vec2 & dim)
{


	GUI_icon * icon = new GUI_icon();
	icon->init(texturePath, pos, dim);
	m_icons.push_back(icon);

	return icon;
}


int lua_GuiHandlerRemoveIcon(lua_State * L)
{

	if (lua_gettop(L) != 2)
	{
		std::cout << "gettop failed (lua_GUIHandlerRemoveIcon) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}
	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));
	GUI_icon * icon = static_cast<GUI_icon*>(lua_touserdata(L, 2));

	battleScene->GUIHandlerRemoveIcon(icon);

	return 0;


}

void BattleScene::GUIHandlerRemoveIcon(GUI_icon * icon)
{

	m_guiHandler->removeIcon(icon);
	
}

int lua_GUIHandlerAddIcon(lua_State * L)
{

	if (lua_gettop(L) != 2)
	{
		std::cout << "gettop failed (lua_GUIHandlerAddIcon) \n";	
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));
	GUI_icon * icon = static_cast<GUI_icon*>(lua_touserdata(L, 2));

	battleScene->GUIHandlerAddIcon(icon);
	
	return 0;
}


void  BattleScene::initTGUI(SDL_Window * window )
{

	TTF_Init();
	m_tgui = new tgui::Gui(window);
	tgui::Font font("./font/ARIALUNI.ttf");

	m_tgui->setFont(font);


	m_iconName = tgui::RichTextLabel::create();	
	m_iconName->setPosition(800,710);
	m_iconName->setTextSize(32);
	m_iconName->getRenderer()->setTextColor(tgui::Color::White);
	m_iconName->getRenderer()->setBorderColor(tgui::Color::Black);
	m_iconName->getRenderer()->setTextOutlineThickness(1);
	//m_iconName->getRenderer()->setTextOutlineColor(tgui::Color::White);
	m_iconName->setText("Name");

	m_iconTurnCost = tgui::RichTextLabel::create();	
	m_iconTurnCost->setPosition(800,760);
	m_iconTurnCost->setTextSize(20);
	m_iconTurnCost->getRenderer()->setTextColor(tgui::Color::White);
	m_iconTurnCost->getRenderer()->setBorderColor(tgui::Color::Black);
	m_iconTurnCost->getRenderer()->setTextOutlineThickness(1);
	m_iconTurnCost->setText("Cost :");

	m_iconManaCost = tgui::RichTextLabel::create();	
	m_iconManaCost->setPosition(800,780);
	m_iconManaCost->setTextSize(20);
	m_iconManaCost->getRenderer()->setTextColor(tgui::Color::White);
	m_iconManaCost->getRenderer()->setBorderColor(tgui::Color::Black);
	m_iconManaCost->getRenderer()->setTextOutlineThickness(1);
	m_iconManaCost->setText("Cost :");

	m_iconDescription = tgui::RichTextLabel::create();	
	m_iconDescription->setPosition(800,820);
	m_iconDescription->setTextSize(18);
	m_iconDescription->getRenderer()->setTextColor(tgui::Color::White);
	m_iconDescription->getRenderer()->setBorderColor(tgui::Color::Black);
	m_iconDescription->getRenderer()->setTextOutlineThickness(1);
	m_iconDescription->setText("hereqwewqe \n<color=#ff0000>C Davai machi</color>");

	m_tgui->add(m_iconName);
	m_tgui->add(m_iconTurnCost);
	m_tgui->add(m_iconManaCost);
	m_tgui->add(m_iconDescription);


}

void BattleScene::GUIHandlerAddIcon(GUI_icon * icon)
{
	
	if(m_guiHandler != nullptr)
	{
		m_guiHandler->addIcon(icon);
	}
}

void BattleScene::setGUIHandlerIconPos(GUI_icon * icon, const glm::vec2 & pos)
{
	if(m_guiHandler != nullptr)
	{
		m_guiHandler->setIconPos(icon, pos);
	}
}

int lua_GuiHandlerSetIconPos(lua_State * L)
{

	if (lua_gettop(L) != 4)
	{
		std::cout << "gettop failed (lua_GuiHandlerSetIconPos) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}
	

	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));
	GUI_icon * icon = static_cast<GUI_icon*>(lua_touserdata(L, 2));
	glm::vec2 pos = glm::vec2(0);

	pos.x = (float)lua_tonumber(L, 3);
	pos.y = (float)lua_tonumber(L, 4);

	std::cout << "[C++] lua_GuiHandlerSetIconPos called \n";
	std::cout << "pos " << pos.x << " " << pos.y << "\n"; 

	battleScene->setGUIHandlerIconPos(icon, pos);
	return 0;

}


int lua_GuiHandlerSetSelectedIcon(lua_State * L)
{

	if (lua_gettop(L) != 2)
	{
		std::cout << "gettop failed (lua_GuiHandlerGetSelectedIcon) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));
	GUI_icon * icon = static_cast<GUI_icon*>(lua_touserdata(L, 2));
	GUI_icon * selectedIcon = battleScene->setGUIHandlerSelectedIcon(icon);
	lua_pushlightuserdata(L, selectedIcon);
	return 1;
}

GUI_icon * BattleScene::setGUIHandlerSelectedIcon(GUI_icon * icon)
{
	if(m_guiHandler)
	{

		GUI_icon * selectedIcon = m_guiHandler->getSelectedIcon(icon);

		std::string name  = selectedIcon->getName();
		// if(m_iconName)
		// {
		m_iconName->setText(name.c_str());
		//}
		
	

		std::string turnCost = "Turn cost: <i><color=#FF8800>";
		turnCost += (feint_common::Instance()->convertPreciousFloatToString(selectedIcon->getTurnCost()));
		turnCost += ("</color></i> ");
		turnCost += (selectedIcon->getTurnCostString());

		std::string manaCost = "Mana cost: <i><color=#0090FF>";
		manaCost += (feint_common::Instance()->convertPreciousFloatToString(selectedIcon->getManaCost()));
		manaCost += ("</color></i> ");
		manaCost += (selectedIcon->getManaCostString());

		m_iconTurnCost->setText(turnCost);
		m_iconManaCost->setText(manaCost);
		m_iconDescription->setText(selectedIcon->getDescription());

		return selectedIcon;
	}
}

int lua_SetPhase(lua_State * L)
{

	if (lua_gettop(L) != 3)
	{
		std::cout << "gettop failed (lua_SetPhase) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));
	int phase = lua_tonumber(L, 2);
	int side = lua_tonumber(L, 3);	
	battleScene->setPhase(phase, side);
	return 0;
}

int lua_GetIconPos(lua_State * L)
{
	if(lua_gettop(L) != 1)
	{
		std::cout << "gettop failed (lua_SetIconPos) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	GUI_icon * icon = static_cast<GUI_icon*>(lua_touserdata(L, 1));
	glm::vec2 pos = icon->getPos();
	lua_pushnumber(L, pos.x);
	lua_pushnumber(L, pos.y);
	return 2;
}


int lua_GuiHandlerSetFocusColor(lua_State * L)
{

	if (lua_gettop(L) != 5)
	{
		std::cout << "gettop failed (lua_GuiHandlerSetFocusColor) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));
	int r = lua_tonumber(L, 2);
	int g = lua_tonumber(L, 3);
	int b = lua_tonumber(L, 4);
	int a = lua_tonumber(L, 5);
	Feintgine::Color color = Feintgine::Color(r, g, b, a);
	battleScene->setGUIHandlerFocusColor(color);
	return 0;
}

void BattleScene::setGUIHandlerFocusColor(const Feintgine::Color & color)
{

	if(m_guiHandler)
	{
		m_guiHandler->setFocusColor(color);
	}

}


void BattleScene::setPhase(int phaseType, int sides)
{
	m_phaseType = phaseType;
	m_SelectionSide = sides;

	//m_guiHandler->setPhase(phaseType, sides);
}

int lua_SetSlothandlerActive(lua_State * L)
{
	if(lua_gettop(L) != 2)
	{
		std::cout << "gettop failed (lua_SetSlothandlerActive) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	SlotHandler * handler = static_cast<SlotHandler*>(lua_touserdata(L, 1));
	bool active = lua_toboolean(L, 2);

	handler->setActive(active);
	return 0;
}

int lua_SelectHoverSlot(lua_State * L)
{

	if(lua_gettop(L) != 2)
	{
		std::cout << "gettop failed (lua_SelectHoverSlot) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	// if (lua_gettop(L) == 2)
	// {
	SlotHandler * handler = static_cast<SlotHandler*>(lua_touserdata(L, 1));
	Slot * slot = static_cast<Slot*>(lua_touserdata(L, 2));

	handler->setSelectTargetSlot(slot);
	//}
	// else if (lua_gettop(L) == 3)
	// {
	// 	SlotHandler * handler = static_cast<SlotHandler*>(lua_touserdata(L, 1));
	// 	int col = lua_tonumber(L, 2);
	// 	int row = lua_tonumber(L, 3);
	// 	handler->setSelectTargetSlot(col, row);
	// }
	
}


int lua_SetDescriptionBoxPos(lua_State * L)
{

	if(lua_gettop(L) != 3)
	{
		std::cout << "gettop failed (lua_SetDescriptionBoxPos) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));

	glm::vec2 pos  = glm::vec2(0);
	// glm::vec2(lua_tonumber(L, 2), lua_tonumber(L, 3));
	pos.x = lua_tonumber(L, 2);
	pos.y = lua_tonumber(L, 3);

	battleScene->setDescriptionBoxPos(pos);
	return 0;
}

void BattleScene::setDescriptionBoxPos(const glm::vec2 & pos)
{
	m_descriptionBox.setPos(pos);
}

int lua_SetDescriptionBoxDim(lua_State * L)
{
	if(lua_gettop(L) != 3)
	{
		std::cout << "gettop failed (lua_SetDescriptionBoxDim) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));

	glm::vec2 dim  = glm::vec2(0);
	// glm::vec2(lua_tonumber(L, 2), lua_tonumber(L, 3));
	dim.x = lua_tonumber(L, 2);
	dim.y = lua_tonumber(L, 3);

	std::cout << "lua_SetDescriptionBoxDim " << dim.x << " " << dim.y << "\n";
	battleScene->setDescriptionBoxDim(dim);
	return 0;
}

int lua_GuiHandlerClearIcons(lua_State * L)
{

	if(lua_gettop(L) != 1)
	{
		std::cout << "gettop failed (lua_GuiHandlerClearIcons) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));

	battleScene->GUIHandlerClearIcons();
}

void BattleScene::GUIHandlerClearIcons()
{
	m_guiHandler->clearIcons();
}

void BattleScene::setDescriptionBoxDim(const glm::vec2 & dim)
{
	std::cout << "setDescriptionBoxDim " << dim.x << " " << dim.y << "\n";
	m_descriptionBox.setDim(dim);
}


int lua_IsSlotEmpty(lua_State * L)
{

	if(lua_gettop(L) != 2)
	{
		std::cout << "gettop failed (lua_IsSlotEmpty) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));
	Slot * slot = static_cast<Slot*>(lua_touserdata(L, 2));

	bool value = true; // default value is empty
	value = battleScene->checkIfSlotEmpty(slot);
	//std::cout << "lua_IsSlotEmpty " << value << "\n";
	lua_pushboolean(L, value);

	return 1;

}


bool BattleScene::checkIfSlotEmpty(Slot * slot)
{
	for(int i = 0 ; i < m_entities.size(); i++)
	{
		//std::cout << "m_entities[i]->getCurrentSlot() " << m_entities[i]->getCurrentSlot() << "|" << slot << "\n";
		if(m_entities[i]->getCurrentSlot() == slot)
		{
			//std::cout << ""
			return false;
		}
	}

	return true;
}

int lua_GetSlotPos(lua_State * L)
{

	if(lua_gettop(L) != 1)
	{
		std::cout << "gettop failed (lua_GetSlotPos) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}
	Slot * slot = static_cast<Slot*>(lua_touserdata(L, 1));

	glm::vec2 pos = slot->getPos();

	lua_pushnumber(L, pos.x);
	lua_pushnumber(L, pos.y);

	return 2;
}


int lua_SlotHandlerSetValidTarget(lua_State * L)
{

	if(lua_gettop(L) != 2)
	{
		std::cout << "gettop failed (lua_SlotHandlerSetValidTarget) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));
	bool value = lua_toboolean(L, 2);

	battleScene->SlotHandlerSetValidSlot(value);

	return 0;	
}


void BattleScene::SlotHandlerSetValidSlot(bool isValidSlot)
{
	if(m_slotHandler)
	{
		m_slotHandler->setValidTargetSlot(isValidSlot);
	}

}

int lua_GetEntityPortrait(lua_State * L)
{

	if(lua_gettop(L) != 1)
	{
		std::cout << "gettop failed (lua_GetEntityPortrait) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	F_Lua_BaseEntity * entity = static_cast<F_Lua_BaseEntity*>(lua_touserdata(L, 1));

	lua_pushlightuserdata(L, entity->getPortrait());
	return 1;

}

int lua_SetPortraitPos(lua_State * L)
{

	if(lua_gettop(L) != 3)
	{
		std::cout << "gettop failed (lua_SetPortraitPos) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	EmptyObject * portrait = static_cast<EmptyObject*>(lua_touserdata(L, 1));
	float x = lua_tonumber(L, 2);
	float y = lua_tonumber(L, 3);

	portrait->setPos(glm::vec2(x, y));

	return 0;

}



int lua_CameraTargetZoom(lua_State * L)
{
	if(lua_gettop(L) != 7)
	{
		std::cout << "gettop failed (lua_SetPhase) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));

	F_Lua_BaseEntity * entity = static_cast<F_Lua_BaseEntity*>(lua_touserdata(L, 2));
	bool isWait = lua_toboolean(L, 3);

	float x = lua_tonumber(L, 4);
	float y = lua_tonumber(L, 5);
	float zoom = lua_tonumber(L, 6);
	float time = lua_tonumber(L, 7);
	
	F_Lua_EntityManipulator * manipulator = new F_Lua_EntityManipulator();
	manipulator->setZoomCamera(entity,battleScene->getCamera(), glm::vec2(x, y), zoom, time);
	// if(isWait)
	// {
	// 	battleScene->addEntityManipulator(manipulator);
	// }
	// else 
	// {
	// 	battleScene->addNonWaitEntityManipulator(manipulator);
	// }
	battleScene->addNonWaitEntityManipulator(manipulator);
	//battleScene->addEntityManipulator(manipulator);

	return 0;

}


int lua_WaitTime(lua_State * L)
{

	if(lua_gettop(L) != 3)
	{
		std::cout << "gettop failed (lua_WaitTime) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}


	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));
	F_Lua_BaseEntity * entity = static_cast<F_Lua_BaseEntity*>(lua_touserdata(L, 2));

	float time = lua_tonumber(L, 3);


	F_Lua_EntityManipulator * manipulator = new F_Lua_EntityManipulator();
	manipulator->waitTime(entity, time);
	battleScene->addEntityManipulator(manipulator);

	return 0;

}

int lua_ResetCamera(lua_State * L)
{

	if(lua_gettop(L)  < 1 || lua_gettop(L) > 4)
	{
		std::cout << "gettop failed (lua_ResetCamera) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;	
	}

	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1)); 
	F_Lua_BaseEntity * entity = static_cast<F_Lua_BaseEntity*>(lua_touserdata(L, 2));

	bool isWait = false;
	if(lua_gettop(L) == 3)
	{
		isWait = lua_toboolean(L, 3);
	}


	glm::vec2 resetPos = glm::vec2(0, 0);
	float resetZoom = 1;
	float resetTime = 10;
	if(lua_gettop(L) == 4)
	{
		resetTime = lua_tonumber(L, 4);
	}
	F_Lua_EntityManipulator * manipulator = new F_Lua_EntityManipulator();
	manipulator->setZoomCamera(entity,battleScene->getCamera(), resetPos, resetZoom, resetTime);
	if(isWait)
	{
		battleScene->addEntityManipulator(manipulator);
	}
	else
	{
		battleScene->addNonWaitEntityManipulator(manipulator);
	}
	
	return 0;
}

int lua_GetEntityPos(lua_State * L)
{

	if(lua_gettop(L) != 1)
	{
		std::cout << "gettop failed (lua_GetEntityPos) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	F_Lua_BaseEntity * entity = static_cast<F_Lua_BaseEntity*>(lua_touserdata(L, 1));

	lua_pushnumber(L, entity->getPos().x);
	lua_pushnumber(L, entity->getPos().y);

	return 2;
}


int lua_MoveEntity(lua_State * L)
{

	if(lua_gettop(L) != 6)
	{
		std::cout << "gettop failed (lua_SetPhase) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));
	F_Lua_BaseEntity * entity = static_cast<F_Lua_BaseEntity*>(lua_touserdata(L, 2));

	bool isWait = lua_toboolean(L, 3);

	float x = lua_tonumber(L, 4);
	float y = lua_tonumber(L, 5);
	float time = lua_tonumber(L, 6);


	F_Lua_EntityManipulator * manipulator = new F_Lua_EntityManipulator();
	manipulator->moveToPos(entity, glm::vec2(x, y), time);

	if(isWait)
	{
		battleScene->addEntityManipulator(manipulator);
	}
	else
	{
		battleScene->addNonWaitEntityManipulator(manipulator);
	}

	//battleScene->addEntityManipulator(manipulator);

	return 0;
}

int lua_ClearEntityTasks (lua_State * L)
{

	if(lua_gettop(L) != 2)
	{
		std::cout << "gettop failed (lua_ClearEntityTasks) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	
	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));
	F_Lua_BaseEntity * entity = static_cast<F_Lua_BaseEntity*>(lua_touserdata(L, 2));
	battleScene->clearEntityTasks(entity);

	return 0;

}

void BattleScene::clearEntityTasks(F_Lua_BaseEntity * entity)
{
	for(int i = 0 ; i < m_entityManipulators.size(); i++)
	{
		if(m_entityManipulators[i]->getEntity() == entity)
		{
			//delete m_entityManipulators[i];
			std::cout << "clear entity task" <<  i << "\n";
			m_entityManipulators.erase(m_entityManipulators.begin() + i);
			//return;
		}
	}
}


int lua_GetSlotEntity(lua_State * L)
{

	if(lua_gettop(L) != 2)
	{
		std::cout << "gettop failed (lua_GetSlotEntity) \n";
		std::cout << lua_gettop(L) << "\n";
		return -1;
	}

	BattleScene * battleScene = static_cast<BattleScene*>(lua_touserdata(L, 1));
	Slot * slot = static_cast<Slot*>(lua_touserdata(L, 2));

	F_Lua_BaseEntity * entity = battleScene->getEntityBySlot(slot);
	lua_pushlightuserdata(L, entity);

	return 1;
}

F_Lua_BaseEntity * BattleScene::getEntityBySlot(Slot * slot)
{
	for(int i = 0 ; i < m_entities.size(); i++)
	{
		if(m_entities[i]->getCurrentSlot() == slot)
		{
			return m_entities[i];
		}
	}


}


void BattleScene::init(Feintgine::Camera2D * camera )
{

	m_camera = camera;
	 // init lua
    m_script = luaL_newstate();
    luaL_openlibs(m_script);

	// register lua function
	lua_register(m_script, "cppCreateEnity", lua_CreateEntity);
	lua_register(m_script, "cppMoveEntity", lua_MoveEntity);
	lua_register(m_script, "cppSetAttribute", lua_SetAtrribute);
	lua_register(m_script, "cppSetStrAttribute", lua_SetStrAtrribute);
	lua_register(m_script, "cppPickActiveEntity", lua_PickActiveEntity);

	
	lua_register(m_script, "cppGetEntitySlot", lua_GetEntitySlot);
	lua_register(m_script, "cppGetEntityPos", lua_GetEntityPos);
	lua_register(m_script, "cppEntityPlayAnimation", lua_EntityPlayAnimation);
	lua_register(m_script, "cppEntityMoveToslot", lua_EntityMoveToSlot);
	lua_register(m_script, "cppEntityGetTargetSlot", lua_EntityGetTargetSlot);
	lua_register(m_script, "cppSetPhase", lua_SetPhase);

	lua_register(m_script, "cppGetEntityPortrait", lua_GetEntityPortrait);
	lua_register(m_script, "cppSetPortraitPos", lua_SetPortraitPos);

	// slots
	lua_register(m_script, "cppGetSlotCol", lua_GetSlotCol);
	lua_register(m_script, "cppGetSlotRow", lua_GetSlotRow);
	lua_register(m_script, "cppGetSlotPos", lua_GetSlotPos);
	lua_register(m_script, "cppGetSlotEntity", lua_GetSlotEntity);

	// slot Handler
	lua_register(m_script, "cppCreateSlotHandler", lua_CreateSlotHandler);
	lua_register(m_script, "cppCreateSlot", lua_CreateSlot);
	lua_register(m_script, "cppSetSlothandlerActive", lua_SetSlothandlerActive);
	lua_register(m_script, "cppSelectHoverSlot", lua_SelectHoverSlot);
	lua_register(m_script, "cppIsSlotEmpty", lua_IsSlotEmpty);
	lua_register(m_script, "cppSlotHandlerSetValidTarget", lua_SlotHandlerSetValidTarget);

	// GUI_handler data 
	lua_register(m_script, "cppCreateGUIHandler", lua_CreateGUIHandler);
	lua_register(m_script, "cppGUIHandlerAddIcon", lua_GUIHandlerAddIcon);
	lua_register(m_script, "cppGuiHandlerSetIconPos", lua_GuiHandlerSetIconPos);
	lua_register(m_script, "cppGuiHandlerSetSelectedIcon", lua_GuiHandlerSetSelectedIcon);
	lua_register(m_script, "cppGuiHandlerSetFocusColor", lua_GuiHandlerSetFocusColor);
	lua_register(m_script, "cppGuiHandlerRemoveIcon", lua_GuiHandlerRemoveIcon);
	lua_register(m_script, "cppGuiHandlerClearIcons", lua_GuiHandlerClearIcons);

	// create gui icon
	lua_register(m_script, "cppCreateIcon", lua_CreateIcon);
	lua_register(m_script, "cppGetIconPos", lua_GetIconPos);

	// misc
	lua_register(m_script, "cppSetDescriptionBoxPos", lua_SetDescriptionBoxPos);
	lua_register(m_script, "cppSetDescriptionBoxDim", lua_SetDescriptionBoxDim);
	
	// Camera work
	lua_register(m_script, "cppCameraTargetZoom", lua_CameraTargetZoom); 
	lua_register(m_script, "cppResetCamera", lua_ResetCamera);
	lua_register(m_script, "cppWaitTime", lua_WaitTime);


	lua_register(m_script, "cppClearEntityTasks", lua_ClearEntityTasks);



	//lua_register(m_script, "cppSetCameraPos", lua_SetCameraPos);

	m_descriptionBox.init(Feintgine::ResourceManager::getTexture("./Assets/TB_GUI/Description_box.png"), glm::vec2(200, -350), glm::vec2(400, 150), Feintgine::Color(255, 255, 255, 255));


	if (LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, "./Assets/lua/test.lua")))
	{
		std::cout << "read script OK \n";
	
	}

	lua_getglobal(m_script, "init");// get the function name to the top of the stack
	if (lua_isfunction(m_script, -1))
	{
		//std::cout << "host is " << this << "\n";
		lua_pushlightuserdata(m_script, this);
		//std::cout << "C++ called " + functionName << "\n";
		const int argCount = 1;
		const int returnCount =1;
		if (LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, argCount, returnCount, 0)))
		{
			
		}
	}


	
    // lua register 1 ( lua state ) , 2 name will be called in lua, 3 the pointer to function
    //lua_register(m_script, "cppCreateEntity", lua_createEntity);
}

BattleScene::BattleScene()
{

   
}

BattleScene::~BattleScene()
{

}

Slot * BattleScene::addSlot(int row, int colum, int side)
{
	if(m_slotHandler)
	{

		return m_slotHandler->addSlot(row, colum, side);
	}
	return nullptr;
	
}

void BattleScene::handleInput(Feintgine::InputManager & inputManager)
{

	if(m_guiHandler)
	{
		m_guiHandler->handleInput(inputManager, m_script);
	}
	// switch(m_phaseType)
	// {
	// 	case 0: // icon selection
	// 	{
	// 		if(m_guiHandler)
	// 		{
				
	// 		}
	// 	}
	// 	break;

	// 	case 1: // slot selection
	// 	{
	// 		glm::vec2 mousePos = inputManager.getMouseCoords();
	// 		for(int i = 0 ; i < m_slots.size(); i++)
	// 		{
	// 			if(m_slots[i]->isHovered(m_camera->convertScreenToWorld(mousePos)))
	// 			{
	// 				m_slots[i]->setState(1);
	// 			}
	// 			else
	// 			{
	// 				m_slots[i]->setState(0);
	// 			}
	// 		}
	// 	}
	// 	break;

	// 	default:
	// 	break;
	// }
	
}

void BattleScene::pickActiveEntity(F_Lua_BaseEntity * entity)
{

	for(int i = 0 ; i < m_entities.size(); i++)
	{
		if(m_entities[i] == entity)
		{
			m_currentEntity = m_entities[i];
			m_currentEntity->setActive(true);
			//m_entities[i]->setActive(true);

			return;
		}
	
	}
}


void BattleScene::drawGUI()
{
	if(m_tgui)
	{
		m_tgui->draw();
	}
}

void BattleScene::draw(Feintgine::SpriteBatch & spriteBatch)
{

	// for(int i = 0 ; i < m_slots.size(); i++)
	// {
	// 	m_slots[i]->draw(spriteBatch);
	// }

	m_descriptionBox.draw(spriteBatch);

	if(m_slotHandler)
	{
		m_slotHandler->draw(spriteBatch);
	}

	for(int i = 0 ; i < m_entities.size(); i++)
	{
		m_entities[i]->draw(spriteBatch);
	}
	if(m_guiHandler)
	{
		m_guiHandler->draw(spriteBatch);
	}

}

void BattleScene::setMoveTargetSlot(F_Lua_BaseEntity * entity, Slot * slot)
{
		entity->setTargetSlot(slot);
		lua_getglobal(m_script, "setEntityMoveToSlot");
		if (lua_isfunction(m_script, -1))
		{
			//m_luaBossStates[i]->m_luaBoss;
			
			//lua_pushlightuserdata(m_script, pThread);
			lua_pushlightuserdata(m_script, this); // host

			//std::cout << "Issue next task pointer " << object << "\n";

			lua_pushlightuserdata(m_script, entity);

			// lua_pushlightuserdata(m_script, entity->getTargetSlot());

			if (!LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, 2, 1, 0)))
			{
				std::cout << "call setEntityMoveToSlot failed \n";
			}
		}
}

void BattleScene::update(float deltaTime)
{


	
	if(m_guiHandler)
	{
		m_guiHandler->update(deltaTime);
	}
	if(m_slotHandler)
	{
		m_slotHandler->update(deltaTime);
	}
	if(m_camera)
	{
		m_camera->update();
	}
	// for(int i = 0 ; i < m_slots.size(); i++)
	// {
	// 	m_slots[i]->update(deltaTime);
	// 	if(m_currentEntity && !m_isMove)
	// 	{
	// 		if(m_currentEntity->isActive())
	// 		{
	// 			//std::cout << "has active entity \n";
	// 			if(m_slots[i]->getState() == 1)
	// 			{
	// 				setMoveTargetSlot(m_currentEntity, m_slots[i]);
	// 				m_isMove = true;
	// 			}um l,
	// 		}
	// 	}
	// }

	for(int i = 0 ; i < m_entities.size(); i++)
	{
		m_entities[i]->update(deltaTime);
	}

	// update manipulator
	// if(m_entityManipulators.size() > 0)
	// {
	// 	std::cout << "Entity Manipulators size " << m_entityManipulators.size() << "\n";
	// 	for(int i = 0 ; i < m_entityManipulators.size(); i++)
	// 	{
	// 		switch(m_entityManipulators[i]->getState())
	// 		{
	// 			case EntityState::Move:
	// 			{
	// 				std::cout << i << " : is Move \n"; 
	// 			}
	// 			break;

	// 			case EntityState::Animation:
	// 			{
	// 				std::cout << i << " : is Animation \n"; 
	// 			}
	// 			break;

	// 			case EntityState::Wait:
	// 			{
	// 				std::cout << i << " : is Wait \n";
	// 			}
	// 			break;

	// 			case EntityState::None:
	// 			{
	// 				std::cout << i << " : is None \n"; 
	// 			}
	// 			break;


	// 		}
	// 	}
	// }
	for(int i = 0 ; i < m_entityManipulators.size(); i++)
	{
		if(m_entityManipulators[i])
		{
			if(m_entityManipulators[i]->update(deltaTime))
			{
				lua_getglobal(m_script, "HandleSkillTasks");
				if (lua_isfunction(m_script, -1))
				{
					//m_luaBossStates[i]->m_luaBoss;
					F_Lua_BaseEntity * entity = m_entityManipulators[i]->getEntity();
					//lua_pushlightuserdata(m_script, pThread);
					lua_pushlightuserdata(m_script, this); // host

					//std::cout << "Issue next task pointer " << object << "\n";

					lua_pushlightuserdata(m_script, entity);

					//std::string name = entity->getStrAttributeByName("name");
					

					//lua_pusht

					// lua_pushlightuserdata(m_script, entity->getTargetSlot());
					std::cout << "called from C++ " << i << "\n";
					if (!LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, 2, 1, 0)))
					{
						std::cout << "HandleMovingTask failed \n";
					}
				}
				//delete m_entityManipulators[i]; 
				//m_entityManipulators[i] = nullptr;
				// After Issued next task
				m_entityManipulators.erase(m_entityManipulators.begin() + i);
			}
				
		}
	} // for entity manipulators
	for(int i = 0 ; i < m_nonWaitManipulators.size(); i++)
	{
		if(m_nonWaitManipulators[i])
		{
			if(m_nonWaitManipulators[i]->update(deltaTime))
			{
				std::cout << "manipulator" << i << " removed \n";

				delete m_nonWaitManipulators[i];
				m_nonWaitManipulators.erase(m_nonWaitManipulators.begin() + i);

			}
		}
	}
	

}
	
