#pragma once
#include <functional>
#include <iostream>
#include <IGameScreen.h>
#include <IMainGame.h>
#include <InputManager.h>
#include <GUI.h>
#include <Camera2D.h>
#include <vector>
#include <SpriteBatch.h>
#include <GLSLProgram.h>
#include <GLTexture.h>
#include <DebugRender.h>
#include <GLTexture.h>
#include <ResourceManager.h>
#include <Timing.h>
#include <windows.h>
#include <dirent.h>
#include <string>
#include <functional>
#include <feint_common.h>
#include <filesystem>
#include "ObjectUVRect.h"
#include "SpriteSheet.h"
#include "DisplaySample.h"
#include "ColiderBox.h"
#include "ObjectSlot.h"
#include "TemplateObject.h"
#include <algorithm>
//#include <f_object.pb.h>
#include <AnimatedObject.h>
#include <F_Sprite.h>
#include "SpriteListHolder.h"
#include <AudioEngine.h>

#include "EmptyObject.h"


#include <chrono>
#include <T_Scene.h>
#include <Fg_scene.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "EditObject.h"
#include "BuildObjectTool.h"
#include "ObjectListHolder.h"
#include <TextRenderer.h>

#include <locale>
#include <codecvt>
#include <string>

#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>
#include <F_AnimatedObject.h>
#include <Brush.h>
#include "SceneManager.h"
#include <math.h>
#include <F_TileSet.h>
#include "PaternEditor.h"
#include <F_TileStack.h>
#include "EnemyEditorComponent.h"
#include "../../GC3/src/F_MarisaRocket_small.h"
#include "LuaObjectEditorComponent.h"



const int TYPE_ALL = -1;
const int TYPE_TERRIAN = 0;
const int TYPE_OBJECT = 1;
const int TYPE_TREE = 2;
const int TYPE_PLANT = 3;
const int TYPE_DECAL = 4;

// struct lessWidth
// {
// 
// 	inline bool operator() (const ColiderBox & c1, const ColiderBox & c2)
// 	{
// 		return ((c1.getDim().x * c1.getDim().y) < (c2.getDim().x * c2.getDim().y));
// 	}
// };



const int edit_object_mode = 0;
const int edit_scene_mode = 1;
const int edit_animate_mode = 2;
const int edit_damaku_mode = 4;
const int edit_enemy_mode = 5;
const int edit_lua_mode = 6;

const int T_EDIT_SCREEN_MODE = 1;
const int T_EDIT_OJECT_MODE = 2;
const int T_EDIT_ANIMATE_MODE = 3;
const int T_EDIT_DAMAKU_MODE = 4;
const int T_EDIT_ENEMY_MODE = 5;
const int T_EDIT_LUA_MODE = 6;

const float DEFAULT_OBJECT_CAM_SCALE = 2.5f;

const int OBJECTIVE_OBJECT = 0;
const int OBJECTIVE_BRUSH = 1;

using namespace rapidxml;

class EditorScreen : public Feintgine::IGameScreen
{

public:
	
	
	// load packet  
	void loadPacket(const std::string & file);

	//

	EditorScreen();
	~EditorScreen();

	EditorScreen(Feintgine::Window * window);

	virtual int getNextScreenIndex() const override;
  
	virtual int getPreviousScreenIndex() const override;

	virtual void build() override;

	virtual void destroy() override;

	virtual void onEntry() override;

	virtual void onExit() override;

	virtual void update(float deltaTime) override;

	virtual void draw() override;
	
	std::string ExePath() {
		TCHAR NPath[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, NPath);
		std::string::size_type pos = std::string(NPath).find_last_of("\\/");

		 std::string rt = std::string(NPath).substr(0, pos);

		// rt.append("/Editor");
		 return rt;

	}

	void checkInput();
	
	void handleInput(Feintgine::InputManager & inputManager);

	
	//init ********************************************************************************

	
	void initSceneBrowse();

	void initGUI();
	void initShader();
	void initMenuBar();
	void initTextureList();
	void initObjectUI();

	void initFilters();
	void initLayerList();

	void initEditTool();

	void initActionBar();

	void initAObjList();

	//******************************************************************************
	void drawEditScreen();
	void drawSceneScreen();

	void drawSampleScreen();
	void drawObjectsScreen();
	void drawPreviewScreen();

	void drawAnimateObject();

	void drawSpriteList();

	void drawLoadingScene();

	void drawDamaKuScreen();


	//***********************************
	
	// stuffs 

	bool isInsideScreen(const glm::vec2 & pos, glm::vec4 t_sc);


