
#ifndef CHARACTER_ICON_H
#define CHARACTER_ICON_H

#include "EmptyObject.h"

class CharacterIcon
{
public:
    CharacterIcon();
    ~CharacterIcon();

    void init(const std::string & texturePath, const glm::vec2 & dim);

    void draw(Feintgine::SpriteBatch & spriteBatch);


private:
    EmptyObject m_portrait ;
    bool m_isInit = false;
};


#endif // CHARACTER_ICON_H
