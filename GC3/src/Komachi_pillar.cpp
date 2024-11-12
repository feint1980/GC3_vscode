
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

void Komachi_pillar::spawn(const glm::vec2 & pos, const glm::vec2 & dim, const Feintgine::Color & color)
{
    m_pos = pos;
    m_dims = dim;
    m_color = color;
    m_visible = true;
}

void Komachi_pillar::draw(Feintgine::SpriteBatch & spriteBatch)
{

    if(m_visible)
    {
        glm::vec4 desRect;
        desRect.x = m_pos.x - m_displayDim.x / 2.0f;
        desRect.y = m_pos.y - m_displayDim.y / 2.0f;
        desRect.z = m_displayDim.x;
        desRect.w = m_displayDim.y;


        switch (m_frameIndex)
        {
        case 0:
            m_textureId = m_texture_1.id;
            break;
        case 1:
            m_textureId = m_texture_2.id;
            break;
        }
        
        spriteBatch.draw(desRect, m_uv, m_textureId, 0, m_color, 0);
        
    }

}

void Komachi_pillar::setExpand(const glm::vec2 & targetDim, float time)
{
    m_expandTime = time;
    m_targetDim = targetDim;
    // calculate the extend rate based on current m_dims and targetDim
    m_extendRate = (targetDim - m_dims) / m_expandTime;

    m_updateState |= UPDATE_DIMENSION;

}

void Komachi_pillar::setFlash(float time, float freq)
{
    m_flashTime = time;
    m_flashFreq = freq;

    m_updateState |= UPDATE_FLASH;
}

void Komachi_pillar::setUpdateUV(float time, float rate)
{
    m_updateUVTime = time;
    m_updateUVRate = rate;
    m_updateState |= UPDATE_UV;
}

void Komachi_pillar::drawLight(Feintgine::LightBatch & lightBatch)
{
    
}

void Komachi_pillar::update(float deltaTime)
{
    // check update state with bitwise
    if (m_updateState & UPDATE_DIMENSION)
    {
        if (m_expandTime > 0.0f)
        {
            m_dims += m_extendRate * deltaTime;
            m_expandTime -= deltaTime;
        }
        else
        {
            m_dims = m_targetDim;
            m_updateState &= ~UPDATE_DIMENSION;
        }
    }

    if (m_updateState & UPDATE_FLASH)
    {
        if (m_flashTime > 0.0f)
        {
            m_flashTime -= deltaTime;
            m_displayDim = m_dims * sin(m_flashFreq * m_flashTime);
        }
        else
        {
            m_updateState &= ~UPDATE_FLASH;
        }
    
    }

    if (m_updateState & UPDATE_UV)
    {
        if (m_updateUVTime > 0.0f)
        {
            m_updateUVTime -= deltaTime;
            m_uv.y += m_updateUVRate * deltaTime;
        }
        else
        {
            m_updateState &= ~UPDATE_UV;
        }

    }

}