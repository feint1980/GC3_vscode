#include "Chapter_Label.h"

Chapter_Label::Chapter_Label()
{

}


Chapter_Label::~Chapter_Label()
{
}

void Chapter_Label::init(tgui::Gui * t_gui, const glm::vec2 & pos, const std::wstring & chapterName ,const std::wstring & chapterName2, float t_lifeTime )
{
    if(!t_gui)
    {
        std::cout << "gui is null \n";
        return;
    }

    m_pos = pos;
    m_text = tgui::Label::create(); 
    m_text->setPosition(-pos.x, pos.y);
    m_text->setTextSize(34);
    m_text->setText(chapterName);
    m_text->getRenderer()->setTextColor(m_color);
    m_text->getRenderer()->setBorderColor(tgui::Color::Black);
    m_text->setWidth("100%");
    m_text->setHeight(60);
   // m_text->setSize(0)
    m_text->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
    m_text->getRenderer()->setTextOutlineThickness(4);


    m_text2 = tgui::Label::create();
    m_text2->setPosition(-pos.x, pos.y + 70);
    m_text2->setTextSize(27);
    m_text2->setText(chapterName2);
    m_text2->setWidth("100%");
    m_text2->setHeight(60);
    m_text2->getRenderer()->setTextColor(m_color2);
    m_text2->getRenderer()->setBorderColor(tgui::Color::Black);
    m_text2->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
    m_text2->getRenderer()->setTextOutlineThickness(4);

    
    t_gui->add(m_text);
    t_gui->add(m_text2);
}

void Chapter_Label::setText(const std::wstring &  chapterName, float t_lifeTime )
{
    m_text->setText(chapterName);
    m_lifeTime = t_lifeTime;
}


void Chapter_Label::setText2(const std::wstring &  chapterName, float t_lifeTime )
{
    m_text2->setText(chapterName);
    m_lifeTime = t_lifeTime;
}

void Chapter_Label::setTextes(const std::wstring &  chapterName1, const std::wstring &  chapterName2, float t_lifeTime )
{
    m_text->setText(chapterName1);
    m_text2->setText(chapterName2);
    m_lifeTime = t_lifeTime;
    isShowed = false;
    isAlive = true;
}

void Chapter_Label::update(float deltaTime)
{
    if(!m_text || !m_text2 ||m_lifeTime < 0 )
    {
        return;
    }

    if(isAlive)
    {

        m_lifeTime -=  0.01f * deltaTime;
     
        if(!isShowed)
        {
            if(m_tAlpha <= 1.0f)
            {
                m_tAlpha += 0.1f * deltaTime ;
            }
            else
            {   
                isShowed = true;
            }
        }
        else
        {
            if(m_lifeTime >= 0.0f && m_lifeTime < 1.0f)
            {
                m_tAlpha = m_lifeTime;
            }
        }
        m_text->getRenderer()->setTextColor(tgui::Color(255, 255, 0, 255* m_tAlpha));
        m_text2->getRenderer()->setTextColor(tgui::Color(255, 255, 255, 255* m_tAlpha));

        
    }


}
