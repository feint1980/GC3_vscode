
#pragma once
#include "EmptyObject.h"
#include <ResourceManager.h>

class GUI_icon 
{

public:

    GUI_icon();
    ~GUI_icon();

    void init(const std::string & texturePath, const glm::vec2 & pos, const glm::vec2 & dim);
    void setTurnCost(float cost)
    {
        m_turnCost = cost;
    }

    void setManaCost(float cost)
    {
        m_manaCost = cost;
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

    std::string getDescription() const
    {
        return m_description;
    }

    std::string getName() const
    {
        return m_name;
    }

    glm::vec2 getPos() const
    {
        return m_icon.getPos();
    }

    glm::vec2 getDim() const
    {
        return m_icon.getDimentions();
    }

    void setSpecialID(unsigned int id)
    {
        m_specialID = id;
    }

    unsigned int getSpecialID() const
    {
        return m_specialID;
    }

    float getTurnCost() const 
    {
        return m_turnCost;
    }

    float getManaCost() const
    {
        return m_manaCost;
    }

    std::string getTurnCostString() const
    {
        return m_turnCostString;
    }

    std::string getManaCostString() const
    {
        return m_manaCostString;
    }

    void setTurnCostString(const std::string & str)
    {
        m_turnCostString = str;
    }

    void setManaCostString(const std::string & str)
    {
        m_manaCostString = str;
    }

protected:

    unsigned int m_specialID = 0;
    EmptyObject m_icon;
    std::string m_description;
    std::string m_name;
    float m_turnCost = 0.0f;
    float m_manaCost = 0.0f;
    std::string m_turnCostString = "";
    std::string m_manaCostString = "";

    
};