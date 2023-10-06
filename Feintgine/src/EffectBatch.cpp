#include "EffectBatch.h"

namespace Feintgine
{



	EffectBatch::EffectBatch()
	{
	}


	EffectBatch::~EffectBatch()
	{
	}

	void EffectBatch::initEffectBatch(FrameBufferScreen * frameBufferScreen, Camera2D * camera)
	{
		m_frameBufferScreen = frameBufferScreen;
		m_camera = camera;
	}

	void EffectBatch::addRippleEffect(const glm::vec2 & pos, float size, float freq, float lifeTime, float sizeRate, float freqRate)
	{

// 		glm::vec2 convertPos =  m_camera->converWorldToScreen(pos);
// 
// 		glm::vec2 total = glm::vec2(pos.x / (float)m_frameBufferScreen->getWidth(), pos.y / (float)m_frameBufferScreen->getHeight());
// 		
// 		convertPos = glm::vec2( (1.0f  - total.x - 0.5f ) * m_camera->getScale() ,(1.0f - total.y - 0.5f)  *m_camera->getScale());
	
		glm::vec2 * tPos = new glm::vec2(0);

		 // Unsed stuff
		//std::cout << feint_common::Instance()->convertVec2toString(convertPos) << "\n";
		//glm::vec4 total = glm::vec4(convertPos.x, convertPos.y, 0, 1.0f) *m_camera->getCameraMatrix();
		//std::cout << m_camera->getScale() << "\n";

		//m_ripples.emplace_back(convertPos, size, freq, lifeTime);
		//convertPos.x = 1.0f - (convertPos.x / (float)m_frameBufferScreen->getWidth());
		//convertPos.y = 0.5f * m_camera->getScale() + (convertPos.y / (float)m_frameBufferScreen->getWidth())  ;


		m_ripplePos.push_back(tPos);
		//m_ripplePos.push_back(convertPos);
		m_rippleSize.push_back(size * m_camera->getScale());
		m_rippleFreq.push_back(freq * m_camera->getScale());
		m_rippleSizeRate.push_back(sizeRate);
		m_rippleFreqRate.push_back(freqRate);
		m_rippleLifeTime.push_back(lifeTime );
	}

	void EffectBatch::addRippleEffectContinuos(glm::vec2 * pos, float size, float freq, float lifeTime, float sizeRate, float freqRate)
	{
		//glm::vec2 * tPos = new glm::vec2(0);
		//tPos = pos;
		m_ripplePos.push_back(pos);
		//m_ripplePos.push_back(convertPos);
		m_rippleSize.push_back(size * m_camera->getScale());
		m_rippleFreq.push_back(freq * m_camera->getScale());
		m_rippleSizeRate.push_back(sizeRate);
		m_rippleFreqRate.push_back(freqRate);
		m_rippleLifeTime.push_back(lifeTime);
	}

	void EffectBatch::draw()
	{
		// lazy code

		std::vector<glm::vec2> m_tRipplePos;
		
		for (int i = 0; i < m_ripplePos.size(); i++)
		{
			if (m_ripplePos[i])
			{


				glm::vec2 pos = *m_ripplePos[i];
				glm::vec2 convertPos = m_camera->converWorldToScreen(pos);

				glm::vec2 total = glm::vec2(pos.x / (float)m_frameBufferScreen->getWidth(), pos.y / (float)m_frameBufferScreen->getHeight());

				convertPos = glm::vec2((1.0f - total.x - 0.5f) * m_camera->getScale(), (1.0f - total.y - 0.5f)  *m_camera->getScale());

				m_tRipplePos.push_back(convertPos);
			}
		}
		

		GLint ripplePos = m_frameBufferScreen->getUniformLocation("ripplePos");
		glUniform2fv(ripplePos, m_tRipplePos.size(), reinterpret_cast<GLfloat *>(m_tRipplePos.data()));

		GLint rippleSize = m_frameBufferScreen->getUniformLocation("rippleSize");
		glUniform1fv(rippleSize, m_rippleSize.size(), reinterpret_cast<GLfloat *>(m_rippleSize.data()));

		GLint rippleFreq = m_frameBufferScreen->getUniformLocation("rippleFreq");
		glUniform1fv(rippleFreq, m_rippleFreq.size(), reinterpret_cast<GLfloat *>(m_rippleFreq.data()));

		GLint rippleLifeTime = m_frameBufferScreen->getUniformLocation("rippleLifeTime");
		glUniform1fv(rippleLifeTime, m_rippleLifeTime.size(), reinterpret_cast<GLfloat *>(m_rippleLifeTime.data()));


		GLint countIndex = m_frameBufferScreen->getUniformLocation("rippleCount");
		glUniform1i(countIndex, m_tRipplePos.size());

		GLint scaleIndex = m_frameBufferScreen->getUniformLocation("rippleScale");
		glUniform1f(scaleIndex,m_camera->getScale());


	}

	void EffectBatch::update(float deltaTime)
	{
		for (int i = 0; i < m_rippleLifeTime.size(); i++)
		{
			if (m_rippleLifeTime[i] < 18.5f)
			{
				m_rippleLifeTime[i] += 0.5f * deltaTime;
				m_rippleSize[i] += m_rippleSizeRate[i] * deltaTime;
				m_rippleFreq[i] += m_rippleFreqRate[i] * deltaTime;
			}
			else
			{
				//m_ripples.erase(m_ripples.begin() + i);
				//m_ripples.r
				//m_ripplePos[i] = nullptr;
				m_ripplePos.erase(m_ripplePos.begin() + i);
				m_rippleSize.erase(m_rippleSize.begin() + i);
				m_rippleFreq.erase(m_rippleFreq.begin() + i);
				m_rippleLifeTime.erase(m_rippleLifeTime.begin() + i);
				m_rippleSizeRate.erase(m_rippleSizeRate.begin() + i);
				m_rippleFreqRate.erase(m_rippleFreqRate.begin() + i);
				
			}
		}
	}

	void EffectBatch::stopRippleEffect(glm::vec2 * pos)
	{
		for (int i = 0; i < m_ripplePos.size(); i++)
		{
			if (m_ripplePos[i] == pos)
			{
// 				m_ripplePos.erase(m_ripplePos.begin() + i);
// 				m_rippleSize.erase(m_rippleSize.begin() + i);
// 				m_rippleFreq.erase(m_rippleFreq.begin() + i);
// 				m_rippleLifeTime.erase(m_rippleLifeTime.begin() + i);
// 				m_rippleSizeRate.erase(m_rippleSizeRate.begin() + i);
// 				m_rippleFreqRate.erase(m_rippleFreqRate.begin() + i);
				m_rippleLifeTime[i] = -35.0f;

				return;
			}
		}
	}

}