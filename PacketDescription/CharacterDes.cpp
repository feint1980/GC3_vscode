#include "CharacterDes.h"

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

CharacterDesc::CharacterDesc()
{

}

CharacterDesc::~CharacterDesc()
{

}

void CharacterDesc::setCharacterStats(const CharacterStats & characterStats)
{
    m_charStats = characterStats;

    //json j = m_charStats;
    // std::cout << "dump stat \n";
    // std::cout << j.dump(4,'.') << "\n";
    // std::cout << "check path \n";
    // std::cout << m_charStats.panelPath << "\n";
    
}

void CharacterDesc::setAttribute(Attribute attribute, const std::string & value)
{
    switch(attribute)
    {
        case Attribute::name:
        m_charStats.name = value;
        break;
        case Attribute::lastName:
        m_charStats.lastName = value;
        break;
        case Attribute::title:
        m_charStats.title = value;
        break;
        case Attribute::animationPath:
        m_charStats.animationPath = value;
        break;
        case Attribute::portraitPath:
        m_charStats.portraitPath = value;
        break;
        case Attribute::panelPath:
        m_charStats.panelPath = value;
        break;
        case Attribute::ID:
        m_charStats.ID = value;
        break;
        default:
        std::cout << "failed to set att :(" << attribute << ") with: " << value << "\n";  
        break;
    }
}

void CharacterDesc::writeData(const std::string & path)
{
    CharacterStats patchouli = { 3,4,7,4,22,21, "./Assets/F_AObjects/patchouli_tb.xml", "./Assets/TB_GUI/faces/Patchouli_face.png","./Assets/TB_GUI/panels/patchouli_panel.png", 1.0, 30, 370, 0, 100, 4, 25, 3, 13, 0.85, 0.1, 0.125, 8, 7,2,3,1,1,0.035,0.025, 0.25,"Patchouli", "Knowledge", "Unmoving Library",1,1 };

    json j = patchouli;
    std::ofstream o(path);
    o << std::setw(4) << j << "\n";
    o.close();
}


float CharacterDesc::getFloatAttributeByName(const std::string & attributeName)
{
    switch (getAttributeByName(attributeName))
    {
        case Strength:
            return m_charStats.strength;  
        case Vitality:
            return m_charStats.vitality;
        case Dexterity: 
            return m_charStats.dexterity;
        case Agility:
            return m_charStats.agility;
        case Intelligence:
            return m_charStats.intelligence;
        case Wisdom:
            return m_charStats.wisdom;
        case action:
            return m_charStats.action;
        case hp:
            return m_charStats.hp;
        case mana:
            return m_charStats.mana;
        case sp:
            return m_charStats.sp;
        case spCap:
            return m_charStats.spCap;
        case physicDmg:
            return m_charStats.physicDmg;
        case physicDef:
            return m_charStats.physicDef;
        case magicDmg:
            return m_charStats.magicDmg;
        case magicDef:
            return m_charStats.magicDef;
        case accurate:
            return m_charStats.accurate;
        case evadeChance:
            return m_charStats.evadeChance;
        case critChance:
            return m_charStats.critChance;
        case hpScale:
            return m_charStats.hpScale;
        case manaScale:
            return m_charStats.manaScale;
        case physicDmgScale:
            return m_charStats.physicDmgScale;
        case magicDmgScale:
            return m_charStats.magicDmgScale;
        case physicDefScale:
            return m_charStats.physicDefScale;
        case magicDefScale:
            return m_charStats.magicDefScale;
        case accurateScale :
            return m_charStats.accurateScale;
        case evadeChanceScale:
            return m_charStats.evadeChanceScale;
        case deathDoorSurviveChance:
            return m_charStats.deathDoorSurviveChance;
        case side:
            return m_charStats.side;
        case level:
            return m_charStats.level;
        case xp:
            return m_charStats.xp;
        case price:
            return m_charStats.price;
        default:
            std::cout << "warinng, wrong attriute call " << attributeName << "\n";
            return -115114.0f;
    }
}

std::string CharacterDesc::getStrAttributeByName(const std::string & attributeName)
{
    switch (getAttributeByName(attributeName))
    {
        case name:
            return m_charStats.name;
        case lastName:
            return m_charStats.lastName;
        case title:
            return m_charStats.title;
        case animationPath:
            return m_charStats.animationPath;
        case portraitPath:
            return m_charStats.portraitPath;
        case panelPath:
            return m_charStats.panelPath;
        case ID:
            return m_charStats.ID;    
        default:
            std::cout << "warning, wrong attri " << attributeName << "\n";
            return "none";
    }
}

void CharacterDesc::setAttribute(const std::string & attributeName, float value)
{
    setAttribute(getAttributeByName(attributeName), value);
}

void CharacterDesc::setAttribute(const std::string & attributeName, const std::string & value)
{
    setAttribute(getAttributeByName(attributeName), value);
}