	// Eitor functions****************************************************************

	void showFilePicker();

	
	bool openScene(const CEGUI::EventArgs &e);

	bool exitEditor(const CEGUI::EventArgs &e);
	
	bool pickItem(const CEGUI::EventArgs & e );

	bool layer_add_protocol(const CEGUI::EventArgs &e);

	bool layer_delete_protocol(const CEGUI::EventArgs & e);

	bool scene_create_protocol(const CEGUI::EventArgs &e);

	bool scene_select_protocol(const CEGUI::EventArgs &e);

	bool animation_new_protocol(const CEGUI::EventArgs &e);

	bool action_new_protocol(const CEGUI::EventArgs &e);

	void Layout_auto_protocol();

	bool createObject(const CEGUI::EventArgs &e);

	bool recalculateDimforSample(const CEGUI::EventArgs &e);

	bool createColider(const CEGUI::EventArgs &e);

	bool checkValid();

	bool createScene(const CEGUI::EventArgs &e);

	bool save(const CEGUI::EventArgs &e);

	void save_wat();

	bool save_as(const CEGUI::EventArgs &e);

	bool onAmbientLightChanged(const CEGUI::EventArgs &e);

	void readFile();

	bool destroyObjectPannel(const CEGUI::EventArgs & e);

	bool updateColor(const CEGUI::EventArgs & e);

	void DestroyColider();

	bool writeFile(const CEGUI::EventArgs &e);

	//void f_writeFile(const std::string & filePath);

	// void setUV(f_object_uv &uv1, f_object_uv &uv2);

	// void setColor(f_object_color &c1, f_object_color &c2);

	// void setfVec2(f_vec2 &v1, f_vec2 &v2);

	// void setColider(f_colider & c1, f_colider &c2);

	//void loadObject(const std::string & filePath);
	//void addWriteObjectColider(f_)

	void sortObject();

	void initSlot();

	void initAmbientTool();

	int getFirstFreeSlot();

	int listdir(const char *name, int level);

	void listDirver2();
	// *********************************************************************
	//Additional Function 
	void refresh();

	std::vector <TemplateObject > getFiltedList(std::vector<TemplateObject > list);

	void updatePage();

	bool filterChanges(const CEGUI::EventArgs &e);

	bool filterChanges_page(const CEGUI::EventArgs &e);

	bool filterChanges_name(const CEGUI::EventArgs &e);

	bool destroyCreateSceneWindow(const CEGUI::EventArgs &e);

	bool destroyAutoLayout(const CEGUI::EventArgs & e);

	void closeAutoLayout();

	bool addLayer(const CEGUI::EventArgs &e);

	int scanScene(const std::string & fileName);

	void destroySceneCreator();

	void addLayerFunc(const std::string &layerName, float layerDepth);

	void updateList();

	void selectItemFromTempalte(glm::vec2 mousePos);

	int getHoverIndex(glm::vec2 mousepos);

	void refreshFiltedList(std::string name);

	bool changeToEditObject(const CEGUI::EventArgs &e);

	bool changeToEditScene(const CEGUI::EventArgs & e);

	bool changeToEditAnimate(const CEGUI::EventArgs &e);

	bool changeToEditDamaku(const CEGUI::EventArgs &e);

	bool changeToEditEnemy(const CEGUI::EventArgs &e);

	bool changeToEditLua(const CEGUI::EventArgs &e);
	
	bool layout(const CEGUI::EventArgs &e);

	bool selectAction(const CEGUI::EventArgs &e);

	bool fixAnimationScroll(const CEGUI::EventArgs &e);
	
	bool playAnimation(const CEGUI::EventArgs &e);

	bool createAnimation(const CEGUI::EventArgs &e);

	bool createAction(const CEGUI::EventArgs &e);

	bool onMarkAsLoopToggled(const CEGUI::EventArgs &e);

	bool onMarkReady(const CEGUI::EventArgs &e);

	bool onMarkAsStop(const CEGUI::EventArgs &e);

	bool recheckTick(const CEGUI::EventArgs &e);

	bool updateAnimTick(const CEGUI::EventArgs &e);

	bool pauseAnimation(const CEGUI::EventArgs &e);

	bool stopAnimation(const CEGUI::EventArgs &e);

	bool updateAnimation(const CEGUI::EventArgs &e);

	bool onAnimationListChange(const CEGUI::EventArgs &e);

	bool onAnimationDeleteClick(const CEGUI::EventArgs &e);

	int getLastestPage();

	void hideObjectEditor();

	void showObjectEditor();

	void showSceneEditor();

	void hideSceneEditor();

