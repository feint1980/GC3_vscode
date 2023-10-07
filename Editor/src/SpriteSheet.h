#pragma once

#include <string>
#include <GLTexture.h>
#include <glm/glm.hpp>
class SpriteSheet //: public SimpleDrawingObject
{
public:
	SpriteSheet();
	~SpriteSheet();

	void setHasTexture(bool value) { hastexture = value; }
	bool isHasTexture() const { return hastexture; }
	 
	void setPath(const std::string & filePath);
	Feintgine::GLTexture getTexture() const { return m_texture; }

	void loadTexture(Feintgine::GLTexture texture);

	std::string getFilePath() const { return m_texturePath; }

	void setVisibility(bool val);

	bool isVisible() const { return show; }

private: 
	bool hastexture = false;

	bool show = false;

	glm::vec2 m_dims;

	Feintgine::GLTexture m_texture;	

	std::string m_texturePath;
};

