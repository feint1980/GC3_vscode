#ifndef _TEXTRENDERER_H_
#define _TEXTRENDERER_H_

#include "Feintgine.h"
#include <ft2build.h>
#include <freetype/ftstroke.h>
#include "GLTexture.h"
#include <glm/glm.hpp>
#include "Vertex.h"
#include <map>
#include <iostream>
#include "GLSLProgram.h"
#include "Camera2D.h"
#include <cstring>
//#include <unicode/ustring.h> // disable for now
#include <memory>
#include "feint_common.h"
#include FT_FREETYPE_H

#pragma  once
struct Character {
	GLuint TextureID;
	glm::ivec2 Size;
	glm::ivec2 Bearing;
	GLuint Advance;
};
#pragma execution_character_set( "utf-8" )
//static const char *STR = u8"哈哈abcdefghijklmnopqrstuvwxyz1234567890";

const unsigned char ALIGN_FT_LEFT = 1;
const unsigned char ALIGN_FT_RIGHT = 2;
const unsigned char ALIGN_FT_CENTER = 3;

class TextRenderer {

public:

	TextRenderer();
	~TextRenderer();


	

	void init(int fontSize,int charCount, const std::string & fontFilePath);
	void initShader();
	float getTotalScale() const { return totalScale; }
	void renderBorderText(const Feintgine::Camera2D & camera, const std::wstring & text, const glm::vec2 &pos, const  Feintgine::Color &color, float scale, unsigned char justification);
	void renderText(const Feintgine::Camera2D & camera, const std::wstring & text, const glm::vec2 &pos, const  Feintgine::Color &color, float scale, unsigned char justification);
	
private:
	int glyph_index;
	Feintgine::GLSLProgram m_shader;
	std::map<wchar_t, Character> Characters;
	GLuint m_VAO;
	GLuint m_VBO;
	FT_BitmapGlyph glyph_bitmap;
	FT_Face face;
	float totalScale;


	float m_test_time = 0;
};

#endif

