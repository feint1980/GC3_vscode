#include "ItemInfo.h"


ItemInfo::ItemInfo()
{
}


ItemInfo::~ItemInfo()
{
}

void ItemInfo::init(Feintgine::GUI & gui)
{

	border = static_cast<CEGUI::GroupBox*>(gui.createWidget("TaharezLook/GroupBox", glm::vec4(-1,-1,0.25,0.5), glm::vec4(0.0f), "item_info"));
 	item_name = static_cast<CEGUI::DefaultWindow*>(gui.createWidget("TaharezLook/Label", glm::vec4(0.05f, 0, 0.8, 0.2f), glm::vec4(0.0f), "item_name"));
	item_name->setProperty("HorzFormatting", "LeftAligned");
 	item_des = static_cast<CEGUI::MultiLineEditbox*>(gui.createWidget("TaharezLook/MultiLineEditbox", glm::vec4(0.05f, 0.2f, 0.9, 0.75f), glm::vec4(0.0f), "item_des"));
	item_des->setReadOnly(true);
	item_name->setText("name here");
	item_des->setText("des here");
 	bg = static_cast<CEGUI::DefaultWindow*>(gui.createWidget("TaharezLook/StaticImage", glm::vec4(0, 0, 1, 1), glm::vec4(0), "item_bg_border"));
 	border->addChild(bg);
	border->addChild(item_des);
	border->addChild(item_name);

	CEGUI::Colour green = CEGUI::Colour(0.0f, 1.0f, 0.15f, 1.0f);

	item_name->setProperty("NormalTextColour", ::CEGUI::PropertyHelper<::CEGUI::Colour>::toString(green));
}

void ItemInfo::setup(std::string name, std::string des,const glm::vec2 & pos)
{
	item_name->setText(name);
	item_des->setText(des);
	border->setXPosition(CEGUI::UDim(pos.x,0));
	border->setYPosition(CEGUI::UDim(pos.y, 0));
}
