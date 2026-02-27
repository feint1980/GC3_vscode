

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







#include "BattleCharacterStateManager.h"


class BattleInstance
{
public:
    BattleInstance();
    ~BattleInstance();

    void init(const std::string & player1, const std::string & player2);

private:
    BattleCharacterStateManager m_battleCharacterStateManager;


};
