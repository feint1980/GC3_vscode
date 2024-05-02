#pragma once
#include "Yin_Yang_Orb.h"
#include <EffectBatch.h>
class Yin_Yang_Orb_Ex : public Yin_Yang_Orb
{
public:
	Yin_Yang_Orb_Ex();
	~Yin_Yang_Orb_Ex();

	void registerEffectBatch(Feintgine::EffectBatch * effectBatch);

	void update(float deltaTime, std::vector<FairyBase *>  enemy, std::vector<EnemyBulletBase * > bullets);
private :

	Feintgine::EffectBatch * m_effectBatch;
};