void CharacterDesc::setAttribute(Attribute attribute, float value)
{
    switch(attribute)
    {
        case Attribute::Strength:
            m_charStats.strength = value;
            break;
        case Attribute::Vitality:
            m_charStats.vitality = value;
            break;
        case Attribute::Dexterity: 
            m_charStats.dexterity = value;
            break;
        case Attribute::Agility:
            m_charStats.agility = value;
            break;
        case Attribute::Intelligence:
            m_charStats.intelligence = value;
            break;
        case Attribute::Wisdom:
            m_charStats.wisdom = value;
            break;
        case Attribute::action:
            m_charStats.action = value;
            break;
        case Attribute::hp:
            m_charStats.hp = value;
            break;
        case Attribute::mana:
            m_charStats.mana = value;
            break;  
        case Attribute::sp:
            m_charStats.sp = value;
            break;
        case Attribute::spCap:
            m_charStats.spCap = value;
            break;
        case Attribute::physicDmg:
            m_charStats.physicDmg = value;
            break;
        case Attribute::physicDef:
            m_charStats.physicDef = value;
            break;
        case Attribute::magicDmg:
            m_charStats.magicDmg = value;
            break;
        case Attribute::magicDef:
            m_charStats.magicDef = value;
            break;
        case Attribute::accurate:
            m_charStats.accurate = value;
            break;
        case Attribute::evadeChance:
            m_charStats.evadeChance = value;
            break;
        case Attribute::critChance:
            m_charStats.critChance = value;
            break;
        case Attribute::hpScale:
            m_charStats.hpScale = value;
            break;
        case Attribute::manaScale:
            m_charStats.manaScale = value;
            break;
        case Attribute::physicDmgScale:
            m_charStats.physicDmgScale = value;
            break;
        case Attribute::magicDmgScale:
            m_charStats.magicDmgScale = value;
            break;  
        case Attribute::physicDefScale:
            m_charStats.physicDefScale = value;
            break;
        case Attribute::magicDefScale:
            m_charStats.magicDefScale = value;
            break;
        case Attribute::accurateScale:
            m_charStats.accurateScale = value;
            break;
        case Attribute::evadeChanceScale:
            m_charStats.evadeChanceScale = value;
            break;
        case Attribute::deathDoorSurviveChance:
            m_charStats.deathDoorSurviveChance = value;
            break;
        case Attribute::side:
            m_charStats.side = value;
            break;
        case Attribute::level:
            m_charStats.level = value;
            break;
        case Attribute::xp:
            m_charStats.xp = value;
            break;
        case Attribute::price:
        m_charStats.price = value;
        break;
        default:
            std::cout << "error when try to set the att (" << attribute << ") : " << value << "\n";
            break;
    }
}

Attribute CharacterDesc::getAttributeByName(const std::string & attributeName)
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
    else if(toLower == "physicdmg" || toLower == "physicDamage")
    {
        return physicDmg;
    }
    else if(toLower == "magicdmg" || toLower == "magicDamage")
    {
        return magicDmg;
    }
    else if(toLower == "physicdef" || toLower == "physdef")
    {
        return physicDef;
    }
    else if(toLower == "magicdef" || toLower == "magdef")
    {
        return magicDef;
    }
    else if(toLower == "accurate" || toLower == "accuracy" || toLower == "acc")
    {
        return accurate;
    }
    else if(toLower == "evadechance" || toLower == "evade" || toLower == "eva")
    {
        return evadeChance;
    }
    else if(toLower == "crit" || toLower == "critchance")
    {
        return critChance;
    }
    else if(toLower == "hpscale" )
    {
        return hpScale;
    }
    else if(toLower == "manascale" )
    {
        return manaScale;
    } 
    else if(toLower == "physicdmgscale" )
    {
        return physicDmgScale; 
    }
    else if(toLower == "magicdmgscale" )
    {
        return magicDmgScale;
    }
    else if (toLower == "physicdefscale" )
    {
        return physicDefScale;
    }
    else if(toLower == "magicdefscale" )
    {
        return magicDefScale;
    }
    else if(toLower == "accuratescale" || toLower == "accscale" )
    {
        return accurateScale;
    }
    else if(toLower == "evadechancescale" || toLower == "evadescale" || toLower == "evascale")
    {
        return evadeChanceScale;
    }
    else if(toLower == "deathdoorsurvivechance" || toLower == "ddsc")   
    {
        return deathDoorSurviveChance;
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
    else if(toLower == "animationpath" || toLower == "animPath")
    {
        return animationPath;
    }
    else if(toLower == "portraitpath" || toLower == "porttpath")
    {
        return portraitPath;
    }
    else if(toLower == "panelpath")
    {
        return panelPath;
    }
    else if(toLower == "id" )
    {
        return ID;
    }
    else if(toLower == "level" || toLower == "lvl" )
    {
        return level;
    }
    else if(toLower == "exp" || toLower == "xp" )
    {
        return xp;
    }
    else if (toLower == "price")
    {
        return price;
    }
    else
    {
        std::cout << "invalid attribute assign : " << attributeName << "\n";
        return Invalid;
    }   
}