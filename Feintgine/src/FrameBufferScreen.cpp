#include "FrameBufferScreen.h"


namespace Feintgine
{

	void FrameBufferScreen::initShader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
	{
		compileShaders(vertexShaderFilePath, fragmentShaderFilePath);
		addAttribute("tex");
		addAttribute("time");
		addAttribute("posEffect");
		addAttribute("intensityEffect");
		addAttribute("speed");
		linkShaders();
	}

	void FrameBufferScreen::initFrameTexture(GLuint texture, unsigned int width, unsigned int height)
	{
		m_width = width;
		m_height = height;

		if (_programID == 0) exit(-1);
		glUseProgram(_programID);

		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		const GLfloat vpoint[] = { -1.0f, -1.0f, 0.0f,
			+1.0f, -1.0f, 0.0f,
			-1.0f, +1.0f, 0.0f,
			+1.0f, +1.0f, 0.0f };

		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vpoint), vpoint, GL_STATIC_DRAW);

		GLuint vpoint_id = glGetAttribLocation(_programID, "vpoint");
		glEnableVertexAttribArray(vpoint_id);
		glVertexAttribPointer(vpoint_id, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		const GLfloat vtexcoord[] = { /*V1*/ 0.0f, 0.0f,
			/*V2*/ 1.0f, 0.0f,
			/*V3*/ 0.0f, 1.0f,
			/*V4*/ 1.0f, 1.0f };

		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vtexcoord), vtexcoord, GL_STATIC_DRAW);

		GLuint vtexcoord_id = glGetAttribLocation(_programID, "vtexcoord");
		glEnableVertexAttribArray(vtexcoord_id);
		glVertexAttribPointer(vtexcoord_id, 2, GL_FLOAT, GL_FALSE, 0, NULL);

		m_tex = texture;

		glBindVertexArray(0);
		glUseProgram(0);
	}

	void FrameBufferScreen::load_texture(GLuint texture)
	{
		m_tex = texture;
	}


	void FrameBufferScreen::set_ao_texture(GLuint ao_tex)
	{
		m_ao_tex = ao_tex;
	}

	void FrameBufferScreen::set_depth_texture(GLuint depth_tex)
	{
		m_depth_tex = depth_tex;
	}

	void FrameBufferScreen::cleanup()
	{
		// TODO
	}


	void FrameBufferScreen::setScreenSize(int width, int height)
	{
		m_width = width;
		m_height = height;
	}

	void FrameBufferScreen::draw()
	{
		glBindVertexArray(m_vao);


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_tex);
		GLuint tex_id = glGetUniformLocation(_programID, "tex");
		glUniform1i(tex_id, 0 /*GL_TEXTURE0*/);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		glUseProgram(0);
	}

}