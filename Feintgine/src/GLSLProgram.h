
#ifndef _GLSLPROGRAM_H_
#define _GLSLPROGRAM_H_

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "F_Logger.h"
namespace Feintgine {

	//This class handles the compilation, linking, and usage of a GLSL shader program.
	//Reference: http://www.opengl.org/wiki/Shader_Compilation
	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

		void compileShadersFromSource(const char* vertexSource, const char* fragmentSource);

		void linkShaders();

		void addAttribute(const std::string& attributeName);

		GLint getUniformLocation(const std::string& uniformName);

		void setBool(const std::string& name, bool value) const
		{
			glUniform1i(glGetUniformLocation(_programID, name.c_str()), (int)value);
		}
		// ------------------------------------------------------------------------
		void setUniformInt(const std::string& name, int value) const
		{
			glUniform1i(glGetUniformLocation(_programID, name.c_str()), value);
		}
		// ------------------------------------------------------------------------
		void setUniformFloat(const std::string& name, float value) const
		{
			glUniform1f(glGetUniformLocation(_programID, name.c_str()), value);
		}
		// ------------------------------------------------------------------------
		void setUniformVec2(const std::string& name, const glm::vec2& value) const
		{
			glUniform2fv(glGetUniformLocation(_programID, name.c_str()), 1, &value[0]);
		}
		void setUniformVec2(const std::string& name, float x, float y) const
		{
			glUniform2f(glGetUniformLocation(_programID, name.c_str()), x, y);
		}
		// ------------------------------------------------------------------------
		void setUniformVec3(const std::string& name, const glm::vec3& value) const
		{
			glUniform3fv(glGetUniformLocation(_programID, name.c_str()), 1, &value[0]);
		}
		void setUniformVec3(const std::string& name, float x, float y, float z) const
		{
			glUniform3f(glGetUniformLocation(_programID, name.c_str()), x, y, z);
		}
		// ------------------------------------------------------------------------
		void setUniformVec4(const std::string& name, const glm::vec4& value) const
		{
			glUniform4fv(glGetUniformLocation(_programID, name.c_str()), 1, &value[0]);
		}
		void setUniformVec4(const std::string& name, float x, float y, float z, float w)
		{
			glUniform4f(glGetUniformLocation(_programID, name.c_str()), x, y, z, w);
		}
		// ------------------------------------------------------------------------
		void setUniformMat2(const std::string& name, const glm::mat2& mat) const
		{
			glUniformMatrix2fv(glGetUniformLocation(_programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
		}
		// ------------------------------------------------------------------------
		void setUniformMat3(const std::string& name, const glm::mat3& mat) const
		{
			glUniformMatrix3fv(glGetUniformLocation(_programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
		}
		// ------------------------------------------------------------------------
		void setUniformMat4(const std::string& name, const glm::mat4& mat) const
		{
			glUniformMatrix4fv(glGetUniformLocation(_programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
		}

		int getNumAttribute() const { return _numAttributes; }

		void use();
		void unuse();

		GLuint getID() const { return _programID; }

		void dispose();
		protected:

		int _numAttributes;

		void compileShader(const char* source, const std::string& name, GLuint id);

		GLuint _programID;

		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;
		std::string shaderName;
	};

}
#endif 