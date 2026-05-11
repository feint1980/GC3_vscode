#ifndef COMBATCHARACTER_H
#define COMBATCHARACTER_H


#include <F_AnimatedObject.h>
#include <TextRenderer.h>
class CSlot;


struct dCharacterStats
{
    std::string ownerID = "";               // 1 
    std::string characterID = "";           // 2
    
    float strength = 0;                     // 3
    float vitality = 0;                     // 4
    float dexterity = 0;                    // 5
    float agility = 0;                      // 6
    float intelligence = 0;                 // 7
    float wisdom = 0;                       // 8
    float physicDmg = 0.0f;                 // 9
    float magicDmg = 0.0f;                  // 10
    float physicDef = 0.0f;                 // 11
    float magicDef = 0.0f;                  // 12
    float physicalAccuracy = 0.0f;          // 13
    float magicalAccuracy = 0.0f;           // 14
    float evasion = 0.0f;                   // 15
    float critChance = 0.0f;                // 16
    float speed = 0;                        // 17
    float deathDoorSurvival = 0.0f;         // 18
    float maxHP = 0;                        // 19
    float maxMana = 0;                      // 20
    float maxAP = 0.0f;                     // 21
    float maxSP = 0.0f;                     // 22
    float currentHP = 0.0f;                 // 23
    float currentMana = 0.0f;               // 24
    float currentAP = 0.0f;                 // 25
    float currentSP = 0.0f;                 // 26

    float colPos = 0;                         // 27
    float rowPos = 0;                         // 28

};

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

    void setStats( const dCharacterStats & stats) { m_stats = stats; }

private:

    CSlot * m_currentSlot = nullptr;

    int m_side = 1;

    glm::vec2 m_pos = glm::vec2(0);
    glm::vec2 m_scale = glm::vec2(0);
    float m_yOffset = 0.0f;

    int m_colPos = 0;
    int m_rowPos = 0;

    std::string m_characterID = "";

    Feintgine::F_AnimatedObject m_animation;
    dCharacterStats m_stats;
    // 

};


#endif