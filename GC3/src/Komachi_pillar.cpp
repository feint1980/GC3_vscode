
#include "Komachi_pillar.h"



Komachi_pillar::Komachi_pillar()
{

}

Komachi_pillar::~Komachi_pillar()
{

}

void Komachi_pillar::init(const Feintgine::GLTexture & texture_1, const Feintgine::GLTexture & texture_2, const glm::vec2 & pos, const glm::vec2 & dim, const Feintgine::Color & color)
{
    m_texture_1 = texture_1;
    m_texture_2 = texture_2;
    m_pos = pos;
    m_dims = dim;
    m_color = color;
}

void Komachi_pillar::draw(Feintgine::SpriteBatch & spriteBatch)
{
    glm::vec4 desRect;

    desRect.x = m_pos.x - m_dims.x / 2.0f;
    desRect.y = m_pos.y - m_dims.y / 2.0f;
    desRect.z = m_dims.x;
    desRect.w = m_dims.y;


    switch (m_frameIndex)
    {
    case 0:
        m_textureId = m_texture_1.id;
        break;
    case 1:
        m_textureId = m_texture_2.id;
        break;
    }
    

    spriteBatch.draw(desRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), m_textureId, 0, m_color, 0);

}


