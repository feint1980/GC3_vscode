#include "BGM_Label.h"


BGM_Label::BGM_Label()
{

}


BGM_Label::~BGM_Label()
{
}

void BGM_Label::setPos(const glm::vec2 & pos)
{
    m_pos = pos;
    m_text->setPosition(m_pos.x, m_pos.y);
}

void BGM_Label::init(tgui::Gui * t_gui, const glm::vec2 & pos, const std::wstring & songName, float t_lifeTime )
{
    if(!t_gui)
    {
        std::cout << "gui is null \n";
        return;
    }

    m_pos = pos;
    m_text = tgui::Label::create(); 
    m_text->setPosition(pos.x, pos.y);
    m_text->setTextSize(22);
    m_text->setText(songName);
    m_text->getRenderer()->setTextColor(tgui::Color(255, 255, 255, 0));
    m_text->getRenderer()->setBorderColor(tgui::Color::Black);
    m_text->getRenderer()->setTextOutlineThickness(4);
   

    t_gui->add(m_text);
}



void BGM_Label::setText(const std::wstring &  songName, float t_lifeTime )
{
    m_text->setText(songName);
    
    m_lifeTime = t_lifeTime;
}

void BGM_Label::setLifeTime(float t_lifeTime)
{
    m_lifeTime = t_lifeTime;
    isAlive = true;
}

void BGM_Label::update(float deltaTime)
{
    if(!m_text ||m_lifeTime < 0 )
    {
        return;
    }

    if(isAlive)
    {
 
        if (m_pos.x  < 270)
        {
            m_vel.x = 10 ;
        }
        else if (m_pos.x > 270)
        {
            m_vel.x = .25f ;
        }

      //  }

        if (m_lifeTime > 0)
        {
            m_lifeTime -= liveTime * deltaTime;
            m_pos += m_vel * deltaTime;
         
        }
        else
        {
         
            isAlive = false;
        }
        if(m_lifeTime > 0 && m_lifeTime < 1.0f)
        {
            m_tAlpha = m_lifeTime;
        }
        m_text->setPosition(m_pos.x, m_pos.y);
        m_text->getRenderer()->setTextColor(tgui::Color(255, 255,255, 255 * m_tAlpha));

    }
  
}