	void showAnimateEditor();

	void hideAnimateEditor();

	void showDamakuEditor();

	void hideDamakuEditor();

	void showEditEnemyEditor();

	void hideEditEnemyEditor();

	void togglePlayAnimation();

	void handleEditScreen(Feintgine::InputManager & inputManager);

	void handleException(Feintgine::InputManager & inputManager);

	bool selectCurrentLayer(const CEGUI::EventArgs &e);

	void updateListedLayer();

	void closeSelectSceen();

	bool destroySelecrSceen(const CEGUI::EventArgs &e);

	bool selectScene(const CEGUI::EventArgs &e);

	bool addSpriteToObject(const CEGUI::EventArgs &e);

	bool onAddAnimButtonClicked(const CEGUI::EventArgs &e);

	bool onRemoveAnimButtonCLicked(const CEGUI::EventArgs &e);

	bool onDeleteActionButtonClicked(const CEGUI::EventArgs &e);

	bool onListActionChangedEvent(const CEGUI::EventArgs &e);

	bool onApplyToCurrentAnimButtonCLicked(const CEGUI::EventArgs &e);

	bool destroyNewAnimationScreen(const CEGUI::EventArgs &e);

	bool destroyNewActionScreen(const CEGUI::EventArgs &e);

	bool onLoopToggle(const CEGUI::EventArgs &e);

	bool pickAobj(const CEGUI::EventArgs &e);

	bool saveAnimation(const CEGUI::EventArgs &e);

	void pushMassive(int col, int row);

	void deleteCurrentLayer();

	void clearLayer();

	//void loadActions(std::string );

	void toggleHide_ShowLayer();

	void toggleGridMode();

	bool eventSelectSprite();

	void switchScreen(int flag);

	bool onSpriteInvertToggleBoxClicked(const CEGUI::EventArgs &e);

	bool onOffsetAnimationChangedX(const CEGUI::EventArgs &e);
	bool onOffsetAnimationChangedY(const CEGUI::EventArgs &e);

	bool onOffsetPosChangedLeft(const CEGUI::EventArgs &e);
	bool onOffsetPosChangedRight(const CEGUI::EventArgs &e);
	bool onOffsetPosChangedUp(const CEGUI::EventArgs &e);
	bool onOffsetPosChangedDown(const CEGUI::EventArgs &e);
	

	std::string getFrameDataFromAnim(const Feintgine::F_AnimatedObject & obj);

	void updateAnimationLabel();

	void entryRuntime();
	//


private :

	bool m_isMouseLeftHold = false;

	bool m_firstFrame = false;

	std::string m_sceneFileName;

	CEGUI::Editbox * pointerEdit;

	// Basic Screen components
	Feintgine::Camera2D m_camera;
	Feintgine::Camera2D staticCam_Editing;
	Feintgine::Camera2D staticCam_Animating;
	Feintgine::Camera2D staticCam_Sample;
	Feintgine::Camera2D m_sampleCam;
	Feintgine::Camera2D m_animatingCamera;
	Feintgine::Camera2D m_objectsCamera;

	Feintgine::Camera2D m_spriteListCamera;

	Feintgine::Camera2D m_previewCamera;
	Feintgine::Camera2D m_previewCamera_static;

	Feintgine::Camera2D m_sceneCamera;
	Feintgine::Camera2D m_sceneCamera_static;

	Feintgine::Camera2D m_editDamakuCamera;
	Feintgine::Camera2D m_editDamakuCamera_static;

	Feintgine::Camera2D m_editEnemyCamera;
	Feintgine::Camera2D m_editEnemyCamera_static;

	Feintgine::Camera2D m_editLuaCamera;
	Feintgine::Camera2D m_editLuaCamera_static;

	Feintgine::Camera2D * currentCam = nullptr;

	Feintgine::Window * m_window;

	Feintgine::GUI m_gui;

	Feintgine::SpriteBatch m_spriteBatch;

	Feintgine::GLSLProgram m_editObjectShader;
	Feintgine::GLSLProgram m_spriteListShader;
	Feintgine::GLSLProgram m_previewObjectShader;

	Feintgine::GLSLProgram m_editDamakuShader;
	//Feintgine::GLSLProgram m_sceneShader;


	Feintgine::DebugRender m_debug;

	Feintgine::DebugRender m_editorCrosshair;

	Feintgine::DebugRender m_coliderRenderer;

	// UI component

	CEGUI::Menubar* m_MenuBar;
	
	CEGUI::PopupMenu * File_Popup = nullptr;

	CEGUI::PopupMenu * Edit_Popup = nullptr;
	
