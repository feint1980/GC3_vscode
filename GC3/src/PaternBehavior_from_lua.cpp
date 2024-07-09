#include "PaternBehavior_from_lua.h"


PaternBehavior_from_lua::PaternBehavior_from_lua()
{
    for(int i = 0 ; i  < 4 ; i++)
    {
        // init all the values to 1 ( not 0 because it may have division)
        m_factors.push_back(1);
    }
    m_xNode = new Feintgine::AST_Node();
    m_yNode = new Feintgine::AST_Node();

}

void PaternBehavior_from_lua::create(const std::string & xNodeEquation, const std::string & yNodeEquation, float radius)
{

    m_rad = radius;

    m_xNode->setTvalue(&m_t);
    m_yNode->setTvalue(&m_t);
    m_xNode->setRvalue(&m_rad);
    m_yNode->setRvalue(&m_rad);

    m_xNode->parseData(xNodeEquation);
    m_yNode->parseData(yNodeEquation);


}

void PaternBehavior_from_lua::setFactor(const std::vector<float> & factors)
{
    m_factors = factors;
    m_xNode->setFactors(m_factors);
    m_yNode->setFactors(m_factors);
}

void PaternBehavior_from_lua::setValue(char varName, float value)
{
    m_xNode->setValue(varName, value);
    m_yNode->setValue(varName, value);
}

void PaternBehavior_from_lua::setRadius(float radius)
{
    m_rad = radius;
}

PaternBehavior_from_lua::~PaternBehavior_from_lua()
{

}


void PaternBehavior_from_lua::update(float deltaTime)
{
    m_t += m_rate * deltaTime ;  

    float calculateAngle = degreeToRad(360.0f / m_bullets.size());
    for (int i = 0; i < m_bullets.size(); i++)
    {
        m_bullets[i]->setDestination(calculatePos( m_t + (float) i, calculateAngle * i));
    }  

}


glm::vec2 PaternBehavior_from_lua::calculatePos(float t,float additionalAngle)
{
    glm::vec2 returnVal;

    returnVal.x = m_xNode->getValue();
    returnVal.y = m_yNode->getValue();

    std::cout << "calculate value x : " << returnVal.x << " y : " << returnVal.y << "\n";
    return returnVal;
}