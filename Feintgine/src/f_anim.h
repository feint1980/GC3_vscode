#ifndef F_ANIM_H
#define F_ANIM_H
#include "F_Sprite.h"


namespace Feintgine {


	struct f_anim
	{
		F_Sprite sprite;
		float time;
		glm::vec2 offset;
	};
}
#endif // F_ANIM_H