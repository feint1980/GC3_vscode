// #ifndef F_BASEOBJECTMANIPULATOR_H
// #define F_BASEOBJECTMANIPULATOR_H



// #include "F_BaseObject.h"
// class F_Lua_Boss_Manager;


// struct F_ManipulatedObject
// {
// 	Feintgine::F_BaseObject * object;
// 	bool isAssigned = false;
// 	float m_lifeTime = 0.0f;
// };

// class F_BaseObjectManipulator
// {
// public:
// F_BaseObjectManipulator();

// ~F_BaseObjectManipulator();

// void init(lua_State * script,std::vector<Feintgine::F_BaseObject*> * mainObjectList);

// void assignObject(Feintgine::F_BaseObject * object);

// void draw(Feintgine::SpriteBatch & spriteBatch);

// void update(float deltaTime);

// void moveObjectsAsFomula(unsigned int objectsID, float lifeTime, unsigned int formulaID);

// private : 

// std::vector<Feintgine::F_BaseObject*> * m_mainObjectList; // keep the main list, incase of return objects back to the main list
// std::vector<F_ManipulatedObject> m_objects;

// // lua pointer for assign
// lua_State * m_script;


// };


// #endif