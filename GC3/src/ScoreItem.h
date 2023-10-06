#pragma once
#include "F_CollectableItem.h"


class ScoreItem : public F_CollectableItem
{
public:
	ScoreItem();
	~ScoreItem();

	virtual void onCollected(F_Player * player) override;

};

