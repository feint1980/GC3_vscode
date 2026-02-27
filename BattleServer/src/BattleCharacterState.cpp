
#include "BattleCharacterState.h"

BattleCharacterState::BattleCharacterState()
{
    
}

BattleCharacterState::~BattleCharacterState()
{

}


void BattleCharacterState::init(const std::string & statStr)
{
    CharacterStats result ;
    json j = json::parse(statStr);
    result = j.get<CharacterStats>();
    m_characterDesc.setCharacterStats(result);

    std::cout << "Stat check \n";
    std::cout << j.dump(4,'.') << "\n";

}