#pragma once
#include "F_CollectableItem.h"
class PowerItem : public F_CollectableItem
{
public:
	PowerItem();
	~PowerItem();

	

	virtual void onCollected(F_Player * player) override;

private:

	


};

