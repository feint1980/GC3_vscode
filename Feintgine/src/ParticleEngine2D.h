#ifndef _PARTICLEENGINE2D_H_
#define _PARTICLEENGINE2D_H_

#include <vector>
#include "LightBatch.h"
namespace Feintgine
{
	class ParticleBatch2D;
	class SpriteBatch;

	class ParticleEngine2D {
	public:
		ParticleEngine2D();
		~ParticleEngine2D();

		// After adding a particle batch, the ParticleEngine2D becomes
		// responsible for deallocation.
		void addParticleBatch(ParticleBatch2D* particleBatch);

		void update(float deltaTime);

		void draw(SpriteBatch* spriteBatch);
		void drawLight(LightBatch & lightBatch);
		

	private:
		std::vector<ParticleBatch2D*> m_batches;
	};
}
#endif 

