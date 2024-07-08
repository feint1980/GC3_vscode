#pragma once 
#include "PaternBehaviorBase.h"

#include <AST_Node.h>

class PaternBehavior_from_lua : public PaternBehaviorBase
{
public:
    PaternBehavior_from_lua();
    ~PaternBehavior_from_lua();
    virtual void update(float deltaTime)override;

    void setRadius(float radius);

    void init(const std::string & xNodeEquation, const std::string & yNodeEquation, float radius);

    void setFactor(const std::vector<float> & factors);

    void setValue(char varName, float value);

private: 

    glm::vec2 calculatePos(float t,float additionalAngle);

    Feintgine::AST_Node * m_xNode;
    Feintgine::AST_Node * m_yNode;
    
    std::vector<float> m_factors;

    float m_rad = 40;

    float m_t = 0;

    float m_rate = 1.0f;

    //void init(float radius, )
};