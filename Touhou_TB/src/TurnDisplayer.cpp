
#include "TurnDisplayer.h"

TurnDisplayer::TurnDisplayer()
{
    
}

TurnDisplayer::~TurnDisplayer()
{

}

void TurnDisplayer::init()
{
    m_pos = glm::vec2(0.0f, 0.0f);
    m_defaultDimentions = glm::vec2(40.0f, 40.0f);
    m_portraitMap["S_Reimu"] = "./Assets/F_AObjects/Reimu_face.png";
    m_portraitMap["S_Meiling"] = "./Assets/F_AObjects/Meiling_face.png";
    m_portraitMap["S_Yukari"] = "./Assets/F_AObjects/Yukari_face.png";
    m_portraitMap["S_Patchouli"] = "./Assets/F_AObjects/Patchouli_face.png";

}


void TurnDisplayer::addPortrait(const std::string & characterID)
{
    std::shared_ptr<CharacterIcon> icon = std::make_shared<CharacterIcon>();
    icon->init(m_portraitMap[characterID], m_defaultDimentions);
    m_characters.push_back(icon);
}