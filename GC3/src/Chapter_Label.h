#pragma once
#include <glm/glm.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SDL-TTF-OpenGL3.hpp>


class Chapter_Label
{
public:
    Chapter_Label();
    ~Chapter_Label();

    void init(tgui::Gui * t_gui, const glm::vec2 & pos, const std::wstring & chapterName1, const std::wstring & chapterName2, float t_lifeTime );
    void setText(const std::wstring &  chapterName, float t_lifeTime );
    void setText2(const std::wstring &  chapterName, float t_lifeTime );
    void setTextes(const std::wstring &  chapterName1, const std::wstring &  chapterName2, float t_lifeTime );
    void update(float deltaTime);

    private :

    glm::vec2 m_pos;
    glm::vec2 m_vel;
    tgui::Label::Ptr m_text;
    tgui::Label::Ptr m_text2;

    tgui::Color m_color = tgui::Color::Yellow;
    tgui::Color m_color2 = tgui::Color::White;

    bool isAlive = false;
    int fadeDirection = 1;
    bool isShowed = true;
    bool isHiding = false;
    float m_tAlpha = 0.0f;
    float m_lifeTime;
    float liveTime = 0.012f;
};
