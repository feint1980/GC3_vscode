#pragma once

#include "Extra_DemoScreen.h"

class ReplayScreen : public Extra_DemoScreen
{
public:
	ReplayScreen();
	~ReplayScreen();
	ReplayScreen(Feintgine::Window * window);

	void reloadLevel() override;

	virtual int getNextScreenIndex() const override;

private:

};

