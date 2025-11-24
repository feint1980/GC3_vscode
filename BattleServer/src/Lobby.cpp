#include "Lobby.h"

void Lobby::update(float deltaTime)
{
    //std::cout << " lobby " << m_id << "(" << m_name << ") update" << "\n";

}

std::string Lobby::getInfo() const
{
    return "lobby " + std::to_string(m_id) + " (" + m_name + ")";
} 