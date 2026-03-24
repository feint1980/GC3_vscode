#ifndef COMBATCHARACTER_H
#define COMBATCHARACTER_H


#include <F_AnimatedObject.h>
#include <TextRenderer.h>
class Cslot;


struct dCharacterStats
{
    std::string ownerID = "";
    std::string characterID = "";
    
    float agility = 0;
    float strength = 0;
    float vitality = 0;
    float dexterity = 0;
    float intelligence = 0;
    float wisdom = 0;
    float physicDmg = 0.0f;
    float magicDmg = 0.0f;
    float physicDef = 0.0f;
    float magicDef = 0.0f;
    float physicalAccuracy = 0.0f;
    float magicalAccuracy = 0.0f;
    float evasion = 0.0f;
    float critChance = 0.0f;
    float speed = 0;
    float deathDoorSurvival = 0.0f;
    float maxHP = 0;
    float maxMana = 0;
    float maxAP = 0.0f;
    float maxSP = 0.0f;
    float currentHP = 0.0f;
    float currentMana = 0.0f;
    float currentAP = 0.0f;
    float currentSP = 0.0f;

};

// #include "../PacketDescription/CharacterDes.h"
class CombatCharacter
{
public:
    CombatCharacter();
    ~CombatCharacter();

    void init(CSlot * slot, const std::string & animationPath,const std::string & portraitPath, const glm::vec2 & scale , int side); 
    
    void draw(Feintgine::SpriteBatch & spriteBatch);
    
    void drawText(TextRenderer * textRenderer);

    void update(float deltaTime);

    void setStringValue(const std::string & key, const std::string & value);
    
    void setFloatValue(const std::string & key, float value);

    std::string getStringValue(const std::string & key);

    float getFloatValue(const std::string & key);

    void listStats();

private:

    CSlot * m_currentSlot = nullptr;

    int m_side = 1;

    glm::vec2 m_pos;
    glm::vec2 m_scale;
    float m_yOffset = 0.0f;

    int m_colPos = 0;
    int m_rowPos = 0;

    std::string m_characterID;

    Feintgine::F_AnimatedObject m_animation;
    dCharacterStats m_stats;
    // 

};


#endif