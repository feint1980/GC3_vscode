#include "ParticleBatch2D.h"
//#include "GlobalValueClass.h"
namespace Feintgine
{
	ParticleBatch2D::ParticleBatch2D() {
		// Empty
	}


	ParticleBatch2D::~ParticleBatch2D() {
		delete[] m_particles;
	}

	void ParticleBatch2D::init(int maxParticles,
		float decayRate,
		const F_Sprite & sprite,
		std::function<void(Particle2D&,float)> updateFunc /* = defaultParticleUpdate */) {
		m_maxParticles = maxParticles;
		m_particles = new Particle2D[m_maxParticles];
		m_speciaParticles = new Particle2D[m_maxParticles];
		m_decayRate = decayRate;
		m_sprite = sprite;
		m_isAnimated = false;
		m_updateFunc = updateFunc;
	}

	void ParticleBatch2D::init(int maxParticles,
		float decayRate,
		const F_AnimatedObject & animatedObejct,
		std::function<void(Particle2D&,float)> updateFunc /* = defaultParticleUpdate */) {
		m_maxParticles = maxParticles;
		m_particles = new Particle2D[maxParticles];
		m_speciaParticles = new Particle2D[m_maxParticles];
		m_decayRate = decayRate;
		m_animatedObject = animatedObejct;
		m_animatedObject.playAnimation("idle");
		m_isAnimated = true;
		m_updateFunc = updateFunc;
		//m_animatedObject.playAnimation("idle");
	}

	void ParticleBatch2D::update(float deltaTime) {
		for (int i = 0; i < m_maxParticles; i++) {
			// Check if it is active
			if (m_particles[i].life > 0.0f) {
				// Update using function pointer
				m_updateFunc(m_particles[i],deltaTime);
				m_particles[i].life -= m_decayRate * deltaTime;
			}

			if (m_speciaParticles[i].life > 0.0f) {
				// Update using function pointer
				m_updateFunc(m_speciaParticles[i], deltaTime);
				m_speciaParticles[i].life -= m_decayRate * deltaTime;
			}
		}
	}

	void ParticleBatch2D::clear()
	{
		for (int i = 0; i < m_maxParticles; i++) {
			// Check if it is active
			m_particles[i].life = 0.0f;
			m_speciaParticles[i].life = 0.0f;

		}
	}

	void ParticleBatch2D::draw(SpriteBatch* spriteBatch) {
		//glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
		if (spriteBatch)
		{
			if (!m_isAnimated)
			{
				glm::vec4 uvRect = m_sprite.getUV();
				for (int i = 0; i < m_maxParticles; i++)
				{
					// Check if it is active
					auto& p = m_particles[i];
					if (p.life > 0.0f) {
						if (!justLight)
						{
							p.color.a = p.life * 0.75f;
						}
						else
						{
							p.color.a = 0;
						}

						glm::vec4 destRect(p.position.x, p.position.y, p.scale * m_sprite.getDim().x, p.scale * m_sprite.getDim().y);
						spriteBatch->draw(destRect, uvRect, m_sprite.getTexture().id, m_depth, p.color, p.angle);
					}
				}

				for (int i = 0; i < m_maxParticles; i++)
				{
					// Check if it is active
					auto& p = m_speciaParticles[i];
					if (p.life > 0.0f) {
						if (!justLight)
						{
							p.color.a = p.life * 0.75f;
						}
						else
						{
							p.color.a = 0;
						}

						glm::vec4 destRect(p.position.x, p.position.y, p.scale * m_sprite.getDim().x, p.scale * m_sprite.getDim().y);

						spriteBatch->draw(destRect, uvRect, m_sprite.getTexture().id, m_depth, p.color, p.angle);
					}
				}
			}
			else
			{
				for (int i = 0; i < m_maxParticles; i++)
				{
					// Check if it is active
					auto& p = m_particles[i];
					if (p.life > 0.0f) {
						if (!justLight)
						{
							p.color.a = p.life * 0.75f;
							m_animatedObject.setAlpha(0);
						}

						m_animatedObject.setPos(p.position);
						m_animatedObject.setScale(glm::vec2(p.scale));
						m_animatedObject.draw(*spriteBatch);
					}
				}
			}
		}
	}

// 	void ParticleBatch2D::draw(SpriteBatch & spriteBatch)
// 	{
// 		if (!m_isAnimated)
// 		{
// 			glm::vec4 uvRect = m_sprite.getUV();
// 			for (int i = 0; i < m_maxParticles; i++)
// 			{
// 				// Check if it is active
// 				auto& p = m_particles[i];
// 				if (p.life > 0.0f) {
// 					if (!justLight)
// 					{
// 						p.color.a = p.life * 0.75f;
// 					}
// 					else
// 					{
// 						p.color.a = 0;
// 					}
// 
// 					glm::vec4 destRect(p.position.x, p.position.y, p.scale * m_sprite.getDim().x, p.scale * m_sprite.getDim().y);
// 					spriteBatch.draw(destRect, uvRect, m_sprite.getTexture().id, m_depth, p.color, p.angle);
// 				}
// 			}
// 
// 			for (int i = 0; i < m_maxParticles; i++)
// 			{
// 				// Check if it is active
// 				auto& p = m_speciaParticles[i];
// 				if (p.life > 0.0f) {
// 					if (!justLight)
// 					{
// 						p.color.a = p.life * 0.75f;
// 					}
// 					else
// 					{
// 						p.color.a = 0;
// 					}
// 
// 					glm::vec4 destRect(p.position.x, p.position.y, p.scale * m_sprite.getDim().x, p.scale * m_sprite.getDim().y);
// 					spriteBatch.draw(destRect, uvRect, m_sprite.getTexture().id, m_depth, p.color, p.angle);
// 				}
// 			}
// 		}
// 		else
// 		{
// 			for (int i = 0; i < m_maxParticles; i++)
// 			{
// 				// Check if it is active
// 				auto& p = m_particles[i];
// 				if (p.life > 0.0f) {
// 					if (!justLight)
// 					{
// 						p.color.a = p.life * 0.75f;
// 						m_animatedObject.setAlpha(0);
// 					}
// 
// 					m_animatedObject.setPos(p.position);
// 					m_animatedObject.setScale(glm::vec2(p.scale));
// 					m_animatedObject.draw(spriteBatch);
// 				}
// 			}
// 		}
// 	}

