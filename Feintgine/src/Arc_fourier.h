#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "feint_common.h"


struct complexNumber {
	float real;
	float imaginary;

	complexNumber()
	{
		real = 0;
		imaginary = 0;
	}
	complexNumber(float t_real, float t_img)
	{
		real = t_real;
		imaginary = t_img;
	}

	void set(float t_real, float t_img)
	{
		real = t_real;
		imaginary = t_img;
	}

	void get(float & t_real, float & t_img)
	{
		t_real = real;
		t_img = imaginary;
	}

	complexNumber operator + (complexNumber const & complexNum)
	{
		complexNumber returnVal;
		returnVal.real = real + complexNum.real;
		returnVal.imaginary = imaginary + complexNum.imaginary;
		return returnVal;
	}
	complexNumber operator * (complexNumber const & complexNum)
	{
		complexNumber returnVal;
		returnVal.real = real * complexNum.real - imaginary * complexNum.imaginary;
		returnVal.imaginary = imaginary * complexNum.imaginary + imaginary * complexNum.real;
		return returnVal;
	}
	

};

struct fourierData
{

	fourierData(complexNumber t_complex, float t_freq, float t_amp, float t_phase)
	{
		complexNum = t_complex;
		freq = t_freq;
		amplification = t_amp;
		phase = t_phase;
	}

	complexNumber complexNum;
	float freq;
	float amplification;
	float phase;
	

};

class Arc_fourier
{
public:
	Arc_fourier();
	~Arc_fourier();

	void init();

	void calculateFourier();

	void finalizeFourier();

	void loadData(const std::string & filePath);

	void update(float deltaTime);

	glm::vec2 getPos() const { return m_finalPos; }

private:
	std::vector<complexNumber> m_datas;
	std::vector<fourierData> m_fouriers;
	std::vector<glm::vec2> m_finalData;
	int circleNum;
	float m_time;
	float m_rotation;
	glm::vec2 m_finalPos;

	float t_i;
	int i;
};

