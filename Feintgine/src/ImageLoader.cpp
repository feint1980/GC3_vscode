#include "ImageLoader.h"

#include <vector>
#include <string>
namespace Feintgine{


	std::mutex ImageLoader::m_mutex_t;
	GLTexture ImageLoader::loadPNG(const std::string & filePath)
	{
		


		GLTexture *texture =  new GLTexture();

		std::vector <unsigned char> in;
		std::vector <unsigned char> out;
		unsigned long width, height;

		if (IOManager::readFileToBuffer(filePath, in) == false)
		{
			fatalError(" ko load dc PNG " + filePath );
		}
		
		int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
		if (errorCode != 0)
		{
			fatalError("decode that bai " + std::to_string(errorCode));
		}
		
		glGenTextures(1, &(texture->id));

		if(texture->id ==0)
		{

			
			m_mutex_t.lock();

			A_Context_saver::getContext_saver()->addOut(out);
			A_Context_saver::getContext_saver()->addTextureBuffer(filePath,out);
			m_mutex_t.unlock();
		}
		else
		{
		
			glBindTexture(GL_TEXTURE_2D, texture->id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

			glGenerateMipmap(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, 0);
			
		}
	
		texture->width = width;
		texture->height = height;

		return *texture;


	}
}