#pragma once
#include <glm/glm.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SDL-TTF-OpenGL3.hpp>


class BGM_Label
{
public:
    BGM_Label();
    ~BGM_Label();
    
    void init(tgui::Gui * t_gui, const glm::vec2 & pos, const std::wstring & songName, float t_lifeTime );
    void setText(const std::wstring &  songName, float t_lifeTime );
    void update(float deltaTime);
    void setLifeTime(float t_lifeTime);
    void setPos(const glm::vec2 & pos);

    private :

    glm::vec2 m_pos;
    glm::vec2 m_vel;
    tgui::Label::Ptr m_text;
    bool isAlive = false;
    bool isTransit = false;
    float m_tAlpha = 1.0f;
    float m_lifeTime;
    float liveTime = 0.012f;

};


