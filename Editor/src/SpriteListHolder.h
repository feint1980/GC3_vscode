#pragma once
#include <F_Sprite.h>
#include <SpriteManager.h>
#include <SpritePacket.h>
#include <GUI.h>
#include <glm/glm.hpp>
#include <string>
#include "SpriteDisplayer.h"
#include <functional>
#include <SpriteFont.h>
#include <feint_common.h>
#include "DisplaySample.h"
#include <InputManager.h>
#include "EventManager.h"
#include <unordered_map>
#include <map>

class SpriteListHolder
{
public:
	SpriteListHolder();
	~SpriteListHolder();

	void init(glm::vec2 pos, glm::vec2 dim, int col, int row,Feintgine::GUI *gui );

	void draw(Feintgine::SpriteBatch & spriteBatch);
	void drawBorder(Feintgine::DebugRender & renderer);

	void update(glm::vec2 mousePos);

	void setPage(int page);

	void show();
	void hide();

	bool packetFilterChanged(const CEGUI::EventArgs &e);
	bool pageValueChangedClick(const CEGUI::EventArgs &e);
	bool pageValueChangeText(const CEGUI::EventArgs &e);
	bool eventFilterNameTextChanged(const CEGUI::EventArgs &e);

	bool nextPage(const CEGUI::EventArgs &e);
	bool prevPage(const CEGUI::EventArgs &e);

	void clearTotalList();
	void clearFilterList();
	void clearSpriteList();
	
	void loadList();
	bool checkInside(glm::vec2 mousePos);

	bool resetColor(const CEGUI::EventArgs &e);
	
	bool updateColor(const CEGUI::EventArgs &e);

	void resetTheColor();

	void handleInput(Feintgine::InputManager & inputManager , glm::vec2 mousePos);

	void updatePacket();
	void filterList(const std::string & keyword);
	void updateList(bool needUpdatePage = false);

	void setClickSpriteEvent(std::function<bool()> setOnClick);

	void initGUI();

	DisplaySample * getDisplaySample() const { return m_displaySample; }

private :

	Feintgine::GUI *m_gui = nullptr;

	glm::vec2 m_pos;
	glm::vec2 m_dim;
	std::vector <SpriteDisplayer> m_spriteList;
	int m_col;
	int m_row;
	int m_currentPage = 0;
	int m_maxPageSize = 0;
	int totalSize;
	std::vector<SpriteProperty> m_fullSpriteList;
	std::vector<SpriteProperty> m_sizeList;
	std::vector<SpriteProperty> m_filteredList;


	std::function<bool()> m_selectSpriteCallback;

	CEGUI::Combobox * filter_page = nullptr;
	CEGUI::DefaultWindow * page_label = nullptr;

	CEGUI::Combobox * filer_packet = nullptr;
	CEGUI::DefaultWindow * packet_label = nullptr;

	CEGUI::DefaultWindow * filter_label = nullptr; 
	CEGUI::Editbox * filter_name = nullptr;


	CEGUI::PushButton * m_nextPage = nullptr;
	CEGUI::PushButton * m_prevPage = nullptr;

	CEGUI::DefaultWindow * sprite_name_label = nullptr;

	//CEGUI::Font m_font;

	

	float showTime = 2.0f;
	float startTime = 0;
	glm::vec2 tooltipOffset = glm::vec2(-10, -25);

	DisplaySample * m_displaySample = nullptr;

	int packetId = 1;


	CEGUI::DefaultWindow * name_label = nullptr;
	CEGUI::DefaultWindow * type_label = nullptr;
	CEGUI::DefaultWindow * width_label = nullptr;
	CEGUI::DefaultWindow * heigh_label = nullptr;



	CEGUI::PushButton * object_button_create = nullptr;
	CEGUI::PushButton * object_resetColor = nullptr;


};

