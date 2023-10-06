#pragma once
#include "F_ShaderEventBase.h"

namespace Feintgine
{
	class F_ShaderEvent_Float : public F_ShaderEventBase
	{
	public:
		F_ShaderEvent_Float();
		~F_ShaderEvent_Float();

		void setEvent(float targetValue, float duration);

		void setEvent(const glm::vec3 & targetValue, float duration);

		void setDefaultvalue(float val);

		virtual void update(float deltaTime);

		bool isReachTarget();

		virtual void applyToShader();

		void setDefaultvalue(const glm::vec3 &  value);

	private:

		float m_value;

		float m_duration;
		float m_target;

		float m_calculatedValue;
	};
}

