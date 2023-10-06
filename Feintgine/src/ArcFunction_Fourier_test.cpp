#include "ArcFunction_Fourier_test.h"



ArcFunction_Fourier_test::ArcFunction_Fourier_test()
{
}


ArcFunction_Fourier_test::~ArcFunction_Fourier_test()
{
}

glm::vec2 ArcFunction_Fourier_test::getValue(float t)
{
	glm::vec2 returnVal;
	float a = 4.0f;
	int n = 1;
	float b = 7.0f;
	
	                                                                               
	returnVal.x = cos(t ) * m_rad;
	returnVal.y = sin(t)* m_rad ;// fourierSigma(a, b, n, 15, returnVal.x, 0);


	return returnVal;
}

float ArcFunction_Fourier_test::fourierSigma(float a, float b, int n, int l,float x,float total)
{
	if (n < l)
	{
		/*total = a * n * cos(x) + b * n * sin(x);*/
		total += (4 * sin(n * x) / T_PI);
		return total + fourierSigma(a, b, n + 2, l, x, total);

	}
	else
	{
		//std::cout << "final return \n";
		return total;
	}

	//std::cout << "return false\n";
	return -999;

}
