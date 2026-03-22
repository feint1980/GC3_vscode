
#ifndef TURN_DISPLAYER_H
#define TURN_DISPLAYER_H

#include "CharacterIcon.h"



class TurnDisplayer
{
public:
    TurnDisplayer();
    ~TurnDisplayer();

    void init();

    void addPortrait(const std::string & characterID);
    

private:
    
    std::vector< std::shared_ptr<CharacterIcon>> m_characters;
    std::unordered_map<std::string, std::shared_ptr<CharacterIcon>> m_charactersMap;
    glm::vec2 m_pos;
    glm::vec2 m_defaultDimentions;

    std::unordered_map<std::string, std::string> m_portraitMap;
};


#endif // TURN_DISPLAYER_H