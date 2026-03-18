#ifndef CSLOT_H 
#define CSLOT_H
#include <ResourceManager.h>
#include "EmptyObject.h"

class CSlot 
{
public:
    CSlot();
    ~CSlot();

    CSlot(const std::string & texturePath, int row, int colum, int side);

    void draw(Feintgine::SpriteBatch & spriteBatch);

    void update(float deltaTime);

    void init (const std::string & texturePath, int row, int colum, int side);

    glm::vec2 getPos() const
    {
        return m_actualPos;
    }

    glm::ivec2 getIndex() const
    {
        return m_index;
    }

    int getSide() const
    {
        return m_side;
    }


    private:

    glm::ivec2 m_index = glm::ivec2(0,0);
    glm::vec2 m_actualPos = glm::vec2(0,0);
    glm::vec2 m_targetPos = glm::vec2(0,0);


    int m_state = 0;
    int m_side = 1; // 1 | left  2 | right
    EmptyObject m_circle ; 

};


#endif // CSLOT_H