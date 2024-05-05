#pragma once
#include "F_HomingBullet.h"
#include "AfterImageParticle.h"
#include "KanjiEffectManager.h"
#include <AudioEngine.h>
#include <EffectBatch.h>

class SealingAmulet : public F_HomingBullet
{
public:
	SealingAmulet();
	~SealingAmulet();

	virtual void update(float deltaTime, std::vector<FairyBase *> enemy) override;
	
	void initParticle();

	void setTimeLife(float ff);

	EnemyGuardian * getNearstGuardians(const glm::vec2 & pos, std::vector<EnemyGuardian *> guardians);

	void destroy();

	void setIsDone(bool val);

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void registerKanjiEffectManager(KanjiEffectManager * effectManager);

	void registerEffectBatch(Feintgine::EffectBatch * effectBatch);

	void registerAudioEngine(Feintgine::AudioEngine * audioEngine);

	void setPos(const glm::vec2 & pos);


	int getNearestTypeID(F_BaseEnemy * enemy, EnemyGuardian * guardian, EnemyAmplifier * amplifier);

private:

	AfterImageObject m_afterImageParticle;

	KanjiEffectManager * m_kanjiEffectManager_p;

	Feintgine::SoundEffect m_impactSound;

	Feintgine::EffectBatch * m_effectBatch;


};

