
#include "TextRenderer.h"

TextRenderer::TextRenderer()
{

}

TextRenderer::~TextRenderer()
{

}



void TextRenderer::init(int fontSize, int charCount, const std::string & fontFilePath)
{

	initShader();
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "Error :(FREETYPE) : Can't not init library \n"; 
	}
	
	if (FT_New_Face(ft, fontFilePath.c_str(), 0, &face))
	{
		std::cout << "Error: (FREETYPE) : Can't create new Face(load font) \n";
	}

	FT_Stroker stroker;
	FT_Stroker_New(ft, &stroker);
	//  2 * 64 result in 2px outline
	FT_Stroker_Set(stroker, 2 * 64, FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0);

		// generation of an outline for single glyph:
// 	FT_Error err_code;
// 	FT_Glyph glyphDescStroke;
// 	err_code = FT_Get_Glyph(face->glyph, &glyphDescStroke);
	static double outlineThickness = 10.0;
// 	FT_Stroker_Set(stroker, static_cast<FT_Fixed>(outlineThickness * static_cast<float>(1 << 6)), FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0);
// 	if (err_code == 0)
// 		err_code = FT_Glyph_Stroke(&glyphDescStroke, stroker, true);
// 
	
// 	FT_Bitmap *bitmap_stroke = nullptr;
// 	if (err_code == 0)
// 	{
// 		glyph_bitmap = (FT_BitmapGlyph)glyphDescStroke;
// 		bitmap_stroke = &glyph_bitmap->bitmap;
// 	}

	unsigned int cx = 0, cy = 0, ox = 0, oy = 0;
// 
// 	std::vector<unsigned char> buffer;
// 	if (err_code == 0 && bitmap_stroke)
// 	{
// 		cx = bitmap_stroke->width;
// 		cy = bitmap_stroke->rows;
// 		ox = glyph_bitmap->left;
// 		oy = glyph_bitmap->top;
// 
// 		buffer = std::vector<unsigned char>(cx * cy * 2, 0); // * 2 -> 2 color channels (red and green)
// 		for (unsigned int i = 0; i < cx * cy; ++i)
// 			buffer[i * 2 + 1] = bitmap_stroke->buffer[i];      // + 1 -> 2nd color channel
// 	}
// 
// 	

	FT_Glyph glyphDescFill;
// 	err_code = FT_Get_Glyph(face->glyph, &glyphDescFill);
// 	if (err_code == 0)
// 		err_code = FT_Glyph_To_Bitmap(&glyphDescFill, FT_RENDER_MODE_NORMAL, 0, 1);
// 
// 	FT_Bitmap *bitmap_fill = nullptr;
// 	if (err_code == 0)
// 	{
// 		FT_BitmapGlyph glyph_bitmap = (FT_BitmapGlyph)glyphDescFill;
// 		bitmap_fill = &glyph_bitmap->bitmap;
// 	}

