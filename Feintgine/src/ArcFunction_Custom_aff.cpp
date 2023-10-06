#include "ArcFunction_Custom_aff.h"



ArcFunction_Custom_aff::ArcFunction_Custom_aff()
{
	factorsCount = 22;
}


ArcFunction_Custom_aff::~ArcFunction_Custom_aff()
{

}

glm::vec2 ArcFunction_Custom_aff::getValue(float t)
{
	glm::vec2 returnVal;

	if (m_factors.size() < factorsCount)
	{
		std::cout << "Warning, incorrect expected factors \n";
		return returnVal;
	}

	// spriral algorithm

	/*		List of variable 
		0  / c 
		01 / n
		02 / nn
		03 / n2
		04 / t1 
		05 / t2 -> ( n2 * t1 )
		06 / t3 = t2 
		07 / ap -> ( 17/ n2 )
		08 / l1 
		09 / l2
		10 / tm 
		11 / tm2 
		12 / origincosin
		13 / s1
		14 / s2 
		15 / s3 
		16 / s32
		17 / acc1
		18 / acc2
		19 / acc3
		20 / angle rand(0,360)
		21 / posneg
		ObjMove_GetX(objBoss) + cosin * cos(angle) 
		ObjMove_GetY(objBoss) + cosin * sin(angle)

	*/

	float angle = 0.0f;
	float originalcosin = 0.0f;

	//returnVal.x = originalcosin * cos()




	return returnVal;
}
