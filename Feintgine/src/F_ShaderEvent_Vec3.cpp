#include "F_ShaderEvent_Vec3.h"


namespace Feintgine
{
	F_ShaderEvent_Vec3::F_ShaderEvent_Vec3()
	{
	}


	F_ShaderEvent_Vec3::~F_ShaderEvent_Vec3()
	{
	}

	void F_ShaderEvent_Vec3::update(float deltaTime)
	{
		if (!m_isDone)
		{
			m_value += m_calculatedValue * deltaTime;

			m_isDone = isReachTarget();   

		}
	}

	void F_ShaderEvent_Vec3::setEvent(const glm::vec3 & targetValue,float duration)
	{
		m_target = targetValue;
		m_duration = duration;
		m_calculatedValue = (m_target - m_value) / (duration* 60.0f); // 60 is hand pick target
		m_isDone = false;
	}

	void F_ShaderEvent_Vec3::setEvent(float targetValue, float duration)
	{
		// 
	}

	void F_ShaderEvent_Vec3::setDefaultvalue(const glm::vec3 &val)
	{
		m_value = val;
		m_isDone = true;
	}

	void F_ShaderEvent_Vec3::setDefaultvalue(float val)
	{
		m_value = glm::vec3(val);
		m_isDone = true;
	}

	bool F_ShaderEvent_Vec3::isReachTarget()
	{
		return abs(glm::distance(m_value, m_target)) < ACCEPTABLE_VALUE;
	}

	void F_ShaderEvent_Vec3::applyToShader()
	{
		m_location = m_shader->getUniformLocation(m_name);
		glUniform3f(m_location, m_value.x, m_value.y, m_value.z);
	}

}