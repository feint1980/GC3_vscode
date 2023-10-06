#ifndef _LIGHTBATCH_H_
#define _LIGHTBATCH_H_

#include <vector>
#include <glm/glm.hpp>
#include "GLSLProgram.h"


namespace Feintgine
{


	struct Light
	{
		Light(const glm::vec2 & t_pos, const glm::vec4 & t_color, const glm::vec3 & t_atten)
		{
			pos = t_pos;
			color = t_color;
			attenuation = t_atten;
		}

		glm::vec2 pos;
		glm::vec4 color;
		glm::vec3 attenuation;
	};

	class LightBatch
	{
	public:
		LightBatch();
		~LightBatch();


		void initShader(Feintgine::GLSLProgram *shader);

		void begin();

		void addLight(const glm::vec2 & pos, const glm::vec4 & color, const glm::vec3 & attenuation);
		void addLight(const Light & light);


		void addRayLight(const glm::vec2 & pos, const glm::vec4 & color, const glm::vec3 & attenuation,float rotation);



		void renderLight();

	private:

		Feintgine::GLSLProgram * m_shader;


		std::vector<Light> m_lights;

		std::vector<glm::vec2> m_lightListPos;
		std::vector<glm::vec4> m_lightListColor;
		std::vector<glm::vec3> m_lightListAttenuation;


		std::vector<glm::vec2> m_rayLightPos;
		std::vector<glm::vec4> m_rayLightColor;
		std::vector<glm::vec3> m_rayLightAtten;
		std::vector<float>     m_rayRotation;



	};
}

#endif
