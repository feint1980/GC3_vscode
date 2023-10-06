#pragma once
#include "SimpleObject.h"
class TownTile : public SimpleObject
{

public:
	TownTile();
	~TownTile();

	void setTile(int index);
	void update() override;
	void destroy() override;
	bool touchable;
	bool interactable = false;
	
private: 
	
};

