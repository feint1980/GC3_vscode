#pragma once
#include "ArcFunction.h"

class ArcFunction_feint_custom1 : public ArcFunction
{
public:
	ArcFunction_feint_custom1();
	~ArcFunction_feint_custom1();

	virtual glm::vec2 getValue(float t) override;

	int getFactorCount() const { return factorsCount; }
};

