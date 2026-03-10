#include "BattleInstanceCharacterManager.h"

BattleInstanceCharacterManager::BattleInstanceCharacterManager()
{

}


BattleInstanceCharacterManager::~BattleInstanceCharacterManager()
{

}

void BattleInstanceCharacterManager::init(const std::string & player1, const std::string & player2)
{
    m_player1 = player1;
    m_player2 = player2;

    m_characterLists.reserve(2);

    m_characterLists[m_player1].reserve(4);
    m_characterLists[m_player2].reserve(4);

    m_characterMap.reserve(2);
    m_characterMap[m_player1].reserve(4);
    m_characterMap[m_player2].reserve(4);

}


void BattleInstanceCharacterManager::initFormation(const std::string & playerID, std::vector<std::string> characters)
{
    if(characters.size() > 4)
    {
        std::cout << "BattleInstanceCharacterManager::initFormation was called but incorrect, there should be 4 (or less) characters" << "\n";
        return;
    }

    // for(int i = 0; i < characters.size(); i++)
    // {
    //     addCharacter(playerID, characters[i]);
    // }

}

void BattleInstanceCharacterManager::addCharacter(const std::string & playerID, const std::string & characterID, const std::string & characterStat )
{
    BattleCharacter characterState;
    characterState.init(playerID,characterID,characterStat);
    if(m_characterLists[playerID].size() >= 4)
    {
        std::cout << "BattleInstanceCharacterManager::initFormation was called but incorrect, there should be 4 characters" << "\n";
        return;
    }
    m_characterLists[playerID].push_back(characterState);
    m_characterMap[playerID][characterState.getCharacterID()] = m_characterLists[playerID].size() - 1;
    if(m_characterMap[playerID][characterState.getCharacterID()] < 0 || 
        m_characterMap[playerID][characterState.getCharacterID()] > 4
    ) 
    {
        std::cout << "BattleInstanceCharacterManager::initFormation was called but incorrect, map index out of range ("<< m_characterMap[playerID][characterState.getCharacterID()] << ")\n";
    }

    // m_characterMap[playerID][characterState] = characterState;
}

BattleCharacter & BattleInstanceCharacterManager::getCharacterState(const std::string & playerID, const std::string & characterID)
{
    int index = m_characterMap[playerID][characterID];
    return m_characterLists[playerID][index];
}

BattleCharacter & BattleInstanceCharacterManager::getCharacterState(const std::string & playerID,int index)
{
    return m_characterLists[playerID][index];
}
