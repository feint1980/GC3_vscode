

#ifndef BATTLECHARACTERSTATE_H
#define BATTLECHARACTERSTATE_H

#include "CharacterDes.h"


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