#pragma once
#include "F_BulletBase.h"
#include "ParticleBatch2D.h"
#include "EnemyAmplifier.h"
class F_BulletStraight : public F_BulletBase
{
public:
	F_BulletStraight();
	~F_BulletStraight();

	F_BulletStraight(const glm::vec2 & pos, const glm::vec2 & dim, const Feintgine::Color & color,
		const std::string & animationPath, float depth, float dmg,
		Feintgine::ParticleBatch2D * hitParticleBatch = nullptr);

	virtual void update(float deltaTime, std::vector<F_BaseEnemy *> enemy, std::vector<EnemyGuardian *> guardians,
		std::vector<EnemyAmplifier *> amplifiers) override;

	virtual void draw(Feintgine::SpriteBatch & spriteBatch);

	void setParticleNum(int val);

	void setAngle(float angle);


	//glm::vec3 

protected :
	
	int m_particleNum = 1;

};

