#ifndef FL_MANIPULATOR_H
#define FL_MANIPULATOR_H

#include "FL_Object.h"

namespace Feintgine
{

class FL_Manipulator
{
public:
	FL_Manipulator();

	~FL_Manipulator();

	virtual void update(float deltaTime) = 0;

	void init(std::vector <FL_Object*> * mainList);
	
	void manipulateObject(unsigned int ID, std::function<void(float)> func, float duration, float delayTime = 0.0f); 
	

protected:
	std::vector <FL_Object*> * m_mainList;
	//std::vector <FL_Object*> m_objects;

};
}
#endif