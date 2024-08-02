#include "F_Lua_EntityManipulator.h"


F_Lua_EntityManipulator::F_Lua_EntityManipulator()
{


}


F_Lua_EntityManipulator::~F_Lua_EntityManipulator()
{

}

void F_Lua_EntityManipulator::moveToSlot(F_Lua_BaseEntity * entity, Slot * slot, float time)
{
    m_entity = entity;
    m_entity->setTargetSlot(slot);
}