

#include "Banner.h"



Banner::Banner()
{

}

Banner::~Banner()
{

}

void Banner::init(const std::string & backgroundPath)
{
    m_color = Feintgine::Color(255, 255, 255, 255);
    m_bg.init(Feintgine::ResourceManager::getTexture(backgroundPath), glm::vec2(0, 230), glm::vec2(720, 240) * 0.75f, m_color);
    m_visible = true;
}   

void Banner::draw(Feintgine::SpriteBatch & spriteBatch)
{
    if(m_visible)
    {
        m_bg.draw(spriteBatch);
    }
}

void Banner::drawText(TextRenderer * textRenderer)
{
    // textRenderer->renderTextBatched()
    if(m_visible)
    {
        std::wstring ta = feint_common::Instance()->convertStringtoWstring(m_mesage);
        textRenderer->renderTextBatched(ta, m_bg.getPos(), m_color, m_scale, ALIGN_FT_CENTER);
    }

}

void Banner::update(float deltaTime)
{

    if(m_visible)
    {
        // std::cout << m_cTickCount << "\n";
        m_color.a = (0.5f
             * m_cTickCount);
        m_bg.setColor(m_color);
        if(m_scale > 1.0)
        {
            m_scale -= deltaTime * 0.000025f;
            
        }
        else
        {
            m_scale = 1.0f;
        }
        m_bg.setDim(glm::vec2(720, 240) * 0.75f * m_scale);
        if(!m_isFadeIn)
        {
            m_cTickCount += deltaTime * 0.05;
            if(m_cTickCount > DEFAULT_TIME )
            {
                // m_visible = false;
                m_isFadeIn = true;
                // m_cTickCount = 0.0f;
                m_cTickCount = 1.0f;
            }
        }
        else
        {
            m_cTickCount -= deltaTime * 0.05 ;
            if(m_cTickCount < 0.0f)
            {
                m_isFadeIn = false;
                m_visible = false;
                
            }
        }
    }

}