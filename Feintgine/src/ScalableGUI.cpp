#include "ScalableGUI.h"


namespace FeintGUI
{


	ScalableGUI::ScalableGUI()
	{
	}


	ScalableGUI::~ScalableGUI()
	{
	}

	void ScalableGUI::init(const std::string & guiName, glm::vec2 pos, glm::vec2 dim)
	{
		m_guiName = guiName;
		m_pos = pos;
		m_dim = dim;
		for (int i = 0; i < 9; i++)
		{
			FeintGUI::ScalablePart parts;
			parts.init(m_guiName, m_pos, m_dim, i);
			m_parts.push_back(parts);
			
		}

	}

	void ScalableGUI::setPos(glm::vec2 pos)
	{
		m_pos = pos;
	}

	void ScalableGUI::setDim(glm::vec2 dim)
	{
		m_dim = dim;
	}

	void ScalableGUI::draw(Feintgine::SpriteBatch & spriteBatch)
	{
		for (int i = 0; i < m_parts.size(); i++)
		{
			//std::cout << " draw  part " << i << "\n";
			m_parts[i].draw(spriteBatch);
		}
	}

	void ScalableGUI::calculatePart()
	{
		for (int i = 0; i < m_parts.size(); i++)
		{
			m_parts[i].calculateProperty(m_pos, m_dim);
		}
	}

}
