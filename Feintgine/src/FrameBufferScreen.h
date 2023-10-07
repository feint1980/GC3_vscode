#pragma once
#include <GL/glew.h>
#include <iostream>
#include "GLSLProgram.h"
#include <glm/glm.hpp>
// two triangles that should take all the screen space to draw the frame buffer
namespace Feintgine
{
    class FrameBufferScreen : public GLSLProgram
    {

    public:
        //texture is the frame buffer
		void initShader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

		void initFrameTexture(GLuint texture, unsigned int screen_width, unsigned int screen_height);
		

		void load_texture(GLuint texture);


		void set_ao_texture(GLuint ao_tex);

		void set_depth_texture(GLuint depth_tex);

		void cleanup();
		void setScreenSize(int width, int height);
       
		void draw();

		int getWidth() const {
			return m_width;
		}

		int getHeight() const {
			return m_height;
		}
       

    protected:
        GLuint m_vao;
        GLuint m_vbo;
        GLuint m_tex;
        GLuint m_ao_tex;
        GLuint m_depth_tex;
        unsigned int m_width;
        unsigned int m_height;
    };


}