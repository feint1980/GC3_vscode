#include "EGUI_DrawElement.h"
#include "feint_common.h"


EGUI_DrawElement::EGUI_DrawElement()
{
}


EGUI_DrawElement::~EGUI_DrawElement()
{
}

void EGUI_DrawElement::init(const char * text,
	const glm::vec2 & pos,float fontSize)
{

	m_text = text;
	m_pos = ImVec2(pos.x, pos.y);
	m_state |= TEXT_STATE_POS_CHANGE;
	m_fontSize = fontSize;

}


void EGUI_DrawElement::setText(const char * text)
{
	m_text = text;
}

void EGUI_DrawElement::setText(const std::string & text)
{
	m_text = text;
	//m_label2->setText(text.c_str());
}

void EGUI_DrawElement::setText(const std::wstring & text)
{

	m_text = feint_common::Instance()->convertWstringToString(text);
	
}

void EGUI_DrawElement::render()
{

	if (m_state & TEXT_STATE_POS_CHANGE)
	{
		ImGui::SetCursorPos(m_pos);

	}
	// if (m_state & TEXT_STATE_COLOR_CHANGE)
	// {
	// 	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(m_color.x, m_color.y, m_color.z, m_color.w));
	// }
	//ImGui::Text(m_text.c_str());
	
	// split string if detect character ":"
	// std::string str1 ;
	// std::string str2 ;
	// if(m_text.find(":") != std::string::npos)
	// {
	// 	str1 = m_text.substr(0,m_text.find(":"));
	// 	str2 = m_text.substr(m_text.find(":")+1);
	// 	ImGui::TextColored({m_color.x,m_color.y,m_color.z , m_color.w},str1.c_str());
	// 	ImGui::SameLine(m_pos.x + (m_fontSize * 0.5f) * str1.size());
	// 	ImGui::TextColored({m_color.x,m_color.y,m_color.z , m_color.w},str2.c_str());
	// }
	// else
	// {
		ImGui::TextColored({m_color.x,m_color.y,m_color.z , m_color.w},m_text.c_str());
	//}

	
	
	// if (m_state & TEXT_STATE_COLOR_CHANGE)
	// {
	// 	ImGui::PopStyleColor();
	// //	m_state &= ~TEXT_STATE_COLOR_CHANGE;
	// }

}

void EGUI_DrawElement::update(float deltaTime)
{
	if (m_state != 0)
	{
		if (m_state & TEXT_STATE_POS_CHANGE)
		{
			//m_pos.x += m_changeRate * deltaTime;
		}
		if(!m_isChangeDone)
		{
			if (m_state & TEXT_STATE_COLOR_CHANGE)
			{
				glm::vec4 diff = m_targetColor - m_color;
				m_color += diff * m_changeRate * deltaTime;
				if(glm::length(diff) < m_changeRate * deltaTime)
				{
					
					m_color = m_targetColor;
					m_isChangeDone = true;
				}
			}
		}
	}
}

void EGUI_DrawElement::setChangeColor(const glm::vec4 & color, float rate)
{
	m_targetColor = color;
	m_changeRate = rate;
	m_state |= TEXT_STATE_COLOR_CHANGE;
	m_isChangeDone = false;
}


void EGUI_DrawElement::setPos(const glm::vec2 & pos)
{
	m_pos = ImVec2(pos.x, pos.y);
}

void EGUI_DrawElement::setColor(const glm::vec4 & color)
{
	m_color = color;
}

void EGUI_DrawElement::setAlpha(int alpha)
{
	m_color.w = alpha;
}

