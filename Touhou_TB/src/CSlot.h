#ifndef CSLOT_H 
#define CSLOT_H
#include <ResourceManager.h>
#include "EmptyObject.h"

class CombatCharacter;

class CSlot 
{
public:
    CSlot();
    ~CSlot();

    CSlot(const std::string & texturePath, int row, int colum, int side);

    CSlot(int side, int row, int colum);

    void draw(Feintgine::SpriteBatch & spriteBatch);

    void update(float deltaTime);

    void init (const std::string & texturePath, int row, int colum, int side);

    bool isHovered(const glm::vec2 & mousePos);

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

    CombatCharacter * getCurrentCharacter() { return m_characterInSlot; }

    void setCurrentCharacter(CombatCharacter * character) { m_characterInSlot = character; }
    private:

    glm::ivec2 m_index = glm::ivec2(0,0);
    glm::vec2 m_actualPos = glm::vec2(0,0);
    glm::vec2 m_targetPos = glm::vec2(0,0);

    CombatCharacter * m_characterInSlot = nullptr;


    int m_state = 0;
    int m_side = 1; // 1 | left  2 | right
    EmptyObject m_circle ; 

};


#endif // CSLOT_H