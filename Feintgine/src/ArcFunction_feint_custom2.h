#pragma once
#include "ArcFunction.h"

class ArcFunction_feint_custom2 : public ArcFunction
{
public:
	ArcFunction_feint_custom2();
	~ArcFunction_feint_custom2();

	virtual glm::vec2 getValue(float t) override;

	int getFactorCount() const { return factorsCount; }
};

