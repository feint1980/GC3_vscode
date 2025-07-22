#include "SkillDesc.h"

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

SkillDesc::SkillDesc()
{

}

SkillDesc::~SkillDesc()
{

}

void SkillDesc::setSkillStats(SkillStats s)
{ 
    m_skillStats = s; 
}

void SkillDesc::setAttribute(SkillAtt attribute, const std::string & value)
{
    switch (attribute)
    {
    case SkillAtt::skillName:
        m_skillStats.skillName = value;
        break;
    case SkillAtt::skillDescription:
        m_skillStats.description = value;
        break;
    case SkillAtt::skillEffect:
        m_skillStats.effect = value;
        break;
    case SkillAtt::skillQuote: 
        m_skillStats.quote = value;
        break;
    case SkillAtt::skillIconPath:
        m_skillStats.iconPath = value;
        break;
    case SkillAtt::skillID:
        m_skillStats.ID = value;
        break;
    default:
        break;
    }
}


SkillAtt SkillDesc::getAttributeByName(const std::string & attributeName)
{   

    std::string lower = attributeName;
    std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c) { return std::tolower(c); });

    if (lower == "skillname" || lower == "name")
    {
        return SkillAtt::skillName;
    }
    else if (lower == "skilldescription" || lower == "description")
    {
        return SkillAtt::skillDescription;
    }
    else if (lower == "skilleffect" || lower == "effect")
    {
        return SkillAtt::skillEffect;
    }
    else if (lower == "skillquote" || lower == "quote")
    {
        return SkillAtt::skillQuote;
    }
    else if (lower == "skilliconPath" || lower == "iconpath" || lower == "icon")
    {
        return SkillAtt::skillIconPath;
    }
    else if (lower == "skillid" || lower == "id")
    {
        return SkillAtt::skillID;
    }
    else if (lower == "skilltype" || lower == "type")
    {
        return SkillAtt::skillType;
    }
    else
    {
        return SkillAtt::skillInvalid;
    }
}

std::string SkillDesc::getAttribute(SkillAtt attribute)
{
    switch (attribute)
    {
    case SkillAtt::skillName:
        return m_skillStats.skillName;
    case SkillAtt::skillDescription:
        return m_skillStats.description;
    case SkillAtt::skillEffect:
        return m_skillStats.effect;
    case SkillAtt::skillQuote:
        return m_skillStats.quote;
    case SkillAtt::skillIconPath:
        return m_skillStats.iconPath;
    case SkillAtt::skillID:
        return m_skillStats.ID;
    default:
        return "";
    }
}

std::string SkillDesc::getAttribute(const std::string & attributeName)
{
    std::string lower = attributeName;
    std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c) { return std::tolower(c); });
    switch (getAttributeByName(lower))
    {
    case SkillAtt::skillName:
        return m_skillStats.skillName;
    case SkillAtt::skillDescription:
        return m_skillStats.description;
    case SkillAtt::skillEffect:
        return m_skillStats.effect;
    case SkillAtt::skillQuote:
        return m_skillStats.quote;
    case SkillAtt::skillIconPath:
        return m_skillStats.iconPath;
    case SkillAtt::skillID:
        return m_skillStats.ID;
    default:
        std::cout << "warning, wrong attri " << attributeName << "\n";
        return "error";
    }
}

void SkillDesc::setAttribute(SkillAtt attribute, int value)
{
    switch (attribute)
    {
    case SkillAtt::skillType:
        m_skillStats.skillType = value;
        break;
    default:
        std::cout << "warning, wrong attri " << attribute << "\n";
        break;
    }
}

int SkillDesc::getAttributeInt(const std::string & attributeName)
{
    std::string lower = attributeName;
    std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c) { return std::tolower(c); });
    switch (getAttributeByName(lower))
    {
    case SkillAtt::skillType:
        return m_skillStats.skillType;
    default:
        std::cout << "warning, wrong attri " << attributeName << "\n";
        return -1;
    }
}

