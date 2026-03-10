

// Map 
// BattleInstance
//  ├── BattleStateManager
//  ├── TurnScheduler
//  ├── ActionValidator
//  ├── ActionResolver
//  ├── DamageCalculator
//  ├── HitCalculationSystem
//  ├── RNG
//  ├── CharacterBattleState
//  ├── StatSystem
//  ├── StatusSystem
//  ├── Battlefield <---- currently work here
//  ├── MovementSystem
//  ├── EventQueue
//  ├── VictorySystem
//  ├── LuaSkillEngine
//  └── BattleNetworkController


/*
    My Battle Plan.
    Created when the lobby enter in-game mode : 
    Client with locked in formation -> saved
    then Initialize BattleInstance with saved formation 
*/

#include "BattleInstanceCharacterManager.h"


class BattleInstance
{
public:
    BattleInstance();
    ~BattleInstance();

    void init(const std::string & player1, const std::string & player2);

private:

    BattleInstanceCharacterManager m_battleCharacterManager;

    // uint64_t m_lobbyID = 0;
    std::string m_player1 = "";
    std::string m_player2 = "";

};
