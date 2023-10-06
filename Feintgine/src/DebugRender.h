#ifndef _DEBUGRENDER_H_
#define _DEBUGRENDER_H_

#include <glm/glm.hpp>
#include "Vertex.h"
#include <vector>
#include "GLSLProgram.h"
namespace Feintgine
{

	class DebugRender
	{
	public:
		DebugRender();
		~DebugRender();
		void init();
		void drawBox(const glm::vec4 & desRect  , const Color & color , float angle);

		void drawBox_nonCenter(const glm::vec4 & desRect, const Color & color, float angle);
		void drawCircle(const glm::vec2 & center, const Color & color, float radius);

		void drawBox_center(const glm::vec4 desRect, const Color & color, float angle);

		void drawBox(const glm::vec2 & tl, const glm::vec2 & tr, const glm::vec2 & br, const glm::vec2 & bl, Feintgine::Color & color, float angle);

		void drawRectCol(const glm::vec2 & tl, const glm::vec2 & tr, const glm::vec2 & br, const glm::vec2 & bl, Feintgine::Color & color, float angle);

		void dispose();
		void end();
		void render(const glm::mat4& projectionMatrix, float lineWidth);
		struct DebugVertex{
			glm::vec2 position;
			Color color;
		};


	private:
		Feintgine::GLSLProgram m_program;
		std::vector<DebugVertex> m_verts;
		std::vector<GLuint> m_indices;
		GLuint m_vbo, m_vao, m_ibo;
		int m_numElements = 0;

	};
}

#endif
