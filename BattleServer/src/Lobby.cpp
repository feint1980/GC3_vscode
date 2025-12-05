#include "Lobby.h"

bool Lobby::addPlayer(RakNet::SystemAddress address)
{
    bool result = m_playerPair.addPlayer(address);
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