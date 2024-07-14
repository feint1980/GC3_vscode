#include "PaternBehavior_from_lua.h"


PaternBehavior_from_lua::PaternBehavior_from_lua()
{
    for(int i = 0 ; i  < 4 ; i++)
    {
        // init all the values to 1 ( not 0 because it may have division)
        m_factors.push_back(i);
    }
    
}

void PaternBehavior_from_lua::create(const std::string & xNodeEquation, const std::string & yNodeEquation, float radius)
{

    m_rad = radius;


    m_xNode.setTValue(m_t);
    m_yNode.setTValue(m_t);
    m_xNode.setRadius(m_rad);
    m_yNode.setRadius(m_rad);

    m_xNode.init(xNodeEquation);
    m_yNode.init(yNodeEquation);


}

void PaternBehavior_from_lua::setFactor(const std::vector<float> & factors)
{
    m_factors = factors;
    m_xNode.setFactors(m_factors);
    m_yNode.setFactors(m_factors);
}

void PaternBehavior_from_lua::setValue(char varName, float value)
{
    m_xNode.setValue(varName, value);
    m_yNode.setValue(varName, value);
}

void PaternBehavior_from_lua::setRadius(float radius)
{
    m_rad = radius;

    m_xNode.setRadius(m_rad);
    m_yNode.setRadius(m_rad);
}

PaternBehavior_from_lua::~PaternBehavior_from_lua()
{

}


void PaternBehavior_from_lua::update(float deltaTime)
{
    m_t += m_rate * deltaTime ;  

    m_xNode.setTValue(m_t);
    m_yNode.setTValue(m_t);

    float calculateAngle = degreeToRad(360.0f / m_bullets.size());
    for (int i = 0; i < m_bullets.size(); i++)
    {
        m_bullets[i]->setDestination(calculatePos(m_t + (float) i * 4, calculateAngle * i));
    }  

  //  std::cout << "calculate value x : " << m_xNode.getValue() << " y : " << m_yNode.getValue() << "\n";

}

void PaternBehavior_from_lua::setRate(float rate)
{
    m_rate = rate;
}


glm::vec2 PaternBehavior_from_lua::calculatePos(float t,float additionalAngle)
{
    glm::vec2 returnVal;


    returnVal.x = m_xNode.getValue();
    returnVal.y = m_yNode.getValue();

    //std::cout << "calculate value x : " << returnVal.x << " y : " << returnVal.y << "\n";
    return rotatePoint(returnVal, additionalAngle);
}