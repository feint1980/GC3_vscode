#include "EditorProperty.h"

EditorProperty *EditorProperty::p_Instance = 0;

EditorProperty::EditorProperty()
{
}


EditorProperty::~EditorProperty()
{
}

void EditorProperty::setSpacingOffset(const glm::vec2 & spacing)
{
	m_spacingOffset = spacing;
}

void EditorProperty::setCurrentEditObject(const EditObject & object)
{
	currentEditObject = object;
}
