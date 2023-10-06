#include "F_ShaderEventBase.h"


namespace Feintgine
{
	F_ShaderEventBase::F_ShaderEventBase()
	{
	}


	F_ShaderEventBase::~F_ShaderEventBase()
	{
	}

	void F_ShaderEventBase::init(GLSLProgram * shader, const std::string & name)
	{
		m_shader = shader;
		m_name = name;
	}
}