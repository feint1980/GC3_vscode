#include "AfterImageParticle.h"



AfterImageParticle::AfterImageParticle()
{
}


AfterImageParticle::~AfterImageParticle()
{
}

AfterImageObject::AfterImageObject()
{
	m_alphaRate = .5f;
	m_scale = glm::vec2(1.0f);
}

AfterImageObject::~AfterImageObject()
{

}


void AfterImageObject::init(glm::vec2 * pos, Feintgine::F_AnimatedObject * animatedObject, Feintgine::Color * color,
	float traceInterval, int numberOfTrace,float scaleRate)
{
	m_pos = pos;
	m_animatedObj = animatedObject;
	m_traceInterval = traceInterval;
	m_currentTraceTrack = 0.0f;
	m_numberOfTrace = numberOfTrace;
	m_color = color;
	m_scaleRate = scaleRate;
	for (int i = 0; i < m_traces.size(); i++)
	{		
		m_traces.erase(m_traces.begin() + i);		
	}
	m_traces.clear();
}

void AfterImageObject::init(glm::vec2 * pos,const Feintgine::F_Sprite &sprite, Feintgine::Color * color,
	float traceInterval , int numberOfTrace,float scaleRate)
{
	m_pos = pos;
	m_sprite = sprite;
	m_traceInterval = traceInterval;
	m_currentTraceTrack = 0.0f;
	m_numberOfTrace = numberOfTrace;
	m_color = color;
	m_scaleRate = scaleRate;

	for (int i = 0; i < m_traces.size(); i++)
	{
		m_traces.erase(m_traces.begin() + i);
	}
	m_traces.clear();
	
}



void AfterImageObject::init(glm::vec2 * pos, Feintgine::Color * color, float traceInterval, int numberOfTrace)
{
	m_pos = pos;
	m_traceInterval = traceInterval;
	m_currentTraceTrack = 0.0f;
	m_numberOfTrace = numberOfTrace;
	m_color = color;

	for (int i = 0; i < m_traces.size(); i++)
	{
		m_traces.erase(m_traces.begin() + i);
	}
	m_traces.clear();
}

void AfterImageObject::setTraceLifeTime(float val)
{
	m_traceLifeTime = val;
}

void AfterImageObject::draw(Feintgine::SpriteBatch & spriteBatch)
{
	for (int i = 0; i < m_traces.size(); i++)
	{
		m_traces[i].draw(spriteBatch);
	}
}

void AfterImageObject::update(float deltaTime, int animationIndex,float angle)
{
	m_currentTraceTrack += 0.1f * deltaTime;

	//std::cout << animatedObj.getCurrentAnimation()->getCurrentIndex() << " / " << animatedObj.getCurrentAnimation()->getSize() << "\n";

	if (m_animatedObj)
	{


		if (m_animatedObj->getCurrentAnimation())
		{

			if (&m_animatedObj->getCurrentAnimation()->getAnims()[animationIndex])
			{
				//m_sprite = m_animatedObj->getCurrentAnimation()->getAnims()[m_animatedObj->getCurrentAnimation()->getCurrentIndex()].sprite;
				//m_sprite = &m_animatedObj->getCurrentAnimation()->getAnims()[m_animatedObj->getCurrentAnimation()->getCurrentIndex()].sprite;
				//m_sprite = &m_animatedObj->getCurrentAnimation()->getCurrentAnim()->sprite;
				//std::cout << m_animatedObj->getCurrentAnimation()->getCurrentIndex() << "\n";
				m_sprite = m_animatedObj->getCurrentAnimation()->getAnims()[animationIndex].sprite;

				//std::cout << ">>update function \n";
				//std::cout << m_animatedObj->getCurrentAnimation()->getAnims()[animationIndex].sprite.getName() << "\n";
				//m_traces.push_back(trace);
			}
			
		}
	}
	
	if (m_currentTraceTrack >= m_traceInterval)
	{
		m_currentTraceTrack = 0.0f;
		AfterImageTrace trace;
	
// 		if (m_sprite)
// 		{
			//std::cout << "create \n";
		trace.init(m_sprite,*m_pos /*- (m_sprite.getDim() * 0.5f * m_scale)*/, m_scale
			, m_animatedObj->getColor(), m_traceLifeTime, angle);
		trace.setAlphaRate(m_alphaRate);
		trace.setScale(m_animatedObj->getScale());
		trace.setScaleRate(m_scaleRate);
		m_traces.push_back(trace);
//		}
		
	}
	for (int i = 0; i < m_traces.size(); i++)
	{
		m_traces[i].update(deltaTime);	
		if (m_traces[i].getLifeTime() < 0.0f)
		{
			m_traces.erase(m_traces.begin() + i);
		}
	}

}

void AfterImageObject::update(float deltaTime, const Feintgine::F_Sprite & sprite)
{
	m_currentTraceTrack += 0.1f * deltaTime;
	if (m_currentTraceTrack >= m_traceInterval)
	{
		m_currentTraceTrack = 0.0f;
		AfterImageTrace trace;

		// 		if (m_sprite)
		// 		{
		//std::cout << "create \n";
		trace.init(sprite, *m_pos - (m_sprite.getDim() * 0.5f * m_scale), m_scale
			, Feintgine::Color(255, 255, 255, 255), m_traceLifeTime, 0.0f);
		trace.setAlphaRate(m_alphaRate);
		trace.setScaleRate(m_scaleRate);
		m_traces.push_back(trace);
		//		}

	}
	for (int i = 0; i < m_traces.size(); i++)
	{
		m_traces[i].update(deltaTime);
		if (m_traces[i].getLifeTime() < 0.0f)
		{
			m_traces.erase(m_traces.begin() + i);
		}
	}
}

