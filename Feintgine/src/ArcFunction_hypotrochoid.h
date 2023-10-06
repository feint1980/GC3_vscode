#pragma once
#include "ArcFunction.h"
#include <iostream>

class ArcFunction_hypotrochoid : public ArcFunction
{
public:
	ArcFunction_hypotrochoid();
	~ArcFunction_hypotrochoid();

	virtual glm::vec2 getValue(float t) override;

	int getFactorCount() const { return factorsCount; }

private :

};

