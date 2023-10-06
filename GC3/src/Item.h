#pragma once
#include <string>
#include <SpriteBatch.h>
#include <TileSheet.h>
#include <ResourceManager.h>
#include <vector>
#include "DataManager.h"
#include <SpriteFont.h>

class Item
{
public:
	Item();
	~Item();
	Item(glm::vec2 & pos, glm::vec2 & dim, std::string & id);
	void init(glm::vec2 & pos, glm::vec2 & dim, std::string & id);
	void draw(Feintgine::SpriteBatch & spriteBatch);
	void setPos(glm::vec2 & newPos);
	bool update(glm::vec2 & mousePos);
	std::string getName() const{ return m_name; }
	std::string getDes() const{ return m_desciption; }
	glm::vec2 getPos() const { return m_pos; }
	std::string getID() const { return m_id; }
	
private:
	glm::vec2 m_pos;
	glm::vec2 m_dim;
	Feintgine::TileSheet m_texture;
	int tileIndex;
	std::string m_id;
	std::string m_desciption;
	std::string m_name;
	bool m_type;
	Feintgine::Color white = Feintgine::Color(255, 255, 255, 255);
	Feintgine::Color red = Feintgine::Color(255, 0, 0, 255);
	std::vector<std::string> m_item_data;
	int m_num;
	std::vector<std::string> m_item_num;

	Feintgine::SpriteFont * item_num;
	char * num_buffer;
	
};

