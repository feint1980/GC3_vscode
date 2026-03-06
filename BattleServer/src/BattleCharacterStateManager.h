
#ifndef BATTLECHARACTERSTATEMANAGER_H
#define BATTLECHARACTERSTATEMANAGER_H

#include "BattleCharacterState.h"
#include <unordered_map>
#include <vector>

class BattleCharacterStateManager
{
public:
    BattleCharacterStateManager();
    ~BattleCharacterStateManager();

    void init(const std::string & player1, const std::string & player2);

    void initFormation(const std::string & playerID, std::vector<std::string> characters);

    void addCharacter(const std::string & playerID, const std::string & characterStat );

    BattleCharacterState & getCharacterState(const std::string & playerID, const std::string & characterID);

    BattleCharacterState & getCharacterState(const std::string & playerID,int index);
    

private:
    std::unordered_map<std::string, std::vector<BattleCharacterState>> m_stateLists;
    std::unordered_map<std::string, std::unordered_map<std::string, int>> m_stateMaps;


    std::string m_player1;
    std::string m_player2;
};


#endif