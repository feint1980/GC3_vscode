
#include "F_BaseObjectManipulator.h"
#include "F_Lua_Boss_Manager.h"


F_BaseObjectManipulator::F_BaseObjectManipulator()
{
    //ctor
}
F_BaseObjectManipulator::~F_BaseObjectManipulator()
{
    //dtor
}

void F_BaseObjectManipulator::draw(Feintgine::SpriteBatch & spriteBatch)
{
    for (size_t i = 0; i < m_objects.size(); i++)
    {
        m_objects[i].object->draw(spriteBatch);
    }
}

void F_BaseObjectManipulator::update(float deltaTime)
{
    for (size_t i = 0; i < m_objects.size(); i++)
    {
        m_objects[i].object->update(deltaTime);
    }
}



int lua_CreateHelperR(lua_State * L)
{
  	if(lua_gettop(L) != 16)
	{
		std::cout << "bad gettop " << lua_gettop(L) << " \n";
		return -1;
	}
	std::cout << "lua create helper called \n";
	F_Lua_Boss_Manager * objectManager = static_cast<F_Lua_Boss_Manager*>(lua_touserdata(L, 1)); //host
	F_Lua_Boss * dynamicObject = static_cast<F_Lua_Boss*>(lua_touserdata(L, 2)); // dynob
	unsigned int id = lua_tonumber(L, 3); //
	std::string objectName = lua_tostring(L, 4); //
	std::string asset = lua_tostring(L, 5); //
	float x = lua_tonumber(L, 6); //
	float y = lua_tonumber(L, 7); //
	float scaleX = lua_tonumber(L, 8); //
	float scaleY = lua_tonumber(L, 9); //
	float depth = lua_tonumber(L, 10); //
	float velX = lua_tonumber(L, 11); //
	float velY = lua_tonumber(L, 12); //
	int afterImageCount = lua_tonumber(L, 13); //
	float afterImageRate = lua_tonumber(L, 14); //
	float scaleRate = lua_tonumber(L, 15); //
	double time = lua_tonumber(L, 16); //

	objectManager->createHelper(dynamicObject,id, objectName, asset, x, y, scaleX, scaleY, depth, velX, velY, afterImageCount, afterImageRate,scaleRate, time);
	
	return 0 ;

}



void F_BaseObjectManipulator::init(lua_State * script,std::vector<Feintgine::F_BaseObject*> * mainObjectList)
{
    m_script = script;
    m_mainObjectList = mainObjectList;

    // lua register 
    lua_register(m_script, "cppCreateHelperR", lua_CreateHelperR);

}

void F_BaseObjectManipulator::moveObjectsAsFomula(unsigned int objectsID, float lifeTime, unsigned int formulaID)
{
    for (size_t i = 0; i < m_mainObjectList->size(); i++)
    {
        if (m_mainObjectList->at(i)->getID() == objectsID)
        {
            F_ManipulatedObject temp;
            temp.object = m_mainObjectList->at(i);
            temp.isAssigned = true;
            temp.m_lifeTime = lifeTime;
            m_mainObjectList->erase(m_mainObjectList->begin() + i);

            m_objects.push_back(temp);
        }
    }
}



