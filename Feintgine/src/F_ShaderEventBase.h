#pragma once
#include <string>
#include "GLSLProgram.h"


#define ACCEPTABLE_VALUE 0.05f

namespace Feintgine
{
	class F_ShaderEventBase
	{
	public:
		F_ShaderEventBase();
		virtual ~F_ShaderEventBase() ;

		virtual void update(float deltaTime) = 0;

		void init(GLSLProgram * shader, const std::string & name);
		
		bool isDone() const { return m_isDone; }

		std::string getName() const { return m_name; }

		virtual void setEvent(const glm::vec3 & targetValue, float duration) = 0;

		virtual void setEvent(float targetValue, float duration) = 0;

		virtual void applyToShader() = 0;

		virtual void setDefaultvalue(float value) = 0;
		virtual void setDefaultvalue(const glm::vec3 & value) = 0;


	protected:

		bool m_isDone ;
		std::string m_name;

		GLSLProgram * m_shader;

		GLuint m_location;
	};

}