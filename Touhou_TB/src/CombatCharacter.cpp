
#include "CSlot.h"
#include "CombatCharacter.h"
#include <algorithm>

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

    if (m_isMoving)
    {
        m_moveElapsed += deltaTime;
        float t = (m_moveDuration > 0.0f) ? std::min(m_moveElapsed / m_moveDuration, 1.0f) : 1.0f;
        m_pos = m_moveStartPos + (m_moveTargetPos - m_moveStartPos) * t;

        if (t >= 1.0f)
        {
            m_pos = m_moveTargetPos;
            m_isMoving = false;
            m_currentSlot = m_targetSlot;
            m_moveJustCompleted = true; // flag only - updateEvents() fires it into Lua
        }
    }

    if (m_waitingAnimDone)
    {
        bool playingNow = m_animation.isPlaying();
        if (m_wasAnimPlayingLastFrame && !playingNow)
        {
            m_waitingAnimDone = false;
            m_animJustCompleted = true; // flag only - updateEvents() fires it into Lua
        }
        m_wasAnimPlayingLastFrame = playingNow;
    }
}

void CombatCharacter::updateEvents(lua_State * L)
{
    if (m_moveJustCompleted)
    {
        m_moveJustCompleted = false;
        fireLuaEvent(L, "moveComplete");
    }

    if (m_animJustCompleted)
    {
        m_animJustCompleted = false;
        fireLuaEvent(L, "animComplete");
    }
}

void CombatCharacter::drawText(TextRenderer * textRenderer)
{
    
}

void CombatCharacter::setStringValue(const std::string & key, const std::string & value)
{
    if(key == "userID" || key == "ownerID" || key == "usrID" || key == "ownerId")
    {
        m_stats.ownerID = value;
        return;
    }
    if(key == "characterID" || key == "charID" || key == "cID" || key == "characterId")
    {
        m_characterID = value;
        return;
    }

    std::cout << "unknown key (setStringValue) " << key << "\n";
}


void CombatCharacter::setFloatValue(const std::string & key, float value)
{

    if(key == "str" || key == "strength")
    {
        m_stats.strength = value;
        return;
    }
    if(key == "vit" || key == "vitality")
    {
        m_stats.vitality = value;
        return;
    }

    if(key == "dex" || key == "dexterity")
    {
        m_stats.dexterity = value;
        return;
    }

    if(key == "agi" || key == "agility")
    {
        m_stats.agility = value;
        return;
    }

    if(key == "int" || key == "intelligence")
    {
        m_stats.intelligence = value;
        return;
    }
    if(key == "wis" || key == "wisdom")
    {
        m_stats.wisdom = value;
        return;
    }
    if(key == "physicDmg" || key == "physicalDmg")
    {
        m_stats.physicDmg = value;
        return;
    }
    if(key == "magicDmg" || key == "magicDmg")
    {
        m_stats.magicDmg = value;
        return;
    }
    if(key == "physicDef" || key == "physicalDef")
    {
        m_stats.physicDef= value;
        return;
    }
    if(key == "magicDef" || key == "magicDefense")
    {
        m_stats.magicDef = value;
        return;
    }
    if (key == "physicalAccuracy")
    {
        m_stats.physicalAccuracy = value;
        return;
    }
    if (key == "magicalAccuracy")
    {
        m_stats.magicalAccuracy = value;
        return;
    }
    if( key == "evasion")
    {
        m_stats.evasion = value;
        return;
    }

    if(key == "crit" || key == "critical" || key == "critChance")
    {
        m_stats.critChance = value;
        return;
    }
    if(key == "speed" || key == "spd")
    {
        m_stats.speed = value;
        return;
    }
    if(key == "DDS" || key == "deathDoorSur" || key == "deathDoorSurvival")
    {
        m_stats.deathDoorSurvival = value;
        return;
    }
    if(key == "maxHP" || key == "maxHp" || key == "maxHealth")
    {
        m_stats.maxHP = value;
        return;
    }
    if(key == "currentHP" || key == "currentHealth" || key == "cHp" || key == "cHP")
    {
        m_stats.currentHP = value;
        return;
    }
    if(key == "maxMana" )
    {
        m_stats.maxMana = value;
        return;
    }
    if(key == "currentMana" || key == "cMana")
    {
        m_stats.currentMana = value;
        return;
    }
    
    if(key == "maxAP")
    {
        m_stats.maxAP = value;
        return;
    }
    if(key == "currentAP" || key == "cAP")
    {
        m_stats.currentAP = value;
        return;
    }

    if(key == "maxSP")
    {
        m_stats.maxSP = value;
        return;
    }
    if(key == "currentSP" || key == "cSP")
    {
        m_stats.currentSP = value;
        return;
    }
    if(key == "colPos" || key == "cPos")
    {
        m_stats.colPos = value;
        m_colPos = value;
        return;
    }
    if(key == "rowPos" || key == "rPos")
    {
        m_stats.rowPos = value;
        m_rowPos = value;
        return;
    }

    std::cout << "warning : unknown key setFloatValue " << key << " \n";
    
}


std::string CombatCharacter::getStringValue(const std::string & key)
{
    if(key == "characterID" || key == "charID" || key == "cID" || key == "characterId")
    {
        return m_characterID;
    }
    if(key == "ownerID" || key == "oID" || key == "ownerId")
    {
        return m_stats.ownerID;
    }

    std::cout << "warning : unknown key getStringValue " << key << " \n";
    return "";
}

