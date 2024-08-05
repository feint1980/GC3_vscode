
#pragma once
#include "EmptyObject.h"
#include <ResourceManager.h>

class GUI_icon 
{

public:

    GUI_icon();
    ~GUI_icon();

    void init(const std::string & texturePath, const glm::vec2 & pos, const glm::vec2 & dim, float depth);
    void setTurnCost(float cost)
    {
        m_turnCost = cost;
    }
    void setDescription(const std::string & description)
    {
        m_description = description;
    }
    void setName(const std::string & name)
    {
        m_name = name;
    }
    void draw(Feintgine::SpriteBatch & spriteBatch);
    void update(float deltaTime);

    void setPos(const glm::vec2 & pos);

    void setDim(const glm::vec2 & dim);

    glm::vec2 getPos() const
    {
        return m_icon.getPos();
    }

    glm::vec2 getDim() const
    {
        return m_icon.getDimentions();
    }


    float getTurnCost() const 
    {
        return m_turnCost;
    }


    

protected:


    EmptyObject m_icon;
    std::string m_description;
    std::string m_name;
    float m_turnCost = 0.0f;

    
};