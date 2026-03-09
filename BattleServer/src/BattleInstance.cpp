

#include "BattleInstance.h"



BattleInstance::BattleInstance()
{

}


BattleInstance::~BattleInstance()
{

}


void BattleInstance::init( const std::string & player1, const std::string & player2)
{
    // m_lobbyID = lobbyID;
    m_battleCharacterManager.init(player1, player2);
    m_player1 = player1;
    m_player2 = player2;

}

