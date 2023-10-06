#pragma once
#include "ArcFunction.h"
class ArcFunction_Epicycloid : public ArcFunction
{
public:
	ArcFunction_Epicycloid();
	~ArcFunction_Epicycloid();


	virtual glm::vec2 getValue(float t) override;

	int getFactorCount() const { return factorsCount; }

private:
	
};

