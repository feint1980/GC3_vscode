// #pragma once
// #include <glm/glm.hpp>
// #include <SpriteBatch.h>
// #include "ItemSlot.h"
// #include <vector>

// #include <SpriteFont.h>
// #include <map>
// #include <GUI.h>
// #include "ItemInfo.h"
// #include <InputManager.h>
// #include "QuickSlot.h"
// #include <memory>
// #include "DataManager.h"
// using namespace std;

// class Iventory 
// {
// public:
// 	Iventory();
// 	~Iventory();
// 	void init(glm::vec2 & pos , glm::vec2 & dim , glm::vec2 slot_dims , Feintgine::GUI & gui);
// 	void draw(Feintgine::SpriteBatch & spriteBatch);
// 	bool show = false;
// 	void setPos(glm::vec2 & pos);
// 	void clear();
// 	void update(Feintgine::InputManager & inputManager ,QuickSlot &q );
// 	glm::vec2 getPos() const { return m_pos; }
// 	bool draging = false;
// 	void dragItem();
// 	void refreshItem();

// 	int getFirstFreeSlot();
// private:

// 	glm::vec2 m_mousePos = glm::vec2(0);
// 	glm::vec2 m_mouseWorldPos = glm::vec2(0);



// 	glm::vec2 m_pos;
// 	glm::vec2 m_dims;
// 	glm::vec2 m_slotDim;
// 	Feintgine::GLTexture m_texture;
// 	Feintgine::Color m_color;
// 	std::vector<ItemSlot> m_slots;
// 	std::vector<std::string> itemList;
// 	char * mon_buffer;
// 	Feintgine::SpriteFont * m_mon;
// 	vector<string> item_id;
// 	vector<string> item_pos;

// 	Item * dragingItem = nullptr;
// 	glm::vec2 returnPos;
	
// 	ItemInfo item_info;
	

	
// };

