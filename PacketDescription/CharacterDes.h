#ifndef CHARACTERDESC_H
#define CHARACTERDESC_H

#include <string>
#include <vector>

enum Attribute
{
    Strength = 0,
    Vitality,
    Dexterity,
    Agility,
    Intelligence,
    Wisdom,
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
    name,
    lastName,
    title,
    Invalid
};


class CharacterDesc
{
    public:
        CharacterDesc();
        ~CharacterDesc();

        // void init()

        float getFloatAttributeByName(const std::string & attributeName);

        std::string getStrAttributeByName(const std::string & attributeName);
    
};



#endif // CHARACTERDESC_H

