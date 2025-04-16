#pragma once
#include <Fg_scene.h>
#include <InputManager.h>
#include <dirent.h>
#include <GUI.h>
#include <SpriteBatch.h>
#include <DebugRender.h>
#include <EmptyObject.h>
#include "EditorProperty.h"
#include <feint_common.h>


const int SELECT_MODE = 1;
const int EDIT_MODE = 2;

const int BRUSH_UV_MODE = 0;
const int BRUSH_CUSTOM_MODE = 1;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	bool createScene(const std::string & fileName);
	int listdir(const char *name, int level, const char *fileName);

	void init(Feintgine::Camera2D * cam, Feintgine::GUI * gui);

	void loadIcons();

	int browseScene(const char *name, int level,CEGUI::Listbox * listBox);
	void closeCurrentScene();

	void loadSceneFromFile(const std::string & filePath,CEGUI::MultiColumnList * list);

	Feintgine::Fg_scene * getCurrentScene() const { return m_currentScene; }

	void handleInput(Feintgine::InputManager & inputManager, bool isSelected, const Feintgine::F_Object &object,CEGUI::MultiColumnList * list);

	void update(const glm::vec2 & mousePos);

	void drawBox(Feintgine::DebugRender & debugRenderer);

	void selectCurrentLayer(const std::string & layerName);

	glm::vec2 getOffsetPos();

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void showGUIcomponent(bool val);

	void drawIcons(Feintgine::SpriteBatch & spriteBatch);
	void drawLight(Feintgine::LightBatch & lightBatch);
	void drawIconsBorder(Feintgine::DebugRender & debugRenderer);

	bool onSpacingXOffsetChanged(const CEGUI::EventArgs &e);

	bool onAddBurshClick(const CEGUI::EventArgs &e);

	bool onSpacingYOffsetChanged(const CEGUI::EventArgs &e);

	bool onApplyGridClick(const CEGUI::EventArgs & e);

	bool onCloseBrushProtocol(const CEGUI::EventArgs  &e);

	bool addBrushOnCurrentLayer(const CEGUI::EventArgs &e);

	bool onXPosTextChange(const CEGUI::EventArgs &e);

	bool onPosEditBoxClick(const CEGUI::EventArgs &e);

	bool onPosUpPadClick(const CEGUI::EventArgs &e);

	bool onPosDownPadClick(const CEGUI::EventArgs &e);

	bool onPosLeftPadClick(const CEGUI::EventArgs &e);

	bool onPosRightPadClick(const CEGUI::EventArgs &e);

	bool onAnglePadLeftClick(const CEGUI::EventArgs &e);

	void updatePosClick(int signal);

	void updateSelectObjectPos(const glm::vec2 & pos);

	void updateSelectObjectsAngle(float angle);

	void updateSpacingOffset();

	void updateSelectObjectsPos();

	void updateSelectObjectAngle();

	void loadBrushTexture(CEGUI::Combobox * list,const std::string & itemName) ;

	void switchMode(int BrushMode);

	bool isGrided() const { return isGrid; }

	void saveScene();

	int listdir(const char *name, int level);
	//void update(const Feintgine::F_Object & m_selectedObject);

private:

	EmptyObject m_selectIcon;
	EmptyObject m_moveIcon;

	Feintgine::Fg_layer * m_currentLayer = nullptr;

	int m_currentMode = SELECT_MODE;

	CEGUI::MultiColumnList * m_layerList = nullptr;

	glm::vec2 curMousePos;

	bool i_move = false;

	bool isGrid = false;

	glm::vec2 firstClick;

	Feintgine::Camera2D * m_sceneCam = nullptr;

	Feintgine::Fg_scene * m_currentScene = nullptr;
	std::string m_name;

	Feintgine::GUI * m_gui = nullptr;

	CEGUI::DefaultWindow * gridOffset_label = nullptr;
	CEGUI::Editbox * gridOffset_x = nullptr;
	CEGUI::Editbox * gridOffset_y = nullptr;

	CEGUI::ToggleButton * brushUVMode = nullptr;;
	CEGUI::ToggleButton * brushCustomMode = nullptr;

	CEGUI::Combobox * texturePicker = nullptr;

	CEGUI::PushButton * addBrushButton; 
	CEGUI::PushButton * gridApply;

	CEGUI::Window * m_addBrushWindow;

	CEGUI::Editbox * m_brushCollum;
	CEGUI::Editbox * m_brushRow;

	CEGUI::Editbox * m_brushPosX;
	CEGUI::Editbox * m_brushPosY;

	CEGUI::DefaultWindow * m_pos_label;
	CEGUI::Editbox * m_posXEditBox;
	CEGUI::Editbox * m_posYEditBox;

	CEGUI::PushButton * m_posUpButton;
	CEGUI::PushButton * m_posDownButton;
	CEGUI::PushButton * m_posLeftButton;
	CEGUI::PushButton * m_posRightButton;

	CEGUI::PushButton * m_angleLeftRotate;
	CEGUI::PushButton * m_angleRightRotate;


	CEGUI::DefaultWindow * m_angle_label;
	CEGUI::Editbox * m_angleEditBox;

	bool m_moveObject = false;

	int m_itemCount = 0;
	glm::vec2 savedPos;
	glm::vec2 m_centerPos;
	float m_centerAngle = 0.0f;

};

