#pragma once
#include <glm/glm.hpp>
#include "EditObject.h"

class EditorProperty
{
public:
	EditorProperty();
	~EditorProperty();



	static EditorProperty *Instance()
	{
		if (p_Instance == 0)
		{
			p_Instance = new EditorProperty;
			return p_Instance;
		}
		return p_Instance;
	}
	glm::vec2 getSpacingOffset() const { return m_spacingOffset; }
	void setSpacingOffset(const glm::vec2 & spacing);

	EditObject getCurrentEditObject() const { return currentEditObject; }

	void setCurrentEditObject(const EditObject & object);

private:

	static EditorProperty * p_Instance;

	EditObject currentEditObject;

	glm::vec2 m_spacingOffset;
};

