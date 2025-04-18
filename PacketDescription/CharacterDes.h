#ifndef CHARACTERDESC_H
#define CHARACTERDESC_H

#include <string>
#include <vector>
#include <iostream>

#include <fstream>

#include <algorithm>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct CharacterStats 
{
    float strength;
    float vitality ;
    float dexterity ;
    float agility ;
    float intelligence ;
    float wisdom ;
    std::string animationPath;
    std::string portraitPath;
    float action;
    float hp;
    float mana;
    float sp;
    float spCap;
    float physicDmg;
    float magicDmg;
    float physicDef;
    float magicDef;
    float accurate;
    float evadeChance;
    float critChance;
    float hpScale;
    float manaScale;
    float physicDmgScale;
    float magicDmgScale ;
    float physicDefScale ;
    float magicDefScale ;
    float accurateScale;
    float evadeChanceScale ;
    float deathDoorSurviveChance;
    std::string name ;
    std::string lastName ;
    std::string title ;
    int side ;
    int level;
    int xp;
    std::string ID;
};

enum Attribute
{
    Strength ,
    Vitality ,
    Dexterity ,
    Agility ,
    Intelligence ,
    Wisdom ,
    animationPath,
    portraitPath,
    action,
    hp,
    mana,
    sp,
    spCap,
    physicDmg,
    physicDef,
    magicDmg,
    magicDef,
    accurate,
    evadeChance,
    critChance,
    hpScale,
    manaScale,
    physicDmgScale,
    magicDmgScale ,
    physicDefScale ,
    magicDefScale ,
    accurateScale,
    evadeChanceScale ,
    deathDoorSurviveChance,
    name ,
    lastName ,
    title ,
    side ,
    level,
    xp,
    ID,
    Invalid
};

class CharacterDesc
{
    public:
    CharacterDesc();
    ~CharacterDesc();

    CharacterStats getCharacterStats() const { return m_charStats; }

    void writeData(const std::string & path);

    CharacterStats readFromLua(const std::string & path);

    Attribute getAttributeByName(const std::string & attributeName);

    void setAttribute(const std::string & attributeName, float value);

    void setAttribute(const std::string & attributeName, const std::string & value);

    void setAttribute(Attribute attribute, float value);

    void setAttribute(Attribute attribute, const std::string & value);

    float getFloatAttributeByName(const std::string & attributeName);

    std::string getStrAttributeByName(const std::string & attributeName);
    private :
    CharacterStats m_charStats;

};

#endif // CHARACTERDESC_H