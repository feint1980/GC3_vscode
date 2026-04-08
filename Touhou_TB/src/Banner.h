
#ifndef BANNER_H
#define BANNER_H

#include <TextRenderer.h>
// #include "TB_EmptyObject.h"
#include "TB_EmptyObject.h"
#include <ResourceManager.h>

#define DEFAULT_TIME 10

class Banner
{
public:
    Banner();
    ~Banner();

    void init(const std::string & backgroundPath);
    void draw(Feintgine::SpriteBatch & spriteBatch);

    void drawText(TextRenderer * textRenderer);

    void update(float deltaTime);

    void setVisible(bool value) { 
        m_visible = value;
    }

    void setMessage(const std::string & mesage) 
    { 

        m_mesage = mesage; 
        m_wMessage = feint_common::Instance()->convertStringtoWstring(mesage);
    }
    void showMessage(const std::string & mesage) 
    {   
        // if(!m_visible)
        // {
        m_scale = 3.4f;
        // } 
        m_mesage = mesage;
        m_visible = true;
        m_cTickCount = 0.0f;
        m_isFadeIn = false;
        m_wMessage = feint_common::Instance()->convertStringtoWstring(mesage);
    }

    void setMessage(const std::wstring & mesage) 
    { 
        m_wMessage = mesage; 
    }
    void showMessage(const std::wstring & mesage) 
    {    
        // if(!m_visible)
        // {
        m_scale = 3.4f;
        // } 
        m_wMessage = mesage;
        m_visible = true;
        m_cTickCount = 0.0f;
        m_isFadeIn = false;
    }

    private:

    bool m_visible = false;
    bool m_isFadeIn = false;

    glm::vec2 m_bgPos;

    TB_EmptyObject m_bg;

    float m_textScale = 1.0f;
    float m_scale = 1.0;

    Feintgine::Color m_color;

    float m_cTickCount = 0.0;
    float m_targetTickCount = 0.0;

    float m_alpha = 1.0f;

    std::string m_mesage;
    std::wstring m_wMessage;
    glm::vec2 m_mesagePos;

    float m_maxScale = 1.5;
    float m_scaleRate = 0.1f;


};



#endif // BANNER_H