#pragma once
#include "FrameBufferScreen.h"
#include <vector>
#include "Camera2D.h"

namespace Feintgine
{



	struct Fx_Light
	{
		glm::vec2 lightPos;
		glm::vec4 lightColor;
		glm::vec3 m_attenuation;
	};


	struct Ripple
	{
		glm::vec2 ripplePos;
		float rippleSize;
		float rippleFreq;
		float rippleLifeTime;

		Ripple(const glm::vec2 pos, float size,float freq, float lifeTime)
		{
			ripplePos = pos;
			rippleSize = size;
			rippleFreq = freq;
			rippleLifeTime = lifeTime;
		}
	};

	class EffectBatch
	{
	public:
		EffectBatch();
		~EffectBatch();

		void initEffectBatch(FrameBufferScreen * frameBufferScreen, Camera2D * camera);

		void addRippleEffect(glm::vec2 pos, float size, float freq, float lifeTime, float sizeRate, float freqRate);

		void addRippleEffectContinuos(glm::vec2 * pos, float size, float freq, float lifeTime, float sizeRate, float freqRate);
		void stopRippleEffect(glm::vec2 * pos);
		void draw();

		void update(float deltaTime);


		

	private:
		FrameBufferScreen * m_frameBufferScreen;

		std::vector<Ripple> m_ripples;
		std::vector<glm::vec2 * > m_ripplePos;
		std::vector<float> m_rippleSize;
		std::vector<float> m_rippleFreq;
		std::vector<float> m_rippleLifeTime;
		std::vector<float> m_rippleSizeRate;
		std::vector<float> m_rippleFreqRate;

		//std::vector<glm::vec2*> m_contiRipplePos;
		//std::vector<float> m_contiRippleSize;
		//std::vector<float> m_contiRippleFreq;
		//std::vector<float> m_contiRippleLifeTime;
		Camera2D * m_camera;

	};
}
