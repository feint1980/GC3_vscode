
#include "CSlot.h"
#include "CombatCharacter.h"



CombatCharacter::CombatCharacter()
{


}

CombatCharacter::~CombatCharacter()
{

}


void CombatCharacter::init(CSlot * slot, const std::string & animationPath,const std::string & portraitPath, const glm::vec2 & scale , int side)
{
    m_currentSlot = slot; 
    if(!m_currentSlot)
    {
        std::cout << "slot is null \n";
        return;
    }

    m_side = side;
    m_pos = m_currentSlot->getPos();
    m_scale = scale;

    m_animation.init(animationPath, m_scale);
    m_animation.playAnimation("idle");
    m_animation.setPos(m_pos);
    m_animation.setScale(m_scale);
    if(m_side == 2)
    {
        m_animation.setInvertAnimation();
    }

    m_yOffset = m_animation.getDim().y * 0.5f;

    // std::cout << "chracter init with texture " << animationPath << "\n";
    // std::cout << "curPos" << m_pos.x << " " << m_pos.y << "\n";
}

void CombatCharacter::draw(Feintgine::SpriteBatch & spriteBatch)
{
    m_animation.setPos((m_pos + glm::vec2(0.0f, m_yOffset)));
    m_animation.draw(spriteBatch);
}

void CombatCharacter::update(float deltaTime)
{
    m_animation.update(deltaTime);
}

void CombatCharacter::setStringValue(const std::string & key, const std::string & value)
{
    if(key == "userID" || key == "ownerID" || key == "usrID")
    {
        m_stats.ownerID = value;
    }
    if(key == "characterID" || key == "charID" || key == "cID")
    {
        m_characterID = value;
    }
}

void CombatCharacter::setFloatValue(const std::string & key, float value)
{

    if(key == "str" || key == "strength")
    {
        m_stats.strength = value;
    }
    if(key == "vit" || key == "vitality")
    {
        m_stats.vitality = value;
    }

    if(key == "dex" || key == "dexterity")
    {
        m_stats.dexterity = value;
    }

    if(key == "agi" || key == "agility")
    {
        m_stats.agility = value;
    }

    if(key == "int" || key == "intelligence")
    {
        m_stats.intelligence = value;
    }
    if(key == "wis" || key == "wisdom")
    {
        m_stats.wisdom = value;
    }
    if(key == "physicDmg" || key == "physicalDmg")
    {
        m_stats.physicDmg = value;
    }
    if(key == "magicDmg" || key == "magicDmg")
    {
        m_stats.magicDmg = value;
    }
    if(key == "physicDef" || key == "physicalDef")
    {
        m_stats.physicDef= value;
    }
    if(key == "magicDef" || key == "magicDefense")
    {
        m_stats.magicDef = value;
    }
    if(key == "crit" || key == "critical" || key == "critChance")
    {
        m_stats.critChance = value;
    }
    if(key == "speed" || key == "spd")
    {
        m_stats.speed = value;
    }
    if(key == "DDS" || key == "deathDoorSur" || key == "deathDoorSurvival")
    {
        m_stats.deathDoorSurvival = value;
    }
    if(key == "maxHP" || key == "maxHealth")
    {
        m_stats.maxHP = value;
    }
    if(key == "currentHP" || key == "currentHealth" || key == "cHp" || key == "cHP")
    {
        m_stats.currentHP = value;
    }
    if(key == "maxMana" )
    {
        m_stats.maxMana = value;
    }
    if(key == "currentMana" || key == "cMana")
    {
        m_stats.currentMana = value;
    }
    

    if(key == "maxAP")
    {
        m_stats.maxAP = value;
    }
    if(key == "currentAP" || key == "cAP")
    {
        m_stats.currentAP = value;
    }

    if(key == "maxSP")
    {
        m_stats.maxSP = value;
    }
    if(key == "currentSP" || key == "cSP")
    {
        m_stats.currentSP = value;
    }
}

}
