
#ifndef _BRUSH_H_
#define _BRUSH_H_
#include <glm/glm.hpp>
#include "SpriteBatch.h"
#include "GLTexture.h"
#include "objectData.pb.h"
#include "ResourceManager.h"
#include "feint_common.h"

namespace Feintgine
{


	class Brush
	{
	public:
		Brush();
		~Brush();
		void setDepth(float depth);
		
		
		void loadFromProto(const Proc_Brush & proc_brush);

		Proc_Brush getProtoSer(); 

		void draw(Feintgine::SpriteBatch & spriteBatch);
		void init(const std::string & filePath, glm::vec2 pos, glm::vec2 dims, glm::vec2 uv,Feintgine::Color color,float depth);

		float getDepth() const { return m_depth; }
	private:

	
		std::string m_filePath;
		glm::vec2 m_pos;
		glm::vec2 m_dim;
		glm::vec2 m_uv;
		GLTexture m_texture;
		Color m_color;
		float m_depth;

	};
}

#endif
