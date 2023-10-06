#include "SpellcardIcon.h"



SpellcardIcon::SpellcardIcon()
{
}


SpellcardIcon::~SpellcardIcon()
{

}

void SpellcardIcon::draw(Feintgine::SpriteBatch & spriteBatch)
{
	glm::vec4 desRect;
	desRect.x = m_pos.x - (m_sprite.getDim().x * m_scale / 2.0f);
	desRect.y = m_pos.y - (m_sprite.getDim().y * m_scale / 2.0f);
	desRect.z = m_scale * m_sprite.getDim().x;
	desRect.w = m_scale * m_sprite.getDim().y;

	spriteBatch.draw(desRect, m_sprite.getUV(),
		m_sprite.getTexture().id, m_depth, m_color, 0);
	
	
	m_frame.draw(spriteBatch);

	m_frame.setPos(m_pos);
	m_frame.setScale(glm::vec2(m_animScale * m_scale));
}


void SpellcardIcon::init(const Feintgine::F_Sprite & sprite, 
	const glm::vec2 dim, const Feintgine::Color & color)
{
	m_dim = dim;
	m_sprite = sprite;
	m_color = color;
	m_frame.init("Assets/F_AObjects/spellcard_frame.xml");
	m_frame.playAnimation("ready");
	m_frame.setColor(Feintgine::Color(500, 500, 500, 255));


	m_scale = 1.0f;
	m_targetScale;
	transitionflag = 0;

	m_depth = 40.0f;

	m_animScale = 4.0f;

	m_isMoving = false;

	scaleRate = 0.025f;

	m_isFocus = false;
	//m_prevPos = m_pos;
}

void SpellcardIcon::setID(SPELL_ID id)
{
	m_id = id;
}

void SpellcardIcon::setPos(const glm::vec2 & pos, bool motion /*= true*/)
{
	//m_pos = pos;

	t_pos = pos;
	m_isMoving = motion;
	if (motion)
	{
		m_vector = t_pos - m_pos;
	}
	else
	{
		m_pos = pos;
	}
	
}

void SpellcardIcon::setColor(const Feintgine::Color color)
{
	m_color = color;
}

void SpellcardIcon::setScale(float scale)
{
	//m_scale = scale;
	m_targetScale = scale;
	if (m_targetScale > m_scale)
	{
		transitionflag = 1;
	}
	else if (m_targetScale < m_scale)
	{
		transitionflag = 2;
	}
}

void SpellcardIcon::update(float deltaTime)
{

	switch (transitionflag)
	{
	case 1:
		if (m_scale < m_targetScale)
		{
			m_scale += scaleRate * deltaTime;
		}
		else
		{
			m_scale = m_targetScale;
			transitionflag = 0;
		}
		break;
	case 2:
		if (m_scale > m_targetScale)
		{
			m_scale -= scaleRate * deltaTime;
		}
		else
		{
			m_scale = m_targetScale;
			transitionflag = 0;
		}
		break;
	default:
		break;
	}

	if (m_isMoving)
	{
		m_pos += m_vector * 0.01f * glm::distance(m_pos, t_pos) * deltaTime;
		if (glm::distance(m_pos, t_pos) < 0.1f)
		{
			m_pos = t_pos;
			m_isMoving = false;
			m_vector = glm::vec2(0);
			//m_prevPos = m_pos;
		}
		else if(glm::distance(m_pos, t_pos) > 76.0f)
		{
			m_pos = t_pos;
			m_isMoving = false;
			m_vector = glm::vec2(0);
			//m_prevPos = m_pos;
		}
	}
	
	m_frame.update(deltaTime);

}

void SpellcardIcon::setDepth(float depth)
{
	m_depth = depth;
	m_frame.setDepth(m_depth - 1);
}


void SpellcardIcon::setFocus(bool val)
{
	m_isFocus = val;
	if (m_previousReady == m_isFocus)
	{
		//std::cout << "match, skip \n";
		return;
	}
	else
	{
		//std::cout << "not match \n";
		m_previousReady = val;
		if (m_previousReady)
		{
			m_frame.playAnimation("ready");
		}
		else
		{
			m_frame.playAnimation("idle");
		}
	}
	
}

void SpellcardIcon::setSignName(const std::wstring & signName)
{
	m_signName = signName;
}

void SpellcardIcon::setSpellName(const std::wstring & spellName)
{
	m_spellcardName = spellName;
}

void SpellcardIcon::setGrazeCost(int val)
{
	m_grazeCost = val;
}

void SpellcardIcon::setCD(float val)
{
	m_cd = val;
}

