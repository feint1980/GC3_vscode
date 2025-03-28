#include "F_Lua_BaseEntity.h"

F_Lua_BaseEntity::F_Lua_BaseEntity()
{

}

F_Lua_BaseEntity::~F_Lua_BaseEntity()
{

}

void F_Lua_BaseEntity::init(Slot * slot, const std::string & animationPath,const std::string & portraitPath , const glm::vec2 & scale)
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

    m_portrait = new EmptyObject();

    m_portrait->init(Feintgine::ResourceManager::getTexture(portraitPath), glm::vec2(0),glm::vec2(100,100),Feintgine::Color(255, 255, 255, 255));
    m_portrait->setDepth(22);

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

    if(m_portrait)
    {
        m_portrait->draw(spriteBatch);
    }
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
    if(toLower == "strength" || toLower == "str")
    {
        return Strength;
    }
    else if(toLower == "vitality" || toLower == "vit")
    {
        return Vitality;
    }
    else if(toLower == "dexterity" || toLower == "dex")
    {
        return Dexterity;
    }
    else if(toLower == "agility" || toLower == "agi")
    {
        return Agility;
    }
    else if(toLower == "intelligence" || toLower == "int")
    {
        return Intelligence;
    }
    else if(toLower == "wisdom" || toLower == "wis")
    {
        return Wisdom;
    }
    else if(toLower == "action")
    {
        return action;
    }
    else if(toLower == "hp" || toLower == "health")
    {
        return hp;
    }
    else if(toLower == "mana" || toLower == "mp")
    {
        return mana;
    }
    else if(toLower == "sp")
    {
        return sp;
    }
    else if(toLower == "spcap")
    {
        return spCap;
    }
    else if(toLower == "physicdmg" || toLower == "physic")
    {
        return physicDmg;
    }
    else if(toLower == "magicdmg" || toLower == "magic")
    {
        return magicDmg;
    }
    else if(toLower == "magicdef" || toLower == "magdef" || toLower == "magicdef")
    {
        return magicDef;
    }
    else if(toLower == "physicdef" || toLower == "physdef" || toLower == "physicdef")
    {
        return physicDef;
    }
    else if(toLower == "accurate" || toLower == "accuracy" || toLower == "acc")
    {
        return accurate;
    }
    else if(toLower == "evadechance" || toLower == "evade")
    {
        return evadeChance;
    }
    else if(toLower == "name")
    {
        return name;
    }
    else if(toLower == "lastname")
    {
        return lastName;
    }
    else if(toLower == "title")
    {
        return title;
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

void F_Lua_BaseEntity::setAttribute(const std::string & attributeName, const std::string & value)
{
    Attribute attribute = getAttributeByName(attributeName);
    setAttribute(attribute, value);
}

float F_Lua_BaseEntity::getFloatAttributeByName(const std::string & attributeName)
{

    Attribute attribute = getAttributeByName(attributeName);
    switch (attribute)
    {
        case Strength:
            return m_strength;  
        case Vitality:
            return m_vitality;
        case Dexterity: 
            return m_dexterity;
        case Agility:
            return m_agility;
        case Intelligence:
            return m_intelligence;
        case Wisdom:
            return m_wisdom;
        case action:
            return m_action;
        case hp:
            return m_hp;
        case mana:
            return m_mana;
        case sp:
            return m_sp;
        case spCap:
            return m_spCap;
        case physicDmg:
            return m_physicDmg;
        case physicDef:
            return m_physicDef;
        case magicDmg:
            return m_magicDmg;
        case magicDef:
            return m_magicDef;
        case accurate:
            return m_accurate;
        case evadeChance:
            return m_evadeChance;
        default:
            return -115114.0f;
    }
}

std::string F_Lua_BaseEntity::getStrAttributeByName(const std::string & attributeName)
{

    Attribute attribute = getAttributeByName(attributeName);
    switch (attribute)
    {
        case name:
            return m_name;
        case lastName:
            return m_lastName;
        case title:
            return m_title;
        default:
            return "none";
    }
}


void F_Lua_BaseEntity::setAttribute(Attribute attribute, const std::string & value)
{

    if(attribute != Invalid)
    {

        switch(attribute)
        {
            case name:
                m_name = value;
                std::cout << "set name: " << m_name << "\n";
                break;
            case lastName:
                m_lastName = value;
                break;
            case title:
                m_title = value;
                break;
            default:
                break;
        }
    }
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
            case action:
                m_action = value;
                break;
            case hp:
                m_hp = value;
                break;
            case mana:
                m_mana = value;
                break;  
            case sp:
                m_sp = value;
                break;
            case spCap:
                m_spCap = value;
                break;
            case physicDmg:
                m_physicDmg = value;
                break;
            case physicDef:
                m_physicDef = value;
                break;
            case magicDmg:
                m_magicDmg = value;
                break;
            case magicDef:
                m_magicDef = value;
                break;
            case accurate:
                m_accurate = value;
                break;
            case evadeChance:
                m_evadeChance = value;
                break;
            default:
                break;
        }
    }
}