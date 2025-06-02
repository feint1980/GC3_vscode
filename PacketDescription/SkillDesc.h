#ifndef SKILLDESC_H
#define SKILLDESC_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

enum SkillAtt 
{
    skillName,
    skillDescription,
    skillEffect,
    skillQuote,
    skillIconPath,
    skillID,
    skillInvalid = 67
};

struct SkillStats {
    std::string skillName;
    std::string description;
    std::string effect;
    std::string quote;
    std::string iconPath;
    std::string ID;
};

class SkillDesc  {
public:
    SkillDesc();
    ~SkillDesc();
    

    void setSkillStats(SkillStats s);
    void setAttribute(SkillAtt attribute, const std::string & value);
    SkillAtt getAttributeByName(const std::string & attributeName);
    std::string getAttribute(const std::string & attributeName);
    std::string getAttribute(SkillAtt attribute);


private:

    SkillStats m_skillStats;
};


#endif 