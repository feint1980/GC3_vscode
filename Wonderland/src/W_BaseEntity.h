#pragma once

#include <SpriteBatch.h>
#include <F_Sprite.h>
#include <F_AnimatedObject.h>
#include <F_oEvent.h>


class W_BaseEntity
{
public:
    W_BaseEntity();
    ~W_BaseEntity();

    void init(const std::string & animPath, const glm::vec2 & pos);
    void draw(Feintgine::SpriteBatch & spriteBatch);
    void update(float deltaTime);
    void setPos(const glm::vec2 & pos) { m_pos = pos; }
    void playAnimation(const std::string & animationName, int time = -1);

private:
    glm::vec2 m_pos;
    glm::vec2 m_scale;

    Feintgine::F_AnimatedObject m_animations;
};