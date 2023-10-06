#include "ScoreItem.h"
#include "F_Player.h"


ScoreItem::ScoreItem()
{
}


ScoreItem::~ScoreItem()
{
}

void ScoreItem::onCollected(F_Player * player)
{
	player->addScore(100);
}