//	if (err_code == 0 && bitmap_fill)
// 	{
// 		unsigned int cx_fill = bitmap_fill->width;
// 		unsigned int cy_fill = bitmap_fill->rows;
// 		unsigned int offset_x = (cx - cx_fill) / 2; // offset because the bitmap my be smaller, 
// 		unsigned int offset_y = (cy - cy_fill) / 2; // then the former
// 
// 		for (unsigned int y = 0; y < cy_fill; ++y)
// 		{
// 			for (unsigned int x = 0; x < cx_fill; ++x)
// 			{
// 				unsigned int i_source = y * cx_fill + x;
// 				unsigned int i_target = (y + offset_y) * cx + x + offset_x;
// 				buffer[i_target * 2 + 0] = bitmap_fill->buffer[i_source]; // + 0 -> 1st color channel
// 			}
// 		}
// 	}

	//FT_Done_Glyph(glyphDescFill);
	//FT_Done_Glyph(glyphDescStroke);

	//FT_Select_Charmap(face, ft_encoding_unicode);
	//glyph_index = 
	


	FT_Set_Pixel_Sizes(face, 0, fontSize);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//glPixelStorei(GL_PACK_ALIGNMENT, 1);

	//FT_Encoding();
	// 9000 for full vn 
	// 15000 for jap 
	for (int c = 0; c < charCount; c++)
	{
		// Load character glyph 

		//glyph_index =  FT_Get_Char_Index(face, c);
		unsigned long t = FT_Get_Char_Index(face, c);
		if (FT_Load_Glyph(face, t, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
// 		FT_UInt glyphIndex = FT_Get_Char_Index(face, c);
// 		FT_Load_Glyph(face, glyphIndex, FT_LOAD_RENDER);
// 		FT_Glyph glyph;
// 		FT_Get_Glyph(face->glyph, &glyph);
// 		FT_Glyph_StrokeBorder(&glyph, stroker, false, true);
// 		FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, nullptr, true);
// 		FT_BitmapGlyph bitmapGlyph = reinterpret_cast<FT_BitmapGlyph>(glyph		
		// Generate textures
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RG8,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


		// Now store character for later use
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		Characters.insert(std::pair<int, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	// Destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void TextRenderer::initShader()
{
	m_shader.compileShaders("Shaders/textShader.vert", "Shaders/textShader.frag");
	m_shader.addAttribute("TexCoords");
	//m_shader.addAttribute("vertexColor");
	//m_shader.addAttribute("vertexUV");
	m_shader.linkShaders();
	
}


void TextRenderer::renderBorderText(const Feintgine::Camera2D & camera, const std::wstring & text,const glm::vec2 &pos,const  Feintgine::Color &color, float scale, unsigned char justification)
{
	
	renderText(camera, text, pos, color, scale, justification);
	
}

void TextRenderer::renderText(const Feintgine::Camera2D & camera, const std::wstring & text, const glm::vec2 & pos,const Feintgine::Color &color, float scale /*= 1*/, unsigned char justification)
{

	m_shader.use();
	
	glBindVertexArray(m_VAO);
	GLint textureUniform = m_shader.getUniformLocation("textColor");
	glUniform4f(textureUniform, color.r, color.g, color.b,color.a);
	glActiveTexture(GL_TEXTURE0);

	GLint pUniform = m_shader.getUniformLocation("projection");
	glm::mat4 objectsMatrix = camera.getCameraMatrix();
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &objectsMatrix[0][0]);

	float xHolder = 0;
	float xGo = 0;
	//float yCenter = 0;
	float middle_y;
	float min_middle_y;
	int count = 0;
	float middle_x = 0;
	
	std::wstring::const_iterator c;
	if (justification == ALIGN_FT_LEFT)
	{
		middle_x = pos.x;
	}

	
	
	if (justification == ALIGN_FT_CENTER)
	{
		for (c = text.begin(); c != text.end(); c++)
		{

			Character ch = Characters[*c];
			middle_y = ch.Size.y * scale;
			if (count == 0)
			{
				min_middle_y = middle_y;
			}
			else
			{
				if (middle_y < min_middle_y)
				{
					min_middle_y = middle_y;

				}
			}
			//middle_y = ch.Bearing.y;
			xGo += (ch.Advance >> 6) * scale;
			count++;

		}
		middle_x = pos.x + ((xHolder - xGo) / 2.0f);
		
	}

	if (justification == ALIGN_FT_RIGHT)
	{
		for (c = text.begin(); c != text.end(); c++)
		{

			Character ch = Characters[*c];
			middle_y = ch.Size.y * scale;
			if (count == 0)
			{
				min_middle_y = middle_y;
			}
			else
			{
				if (middle_y < min_middle_y)
				{
					min_middle_y = middle_y;

				}
			}
			//middle_y = ch.Bearing.y;
			xGo += (ch.Advance >> 6) * scale;
			count++;

		}
		middle_x = pos.x + (xHolder - xGo) ;
	}

	//float middle_x = pos.x;


	totalScale = 0;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];


 		GLfloat xpos = middle_x + ch.Bearing.x * scale;
 		GLfloat ypos = (pos.y - (min_middle_y /2.0f)) - (ch.Size.y - ch.Bearing.y) * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;

		// Update VBO for each character
		GLfloat vertices[6][4] = {

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);

	

		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		middle_x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
		totalScale += (ch.Advance >> 6) * scale;;
	}

	
	
	
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	m_shader.unuse();
	
}

