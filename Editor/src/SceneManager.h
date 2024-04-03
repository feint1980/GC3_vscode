#pragma once
#include <Fg_scene.h>
#include <InputManager.h>
#include <dirent.h>
#include <GUI.h>
#include <SpriteBatch.h>
#include <DebugRender.h>
#include <EmptyObject.h>
#include "EditorProperty.h"


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

	void updateSpacingOffset();

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

	glm::vec2 curMousePos;

	bool i_move = false;

	bool isGrid = false;


	glm::vec2 firstClick;

	Feintgine::Camera2D * m_sceneCam;

	Feintgine::Fg_scene * m_currentScene;
	std::string m_name;

	Feintgine::GUI * m_gui;

	CEGUI::DefaultWindow * gridOffset_label;
	CEGUI::Editbox * gridOffset_x;
	CEGUI::Editbox * gridOffset_y;

	CEGUI::ToggleButton * brushUVMode = nullptr;;
	CEGUI::ToggleButton * brushCustomMode = nullptr;

	CEGUI::Combobox * texturePicker = nullptr;

	CEGUI::PushButton * addBrushButton; 


	CEGUI::Window * m_addBrushWindow;

	CEGUI::Editbox * m_brushName;
	CEGUI::Editbox * m_brushDepth;

	CEGUI::Editbox * m_brushCollum;
	CEGUI::Editbox * m_brushRow;

	CEGUI::Editbox * m_brushPosX;
	CEGUI::Editbox * m_brushPosY;



	int m_itemCount = 0;

	CEGUI::PushButton * gridApply;

	glm::vec2 savedPos;
	

};

