#pragma once 
#include "PaternBehaviorBase.h"


enum Operator{
    NONE,
    ADD,
    SUB,
    MUL,
    DIV,
    SQRT,
    COS, 
    SIN
};

struct Node {
    float value = 0;
    Node * left;
    Node * right;
    Operator op = NONE;

    float getValue() {
        switch (op) {
            case ADD:
                return left->getValue() + right->getValue();
            case SUB:
                return left->getValue() - right->getValue();
            case MUL: 
                return left->getValue() * right->getValue();
            case DIV:   
                return left->getValue() * right->getValue();
            case SQRT:
                return sqrt(left->getValue());
            case COS:
                return cos(left->getValue());
            case SIN:
                return sin(left->getValue());
            default:
                return value;
        }
    }   




};


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

    
    //void init(float radius, )
};