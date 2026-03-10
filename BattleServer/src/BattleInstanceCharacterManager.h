
#ifndef BATTLEINSTANCECHARACTERMANAGER_H
#define BATTLEINSTANCECHARACTERMANAGER_H

#include "BattleCharacter.h"
#include <unordered_map>
#include <vector>

class BattleInstanceCharacterManager
{
public:
    BattleInstanceCharacterManager();
    ~BattleInstanceCharacterManager();

    void init(const std::string & player1, const std::string & player2);

    void initFormation(const std::string & playerID, std::vector<std::string> characters);

    void addCharacter(const std::string & playerID, const std::string & characterID, const std::string & characterStat );

    BattleCharacter & getCharacterState(const std::string & playerID, const std::string & characterID);

    BattleCharacter & getCharacterState(const std::string & playerID,int index);
    

private:
    std::unordered_map<std::string, std::vector<BattleCharacter>> m_characterLists;
    std::unordered_map<std::string, std::unordered_map<std::string, int>> m_characterMap;


    std::string m_player1;
    std::string m_player2;
};


#endif //BATTLEINSTANCECHARACTERMANAGER_H