#include "TemplateObject.h"



TemplateObject::TemplateObject()
{
}


TemplateObject::~TemplateObject()
{
}


glm::vec2 TemplateObject::getFitDim(glm::vec2 t_template)
{
	float largest_target = t_template.x;
	if (t_template.y >= t_template.x)
	{
		largest_target = t_template.y;
	}
	float largest_self = m_dims.x;

	if (m_dims.y >= m_dims.x)
	{
		largest_self = m_dims.y;

	}
	
	float ti_le = largest_target / largest_self;
	saved_tile = ti_le;
	return m_dims * ti_le;
	

}
