

#include "BattleInstance.h"



BattleInstance::BattleInstance()
{

}


BattleInstance::~BattleInstance()
{

}


void BattleInstance::init(const std::string & player1, const std::string & player2)
{
    m_battleCharacterStateManager.init(player1, player2);
}