void AfterImageObject::update(const glm::vec2 pos , float deltaTime, const Feintgine::GLTexture & texture, float angle,bool isDone)
{
	m_currentTraceTrack += 0.1f * deltaTime;
	if (!isDone)
	{


		if (m_currentTraceTrack >= m_traceInterval)
		{
			m_currentTraceTrack = 0.0f;
			AfterImageTrace trace;

			// 		if (m_sprite)
			// 		{
			//std::cout << "create \n";
			trace.init(texture, pos - (glm::vec2(texture.width, texture.height) * 0.5f), m_scale
				, Feintgine::Color(255, 255, 255, 255), 4.0f, angle);
			trace.setAlphaRate(m_alphaRate);
			trace.setScaleRate(m_scaleRate);
			m_traces.push_back(trace);
			//		}

		}
	}
	for (int i = 0; i < m_traces.size(); i++)
	{
		m_traces[i].update(deltaTime);
		if (m_traces[i].getLifeTime() < 0.0f)
		{
			m_traces.erase(m_traces.begin() + i);
		}
	}
}

void AfterImageObject::setTotalTrace(int num)
{
	m_numberOfTrace = num;
}

void AfterImageObject::setTraceInterval(float val)
{
	m_traceInterval = val;
}

void AfterImageObject::setAlphaRate(float value)
{
	m_alphaRate = value;
}



void AfterImageObject::setScale(const glm::vec2 & scale)
{
	m_scale = scale;
}

void AfterImageObject::setScaleRate(float value)
{
	m_scaleRate = value;
}

void AfterImageObject::setOffsetPos(const glm::vec2 & pos)
{
	m_offsetPos = pos;
}

void AfterImageObject::clear()
{
	for (int i = 0; i < m_traces.size(); i++)
	{
		m_traces.erase(m_traces.begin() + i);
	}
	m_traces.clear();
}

void AfterImageObject::addTrace(const AfterImageTrace & trace)
{
	if (m_traces.size() > m_numberOfTrace -1)
	{
		std::swap(m_traces.front(), m_traces.back());
		m_traces.pop_back();
		//m_traces.swap(m_traces.begin(), m_traces[m_traces.size() -1])
	}
	//m_traces.push_back(trace);
}
// --------------------- AfterImage Object End ---------------------


















// --------------------- AfterImageTrace ---------------------
AfterImageTrace::AfterImageTrace()
{
	m_alphaRate = .5f;
}

AfterImageTrace::~AfterImageTrace()
{

}

void AfterImageTrace::init(const Feintgine::F_Sprite & sprite, const glm::vec2 & pos,
	const glm::vec2 & scale, const Feintgine::Color & color, float lifeTime, float angle, float scaleRate)
{
	m_sprite = sprite;
	m_pos = pos;
	m_scale = scale;
	m_color = color;
	m_lifeTime = lifeTime;
	m_angle = angle;
	drawMode = DRAW_MODE_F_SPRITE;
	m_scaleRate = scaleRate;
}

void AfterImageTrace::init(const Feintgine::GLTexture & texture, const glm::vec2 & pos, const glm::vec2 & scale, const Feintgine::Color & color, float lifeTime, float angle, float scaleRate)
{
	m_texture = texture;
	m_pos = pos;
	m_scale = scale;
	m_color = color;
	m_lifeTime = lifeTime;
	m_angle = angle;
	drawMode = DRAW_MODE_GL_TEXTURE;
	m_scaleRate = scaleRate;
}

void AfterImageTrace::draw(Feintgine::SpriteBatch & spriteBatch)
{
	switch (drawMode)
	{
	case DRAW_MODE_F_SPRITE:
	{
		
		glm::vec4 uvRect = m_sprite.getUV();
		glm::vec4 destRect(m_pos.x  -( m_scale.x * m_sprite.getDim().x * 0.5f), 
			m_pos.y - (m_scale.y * m_sprite.getDim().y * 0.5f), 
			m_scale.x * m_sprite.getDim().x
			, m_scale.y * m_sprite.getDim().y);

		spriteBatch.draw(destRect, uvRect, m_sprite.getTexture().id, 20, m_color, m_angle);
	}
	break;
	case DRAW_MODE_GL_TEXTURE:
	{
		glm::vec4 uvRect =glm::vec4(0,0,1,1);
		glm::vec4 destRect(m_pos.x, m_pos.y, m_scale.x * m_texture.width
			, m_scale.y * m_texture.height);

		spriteBatch.draw(destRect, uvRect, m_texture.id, 20, m_color, m_angle);
	}
	break;

	default:
		break;
	}
	
}

void AfterImageTrace::update(float deltaTime)
{
	m_lifeTime -= 0.1f * deltaTime;
	float alphaRate = 1.0f;
	if (m_lifeTime > 1.0f)
	{
		alphaRate = 1.0f;
	}
	else
	{
		alphaRate = m_lifeTime;
	}
	if(m_isShrink)
	{
		m_scale.x -= m_scaleRate * deltaTime;
		m_scale.y -= m_scaleRate * deltaTime;
		if (m_scale.x <= 0.0f || m_scale.y <= 0.0f)
		{
			m_scale.x = 0.0f;
			m_scale.y = 0.0f;
			m_isShrink = false;
		}
	}

	m_color.a = alphaRate * m_alphaRate;
}

void AfterImageTrace::setScale(const glm::vec2 & scale)
{
	m_scale = scale;
}

void AfterImageTrace::setAlphaRate(float value)
{
	m_alphaRate = value;
}
void AfterImageTrace::setScaleRate(float value)
{

	m_scaleRate = value;
	if(m_scaleRate != 0.0f)
	{
		m_isShrink = true;
	}
	
}
