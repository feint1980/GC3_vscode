#include "SpriteSheet.h"



SpriteSheet::SpriteSheet()
{
}


SpriteSheet::~SpriteSheet()
{
}

void SpriteSheet::setPath(const std::string & filePath)
{
	m_texturePath = filePath;
}

void SpriteSheet::loadTexture(Feintgine::GLTexture texture)
{
	m_texture = texture;
	m_dims.x = m_texture.width;
	m_dims.y = m_texture.height;
}

void SpriteSheet::setVisibility(bool val)
{
	show = val;
}
