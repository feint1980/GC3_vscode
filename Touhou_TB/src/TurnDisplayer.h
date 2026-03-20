
#ifndef TURN_DISPLAYER_H
#define TURN_DISPLAYER_H

#include "CharacterIcon.h"

class TurnDisplayer
{
public:
    TurnDisplayer();
    ~TurnDisplayer();

    void init();

    // void add

private:
    
    std::vector< std::shared_ptr<CharacterIcon>> m_characters;
    std::unordered_map<std::string, std::shared_ptr<CharacterIcon>> m_charactersMap;

};


#endif // TURN_DISPLAYER_H