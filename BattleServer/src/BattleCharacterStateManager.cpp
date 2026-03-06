#include "BattleCharacterStateManager.h"

BattleCharacterStateManager::BattleCharacterStateManager()
{

}


BattleCharacterStateManager::~BattleCharacterStateManager()
{

}

void BattleCharacterStateManager::init(const std::string & player1, const std::string & player2)
{
    m_player1 = player1;
    m_player2 = player2;

    m_stateLists.reserve(2);

    m_stateLists[m_player1].reserve(4);
    m_stateLists[m_player2].reserve(4);

    m_stateMaps.reserve(2);
    m_stateMaps[m_player1].reserve(4);
    m_stateMaps[m_player2].reserve(4);

}


void BattleCharacterStateManager::initFormation(const std::string & playerID, std::vector<std::string> characters)
{
    if(characters.size() > 4)
    {
        std::cout << "BattleCharacterStateManager::initFormation was called but incorrect, there should be 4 (or less) characters" << "\n";
        return;
    }

    for(int i = 0; i < characters.size(); i++)
    {
        addCharacter(playerID, characters[i]);
    }

}

void BattleCharacterStateManager::addCharacter(const std::string & playerID, const std::string & characterStat )
{
    BattleCharacterState characterState;
    characterState.init(characterStat);
    if(m_stateLists[playerID].size() >= 4)
    {
        std::cout << "BattleCharacterStateManager::initFormation was called but incorrect, there should be 4 characters" << "\n";
        return;
    }
    m_stateLists[playerID].push_back(characterState);
    m_stateMaps[playerID][characterState.getCharacterID()] = m_stateLists[playerID].size() - 1;
    if(m_stateMaps[playerID][characterState.getCharacterID()] < 0 || 
        m_stateMaps[playerID][characterState.getCharacterID()] > 4
    ) 
    {
        std::cout << "BattleCharacterStateManager::initFormation was called but incorrect, map index out of range ("<< m_stateMaps[playerID][characterState.getCharacterID()] << ")\n";
    }

    // m_stateMaps[playerID][characterState] = characterState;
}

BattleCharacterState & BattleCharacterStateManager::getCharacterState(const std::string & playerID, const std::string & characterID)
{
    int index = m_stateMaps[playerID][characterID];
    return m_stateLists[playerID][index];
}

BattleCharacterState & BattleCharacterStateManager::getCharacterState(const std::string & playerID,int index)
{
    return m_stateLists[playerID][index];
}
