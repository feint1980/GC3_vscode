#pragma once
#include <SimpleDrawingObejct.h> 
#include <ObjectColider.h>
#include <ResourceManager.h>
#include <glm/glm.hpp>
class TemplateObject 
{
public:
	TemplateObject();
	~TemplateObject();

	glm::vec2 getFitDim(glm::vec2 t_template);



private:

	float saved_tile = 1;

	glm::vec2 m_dims;	

	//glm::vec4 m_uv;
};

