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
    name,
    description,
    effect,
    quote,
    iconPath
};

struct SkillStats {
    std::string skillName;
    std::string description;
    std::string effect;
    std::string quote;
    std::string iconPath;
};

class SkillDesc {
public:
    SkillDesc();
    ~SkillDesc();
private:

    SkillStats m_
};


#endif 