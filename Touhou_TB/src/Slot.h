
#pragma once
#include <ResourceManager.h>
#include "EmptyObject.h"


class Slot 
{

public: 

    Slot();
    ~Slot();

    void draw(Feintgine::SpriteBatch & spriteBatch);
    void update(float deltaTime);

    void init(int row, int colum, int side);

    bool isHovered(const glm::vec2 & mousePos);

    void setState(int state);

    int getState() const
    {
        return m_state;
    }

    glm::vec2 getPos() const
    {
        return m_actualPos;
    }

    glm::ivec2 getIndex() const
    {
        return m_index;
    }

    private:
    
    glm::ivec2 m_index = glm::ivec2(0,0);
    glm::vec2 m_actualPos = glm::vec2(0,0);

    int m_state = 0;
    int m_side = 1; // 1 | left  2 | right
    EmptyObject m_circle ; 


};