	CEGUI::PopupMenu * Object_Popup = nullptr;

	CEGUI::PopupMenu * Animate_Popup = nullptr;

	//Edit Ovbject 
	

	CEGUI::Listbox * m_AObjList = nullptr;

	CEGUI::Listbox * m_actionList = nullptr;
	CEGUI::DefaultWindow * m_actionLabel = nullptr;


	CEGUI::Editbox * object_edit_name = nullptr;
	CEGUI::Combobox * object_combo_type = nullptr;

	CEGUI::Editbox * object_edit_width = nullptr;
	CEGUI::Editbox * object_edit_heigh = nullptr;

	CEGUI::Editbox * color_red_value = nullptr;
	CEGUI::Editbox * color_green_value = nullptr;

	CEGUI::Editbox * color_blue_value = nullptr;
	CEGUI::Editbox * color_alpha_value = nullptr;

	CEGUI::PushButton * object_button_create = nullptr;

	CEGUI::PushButton * object_button_addColider = nullptr;

	CEGUI::Scrollbar  * animation_slide = nullptr;

	CEGUI::PushButton * playAnimation_button = nullptr;

	CEGUI::PushButton * pauseAnimation_button = nullptr;

	CEGUI::PushButton * stopAnimation_button = nullptr;

	CEGUI::ToggleButton * animation_enableLoop_toggle = nullptr;

	CEGUI::ToggleButton * animation_markAsLoop_toggle = nullptr;

	CEGUI::ToggleButton * animation_isSpriteInverted = nullptr;

	CEGUI::DefaultWindow * animation_markAsLoop_label = nullptr;

	CEGUI::DefaultWindow * enableLoop_toggle_label = nullptr;

	CEGUI::DefaultWindow * animation_index_label = nullptr;

	CEGUI::Editbox * animation_tick_textbox = nullptr;

	CEGUI::PushButton * animation_saveAnimation = nullptr;

	CEGUI::PushButton * animation_newAction = nullptr;

	CEGUI::PushButton * animation_deleteAction = nullptr;

	CEGUI::PushButton * animation_addAnim = nullptr;

	CEGUI::PushButton * animation_removeAnim = nullptr;

	CEGUI::PushButton * animation_applySprite = nullptr;

	CEGUI::PushButton * animation_addNewAnimation = nullptr;

	CEGUI::PushButton * animation_deleteAnimation = nullptr;

	CEGUI::DefaultWindow * animation_tick_label = nullptr;

	CEGUI::DefaultWindow * animation_sprite_label = nullptr;

	CEGUI::PushButton * animation_addNewAnimation_sub = nullptr;

	CEGUI::Editbox * animation_addNewAnimation_textBox = nullptr;

	CEGUI::DefaultWindow * animation_addNewAnimation_sub_label = nullptr;

	CEGUI::PushButton * animation_addNewAction_sub = nullptr;

	CEGUI::Editbox * animation_addNewAction_textBox = nullptr;

	CEGUI::DefaultWindow * animation_addNewAction_sub_label = nullptr;

	//CEGUI::Combobox * filter_type = nullptr;

	//CEGUI::Combobox * filter_page = nullptr;

	/*CEGUI::Editbox * filer_name = nullptr;*/


	// Label
	CEGUI::DefaultWindow * listDes = nullptr;
	CEGUI::DefaultWindow * type_label = nullptr;
	CEGUI::DefaultWindow * name_label = nullptr;
	CEGUI::DefaultWindow * width_label = nullptr;
	CEGUI::DefaultWindow * heigh_label = nullptr;
	CEGUI::DefaultWindow * red_label = nullptr;
	CEGUI::DefaultWindow * green_label = nullptr;
	CEGUI::DefaultWindow * blue_label = nullptr;
	CEGUI::DefaultWindow * alpha_label = nullptr;
	//


	// Offset components

	CEGUI::DefaultWindow * animation_anim_offset_label = nullptr;

	CEGUI::Editbox * animation_anim_offset_textbox_x = nullptr;
	CEGUI::Editbox * animation_anim_offset_textbox_y = nullptr;

	CEGUI::PushButton * animation_anim_offset_button_up = nullptr;
	CEGUI::PushButton * animation_anim_offset_button_down = nullptr;
	CEGUI::PushButton * animation_anim_offset_button_left = nullptr;
	CEGUI::PushButton * animation_anim_offset_button_right = nullptr;

	// Layer List

	CEGUI::MultiColumnList *m_layers;
	
