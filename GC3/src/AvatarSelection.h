#pragma once
#include "CharacterAvatar.h"
#include <vector>

class AvatarSelection
{
public:
	AvatarSelection();
	~AvatarSelection();

	void addCharacter(const CharacterAvatar & character);

	void setVisible(bool val);

	void update(float delta);

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void handleInput(Feintgine::InputManager & inputManager, Feintgine::Camera2D & camera);

	void clearAllSelection();

	int getCurrentSelection() const { return m_currentSelection; }

private:

	std::vector<CharacterAvatar> m_characters;

	int m_currentSelection = -1;


};

