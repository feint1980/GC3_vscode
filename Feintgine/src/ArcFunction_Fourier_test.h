#pragma once
#include "ArcFunction.h"
#include <iostream>
#define T_PI 3.14159f

class ArcFunction_Fourier_test : public ArcFunction
{
public:
	ArcFunction_Fourier_test();
	~ArcFunction_Fourier_test();

	virtual glm::vec2 getValue(float t) override;


	float fourierSigma(float a, float b,int n, int l,float x,float total);

	int getFactorCount() const { return factorsCount; }

};

