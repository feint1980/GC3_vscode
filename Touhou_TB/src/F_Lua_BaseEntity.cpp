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

    m_animation.init(animationPath, m_scale);
    m_animation.playAnimation("idle");
    m_yOffset = m_animation.getDim().y * 0.5f;

    m_pos = m_currentSlot->getPos();
    m_pos.y += m_yOffset;

    m_isActive = false;

}

void F_Lua_BaseEntity::setPos(const glm::vec2 & pos)
{
    m_pos = pos;
}


void F_Lua_BaseEntity::playAnimation(const std::string & animationName, int time)
{

    std::cout << "entity play animation " << animationName <<  " " << time << std::endl; 
    m_animation.playAnimation(animationName, time);
}

bool F_Lua_BaseEntity::isAnimationStoped() const
{
    return  m_animation.isPlaying() == false;
}

void F_Lua_BaseEntity::setActive(bool value)
{
    m_isActive = value;
}
void F_Lua_BaseEntity::draw(Feintgine::SpriteBatch & spriteBatch)
{

    m_animation.setScale(m_scale);
    m_animation.setPos(m_pos);
    m_animation.draw(spriteBatch);
}

void F_Lua_BaseEntity::setTargetSlot(Slot * slot)
{
    m_moveTargetSlot = slot;
    // m_startPos = m_pos;
    // m_isActive = false;
    // m_elaspedTime = 0.0f;
    // m_completionTime = 100.0f;
    // m_endPos = m_moveTargetSlot->getPos();
    // std::string animationName = "dash_fw";
    // if(m_endPos.x < m_startPos.x)
    // {
    //     animationName = "dash_bw";
    // }

    // m_animation.playAnimation(animationName);
    // //m_endPos += m_yOffset;
}

void F_Lua_BaseEntity::update(float deltaTime)
{
    
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