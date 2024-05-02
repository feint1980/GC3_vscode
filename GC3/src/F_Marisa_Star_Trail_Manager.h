#pragma once
#include "F_Marisa_Star_Trail.h"
#include "F_Marisa_Laser_trail.h"
class F_Marisa_Star_Trail_Manager
{
public:
	F_Marisa_Star_Trail_Manager();
	~F_Marisa_Star_Trail_Manager();

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void drawLight(Feintgine::LightBatch & lightBatch);

	void update(const glm::vec2 & pos,float deltaTime, std::vector<FairyBase *>  enemy,
		std::vector<EnemyBulletBase * > bullets);

	void init(const Feintgine::F_AnimatedObject & starAnim,float trailThreshold);

	void setTrailThreshold(float val);

	void registerParticleBatch(Feintgine::ParticleBatch2D * particleBatch);

	void spawnLaserTrait(const glm::vec2 & pos,
		const glm::vec3 & attenuation, int colorFlag,
		Feintgine::Color color,float angle);


	Feintgine::Color getStarColor(int index);

	void setLeaveTrail(bool val);
	
	float getAngleSpawn(int index);

private :

	glm::vec2 m_pos;

	bool m_isLeaveTrail = false;

	float m_currentTrailCounter = 0.0f;
	float m_trailThreshold = 0.25f;
	int m_count = 0;
	Feintgine::F_AnimatedObject m_starAnim;


	Feintgine::ParticleBatch2D * m_hitParticleBatch = nullptr;

	std::vector<F_Marisa_Star_Trail *> m_trails;

	std::vector<F_Marisa_Laser_trail*> m_laserTrails;


};

