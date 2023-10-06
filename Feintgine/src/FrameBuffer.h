#pragma once

#include <glew.h>
#include <iostream>


namespace Feintgine
{

	class FrameBuffer
	{
	public:
		FrameBuffer();
		~FrameBuffer();

		void bind();

		void setScreenSize(int width, int height);

		void unbind();

		int init(int width, int height, bool isMultisampled = true, bool useInterpolation = false);

		GLuint get_texture()
		{
			return m_color_tex_single;
		}

		void cleanup();
	private:
		bool multisampled;
		int m_width;
		int m_height;
		GLuint m_fbo_multi;
		GLuint m_fbo_single;
		GLuint m_depth_rb_multi;
		GLuint m_depth_rb_single;
		GLuint m_color_tex_multi;
		GLuint m_color_tex_single;

	};
}

