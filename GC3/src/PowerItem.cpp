#include "PowerItem.h"
#include "F_Player.h"


PowerItem::PowerItem()
{
}


PowerItem::~PowerItem()
{
}


void PowerItem::onCollected(F_Player * player)
{
	player->addPower(m_powerValue);
}
