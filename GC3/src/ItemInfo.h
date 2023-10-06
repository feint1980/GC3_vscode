#pragma once
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <glm/glm.hpp>
#include <string>
#include <GUI.h>
class ItemInfo
{
public:
	ItemInfo();
	~ItemInfo();
	void init(Feintgine::GUI & gui);
	void setup(std::string name, std::string des, const glm::vec2 & pos);
	private:
		CEGUI::GroupBox * border = nullptr;
		CEGUI::DefaultWindow * bg = nullptr;
		CEGUI::DefaultWindow * item_name = nullptr;
		CEGUI::MultiLineEditbox * item_des = nullptr;



};

