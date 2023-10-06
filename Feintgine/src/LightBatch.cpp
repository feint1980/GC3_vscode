#include "LightBatch.h"


namespace Feintgine {



	LightBatch::LightBatch()
	{
	}


	LightBatch::~LightBatch()
	{
	}

	void LightBatch::initShader(Feintgine::GLSLProgram *shader)
	{
		m_shader = shader;
	}

	void LightBatch::begin()
	{
		m_lightListPos.reserve(m_lightListPos.size());
		m_lightListColor.reserve(m_lightListPos.size());
		m_lightListAttenuation.reserve(m_lightListPos.size());

		m_lights.reserve(m_lights.size());


		
		m_rayLightPos.reserve(m_rayLightPos.size());
		m_rayLightColor.reserve(m_rayLightColor.size());
		m_rayLightAtten.reserve(m_rayLightAtten.size());
		m_rayRotation.reserve(m_rayRotation.size());


		m_lights.clear();
		m_lightListPos.clear();
		m_lightListColor.clear();
		m_lightListAttenuation.clear();

		m_rayLightPos.clear();
		m_rayLightColor.clear();
		m_rayLightAtten.clear();
		m_rayRotation.clear();


	}

	void LightBatch::addLight(const glm::vec2 & pos, const glm::vec4 & color, const glm::vec3 & attenuation)
	{
		m_lightListPos.push_back(pos);
		m_lightListColor.push_back(color);
		m_lightListAttenuation.push_back(attenuation);
		Light lt(pos, color, attenuation);
		m_lights.push_back(lt);
	}


	void LightBatch::addLight(const Light & light)
	{

		//Light lt(pos, color, attenuation);
		m_lights.push_back(light);
// 		m_lightListPos.push_back(light.pos);
// 		m_lightListColor.push_back(light.color);
// 		m_lightListAttenuation.push_back(light.attenuation);
	}


	void LightBatch::addRayLight(const glm::vec2 & pos, const glm::vec4 & color, const glm::vec3 & attenuation,float rotation)
	{
		m_rayLightPos.push_back(pos);
		m_rayLightColor.push_back(color);
		m_rayLightAtten.push_back(attenuation);
		m_rayRotation.push_back(rotation);
	}

	void LightBatch::renderLight()
	{

		GLint lightPosIndex = m_shader->getUniformLocation("lightPos");
		glUniform2fv(lightPosIndex, m_lightListPos.size(), reinterpret_cast<GLfloat *>(m_lightListPos.data()));

		GLint lightColorIndex = m_shader->getUniformLocation("lightColor");
		glUniform4fv(lightColorIndex, m_lightListColor.size(), reinterpret_cast<GLfloat *>(m_lightListColor.data()));

		GLint lightAttenuationIndex = m_shader->getUniformLocation("lightAttenuation");
		glUniform3fv(lightAttenuationIndex, m_lightListAttenuation.size(), reinterpret_cast<GLfloat *>(m_lightListAttenuation.data()));


// 		int numLight = 0;
// 		for (int i = 0; i < m_lights.size(); i++)
// 		{
// 			m_shader->setUniformVec2("lights[" + std::to_string(numLight) + "].pos", m_lights[i].pos);
// 			m_shader->setUniformVec4("lights[" + std::to_string(numLight) + "].color", m_lights[i].color);
// 			m_shader->setUniformVec3("lights[" + std::to_string(numLight) + "].attenuation",m_lights[i].attenuation);
// 			numLight++;
// 		}
		GLint countIndex = m_shader->getUniformLocation("lightCount");
		glUniform1i(countIndex, m_lightListPos.size());




		GLint rayLightPosXIndex = m_shader->getUniformLocation("rayLightPos");
		glUniform2fv(rayLightPosXIndex, m_rayLightPos.size(), reinterpret_cast<GLfloat *>(m_rayLightPos.data()));

		GLint rayLightColorIndex = m_shader->getUniformLocation("rayLightColor");
		glUniform4fv(rayLightColorIndex, m_rayLightColor.size(), reinterpret_cast<GLfloat *>(m_rayLightColor.data()));

		GLint rayLightAttenIndex = m_shader->getUniformLocation("rayLightAtten");
		glUniform3fv(rayLightAttenIndex, m_rayLightAtten.size(), reinterpret_cast<GLfloat *>(m_rayLightAtten.data()));

		GLint rayRotationIndex = m_shader->getUniformLocation("rayRotation");
		glUniform1fv(rayRotationIndex, m_rayRotation.size(), reinterpret_cast<GLfloat *>(m_rayRotation.data()));

		GLint rayCountIndex = m_shader->getUniformLocation("rayCount");
		glUniform1i(rayCountIndex, m_rayLightPos.size());

	}
}


