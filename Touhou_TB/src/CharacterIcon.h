
#ifndef CHARACTER_ICON_H
#define CHARACTER_ICON_H

#include "EmptyObject.h"
#include <ResourceManager.h>
class CharacterIcon
{
public:
    CharacterIcon();
    ~CharacterIcon();

    void init(const std::string & texturePath,int side, const glm::vec2 & dim);

    void draw(Feintgine::SpriteBatch & spriteBatch);

    void setPos(const glm::vec2 & pos)
    {
        m_portrait.setPos(pos);
        m_border.setPos(pos);
    }
    void setSpeed(int speed) { m_speed = speed; }
    void setSpeedRoll(int speed) { m_speedRoll = speed; }
    int getSpeed() { return m_speed; }
    int getSpeedRoll() { return m_speedRoll; }

private:
    EmptyObject m_portrait;
    EmptyObject m_border;
    int m_side = 0;
    int m_speed = 0;
    int m_speedRoll = 0;
    bool m_isInit = false;
};


#endif // CHARACTER_ICON_H
