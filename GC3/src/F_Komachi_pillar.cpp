
#include "F_Komachi_pillar.h"



F_Komachi_pillar::F_Komachi_pillar()
{

}

F_Komachi_pillar::~F_Komachi_pillar()
{

}

void F_Komachi_pillar::init(const Feintgine::GLTexture & texture_1, const Feintgine::GLTexture & texture_2, const glm::vec2 & pos, const glm::vec2 & dim, const Feintgine::Color & color)
{
    m_texture_1 = texture_1;
    m_texture_2 = texture_2;
    m_pos = pos;
    m_dims = dim;
    m_displayDim = dim;
    m_color = color;
}

void F_Komachi_pillar::spawn(const glm::vec2 & pos, const glm::vec2 & dim, const Feintgine::Color & color)
{
    m_pos = pos;
    m_dims = dim;
    m_color = color;
    m_visible = true;
}

void F_Komachi_pillar::draw(Feintgine::SpriteBatch & spriteBatch)
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
        
        spriteBatch.draw(desRect, m_uv, m_textureId, -1, m_color, 0);
        
    }

}

void F_Komachi_pillar::setExpand(const glm::vec2 & targetDim, float time)
{
    m_expandTime = time;
    m_targetDim = targetDim;
    // calculate the extend rate based on current m_dims and targetDim
    m_extendRate = (targetDim - m_dims) / m_expandTime;

    m_updateState |= UPDATE_DIMENSION;

}


void F_Komachi_pillar::setMove(const glm::vec2 & targetPos, float time)
{
    m_moveTime = time;
    m_targetPos = targetPos;
    m_moveRate = (targetPos - m_pos) / m_moveTime;    

    m_updateState |= UPDATE_POS;

}

void F_Komachi_pillar::setFlash(float time, float freq)
{
    m_flashTime = time;
    m_flashFreq = freq;

    m_updateState |= UPDATE_FLASH;
}

void F_Komachi_pillar::setUpdateUV(float time, float rate)
{
    m_updateUVTime = time;
    m_updateUVRate = rate;
    m_updateState |= UPDATE_UV;
}

void F_Komachi_pillar::setColorChange(const Feintgine::Color & targetColor, float time)
{
    m_targetColor = targetColor;
    m_changeColorTime = time;
    m_updateState |= UPDATE_COLOR;
    m_changeColorRate.r = (targetColor.r - m_color.r) / m_changeColorTime;
    m_changeColorRate.g = (targetColor.g - m_color.g) / m_changeColorTime;
    m_changeColorRate.b = (targetColor.b - m_color.b) / m_changeColorTime;
    m_changeColorRate.a = (targetColor.a - m_color.a) / m_changeColorTime;

}

void F_Komachi_pillar::setLight(const glm::vec4 & color, const glm::vec3 & attenuation, float lifeTime)
{
    std::cout << "cpp setlight called \n";
    m_lightColor = color;
    m_attentionua = attenuation;
    m_lightLifetime = lifeTime;
}

void F_Komachi_pillar::setLightColorTarget(const Feintgine::Color & targetColor, float time)
{
    m_lightColorTarget = targetColor;
    m_lightColorTime = time;
    m_updateState |= UPDATE_LIGHT_COLOR;

    m_lightColorRate.r = (targetColor.r - m_lightColor.r) / m_lightColorTime;
    m_lightColorRate.g = (targetColor.g - m_lightColor.g) / m_lightColorTime;
    m_lightColorRate.b = (targetColor.b - m_lightColor.b) / m_lightColorTime;
    m_lightColorRate.a = (targetColor.a - m_lightColor.a) / m_lightColorTime;

}

void F_Komachi_pillar::setLightAttenuationTarget(const glm::vec3 & targetAttenuation, float time)
{
    m_attentionuaTarget = targetAttenuation;
    m_attentionuaTime = time;
    m_updateState |= UPDATE_LIGHT_ATT;

    m_attentionuaRate = (targetAttenuation - m_attentionua) / m_attentionuaTime;
}

