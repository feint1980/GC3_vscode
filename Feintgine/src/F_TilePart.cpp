#include "F_TilePart.h"


namespace Feintgine
{


	F_TilePart::F_TilePart()
	{
		m_depth = -10;
	}


	F_TilePart::~F_TilePart()
	{
	}

	void F_TilePart::create(const glm::vec2 & pos, const glm::vec2 & dim,
		glm::ivec2 index, const GLTexture & texture)
	{
		m_pos = pos;
		m_texture = texture;
		m_dim = dim;
		m_index = index;
		calculateUV();
	}

	void F_TilePart::setDepth(float depth)
	{
		m_depth = depth;
	}

	void F_TilePart::draw(SpriteBatch & spriteBatch)
	{
		glm::vec4 desRect;
		desRect.x = m_pos.x - m_dim.x / 2.0f;
		desRect.y = m_pos.y - m_dim.y / 2.0f;
		desRect.z = m_dim.x;
		desRect.w = m_dim.y;
		spriteBatch.draw(desRect, m_uv, m_texture.id, m_depth, m_color);
	}

	void F_TilePart::update(float delta)
	{

		
		if (animationTime >= totalTime)
		{
			
			float rt_x = m_uv.x + ((float)SPACING_OFFSET / (m_texture.width) * 4.0f);
			m_uv.x = rt_x;
			animationTime = 0;			
			m_currentJump++;
			if (m_currentJump > m_maxJump)
			{
				m_currentJump = 0;
				m_uv.x = backUpUVX;
			}

		}
		animationTime += 0.05 * delta;
	
	}

	void F_TilePart::setIndex(const glm::ivec2 index)
	{
		m_index = index;
		//shrink indices 
		glm::ivec2 idx1(2, 1);
		glm::ivec2 idx2(3, 1);
		glm::ivec2 idx3(2, 0);
		glm::ivec2 idx4(3, 0);
		if (index == idx2 || index == idx4)
		{
			offsetUVx = 0.99f;
			offsetUVy = 0.99f;
		}
		else
		{
			offsetUVx = 1.0f;
			offsetUVy = 1.0f;
		}
		if (index == idx1 )
		{
			rOffsetUVx = 1.005f;
			rOffsetUVy = 1.005f;
		}
		else
		{
			rOffsetUVx = 1.0f;
			rOffsetUVy = 1.0f;
		}
		
		calculateUV();
	}

	void F_TilePart::calculateUV()
	{
		glm::vec4 retUV = glm::vec4(0, 0, 1, 1);
		float rt_x = (float)SPACING_OFFSET / (m_texture.width);
		float rt_y = (float)SPACING_OFFSET / (m_texture.height);

		glm::vec2 prevUV;
		prevUV.x = (float)(m_index.x - 1)  * rt_x;
		prevUV.y = 1.0f - ((float)(m_index.y-1) * rt_y) - rt_y;

		m_uv.x = (prevUV.x * rOffsetUVx) + (rt_x * offsetUVx);
		m_uv.y = (prevUV.y * rOffsetUVy) - (rt_y * offsetUVy);
		m_uv.z = rt_x;
		m_uv.w = rt_y;
		backUpUVX = m_uv.x;
	}

	void F_TilePart::drawText(TextRenderer & textRenderer, const Feintgine::Camera2D cam)
	{


		textRenderer.renderText(cam, feint_common::
			Instance()->convertStringtoWstring(feint_common::Instance()->convertiVec2toString(m_index)), m_pos,
			m_color, .8f, ALIGN_FT_CENTER);
	}

	void F_TilePart::setUV(const glm::vec4 & uv)
	{
		m_uv = uv;
	}

	void F_TilePart::resetStatus()
	{
		m_uv.x = backUpUVX;
		m_currentJump = 0;
		animationTime = 0;
	}

	void F_TilePart::initAnim(int maxJump)
	{
		m_maxJump = maxJump;
	}

}
