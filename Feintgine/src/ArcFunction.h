#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
class ArcFunction
{
public:
	ArcFunction();
	~ArcFunction();
	
	virtual glm::vec2 getValue(float t) = 0;

	size_t getFactorCount() {
		return m_factors.size();
	}
	void init(float rad,std::vector<float> factors);
protected:
	std::vector<float> m_factors;
	unsigned int factorsCount;
	float m_rad;

	float m_t;

};

