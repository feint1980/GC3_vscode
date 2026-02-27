

#ifndef BATTLECHARACTERSTATE_H
#define BATTLECHARACTERSTATE_H

#include "CharacterDes.h"



static void to_json(json& j, const CharacterStats& c) 
{
    j = json{
        {"strength", c.strength},
        {"vitality", c.vitality},
        {"dexterity", c.dexterity},
        {"agility", c.agility},
        {"intelligence", c.intelligence},
        {"wisdom", c.wisdom},
        {"animationPath", c.animationPath},
        {"portraitPath", c.portraitPath},
        {"panelPath",c.panelPath},
        {"action",c.action},
        {"hp",c.hp},
        {"mana",c.mana},
        {"sp",c.sp},
        {"spCap",c.spCap},
        {"physicDmg",c.physicDmg},
        {"physicDef",c.physicDef},
        {"magicDmg",c.magicDmg},
        {"magicDef",c.magicDef},
        {"accurate",c.accurate},
        {"evadeChance",c.evadeChance},
        {"critChance",c.critChance},
        {"hpScale",c.hpScale},
        {"manaScale",c.manaScale},
        {"physicDmgScale",c.physicDmgScale},
        {"magicDmgScale",c.magicDmgScale},
        {"physicDefScale",c.physicDefScale},
        {"magicDefScale",c.magicDefScale},
        {"accurateScale",c.accurateScale},
        {"evadeChanceScale",c.evadeChanceScale},
        {"deathDoorSurviveChance",c.deathDoorSurviveChance},
        {"name",c.name},
        {"lastName",c.lastName},
        {"title",c.title},
        {"side",c.side},
        {"level",c.level},
        {"xp", c.xp},
        {"price",c.price},
        {"ID",c.ID}
    };
}

// Convert JSON to struct
static void from_json(const json& j, CharacterStats& c) {
    j.at("strength").get_to(c.strength);
    j.at("vitality").get_to(c.vitality);
    j.at("dexterity").get_to(c.dexterity);
    j.at("agility").get_to(c.agility);
    j.at("intelligence").get_to(c.intelligence);
    j.at("wisdom").get_to(c.wisdom);
    j.at("animationPath").get_to(c.animationPath);
    j.at("portraitPath").get_to(c.portraitPath);
    j.at("panelPath").get_to(c.panelPath);
    j.at("action").get_to(c.action);
    j.at("hp").get_to(c.hp);
    j.at("mana").get_to(c.mana);
    j.at("sp").get_to(c.sp);
    j.at("spCap").get_to(c.spCap);
    j.at("physicDmg").get_to(c.physicDmg);
    j.at("physicDef").get_to(c.physicDef);
    j.at("magicDmg").get_to(c.magicDmg);
    j.at("magicDef").get_to(c.magicDef);
    j.at("accurate").get_to(c.accurate);
    j.at("evadeChance").get_to(c.evadeChance);
    j.at("critChance").get_to(c.critChance);
    j.at("hpScale").get_to(c.hpScale);  
    j.at("manaScale").get_to(c.manaScale);
    j.at("physicDmgScale").get_to(c.physicDmgScale);
    j.at("magicDmgScale").get_to(c.magicDmgScale);
    j.at("physicDefScale").get_to(c.physicDefScale);
    j.at("magicDefScale").get_to(c.magicDefScale);
    j.at("accurateScale").get_to(c.accurateScale);
    j.at("evadeChanceScale").get_to(c.evadeChanceScale);
    j.at("deathDoorSurviveChance").get_to(c.deathDoorSurviveChance);
    j.at("name").get_to(c.name);
    j.at("lastName").get_to(c.lastName);
    j.at("title").get_to(c.title);
    j.at("side").get_to(c.side);
    j.at("level").get_to(c.level);
    j.at("xp").get_to(c.xp);
    j.at("price").get_to(c.price);
    j.at("ID").get_to(c.ID);
}


class BattleCharacterState
{
public:
    BattleCharacterState();
    ~BattleCharacterState();

    void init(const std::string & statStr);

    std::string getCharacterID() const { return m_characterDesc.getCharacterStats().ID; }

private :
    CharacterDesc m_characterDesc;
};


#endif // BATTLECHARACTERSTATE_H