#pragma once
#include <glm/glm.hpp>
#include <DebugRender.h>
#include "F_BulletBase.h"
#include "IcedObject.h"
#include "F_Player.h"
#include <feint_common.h>
class IceWall
{
public:
	IceWall();
	~IceWall();


	void init();

	void registerAudioEngine(Feintgine::AudioEngine * audioEngine);

	void update(float deltaTime, F_Player & player);

	void setPos(const glm::vec2 & pos);

	void setDim(const glm::vec2 & dim);

	


	void freezeBullet( F_BulletBase * bullet);

	void drawDebug(Feintgine::DebugRender & debugRenderer);

	void draw(Feintgine::SpriteBatch & spriteBatch);

private :
	glm::vec2 m_pos;
	glm::vec2 m_dim;

	std::vector<IcedObject> m_iceObjects;

	std::vector<Feintgine::F_Sprite> m_sprites;

	std::vector<Feintgine::SoundEffect>  m_iceSoundEffects;
	
};

