#ifndef _SCALABLEGUI_H_
#define _SCALABLEGUI_H_

#include <glm/vec2.hpp>
#include "F_Sprite.h"
#include "ScalablePart.h"
namespace FeintGUI
{


	class ScalableGUI
	{
	public:
		ScalableGUI();
		~ScalableGUI();

		void init(const std::string & guiName, glm::vec2 pos, glm::vec2 dim);

		void setPos(glm::vec2 pos);
		void setDim(glm::vec2 dim);

		void draw(Feintgine::SpriteBatch & spriteBatch);
		void calculatePart();

		glm::vec2 getPos() const { return m_pos; }
		glm::vec2 getDim() const { return m_dim; }

	private:

		std::string m_guiName;
		glm::vec2 m_pos;
		glm::vec2 m_dim;
		std::vector<ScalablePart> m_parts;


	};
}

#endif