float CombatCharacter::getFloatValue(const std::string & key)
{
    if(key == "str" || key == "strength")
    {
        return m_stats.strength;
    }
    if(key == "vit" || key == "vitality")
    {
        return m_stats.vitality;
    }

    if(key == "dex" || key == "dexterity")
    {
        return m_stats.dexterity;
    }

    if(key == "agi" || key == "agility")
    {
        return m_stats.agility;
    }

    if(key == "int" || key == "intelligence")
    {
        return m_stats.intelligence;
    }
    if(key == "wis" || key == "wisdom")
    {
        return m_stats.wisdom;
    }
    if(key == "physicDmg" || key == "physicalDmg")
    {
        return m_stats.physicDmg;
    }
    if(key == "magicDmg" || key == "magicDmg")
    {
        return m_stats.magicDmg;
    }
    if(key == "physicDef" || key == "physicalDef")
    {
        return m_stats.physicDef;
    }
    if(key == "magicDef" || key == "magicDefense")
    {
        return m_stats.magicDef;
    }
    if (key == "physicalAccuracy")
    {
        return m_stats.physicalAccuracy;
    }
    if (key == "magicalAccuracy")
    {
        return m_stats.magicalAccuracy;
    }
    if( key == "evasion")
    {
        return m_stats.evasion;
    }

    if(key == "crit" || key == "critical" || key == "critChance")
    {
        return m_stats.critChance;
    }
    if(key == "speed" || key == "spd")
    {
        return m_stats.speed;
    }
    if(key == "DDS" || key == "deathDoorSur" || key == "deathDoorSurvival")
    {
        return m_stats.deathDoorSurvival;
    }
    if(key == "maxHP" || key == "maxHp" || key == "maxHealth")
    {
        return m_stats.maxHP;
    }
    if(key == "currentHP" || key == "currentHealth" || key == "cHp" || key == "cHP")
    {
        return m_stats.currentHP;
    }
    if(key == "maxMana" )
    {
        return m_stats.maxMana;
    }
    if(key == "currentMana" || key == "cMana")
    {
        return m_stats.currentMana;
    }
    
    if(key == "maxAP")
    {
        return m_stats.maxAP;
    }
    if(key == "currentAP" || key == "cAP")
    {
        return m_stats.currentAP;
    }

    if(key == "maxSP")
    {
        return m_stats.maxSP;
    }
    if(key == "currentSP" || key == "cSP")
    {
        return m_stats.currentSP;
    }

    std::cout << "warning : unknown key getFloatValue " << key << " \n";
    return -1919.0f;
}

void CombatCharacter::listStats()
{
    std::cout << "characterID " << m_stats.characterID << "\n";
    std::cout << "ownerID " << m_stats.ownerID << "\n";

    std::cout << "strength " << m_stats.strength << "\n";
    std::cout << "vitality " << m_stats.vitality << "\n";
    std::cout << "dexterity " << m_stats.dexterity << "\n";
    std::cout << "agility " << m_stats.agility << "\n";
    std::cout << "intelligence " << m_stats.intelligence << "\n";
    std::cout << "wisdom " << m_stats.wisdom << "\n";
    std::cout << "physicalDmg " << m_stats.physicDmg << "\n";
    std::cout << "magicDmg " << m_stats.magicDmg << "\n";
    std::cout << "physicalDef " << m_stats.physicDef << "\n";
    std::cout << "magicDef " << m_stats.magicDef << "\n";
    std::cout << "critical " << m_stats.critChance << "\n";
    std::cout << "speed " << m_stats.speed << "\n";
    std::cout << "deathDoorSurvival " << m_stats.deathDoorSurvival << "\n";
    std::cout << "maxHP " << m_stats.maxHP << "\n";
    std::cout << "currentHP " << m_stats.currentHP << "\n";
    std::cout << "maxMana " << m_stats.maxMana << "\n";
    std::cout << "currentMana " << m_stats.currentMana << "\n";
    std::cout << "maxAP " << m_stats.maxAP << "\n";
    std::cout << "currentAP " << m_stats.currentAP << "\n";
    std::cout << "maxSP " << m_stats.maxSP << "\n";
    std::cout << "currentSP " << m_stats.currentSP << "\n";

}

void CombatCharacter::playAnimation(const std::string & animationName, bool loop)
{
    if (loop)
    {
        m_animation.playAnimation(animationName, -1);
        m_waitingAnimDone = false;
    }
    else
    {
        m_animation.playAnimation(animationName, 1); // play through once then stop
        m_waitingAnimDone = true;
        m_wasAnimPlayingLastFrame = true;
    }
}

void CombatCharacter::moveToCell(CSlot * targetSlot, float duration)
{
    if (!targetSlot)
    {
        std::cout << "moveToCell: targetSlot is null\n";
        return;
    }

    m_targetSlot = targetSlot;
    m_moveStartPos = m_pos;
    m_moveTargetPos = targetSlot->getPos();
    m_moveDuration = duration;
    m_moveElapsed = 0.0f;
    m_isMoving = true;
}

void CombatCharacter::fireLuaEvent(lua_State * L, const std::string & eventName)
{
    if (!L)
    {
        std::cout << "fireLuaEvent: lua_State is null, cannot fire " << eventName << "\n";
        return;
    }

    lua_getglobal(L, "CC_Event");
    if (lua_isnil(L, -1))
    {
        std::cout << "fireLuaEvent: CC_Event global not found\n";
        lua_pop(L, 1);
        return;
    }

    lua_getfield(L, -1, "fire");
    if (lua_isnil(L, -1))
    {
        std::cout << "fireLuaEvent: CC_Event.fire not found\n";
        lua_pop(L, 2);
        return;
    }

    lua_remove(L, -2); // pop CC_Event table, leave fire function on top

    std::string fullKey = getMapKey() + "_" + eventName;
    lua_pushstring(L, fullKey.c_str());

    if (lua_pcall(L, 1, 0, 0) != 0)
    {
        std::cout << "fireLuaEvent error: " << lua_tostring(L, -1) << "\n";
        lua_pop(L, 1);
    }
}