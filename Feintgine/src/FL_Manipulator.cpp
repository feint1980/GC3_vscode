#include "FL_Manipulator.h"


namespace Feintgine
{

    FL_Manipulator::FL_Manipulator()
    {
    }

    FL_Manipulator::~FL_Manipulator()
    {
    }

    void FL_Manipulator::init(std::vector <FL_Object*> * mainList)
    {
        m_mainList = mainList;
    }

    void FL_Manipulator::manipulateObject(unsigned int ID, std::function<void(float)> func,float duration, float delayTime)
	{
		for(size_t t = 0; t < m_mainList->size(); t++)
		{
			if(m_mainList->at(t)->getID() == ID)
			{
                m_mainList->at(t)->setManipulatedFunc(func,duration,delayTime);
				//m_objects.push_back(std::move(m_mainList->at(t)));
                //m_objects.back()->setManipulatedFunc(func,duration,delayTime);
			}
		}
	
	}

}