#include "F_ShaderEvent_Float.h"

namespace Feintgine
{

	F_ShaderEvent_Float::F_ShaderEvent_Float()
	{
	}


	F_ShaderEvent_Float::~F_ShaderEvent_Float()
	{
	}

	void F_ShaderEvent_Float::update(float deltaTime)
	{
		if (!m_isDone)
		{
			m_value += m_calculatedValue * deltaTime;
			
			m_isDone = isReachTarget();    //        | Or .....

		}
	}

	bool F_ShaderEvent_Float::isReachTarget()
	{
		//write this shit in 1 line of code in case there 
		//is some cool and hip nerd checking my code
		
		return abs(m_target - m_value) < ACCEPTABLE_VALUE;

		// for serious people it translate to this
	/*	float dif = m_target - m_value;
		if (abs(dif) < ACCEPTABLE_VALUE)
		{
			return true;
		}
		return false;
	*/
	}

	void F_ShaderEvent_Float::applyToShader()
	{
		m_location = m_shader->getUniformLocation(m_name);
		glUniform1f(m_location, m_value);
	}

	void F_ShaderEvent_Float::setEvent(float targetValue, float duration)
	{
	
		m_target = targetValue;
		m_duration = duration;
		m_calculatedValue = (m_target - m_value) / (duration* 30.0f); // 30 is hand pick target
		m_isDone = false;

	}

	void F_ShaderEvent_Float::setEvent(const glm::vec3 & targetValue, float duration)
	{
		// offlimit
	}

	void F_ShaderEvent_Float::setDefaultvalue(float val)
	{
		m_value = val;
	}

	void F_ShaderEvent_Float::setDefaultvalue(const glm::vec3 & value)
	{
		// offlimit
	}

}
