

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
        textRenderer->renderTextBatched(L"Testtttt", m_bg.getPos(), Feintgine::Color(255, 255, 255, 255), 1.0f, ALIGN_FT_CENTER);
    }

}

void Banner::update(float deltaTime)
{

    if(m_visible)
    {
        // m_color.a = (255 * m_cTickCount);
        if(m_isFadeIn)
        {
            m_cTickCount += deltaTime;
            if(m_cTickCount > DEFAULT_TIME * 1000.0f)
            {
                // m_visible = false;
                m_isFadeIn = false;
                // m_cTickCount = 0.0f;
                m_cTickCount = 1.0f;
            }
        }
        else
        {
            m_cTickCount -= deltaTime;
            if(m_cTickCount < 0.0f)
            {
                m_visible = false;
                m_isFadeIn = true;
            }
        }
    }

}