#pragma once
#include "F_ShaderEventBase.h"

#include <glm/glm.hpp>

namespace Feintgine
{
	class F_ShaderEvent_Vec3 : public F_ShaderEventBase
	{
	public:
		F_ShaderEvent_Vec3();
		~F_ShaderEvent_Vec3();

		virtual void update(float deltaTime) override;

		void setEvent(const glm::vec3 & targetValue, float duration);
		void setEvent(float targetValue, float duration);

		void setDefaultvalue(const glm::vec3 &val);
		void setDefaultvalue(float val);
		bool isReachTarget();

		virtual void applyToShader();

		


		glm::vec3 getValue() const { return m_value; }

	private:

		glm::vec3 m_value;

		float  m_duration;
		glm::vec3 m_target;

		glm::vec3 m_calculatedValue;


	};
}

