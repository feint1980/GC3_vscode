
#include "BattleCharacter.h"
#include "Json2Struct.h"

BattleCharacter::BattleCharacter()
{
    
}

BattleCharacter::~BattleCharacter()
{

}


void BattleCharacter::init(const std::string & userID, const std::string & characterID, const std::string & statStr)
{

    m_userID = userID;
    m_characterID = characterID;
    CharacterStats result ;
    json j = json::parse(statStr);
    result = j.get<CharacterStats>();
    m_characterDesc.setCharacterStats(result);

    std::cout << "Stat check \n";
    std::cout << j.dump(4,'.') << "\n";

}