#include "AvatarSelection.h"



AvatarSelection::AvatarSelection()
{
}


AvatarSelection::~AvatarSelection()
{
}

void AvatarSelection::addCharacter(const CharacterAvatar & character)
{
	m_characters.push_back(character);
}

void AvatarSelection::setVisible(bool val)
{

	
	for (int i = 0; i < m_characters.size(); i++)
	{
		m_characters[i].setVisible(val);
	}
}

void AvatarSelection::update(float delta)
{
	for (int i = 0; i < m_characters.size(); i++)
	{
		m_characters[i].update(delta);
	}
	if (m_currentSelection != -1)
	{
		for (int i = 0; i < m_characters.size(); i++)
		{
			m_characters[i].setSelected(false);
		}
		m_characters[m_currentSelection].setSelected(true);
	}
	else
	{
		for (int i = 0; i < m_characters.size(); i++)
		{
			m_characters[i].setSelected(false);
		}
	}
}

void AvatarSelection::draw(Feintgine::SpriteBatch & spriteBatch)
{
	for (int i = 0; i < m_characters.size(); i++)
	{
		m_characters[i].draw(spriteBatch);
	}
}

void AvatarSelection::handleInput(Feintgine::InputManager & inputManager, Feintgine::Camera2D & camera)
{
// 	std::cout << feint_common::Instance()->convertiVec2toString(
// 		inputManager.getMouseCoords()) << "\n";
	glm::vec2 mousePos = inputManager.getMouseCoords();

	mousePos = camera.convertScreenToWorld(mousePos);
	/*if (mousePos.x > 1050 && mousePos.x < 1290)
	{
		if (mousePos.y > 25 && mousePos.y < 230)
		{
			m_currentSelection = 0;
		}
		else if (mousePos.y > 230 && mousePos.y < 460)
		{
			m_currentSelection = 1;
		}
		else if (mousePos.y > 460 && mousePos.y < 749)
		{
			m_currentSelection = 2;
		}
		else
		{
			m_currentSelection = -1;
		}
	}
	else
	{
		m_currentSelection = -1;
	}*/

	for (int i = 0; i < m_characters.size(); i++)
	{
		if (m_characters[i].handleMouseInput(mousePos))
		{
			m_currentSelection = i;
			return;
		}
	}
	m_currentSelection = -1;

}

void AvatarSelection::clearAllSelection()
{
	m_currentSelection = -1;
}

