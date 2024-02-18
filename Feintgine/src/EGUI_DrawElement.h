#pragma once
#include <glm/glm.hpp>
#include "GUI.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "feint_common.h"

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#if defined(_MSC_VER)
#  pragma warning (disable: 4505) // don't warn about dead code in stb_image.h
#elif defined(__GNUC__)
#   pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include <stb_image.h>


#define TEXT_STATE_POS_CHANGE 1
#define TEXT_STATE_COLOR_CHANGE 2



class EGUI_DrawElement
{
public:
	EGUI_DrawElement();
	~EGUI_DrawElement();

	void init( const char * text,
		const glm::vec2 & pos,float fontSize = 24.0f);


	void setText(const char * text);

	void setText(const std::string & text);
	void setText(const std::wstring & text);

	void setPos(const glm::vec2 & pos);

	void setColor(const glm::vec4 & color);

	void setChangeColor(const glm::vec4 & color, float rate);

	void render();

	void setAlpha(int alpha);

	//void setAlignment(int value);

	void update(float deltaTime);

private:

	//glm::vec2 m_pos;
	//glm::vec2 m_dim;


	int m_state = 0;
	// state table 
	// 0 - normal
	// 1 - change pos
	// 2 - change color

	bool m_isChangeDone = true;

	ImVec2 m_pos;
	std::string m_text;

	float m_changeRate;

	glm::vec4 m_targetColor;

	float m_fontSize;

	
	glm::vec4 m_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	//CEGUI::TextComponent * m_label
	//CEGUI::Window

};

