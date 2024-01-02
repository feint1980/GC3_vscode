#pragma once
#include "F_DamakuBase.h"
#include <GUI.h>
#include <SpriteManager.h>
#include <SpriteBatch.h>
#include <InputManager.h>
#include "SpriteListHolder.h"
#include <F_oEvent.h>

struct ParamWidget
{
	ParamWidget(CEGUI::Editbox * t_editBox, CEGUI::DefaultWindow * t_editLabel)
	{
		editBox = t_editBox;
		editLabel = t_editLabel;
	}

	CEGUI::Editbox * editBox;
	CEGUI::DefaultWindow * editLabel;

};

class PaternEditor
{
public:
	PaternEditor();
	~PaternEditor();


	void init(Feintgine::GUI * gui,SpriteListHolder * spriteholder);

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void update(float deltaTime);

	void handleInput(Feintgine::InputManager & inputManager/*, SDL_Event & evnt*/);

	void show(bool value);

	void togglePlay();

	bool applySpriteToDamaku(const CEGUI::EventArgs &e);

	bool onComboValueChanged(const CEGUI::EventArgs &e);

	bool onParamChanged(const CEGUI::EventArgs &e);

	bool onTotalNumberChange(const CEGUI::EventArgs &e);

	bool onTraceValueChange(const CEGUI::EventArgs &e);

	void setSpriteHolder(SpriteListHolder * holder);

	bool onDestinationToggle(const CEGUI::EventArgs &e);

	void resetParams();


private : 
	F_DamakuBase m_damakuTest;
	
	std::vector<F_DamakuBase> m_damakuTests;

	Feintgine::GUI * m_gui;
	bool m_isPlay = false;

	int totalDamakuClone = 10;

	CEGUI::Combobox* patern_combolist = nullptr;
	CEGUI::PushButton * damaku_applySprite = nullptr;

	CEGUI::MultiColumnList * m_paternList = nullptr;

	CEGUI::Editbox * patern_factor_a = nullptr;
	CEGUI::Editbox * patern_factor_b = nullptr;
	CEGUI::Editbox * patern_factor_c = nullptr;
	CEGUI::Editbox * patern_factor_d = nullptr;
	CEGUI::Editbox * patern_factor_r = nullptr;

	// maximum 4 value can be modified

	CEGUI::Editbox * patern_totalClone = nullptr;

	CEGUI::Editbox * patern_traceTime = nullptr;

	CEGUI::ToggleButton * patern_destination_mode = nullptr;


	CEGUI::DefaultWindow * patern_factor_a_label = nullptr;
	CEGUI::DefaultWindow * patern_factor_b_label = nullptr;
	CEGUI::DefaultWindow * patern_factor_c_label = nullptr;
	CEGUI::DefaultWindow * patern_factor_d_label = nullptr;
	CEGUI::DefaultWindow * patern_factor_r_label = nullptr;

	CEGUI::DefaultWindow * patern_totalClone_label = nullptr;

	CEGUI::DefaultWindow * patern_destination_mode_label = nullptr;

	CEGUI::DefaultWindow * patern_traceTime_label = nullptr;

	std::vector<ParamWidget> m_widgetFactors;

	SpriteListHolder * m_spriteListHolder;
};

