#pragma once
#include "EditObject.h"
#include <GUI.h>
#include <DebugRender.h>
#include <feint_common.h>
#include <InputManager.h>
#include <Camera2D.h>
#include <iomanip> 
#include <EmptyObject.h>
#include <iomanip> // setprecision
#include <sstream> // stringstream
class BuildObjectTool
{
public:
	BuildObjectTool();
	~BuildObjectTool();

	void init(EditObject *object, Feintgine::GUI* gui, Feintgine::Camera2D * camera);

	void loadObject(EditObject *object);

	void addSpriteToObject(Feintgine::F_Sprite t_sprite, glm::vec2 t_posOffset, glm::vec2 t_scaleOffset, Feintgine::Color t_color, float offsetAngle, float t_depth);

	void drawBoxes(Feintgine::DebugRender & renderer);

	void drawShadowing(Feintgine::SpriteBatch & spriteBatch);

	EditObject * getObject() { return m_object; }

	void handleInput(Feintgine::InputManager & inputManger);

	void selectASprite();
	void update();

	void removeSpriteInList(int ID);
	void removeColiderInList();

	bool onSpriteListDoubleClick(const CEGUI::EventArgs & e);
	bool onLightLiseDoubleClick(const CEGUI::EventArgs &e);
	bool onColiderLiseDoubleClick(const CEGUI::EventArgs &e);

	bool addLightToObject(const CEGUI::EventArgs &e);

	bool onPositionOffsetChanged(const CEGUI::EventArgs &e);

	bool onScaleOffsetChanged(const CEGUI::EventArgs &e);

	bool onColorValueChanged(const CEGUI::EventArgs &e);

	bool onLightAttenuationValueChanged(const CEGUI::EventArgs &e);

	bool onLightPosValueChanged(const CEGUI::EventArgs &e);

	bool onLightColorValueChanged(const CEGUI::EventArgs &e);

	bool onAmbientLightValueChanged(const CEGUI::EventArgs &e);

	bool onDepthValueChanged(const CEGUI::EventArgs &e);

	bool onAddColiderClick(const CEGUI::EventArgs &e);

	bool onColiderDimValueChanged(const CEGUI::EventArgs &e);

	bool onAngleValueChanged(const CEGUI::EventArgs &e);

	bool onSaveObjectClicked(const CEGUI::EventArgs &e);

	bool onColiderToggleBoxClicked(const CEGUI::EventArgs &e);

	bool onSpriteInvertToggleBoxClicked(const CEGUI::EventArgs &e);
	
	void initTools();

	int getValidSpriteID();

	int getValidLightID();

	int getValidColiderID();

	bool checkInsideLight(glm::vec2 mousePos);

	void toggleShowColider();

	bool isShowColider()const {  return m_showColider; }

	void removeSelectedLightInList();

	float getAmbientLight() const { return m_ambLight; }
	void show();
	void hide();

	bool checkInside(glm::vec2 mousePos);

	Feintgine::F_Sprite getSelectedSprite() const { return m_selectedSprite->sprite; }
	

private :
	EditObject * m_object;

	glm::vec2 m_pos;
	glm::vec2 m_currentDim;
	glm::vec2 m_dim;

	bool m_showColider = true;

	Feintgine::GUI * m_gui;

	CEGUI::MultiColumnList * m_spriteList = nullptr;

	CEGUI::Listbox * m_lightList = nullptr;

	CEGUI::DefaultWindow * m_coliderList_label = nullptr;
	CEGUI::Listbox * m_coliderList = nullptr;

	Feintgine::SelfSprite * m_selectedSprite = nullptr;


	CEGUI::DefaultWindow * m_showColiderButton_label = nullptr;
	CEGUI::ToggleButton * m_showColiderButton = nullptr;

	CEGUI::ToggleButton * m_isSpriteInverted = nullptr;

	CEGUI::DefaultWindow * m_spriteListDesc_label = nullptr;
	CEGUI::DefaultWindow * m_offsetScale_label = nullptr;
	CEGUI::DefaultWindow * m_offsetPos_label = nullptr;
	CEGUI::DefaultWindow * m_colorRGBA_label = nullptr;

	CEGUI::DefaultWindow * m_objectName_label = nullptr;
	CEGUI::Editbox * m_objectName = nullptr;


 	CEGUI::DefaultWindow * m_coliderDim_label = nullptr;
 	CEGUI::Editbox * m_coliderDim_X = nullptr;
 	CEGUI::Editbox * m_coliderDim_Y = nullptr;

	CEGUI::Editbox * m_offsetWidthScale = nullptr;
	CEGUI::Editbox * m_offsetHeightScale = nullptr;
	CEGUI::Editbox * m_offsetPos_X = nullptr;
	CEGUI::Editbox * m_offsetPos_Y = nullptr;
	CEGUI::Editbox * m_ownColor_r = nullptr;
	CEGUI::Editbox * m_ownColor_g = nullptr;
	CEGUI::Editbox * m_ownColor_b = nullptr;
	CEGUI::Editbox * m_ownColor_a = nullptr;

	CEGUI::DefaultWindow * m_lightListDesc_label = nullptr;
	CEGUI::DefaultWindow * m_lightAttenuation_label = nullptr;
	CEGUI::DefaultWindow * m_lightPos_label = nullptr;
	CEGUI::DefaultWindow * m_lightcolorRGBA_label = nullptr;
	CEGUI::DefaultWindow * m_dephValue_label = nullptr;
	CEGUI::DefaultWindow * m_angleValue_label = nullptr;

	CEGUI::DefaultWindow * m_ambientLight_label = nullptr;
	CEGUI::Editbox * m_ambientLight = nullptr;

	CEGUI::Editbox * m_lightPos_X = nullptr;
	CEGUI::Editbox * m_lightPos_Y = nullptr;
	CEGUI::Editbox * m_lightAtten_X = nullptr;
	CEGUI::Editbox * m_lightAtten_Y = nullptr;
	CEGUI::Editbox * m_lightAtten_Z = nullptr;
	CEGUI::Editbox * m_lightColor_r = nullptr;
	CEGUI::Editbox * m_lightColor_g = nullptr;
	CEGUI::Editbox * m_lightColor_b = nullptr;
	CEGUI::Editbox * m_lightColor_a = nullptr;
	CEGUI::Editbox * m_dephValue = nullptr;
	CEGUI::Editbox * m_angleValue = nullptr;

	CEGUI::PushButton * m_addLightButton = nullptr;
	CEGUI::PushButton * m_addColiderButton = nullptr;
	CEGUI::PushButton * m_saveObjetButton = nullptr;

	bool isDrag = false;
	glm::vec2 mouseOffset;
	Feintgine::Camera2D * m_camera;

	int spriteID_count = 1;
	int lightID_count = 1;
	int coliderID_count = 1;

	int saved_SelectedID;

	int propertyDisableCounter = 1;
	int lightPropertyDisableCounter = 1;
	int coliderPropertyDisableCounter = 1;

	float m_ambLight = 0.0f;

	int currentLightIndex = -1;
	int currentColiderIndex = -1;
	EmptyObject bg;

	glm::vec2 object_screen_offset = glm::vec2(165, 175);

};

