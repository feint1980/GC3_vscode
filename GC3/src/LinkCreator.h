#pragma once

#include "EnemyAmplifier.h"
#include "LinkAmplifier.h"
#include "F_Player.h"

class LinkCreator
{
public:
	LinkCreator();
	~LinkCreator();

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void update(float deltaTime, std::vector<EnemyAmplifier *> & amplifiers, std::vector<EnemyBulletBase *> enemy_bullets,  F_Player & player);

	void registerAudioEngine(Feintgine::AudioEngine * audioEngine);
	
	void drawDebug(Feintgine::DebugRender & debugRenderer);

	void createLink(EnemyAmplifier * amplifier);

	void clearList();

private: 

	std::vector<EnemyAmplifier *> m_amplifiers;

	std::vector<LinkAmplifier *> m_links;

	Feintgine::AudioEngine * m_audioEngine;


};

