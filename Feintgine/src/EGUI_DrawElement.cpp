#include "EGUI_DrawElement.h"
#include "feint_common.h"


EGUI_DrawElement::EGUI_DrawElement()
{
}


EGUI_DrawElement::~EGUI_DrawElement()
{
}

// void EGUI_DrawElement::init(Feintgine::GUI & t_gui, const std::string & name,
// 	const glm::vec2 pos, const glm::vec2 dim)
// {
// 	m_pos = pos;
// 	m_dim = dim;
// 	std::string outlineName = name + "_outlined";
// 	m_label = static_cast<CEGUI::DefaultWindow*>(
// 		t_gui.createWidget("AlfiskoSkin/Label",
// 		glm::vec4(m_pos, m_dim), glm::vec4(0), name));
// 	m_label2 = static_cast<CEGUI::DefaultWindow*>(
// 		t_gui.createWidget("AlfiskoSkin/Label",
// 			glm::vec4(m_pos, m_dim), glm::vec4(0), outlineName));
// 	m_label2->setDisabled(true);
	//m_label->color
	//m_label->setProperty("FrameEnabled", "true");
//}

void EGUI_DrawElement::init(Feintgine::GUI & t_gui
	, const std::string & name,
	const glm::vec2 pos, const glm::vec2 dim)
{
	m_pos = pos;
	m_dim = dim;
	std::string outlineName = name + "_outlined";
	m_label = static_cast<CEGUI::Window*>(
		t_gui.createWidget("AlfiskoSkin/Label",
			glm::vec4(m_pos, m_dim), glm::vec4(0), name));

}

void EGUI_DrawElement::setText(const std::string & text)
{
	if (m_label)
	{
		m_label->setText(text.c_str());
	}
	//m_label2->setText(text.c_str());
}

void EGUI_DrawElement::setText(const std::wstring & text)
{
	//(CEGUI::utf8)
	//WideCharToMultiByte()
	
	//m_label2->setText(E_GUI_ws2s(text.c_str()));
	if (m_label)
	{
		m_label->setText(E_GUI_ws2s(text.c_str()));
		//m_label->setWidth(CEGUI::UDim(text.size() * 0.025f, 0));
	}
	
}

void EGUI_DrawElement::setPos(const glm::vec2 & pos, const glm::vec2 \
& aspect)
{
	if (m_label)
	{
	m_pos = pos;
	glm::vec2 conveted = m_pos / aspect;
	m_label->setPosition(CEGUI::UVector2(CEGUI::UDim(conveted.x, conveted.x),
		CEGUI::UDim(conveted.y, conveted.y)));
	}
}

void EGUI_DrawElement::setPos(const glm::vec2 & pos)
{
	if (m_label)
	{

		m_pos = pos + feint_common::Instance()->getResolution() * 0.5f;
		//std::cout << "pos is " + feint_common::Instance()->convertiVec2toString(m_pos) << " !\n";
		//std::cout << "pos is " + feint_common::Instance()->convertiVec2toString(feint_common::Instance()->getResolution()) << " o\n";
		glm::vec2 resol = feint_common::Instance()->getResolution();
		glm::vec2 conveted = m_pos * (1.0f/ resol);
		//glm::vec2 conveted = glm::vec2(((float)(m_pos.x / resol.x), (float)(m_pos.y / resol.y)));
		m_label->setPosition(CEGUI::UVector2(CEGUI::UDim(conveted.x, conveted.x),
			CEGUI::UDim(conveted.y, conveted.y)));

		//std::cout << "pos is " + feint_common::Instance()->convertiVec2toString(conveted) << " ?\n";
	}

}


void EGUI_DrawElement::setDim(const glm::vec2 & dim)
{
	if (m_label)
	{

		m_label->setSize(CEGUI::USize(CEGUI::UDim(dim.x, dim.x),
			CEGUI::UDim(dim.y, dim.y)));

	//	std::cout << "pos is " + feint_common::Instance()->convertiVec2toString(conveted) << " ?\n";
	}
}

void EGUI_DrawElement::setColor(const std::string & colorRef)
{
	
}

void EGUI_DrawElement::setAlpha(float alpha)
{

	m_label->setAlpha(alpha);
	if (alpha <= 0.0f)
	{
		m_label->setVisible(false);
	}
	else
	{
		m_label->setVisible(true);
	}
}

void EGUI_DrawElement::setAlignment(int value)
{
	switch (value)
	{
	case 0:
	{
		m_label->setProperty("HorzFormatting", "LeftAligned");
	}
	break;
	case 1:
	{
		m_label->setProperty("HorzFormatting", "RightAligned");
	}
	break;
	case 2:
	{
		m_label->setProperty("HorzFormatting", "CentreAligned");
	}
	break;
	case 3:
	{
		m_label->setProperty("HorzFormatting", "HorzJustified");
	}
	break;
	case 4:
	{
		m_label->setProperty("HorzFormatting", "WordWrapLeftAligned");
	}
	break;
	case 5:
	{
		m_label->setProperty("HorzFormatting", "WordWrapRightAligned");
	}
	break;
	case 6:
	{
		m_label->setProperty("HorzFormatting", "WordWrapCentred");
	}
	break;
	case 7:
	{
		m_label->setProperty("HorzFormatting", "WordWrapJustified");
	}
	break;
	default:
		//m_label->setProperty("HorzFormatting", "HorzCentred");
		break;
	}
	//m_label->setProperty("HorzFormatting", "HorzCentred");
}
