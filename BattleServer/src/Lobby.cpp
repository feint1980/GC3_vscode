#include "Lobby.h"

bool Lobby::addPlayer(const std::string& guid, const std::string& name,const RakNet::SystemAddress & address)
{
    bool result = m_playerPair.addPlayer(guid, name, address);
    if(!result)
    {
        std::cout << "unable to add player "; // << address.address 
    }

    return result;
}

void Lobby::update(float deltaTime)
{

    // std::cout << " lobby " << m_id << "(" << m_name << ") update" << "\n";

}

std::string Lobby::getInfo() const
{
    return "lobby " + std::to_string(m_id) + " (" + m_name + ")";
} 

void Lobby::destroyLobby()
{
    m_state = LOBBY_STATE_CLOSED;

}


void Lobby::setLobbyState(LobbyState state)
{
    m_state = state;
    switch(state)
    {
        case LOBBY_STATE_OPEN:
            std::cout << "lobby " << m_id << " opened" << "\n";
            break;
        case LOBBY_STATE_CLOSED:
            std::cout << "lobby " << m_id << " closed" << "\n";
            break;
        case LOBBY_STATE_IN_GAME:
            std::cout << "lobby " << m_id << " in game" << "\n";
            
            break;
        case LOBBY_STATE_EXPIRING:
            std::cout << "lobby " << m_id << " expiring" << "\n";
            break;
        case LOBBY_STATE_LOCK_IN:
            std::cout << "lobby " << m_id << " lock in" << "\n";
            break;
        default:
            {
                std::cout << "lobby " << m_id << " unknown state" << "\n";
                break;
            }
    }
}
