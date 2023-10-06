#pragma once

#include "GLSLProgram.h"





namespace Feintgine
{
	class ShaderUpdater
	{
	public:
		ShaderUpdater();
		~ShaderUpdater();

		void init(GLSLProgram * shader);


	private:
		GLSLProgram * m_shader;

	};
}
