#pragma once
#include <F_Sprite.h>
#include <SpriteManager.h>
#include <SpritePacket.h>
#include <GUI.h>
#include <glm/glm.hpp>
#include <string>
#include "ObjectDisplayer.h"
#include <functional>
#include <SpriteFont.h>
#include <feint_common.h>
#include "DisplaySample.h"
#include <InputManager.h>
#include "EventManager.h"
#include <dirent.h>
#include "EditObject.h"

class ObjectListHolder
{
public:
	ObjectListHolder();
	~ObjectListHolder();

	void init(glm::vec2 pos, glm::vec2 dim, int col, int row, Feintgine::GUI *gui);

	void draw(Feintgine::SpriteBatch & spriteBatch);
	void drawBorder(Feintgine::DebugRender & renderer);

	void update(glm::vec2 mousePos);

	void setPage(int page);

	void show();
	void hide();

	bool eventFilterNameTextChanged(const CEGUI::EventArgs &e);

	bool nextPage(const CEGUI::EventArgs &e);
	bool prevPage(const CEGUI::EventArgs &e);

	void clearTotalList();
	void clearFilterList();
	void clearObjectList();

	void loadList();
	bool checkInside(glm::vec2 mousePos);



	void handleInput(Feintgine::InputManager & inputManager, glm::vec2 mousePos);


	void filterList(const std::string & keyword);
	void updateList(bool needUpdatePage = false);

	void clearCurrentObject();

	void setClickSpriteEvent(std::function<bool()> setOnClick);

	void setClickObjectEvent(std::function<bool()> setOnClick);

	void setOnCancelObject(std::function<bool()> setCallback);


	EditObject * getDisplaySample() const { return m_displaySample; }
	EditObject  getNonConstDisplaySample() {
		if (m_displaySample)
		{
			return *m_displaySample;
		}
		return EditObject();
	}

private:

	int listdir(const char * name, int level);

	bool m_isInited = false;
	Feintgine::GUI *m_gui = nullptr;

	glm::vec2 m_pos;
	glm::vec2 m_dim;
	std::vector <ObjectDisplayer> m_objects;
	int m_col;
	int m_row;
	int m_currentPage = 0;
	int m_maxPageSize = 0;
	int totalSize;
 	std::vector<EditObject> m_fullObjectList;
// 	std::vector<SpriteProperty> m_sizeList;
 	std::vector<EditObject> m_filteredList;


	std::function<bool()> m_selectSpriteCallback;
	std::function<bool()> m_selectObjectCallback;
	std::function<bool()> m_onCancelObjectCallback;

	CEGUI::Combobox * filter_page = nullptr;
	CEGUI::DefaultWindow * page_label = nullptr;

// 	CEGUI::Combobox * filer_packet = nullptr;
// 	CEGUI::DefaultWindow * packet_label = nullptr;

	CEGUI::DefaultWindow * filter_label = nullptr;
	CEGUI::Editbox * filter_name = nullptr;


	CEGUI::PushButton * m_nextPage = nullptr;
	CEGUI::PushButton * m_prevPage = nullptr;

	//CEGUI::DefaultWindow * sprite_name_label = nullptr;

	//CEGUI::Font m_font;



	float showTime = 2.0f;
	float startTime = 0;
	glm::vec2 tooltipOffset = glm::vec2(-10, -25);

	EditObject * m_displaySample = nullptr;
	
	int packetId = 1;


};

