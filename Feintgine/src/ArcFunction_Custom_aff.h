#pragma once
#include "ArcFunction.h"
#include <iostream>

class ArcFunction_Custom_aff : public ArcFunction
{
public:
	ArcFunction_Custom_aff();
	~ArcFunction_Custom_aff();

	virtual glm::vec2 getValue(float t) override;
	int getFactorCount() const 
	{
		return factorsCount;
	}

};