	glm::vec4 EditScreen; 
	glm::vec4 SampleSceen;
	glm::vec4 ObjectsScreen;
	glm::vec4 PreviewScreen;
	glm::vec4 SpriteListScreen;
	glm::vec4 AnimateScreen;

	glm::vec4 EditDamaku;

	glm::vec4 EditEnemy;

	glm::vec4 EditLua;

	glm::vec4 SceneScreen;

//	glm::vec4 AnimateScreen;

	// Add Layer Window
	CEGUI::Window * m_addLayerWindow;

	CEGUI::Window * m_newSceneWindow;

	CEGUI::Window * m_selectSceneWindow;

	CEGUI::Window * m_autolayoutWindow;

	CEGUI::Window * animation_newAnimationWindow;

	CEGUI::Window * action_newAnimationWindow;

	CEGUI::Listbox * m_sceneList;


	CEGUI::Editbox * m_layerName;
	CEGUI::Editbox * m_layerDepth;

	CEGUI::Editbox * m_layoutRow;
	CEGUI::Editbox * m_layoutCol;

	CEGUI::PushButton * m_addLayerButton;
	CEGUI::PushButton * m_deleteLayerButton;

	CEGUI::Editbox * scene_edit_name;

	CEGUI::Combobox * m_actionCombo = nullptr;

	
	int m_currentMode = T_EDIT_SCREEN_MODE;

	// Texture components

	SpriteSheet m_currentTexture;

	bool m_move = false;

	//ColiderBox col;

	//
	std::vector <TemplateObject > m_templateList;

	std::vector <TemplateObject > m_filedList;

	std::vector<ColiderBox > m_colider_boxes;

	std::vector<ObjectSlot> m_slots;

	ColiderBox * m_currentCol = nullptr;

	int current_type = 10;
	
	int current_page = 1;

	bool alreadySet = false;

	std::string t_filter_name;

	bool screenLock = false;

	TemplateObject * m_previewObject = nullptr;
	TemplateObject previewObject;

	TemplateObject * m_placeObject = nullptr;
	TemplateObject copy;

	int drawMode = 0;

	//int m_EDITTING_MODE = 0;

	void switchEditingMode(int mode);

	bool showColider = false;

	bool is_ObjectInside = false;

	//Feintgine::Fg_scene * m_scene;

	bool is_hold_CTRL = false;

	bool mouseMove = false;

	bool is_gridMode = false;

	//AnimatedObject m_animatObject;
	Feintgine::F_AnimatedObject m_fAnimatedObject;

	std::vector<Feintgine::F_Sprite> m_sprites;


	SpriteListHolder m_spriteListDisplayer;
	
	EditObject m_buildingObject;

	EditObject fakeObject;

	BuildObjectTool m_buildObjectTool;

	ObjectListHolder m_objectHolder;

	bool CEGUI_interupt = false;

	CEGUI::PushButton * m_addToObject = nullptr;

	EditObject m_selectedObject;
	EditObject * p_selectedObject;
	bool m_objectSelected = false;
	Feintgine::LightBatch m_lightBatch;


	Feintgine::Brush m_brushTest;

	std::vector<Feintgine::Brush> m_brushList;

	//float m_ambientLight = 0.0f;

	glm::vec3 m_ambientLight = glm::vec3(1);

	CEGUI::Editbox * m_ambientColorR;
	CEGUI::Editbox * m_ambientColorG;
	CEGUI::Editbox * m_ambientColorB;

	CEGUI::DefaultWindow * m_ambientColor_label;


	float m_cameraAngle = 0;

	SceneManager m_sceneManager;

	Feintgine::Camera2D m_fullCam;
	SDL_Event evnt;
	CEGUI::PushButton * m_addBrushButton;

	TextRenderer m_textRenderer;

	int objectiveMode = OBJECTIVE_OBJECT;
	int animateCount = 0;

	bool m_markable = false;

	int loopCount = 1;

	bool m_hasSelectAnimation = false;

	Feintgine::F_TileSet m_tileset;

	PaternEditor m_paternEditor;

	EmptyObject bg;


	Feintgine::F_TileStack m_tileStack;
	Feintgine::F_TileManager m_tileManager;

	bool m_isAnimationPlaying = false;

	bool debugTiles = true;
	void toggetDebugTiles();
	//B_Object m_selectObject = nullptr;

	// Edit Enemy Mode here
	EnemyEditorComponent m_enemyEditor;

	LuaObjectEditorComponent m_luaEditor;
	Feintgine::AudioEngine m_audioEngine;
	KanjiEffectManager m_kanjiEffectManager;
	Feintgine::EffectBatch m_effectBatch;

	bool m_isLoaded = false;

};

