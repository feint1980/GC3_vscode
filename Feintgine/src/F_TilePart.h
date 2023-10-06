
#ifndef _F_TILEPART_H_
#define _F_TILEPART_H_

#include "GLTexture.h"
#include <glm/glm.hpp>
#include "SpriteBatch.h"
#include "TextRenderer.h"


#define SPACING_OFFSET 32

enum TileType
{
	TileType_Terrain,
	TileType_Water
};

namespace Feintgine
{
	class F_TilePart
	{
	public:
		F_TilePart();
		~F_TilePart();
		void create(const glm::vec2 & pos, const glm::vec2 & dim, glm::ivec2 index
			, const GLTexture & texture);
		void setDepth(float depth);
		void draw(SpriteBatch & spriteBatch);
		void update(float delta);
		void setIndex(const glm::ivec2 index);

		glm::ivec2 getIndex() const { return m_index; }

		void calculateUV();
		glm::vec2 getPos() const { return m_pos; }

		void drawText(TextRenderer & textRenderer, const Feintgine::Camera2D cam);

		void setUV(const glm::vec4 & uv);


		void resetStatus();

		void initAnim(int maxJump);

	private:
		glm::vec2 m_dim;
		glm::vec4 m_uv;
		GLTexture m_texture;
		glm::vec2 m_pos;
		float m_uvJumpx;
		float m_depth;
		Color m_color = Color(255,255,255,255);

		TileType m_tileType;

		float animationTime = 0;
		float totalTime = 1.25f;
		glm::ivec2 m_index;
		float offsetUVx = 1.0f;
		float offsetUVy = 1.0f;

		float rOffsetUVx = 1.0f;
		float rOffsetUVy = 1.0f;
		int m_maxJump = 2;
		int m_currentJump = 0;
		float backUpUVX = 0;


	};
}

#endif