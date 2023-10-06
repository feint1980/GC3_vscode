
#ifndef _F_EMPTY_OBJECT_H_
#define _F_EMPTY_OBJECT_H_

#include "F_Sprite.h"
#include "SpriteBatch.h"
#include <iostream>

namespace Feintgine {

	class F_EmptyObject
	{
	public:

		void init(F_Sprite sprite, glm::vec2 pos, glm::vec2 scalingFactor, Feintgine::Color color);

		void setPos(glm::vec2 pos);

		void setScaleWithActualSize(glm::vec2 dim);

		void setScale(glm::vec2 scale);

		void setColor(Feintgine::Color color);

		glm::vec2 getPos() const { return m_pos; }

		glm::vec2 getScale() const { return m_scale; }

		void draw(Feintgine::SpriteBatch & spriteBatch);

		F_Sprite getSprite() const { return m_sprite; }

		Feintgine::Color getColor() const { return m_color; }

		F_EmptyObject();
		~F_EmptyObject();
	protected:
		F_Sprite m_sprite;

		glm::vec2 m_pos;
		glm::vec2 m_scale;
		Feintgine::Color m_color;
		float m_depth;
		float m_spec = 1.0f;
		float m_angle = 0;
	};

}
#endif
