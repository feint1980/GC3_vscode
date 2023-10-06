#ifndef _PARTICLEBATCH2D_H_
#define _PARTICLEBATCH2D_H_

#include <functional>
#include <glm/glm.hpp>
#include "Vertex.h"
#include "SpriteBatch.h"
#include "GLTexture.h"
#include <string>
#include "TextureCache.h"
#include "ResourceManager.h"
#include "F_Sprite.h"
#include "F_AnimatedObject.h"
#include "LightBatch.h"
#include "feint_common.h"
namespace Feintgine
{
	class Particle2D {
	public:
		glm::vec2 position = glm::vec2(0.0f);
		glm::vec2 velocity = glm::vec2(0.0f);
		Color color;
		float life = 0.0f;
		float scale = 0.0f;
		float angle = 0.0f;
		float damp = 0.1f;
	};

	// Default function pointer
	inline void defaultParticleUpdate(Particle2D& particle,float deltaTime) {
		particle.position += particle.velocity * deltaTime;
		
	}

	class ParticleBatch2D {
	public:
		ParticleBatch2D();
		~ParticleBatch2D();

		void init(int maxParticles,
			float decayRate,
			const F_Sprite & sprite,
			std::function<void(Particle2D&,float)> updateFunc = defaultParticleUpdate);

		void init(int maxParticles,
			float decayRate,
			const F_AnimatedObject & animatedObject,
			std::function<void(Particle2D&,float)> updateFunc = defaultParticleUpdate);

		void update(float deltaTime);

		void clear();

		void draw(SpriteBatch* spriteBatch);
		//void draw(SpriteBatch & spriteBatch);

		void drawLight(LightBatch & lightBatch);

		void addParticle(const glm::vec2& position,
			const glm::vec2& velocity,
			const Color& color,
			float width);

		void addParticle(const glm::vec2& position,
			const glm::vec2& velocity,
			const Color& color,
			float width,float lifeTime,const glm::vec3 & attenuation);

		void addParticle(bool special, const glm::vec2& position,
			const glm::vec2& velocity,
			const Color& color,
			float width, float lifeTime, const glm::vec3 & attenuation);

		void addParticle(const glm::vec2& position,
			const glm::vec2& velocity,
			const Color& color,
			float width,glm::vec3 attenuation);

		void setLightScale(float val);

	private:
		int findFreeParticle();
		float m_depth = 3;
		std::function<void(Particle2D&,float)> m_updateFunc; ///< Function pointer for custom updates
		float m_decayRate = 0.1f;
		Particle2D* m_particles = nullptr;

		Particle2D* m_speciaParticles = nullptr;
		int m_maxParticles = 0;
		int m_lastFreeParticle = 0;
		F_Sprite m_sprite;
		bool m_isAnimated = false;
		F_AnimatedObject m_animatedObject;
		glm::vec3 m_attentionua  = glm::vec3(14.0f, 10.0f, 15.0f);
		glm::vec3 t_attentionua;
		float m_lightScale = 1.0f;
		bool justLight = false;

	};
}

#endif 