void F_Komachi_pillar::drawLight(Feintgine::LightBatch & lightBatch)
{

    if(m_lightLifetime > 0.1f)
    {
        glm::vec2 tPos = m_pos;
        float algn = 150;
        tPos.y -= 400;
        t_attentionua = m_attentionua + abs(cos(m_lightLifetime)) * 1.3f;

        if(m_isShowLightSupport)
        {
            for (int i = -2; i < 3; i++)
            {
                tPos.x = m_pos.x + algn * i;
                lightBatch.addLight(tPos, glm::vec4(m_lightColor.r, m_lightColor.g, m_lightColor.b, m_lightLifetime),
            glm::vec3(1.0f / t_attentionua.x, 1.0f / t_attentionua.y, 1.0f / t_attentionua.z));
            }
        }
		
		
        // tPos.x += 150;
        // lightBatch.addLight(tPos, glm::vec4(m_lightColor.r, m_lightColor.g, m_lightColor.b, m_lightLifetime),
        // glm::vec3(1.0f / t_attentionua.x, 1.0f / t_attentionua.y, 1.0f / t_attentionua.z));
        // tPos.x -= 300;
        // lightBatch.addLight(tPos, glm::vec4(m_lightColor.r, m_lightColor.g, m_lightColor.b, m_lightLifetime),
        // glm::vec3(1.0f / t_attentionua.x, 1.0f / t_attentionua.y, 1.0f / t_attentionua.z));
        tPos.x = m_pos.x;
		lightBatch.addRayLight(tPos, glm::vec4(m_lightColor.r * 0.5f, m_lightColor.g * 0.5f, m_lightColor.b * 0.5f, m_lightLifetime),
			glm::vec3(1.0f / t_attentionua.x, 1.0f / t_attentionua.y, 1.0f / t_attentionua.z),degreeToRad(-90.0f));
	}

}

void F_Komachi_pillar::update(float deltaTime)
{
    // check update state with bitwise
    if (m_updateState & UPDATE_DIMENSION)
    {
        if (m_expandTime > 0.0f)
        {
            //std::cout << m_expandTime << "\n";
            m_dims += m_extendRate * deltaTime;
            m_displayDim = m_dims;
            m_expandTime -= deltaTime;
        }
        else
        {
            m_dims = m_targetDim;
            m_displayDim = m_dims;
            m_updateState &= ~UPDATE_DIMENSION;
        }
    }
    if (m_updateState & UPDATE_FLASH)
    {
        if (m_flashTime > 0.0f)
        {
            m_flashTime -= deltaTime;
            m_displayDim.x = m_dims.x  + m_flashFreq * sin(  m_flashTime);
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
    if(m_updateState & UPDATE_POS)
    {
        if(m_moveTime > 0.0f)
        {
            m_pos += m_moveRate * deltaTime;
            m_moveTime -= deltaTime;
        }
        else
        {
            m_updateState &= ~UPDATE_POS;
            m_pos = m_targetPos;
        }
    }
    if(m_updateState & UPDATE_COLOR)
    {
        if(m_changeColorTime > 0.0f)
        {
            m_color.r += m_changeColorRate.r * deltaTime;
            m_color.g += m_changeColorRate.g * deltaTime;
            m_color.b += m_changeColorRate.b * deltaTime;
            m_color.a += m_changeColorRate.a * deltaTime;
            m_changeColorTime -= deltaTime;
        }
        else
        {
            m_updateState &= ~UPDATE_COLOR;
            m_color = m_targetColor;
        }
    }
    if(m_updateState & UPDATE_LIGHT_COLOR)
    {
        if(m_lightColorTime > 0.0f)
        {
            m_lightColor.r += m_lightColorRate.r * deltaTime;
            m_lightColor.g += m_lightColorRate.g * deltaTime;
            m_lightColor.b += m_lightColorRate.b * deltaTime;
            m_lightColor.a += m_lightColorRate.a * deltaTime;
            m_lightColorTime -= deltaTime;
        }
        else
        {
            m_updateState &= ~UPDATE_LIGHT_COLOR;
            m_lightColor = m_lightColorTarget;
        }
    }
    if(m_updateState & UPDATE_LIGHT_ATT)
    {
        if(m_attentionuaTime > 0.0f)
        {
            m_attentionua += m_attentionuaRate * deltaTime;
            m_attentionuaTime -= deltaTime;
        }
        else
        {
            m_updateState &= ~UPDATE_LIGHT_ATT;
            m_attentionua = m_attentionuaTarget;
        }
    }
    if(m_lightLifetime > 0.0f)
    {
        m_lightLifetime -= deltaTime;
    }

}