	void ParticleBatch2D::drawLight(LightBatch & lightBatch)
	{
		for (int i = 0; i < m_maxParticles; i++) 
		{
			auto& p = m_particles[i];
			if (p.life > 0.0f) {
				t_attentionua = m_attentionua - (m_attentionua *0.6f) *  m_lightScale;
				lightBatch.addLight(p.position,
					glm::vec4(p.color.r,
						p.color.g,
						p.color.b,
						1.0f),
					1.0f / t_attentionua *  1.0f / std::min(1.0f, p.life));
			}
		}
		for (int i = 0; i < m_maxParticles; i++) 
		{
			auto& p = m_speciaParticles[i];
			if (p.life > 0.0f) {
				t_attentionua = m_attentionua - (m_attentionua *0.6f) *  m_lightScale;
				lightBatch.addLight(p.position,
					glm::vec4(p.color.r,
						p.color.g,
						p.color.b,
						1.0f),
					1.0f / t_attentionua *  1.0f /std::min(1.0f, p.life));
			}
		}

	}

	void ParticleBatch2D::addParticle(const glm::vec2& position,
		const glm::vec2& velocity,
		const Color& color,
		float scale) {
		int particleIndex = findFreeParticle();

		auto& p = m_particles[particleIndex];

		p.damp = 0.0f;
		p.life = 1.0f;
		p.position = position;
		p.velocity = velocity;
		p.color = color;
		p.scale = scale;
		m_attentionua = glm::vec3(14.0f, 10.0f, 15.0f);
		//std::cout << "total " << particleIndex << "\n";

	}


	void ParticleBatch2D::addParticle(const glm::vec2& position,
		const glm::vec2& velocity, const Color& color,
		float width, glm::vec3 attenuation)
	{
		int particleIndex = findFreeParticle();

		auto& p = m_particles[particleIndex];

		p.damp = 0.0f;
		p.life = 1.4f;
		p.position = position;
		p.velocity = velocity;
		p.color = color;
		p.color.a *= 0.25f;
		p.scale = 1.0f;
		m_attentionua = attenuation;
		justLight = true;
	}

	void ParticleBatch2D::addParticle(const glm::vec2& position,
		const glm::vec2& velocity, const Color& color, 
		float scale, float lifeTime, const glm::vec3 & attenuation)
	{
		int particleIndex = findFreeParticle();

		auto& p = m_particles[particleIndex];

	
		p.damp = 0.0f;
		p.life = lifeTime	;
		p.position = position;
		p.velocity = velocity;
		p.color = color;
		if (scale == 0)
		{
			justLight = true;
		}
		p.scale = scale;
		m_attentionua = attenuation;//glm::vec3(14.0f, 10.0f, 15.0f);
	}
	

	void ParticleBatch2D::addParticle(bool special, const glm::vec2& position,
		const glm::vec2& velocity, const Color& color, float scale,
		float lifeTime, const glm::vec3 & attenuation)
	{
		int particleIndex = findFreeParticle();

		auto& p = m_speciaParticles[particleIndex];

		p.damp = 0.0f;
		p.life = lifeTime;
		p.position = position;
		p.velocity = velocity;
		p.color = color;
	
		justLight = special;
		
		p.scale = scale;
		m_attentionua = attenuation;//glm::vec3(14.0f, 10.0f, 15.0f);
	}
	
	void ParticleBatch2D::setLightScale(float val)
	{
		m_lightScale = val;
	}

	int ParticleBatch2D::findFreeParticle() {

		for (int i = m_lastFreeParticle; i < m_maxParticles; i++) {
			if (m_particles[i].life <= 0.0f) {
				m_lastFreeParticle = i;
				return i;
			}
		}

		for (int i = 0; i < m_lastFreeParticle; i++) {
			if (m_particles[i].life <= 0.0f) {
				m_lastFreeParticle = i;
				return i;
			}
		}

		// No particles are free, overwrite first particle
		return 0;
	}
}


