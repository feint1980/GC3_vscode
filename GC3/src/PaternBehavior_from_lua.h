#pragma once 
#include "PaternBehaviorBase.h"

#include <AST_Node.h>

class PaternBehavior_from_lua : public PaternBehaviorBase
{
public:
    PaternBehavior_from_lua();
    ~PaternBehavior_from_lua();
    virtual void update(float deltaTime)override;


    void setXFactor(float x);   
    void setYFactor(float y);

    void setRadius(float radius);

private:

    Feintgine::AST_Node * m_xNode;
    Feintgine::AST_Node * m_yNode;
    
    //void init(float radius, )
};