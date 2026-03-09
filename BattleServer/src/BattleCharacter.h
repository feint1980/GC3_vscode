

#ifndef BATTLECHARACTER_H
#define BATTLECHARACTER_H

#include "CharacterDes.h"


class BattleCharacter
{
public:
    BattleCharacter();
    ~BattleCharacter();

    void init(const std::string & userID, const std::string & characterID, const std::string & statStr);

    std::string getCharacterID() const { return m_characterDesc.getCharacterStats().ID; }

private :
    CharacterDesc m_characterDesc;
    std::string m_characterID;
    std::string m_userID;
};


#endif // BATTLECHARACTER_H