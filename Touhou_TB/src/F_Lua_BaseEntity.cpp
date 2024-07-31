#include "F_Lua_BaseEntity.h"

F_Lua_BaseEntity::F_Lua_BaseEntity()
{

}

F_Lua_BaseEntity::~F_Lua_BaseEntity()
{

}

void F_Lua_BaseEntity::init(Slot * slot, const std::string & animationPath, const glm::vec2 & scale)
{

    m_currentSlot = slot;
    m_moveTargetSlot = nullptr;
    m_scale = scale;

    m_pos = m_currentSlot->getPos();

    m_animation.init(animationPath, m_scale);
    m_animation.playAnimation("idle");

}
void F_Lua_BaseEntity::draw(Feintgine::SpriteBatch & spriteBatch)
{

    m_animation.setScale(m_scale);
    m_animation.setPos(m_pos);
    m_animation.draw(spriteBatch);
}

void F_Lua_BaseEntity::update(float deltaTime)
{
    if(m_moveTargetSlot)
    {
        glm::vec2 m_direction; 
        m_direction.x = m_moveTargetSlot->getPos().x - m_pos.x;
        m_direction.y = m_moveTargetSlot->getPos().y - m_pos.y;
        float distance = glm::distance(m_pos, m_moveTargetSlot->getPos());
        if(distance > 1.0f)
        {
            m_pos += m_direction * deltaTime * distance / 10.0f;
        }
        else
        {
            m_pos = m_moveTargetSlot->getPos();
            m_currentSlot = m_moveTargetSlot;
            m_moveTargetSlot = nullptr;
        }   
    }
    m_animation.update(deltaTime);
}

Attribute F_Lua_BaseEntity::getAttributeByName(const std::string & attributeName)
{

    std::string toLower = attributeName;

    std::transform(toLower.begin(), toLower.end(), toLower.begin(), ::tolower);
    if(toLower == "strength" )
    {
        return Strength;
    }
    else if(toLower == "vitality")
    {
        return Vitality;
    }
    else if(toLower == "dexterity")
    {
        return Dexterity;
    }
    else if(toLower == "agility")
    {
        return Agility;
    }
    else if(toLower == "intelligence")
    {
        return Intelligence;
    }
    else if(toLower == "wisdom")
    {
        return Wisdom;
    }
    else
    {
        return Invalid;
    }
}

void F_Lua_BaseEntity::setAttribute(const std::string & attributeName, int value)
{

    Attribute attribute = getAttributeByName(attributeName);
    setAttribute(attribute, value);
  
}

void F_Lua_BaseEntity::setAttribute(Attribute attribute, float value)
{

    if(attribute != Invalid)
    {   
        switch(attribute)
        {
            case Strength:
                m_strength = value;
                break;
            case Vitality:
                m_vitality = value;
                break;
            case Dexterity: 
                m_dexterity = value;
                break;
            case Agility:
                m_agility = value;
                break;
            case Intelligence:
                m_intelligence = value;
                break;
            case Wisdom:
                m_wisdom = value;
                break;
            default:
                break;
        }
    }
}