#pragma once
#include "ArcFunction.h"
#include <iostream>
class ArcFunction_hypocycloid : public ArcFunction
{
public:
	ArcFunction_hypocycloid();
	~ArcFunction_hypocycloid();

	virtual glm::vec2 getValue(float t) override;

	int getFactorCount() const { return factorsCount; }
private:

};

