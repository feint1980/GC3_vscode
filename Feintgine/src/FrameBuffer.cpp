#include "FrameBuffer.h"


namespace Feintgine
{

	FrameBuffer::FrameBuffer()
	{
	}


	FrameBuffer::~FrameBuffer()
	{
	}

	void FrameBuffer::bind()
	{
		glViewport(0, 0, m_width, m_height);
		if (multisampled) {
			glBindFramebuffer(GL_FRAMEBUFFER, m_fbo_multi);
		}
		else {
			glBindFramebuffer(GL_FRAMEBUFFER, m_fbo_single);
		}
	}

	void FrameBuffer::setScreenSize(int width, int height)
	{
		m_width = width;
		m_height = height;
	}

	void FrameBuffer::unbind()
	{
		if (multisampled) {
			glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo_multi); // Make sure your multisampled FBO is the read frame buffer
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo_single);   // Make sure no FBO is set as the draw frame buffer
			glDrawBuffer(GL_BACK);
			glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, m_width, m_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	int FrameBuffer::init(int width, int height, bool isMultisampled /*= true*/, bool useInterpolation /*= false*/)
	{
		m_width = width;
		m_height = height;
		this->multisampled = multisampled;

		glGenFramebuffers(1, &m_fbo_multi);
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo_multi);

		glGenTextures(1, &m_color_tex_multi);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_color_tex_multi);

		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, m_width, m_height, true);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 /*location = 0*/, GL_TEXTURE_2D_MULTISAMPLE, m_color_tex_multi, 0 /*level*/);

		glGenRenderbuffers(1, &m_depth_rb_multi);
		glBindRenderbuffer(GL_RENDERBUFFER, m_depth_rb_multi);

		glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH_COMPONENT32, m_width, m_height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depth_rb_multi);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cerr << "!!!ERROR: Frame buffer not OK :(" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0); ///< avoid pollution

		 //single sampled frame buffer
		glGenFramebuffers(1, &m_fbo_single);
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo_single);

		glGenTextures(1, &m_color_tex_single);
		glBindTexture(GL_TEXTURE_2D, m_color_tex_single);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		if (useInterpolation) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL); ///< how to load from buffer

		glBindTexture(GL_TEXTURE_2D, 0);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 /*location = 0*/, GL_TEXTURE_2D, m_color_tex_single, 0 /*level*/);

		if (this->multisampled == false) {
			glGenRenderbuffers(1, &m_depth_rb_single);
			glBindRenderbuffer(GL_RENDERBUFFER, m_depth_rb_single);

			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, m_width, m_height);
			glBindRenderbuffer(GL_RENDERBUFFER, 0);

			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depth_rb_single);
		}

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cerr << "!!!ERROR: Frame buffer not OK :(" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0); ///< avoid pollution

		return m_color_tex_single;
	}

	void FrameBuffer::cleanup()
	{
		glDeleteTextures(1, &m_color_tex_single);
		glDeleteTextures(1, &m_color_tex_multi);
		glDeleteRenderbuffers(1, &m_depth_rb_single);
		glDeleteRenderbuffers(1, &m_depth_rb_multi);
		glBindFramebuffer(GL_FRAMEBUFFER, 0 /*UNBIND*/);
		glDeleteFramebuffers(1, &m_fbo_single);
		glDeleteFramebuffers(1, &m_fbo_multi);
	}
}