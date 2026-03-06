
#ifndef BS_JSONPARSER_H
#define BS_JSONPARSER_H

#include "CharacterDes.h"
#include "SkillDesc.h"
// json parse struct
static void to_json(json& j, const CharacterStats& c) 
{
    j = json{
        {"strength", c.strength}, // 1 use to check if all stats are set
        {"vitality", c.vitality}, // 2
        {"dexterity", c.dexterity}, // 3
        {"agility", c.agility}, // 4
        {"intelligence", c.intelligence}, // 5
        {"wisdom", c.wisdom}, // 6
        {"animationPath", c.animationPath}, // 7
        {"portraitPath", c.portraitPath}, // 8
        {"panelPath",c.panelPath}, // 9
        {"action",c.action}, // 10
        {"hp",c.hp}, // 11
        {"mana",c.mana}, // 12
        {"sp",c.sp}, // 13
        {"spCap",c.spCap}, // 14
        {"physicDmg",c.physicDmg}, // 15
        {"physicDef",c.physicDef}, // 16
        {"magicDmg",c.magicDmg}, // 17
        {"magicDef",c.magicDef}, // 18
        {"accurate",c.accurate}, // 19
        {"evadeChance",c.evadeChance}, // 20
        {"critChance",c.critChance}, // 21
        {"hpScale",c.hpScale}, // 22
        {"manaScale",c.manaScale}, // 23
        {"physicDmgScale",c.physicDmgScale}, // 24
        {"magicDmgScale",c.magicDmgScale}, // 25
        {"physicDefScale",c.physicDefScale}, // 26
        {"magicDefScale",c.magicDefScale}, // 27
        {"accurateScale",c.accurateScale}, // 28
        {"evadeChanceScale",c.evadeChanceScale}, // 29
        {"deathDoorSurviveChance",c.deathDoorSurviveChance}, // 30
        {"name",c.name}, // 31
        {"lastName",c.lastName}, // 32
        {"title",c.title}, // 33
        {"side",c.side}, // 34
        {"level",c.level}, // 35
        {"xp", c.xp}, // 36
        {"ID",c.ID}, // 37
        {"price",c.price} // 38
    };
}

// Convert JSON to struct
static void from_json(const json& j, CharacterStats& c) {
    j.at("strength").get_to(c.strength); // 1
    j.at("vitality").get_to(c.vitality); // 2
    j.at("dexterity").get_to(c.dexterity); // 3
    j.at("agility").get_to(c.agility); // 4
    j.at("intelligence").get_to(c.intelligence); // 5
    j.at("wisdom").get_to(c.wisdom); // 6
    j.at("animationPath").get_to(c.animationPath); // 7
    j.at("portraitPath").get_to(c.portraitPath); // 8
    j.at("panelPath").get_to(c.panelPath); // 9
    j.at("action").get_to(c.action); // 10
    j.at("hp").get_to(c.hp); // 11
    j.at("mana").get_to(c.mana); // 12
    j.at("sp").get_to(c.sp); // 13
    j.at("spCap").get_to(c.spCap); // 14
    j.at("physicDmg").get_to(c.physicDmg); // 15
    j.at("physicDef").get_to(c.physicDef); // 16
    j.at("magicDmg").get_to(c.magicDmg); // 17
    j.at("magicDef").get_to(c.magicDef); // 18
    j.at("accurate").get_to(c.accurate); // 19
    j.at("evadeChance").get_to(c.evadeChance); // 20
    j.at("critChance").get_to(c.critChance); // 21
    j.at("hpScale").get_to(c.hpScale);  // 22
    j.at("manaScale").get_to(c.manaScale); // 23
    j.at("physicDmgScale").get_to(c.physicDmgScale); // 24
    j.at("magicDmgScale").get_to(c.magicDmgScale); // 25
    j.at("physicDefScale").get_to(c.physicDefScale); // 26
    j.at("magicDefScale").get_to(c.magicDefScale); // 27
    j.at("accurateScale").get_to(c.accurateScale); // 28
    j.at("evadeChanceScale").get_to(c.evadeChanceScale); // 29
    j.at("deathDoorSurviveChance").get_to(c.deathDoorSurviveChance); // 30
    j.at("name").get_to(c.name); // 31
    j.at("lastName").get_to(c.lastName); // 32
    j.at("title").get_to(c.title); // 33
    j.at("side").get_to(c.side); // 34
    j.at("level").get_to(c.level); // 35
    j.at("xp").get_to(c.xp); // 36
    j.at("ID").get_to(c.ID); // 37
    j.at("price").get_to(c.price); // 38
}

static void to_json(json& j, const SkillStats& s)
{
    j = json{
        {"skillName", s.skillName},
        {"description", s.description},
        {"effect", s.effect},
        {"quote", s.quote},
        {"iconPath", s.iconPath},
        {"ID", s.ID},
        {"skillType", s.skillType}
    };
}

static void from_json(const json& j, SkillStats& s)
{
    j.at("skillName").get_to(s.skillName);
    j.at("description").get_to(s.description);
    j.at("effect").get_to(s.effect);
    j.at("quote").get_to(s.quote);
    j.at("iconPath").get_to(s.iconPath);
    j.at("ID").get_to(s.ID);
    j.at("skillType").get_to(s.skillType);
}


#endif //BS_JSONPARSER