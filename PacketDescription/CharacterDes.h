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
    // move constructor 
    // CharacterStats(CharacterStats&& other) noexcept
    // {
    //     std::cout << "move constructor \n";
    //     *this = std::move(other); 
    // }
    // // move assignment
    // CharacterStats & operator=(CharacterStats && other) noexcept
    // {
    //     std::cout << "move assignment \n";
    //     *this = std::move(other);
    //     return *this;
    // }

    // // copy constructor 
    // CharacterStats(const CharacterStats & other)
    // {
    //     std::cout << "copy constructor \n";
    //     *this = other;
    // }
    // // copy assignment
    // CharacterStats & operator=(const CharacterStats & other)
    // {
    //     *this = other;
    //     return *this;
    // }
    // CharacterStats() {}



    float strength;
    float vitality ;
    float dexterity ;
    float agility ;
    float intelligence ;
    float wisdom ;
    std::string animationPath;
    std::string portraitPath;
    std::string panelPath;
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
    int price;
    std::string ID;
};

enum Attribute
{
    Strength = 1 , // 1
    Vitality , // 2
    Dexterity , // 3
    Agility , // 4
    Intelligence , // 5
    Wisdom , // 6
    animationPath, // 7
    portraitPath, // 8
    panelPath, // 9
    action, // 10
    hp, // 11
    mana, // 12
    sp, // 13
    spCap, // 14
    physicDmg, // 15
    physicDef, // 16
    magicDmg, // 17
    magicDef, // 18
    accurate, // 19
    evadeChance, // 20
    critChance, // 21
    hpScale, // 22
    manaScale, // 23
    physicDmgScale, // 24
    magicDmgScale , // 25
    physicDefScale , // 26
    magicDefScale , // 27
    accurateScale, // 28
    evadeChanceScale , // 29
    deathDoorSurviveChance, // 30
    name , // 31
    lastName , // 32
    title , // 33
    side , // 34
    level, // 35
    xp, // 36
    ID, // 37
    price, // 38
    // any new attribute must be added here 
    
    Invalid
};

class CharacterDesc
{
    public:
    CharacterDesc();
    ~CharacterDesc();

    // move constructor
    CharacterDesc(CharacterDesc && other) noexcept
    {
        // m_charStats = std::move(other.m_charStats);
        m_charStats = other.m_charStats;
    }
    // move assignment
    CharacterDesc & operator=(CharacterDesc && other) noexcept
    {
        // m_charStats = std::move(other.m_charStats);
        m_charStats = other.m_charStats;
        return *this;
    }

    // copy constructor
    CharacterDesc(const CharacterDesc & other)
    {
        m_charStats = other.m_charStats;
    }
    // copy assignment
    CharacterDesc & operator=(const CharacterDesc & other)
    {
        m_charStats = other.m_charStats;
        return *this;
    }

    CharacterStats getCharacterStats() const { return m_charStats; }

    void setCharacterStats(const CharacterStats & characterStats);

    void writeData(const std::string & path);

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