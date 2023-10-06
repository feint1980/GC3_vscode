#include "CharacterAvatar.h"



CharacterAvatar::CharacterAvatar()
{
}


CharacterAvatar::~CharacterAvatar()
{
}

void CharacterAvatar::draw(Feintgine::SpriteBatch & spriteBatch)
{
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 desRect;
	desRect.x = m_pos.x - m_dim.x / 2.0f;
	desRect.y = m_pos.y - m_dim.y / 2.0f;
	desRect.z = m_dim.x;
	desRect.w = m_dim.y;
	spriteBatch.draw(desRect, uvRect, m_texture.id, m_depth, m_color, 0.0f);

	drawDescription(spriteBatch);
}

void CharacterAvatar::drawDescription(Feintgine::SpriteBatch & spriteBatch)
{
	const glm::vec4 uvRect(0, 0, 1, 1);
	glm::vec4 desRect;
	desRect.x = m_desPos.x - m_desDim.x * 0.5f;
	desRect.y = m_desPos.y - m_desDim.y * 0.5f;
	desRect.z = m_desDim.x;
	desRect.w = m_desDim.y; 
	spriteBatch.draw(desRect, uvRect, m_desTexture.id, m_depth, m_desColor, 0.0f);

}

void CharacterAvatar::init(const Feintgine::GLTexture & texture,
	const glm::vec2 & pos, const glm::vec2 & dim, const glm::vec4 & color,
	float depth)
{
	m_texture = texture;
	m_pos = pos;
	m_dim = dim;
	m_color = color;
	m_depth = depth;
	selectionOffset = glm::vec2(-30, 0);
	m_originalPos = m_pos;
}

void CharacterAvatar::initDescription(const std::string & japName, 
	const std::string &engName, const std::string & title)
{
	m_japName = japName;
	m_engName = engName;

}

void CharacterAvatar::addDesciptionTexture(const Feintgine::GLTexture & texture, const glm::vec2 & pos)
{

	//m_desPos = glm::vec2(m_pos.x, m_pos.y - m_dim.y);
	m_desPos = pos;
	m_desDim = glm::vec2(texture.width, texture.height);
	m_desTexture = texture;
}

void CharacterAvatar::getTextRenderer(const TextRenderer & txtrd)
{

}

bool CharacterAvatar::handleMouseInput(const glm::vec2 & mousePos)
{
	if (mousePos.x > m_pos.x - m_dim.x / 2.0f && mousePos.x < m_pos.x + m_dim.x / 2.0f &&
		mousePos.y > m_pos.y - m_dim.y / 2.0f && mousePos.y < m_pos.y + m_dim.y / 2.0f)
	{
		//std::cout << "hit \n";
		return true;
	}
	return false;
}

void CharacterAvatar::setAlpha(float alphaVal)
{
	m_color.a = alphaVal;
}

void CharacterAvatar::setSelected(bool val)
{
	m_isSelected = val;
}

void CharacterAvatar::update(float delta)
{
	if (m_isVisible)
	{
		show(delta);
	}
	else
	{
		hide(delta);
	}
	if (m_isSelected)
	{
		selecting(delta);
	}
	else
	{
		unSelecting(delta);
	}
	
}

void CharacterAvatar::show(float delta)
{
	if (m_color.a < 1.0f)
	{
		//m_color.r += AVATAR_FADE_SPEED * delta;
		//m_color.g += AVATAR_FADE_SPEED * delta;
		//m_color.b += AVATAR_FADE_SPEED * delta;
		m_color.a += AVATAR_FADE_SPEED * delta;
		
	}
	else
	{	
			//m_color.r = 1;
			//m_color.g = 1;
			//m_color.b = 1;
			m_color.a = 1;		
	}
}

void CharacterAvatar::setVisible(bool val)
{
	m_isVisible = val;
}

void CharacterAvatar::selecting(float delta)
{
	if (m_pos.x > m_originalPos.x + selectionOffset.x)
	{
		//m_pos.x -= AVATAR_FADE_SPEED * 14 * delta;
	}

	if (m_color.r <= 1.0f && m_desColor.r <= 1.0f)
	{
		//std::cout << "this is why " << m_desColor.r << "\n";
		m_depth = 10.0f;
		m_color.r += AVATAR_FADE_SPEED * delta;
		m_color.g += AVATAR_FADE_SPEED * delta;
		m_color.b += AVATAR_FADE_SPEED * delta;
		
		m_desColor.r += AVATAR_FADE_SPEED * delta;
		m_desColor.g += AVATAR_FADE_SPEED * delta;
		m_desColor.b += AVATAR_FADE_SPEED * delta;
		m_desColor.a += AVATAR_FADE_SPEED * delta;
	}
	else
	{
		m_color.r = 1;
		m_color.g = 1;
		m_color.b = 1;

		m_desColor.r = 1;
		m_desColor.g = 1;
		m_desColor.b = 1;
		m_desColor.a = 1;
	}
}

void CharacterAvatar::unSelecting(float delta)
{
	if (m_pos.x < m_originalPos.x)
	{
		//m_pos.x += AVATAR_FADE_SPEED * 14 * delta;
	}
	if (m_color.r >= 0.0f && m_desColor.r >= 0.0f)
	{
		m_depth = 1.0f;
		m_color.r -= AVATAR_FADE_SPEED * delta;
		m_color.g -= AVATAR_FADE_SPEED * delta;
		m_color.b -= AVATAR_FADE_SPEED * delta;

		m_desColor.r -= AVATAR_FADE_SPEED * delta;
		m_desColor.g -= AVATAR_FADE_SPEED * delta;
		m_desColor.b -= AVATAR_FADE_SPEED * delta;
		m_desColor.a -= AVATAR_FADE_SPEED * delta;
		
	}
	else
	{
		m_color.r = 0;
		m_color.g = 0;
		m_color.b = 0;


		m_desColor.r = 0;
		m_desColor.g = 0;
		m_desColor.b = 0;
		m_desColor.a = 0;
	}
}

void CharacterAvatar::hide(float delta)
{
	if (m_color.a >= 0.0f)
	{
		//m_color.r -= AVATAR_FADE_SPEED * delta;
		//m_color.g -= AVATAR_FADE_SPEED * delta;
		//m_color.b -= AVATAR_FADE_SPEED * delta;
		m_color.a -= AVATAR_FADE_SPEED * delta;
		m_desColor.r -= AVATAR_FADE_SPEED * delta;
		m_desColor.g -= AVATAR_FADE_SPEED * delta;
		m_desColor.b -= AVATAR_FADE_SPEED * delta;
		m_desColor.a -= AVATAR_FADE_SPEED * delta;

	}
	else
	{
		//m_color.r = 0;
		//m_color.g = 0;
		//m_color.b = 0;
		m_desColor.r = 0;
		m_desColor.g = 0;
		m_desColor.b = 0;
		m_desColor.a = 0;

		m_color.a = 0;
	}
}
