#ifndef _SCALABLEPART_H_
#define _SCALABLEPART_H_


#include <glm/glm.hpp>
#include "F_Sprite.h"
#include "SpriteBatch.h"
#include "SpriteManager.h"
#include "feint_common.h"

namespace FeintGUI {

	const unsigned short TOP_LEFT_PART = 0;
	const unsigned short TOP_BORDER_PART = 1;
	const unsigned short TOP_RIGHT_PART = 2;
	const unsigned short RIGHT_BORDER_PART = 3;
	const unsigned short BOT_RIGHT_PART = 4;
	const unsigned short BOT_BORDER_PART = 5;
	const unsigned short BOT_LEFT_PART = 6;
	const unsigned short LEFT_BORDER_PART = 7;
	const unsigned short CENTER_PART = 8;

	class ScalablePart
	{

	public:
		ScalablePart();
		~ScalablePart();

		void init(const std::string & guiName ,glm::vec2 mainPos , glm::vec2 dim, unsigned short partFlag);

		void setPos(glm::vec2 mainPos);
		void setDim(glm::vec2 maindim);

		void calculateProperty(glm::vec2 mainPos,glm::vec2 mainDim);

		void draw(Feintgine::SpriteBatch & spriteBatch);

		std::string getPartName();


	private:
		unsigned short m_partFlag;
		glm::vec2 m_pos; 
		glm::vec2 m_dim;
		glm::vec2 m_scale;
		glm::vec4 m_uv;
		Feintgine::F_Sprite m_sprite;
		
	};
}

#endif 

