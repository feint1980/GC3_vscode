#pragma once


#include <iostream>

#include <math.h>
#include <string>
#include <stack>
#include <vector>




#define HAS_A 1
#define HAS_B 2
#define HAS_C 4
#define HAS_D 8
#define HAS_E 16
#define HAS_T 32

namespace Feintgine
{

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



struct clause
{
    clause(const std::string & _data, int index) : data(_data), originalIndex(index) {}
    std::string data;
    int originalIndex = -1;
};


struct operationSign
{
    operationSign(char _sign, int _index) : sign(_sign), index(_index) {}
    char sign = ' ';
    int index = -1;
};


struct AST_Node {

    void parseData(const std::string & data);
   
    std::vector<std::stack <int>> bracketStackVector;
    std::stack <int> bracketStack;
    std::stack<clause> clauseStack;
    std::vector<std::stack<clause>> clauses;
    
    float value = 0.0;
    AST_Node * left;
    AST_Node * right;
    Operator op = NONE;
    void setFactors(const std::vector<float> & factors)
    {
        m_factors = factors;
    }

    int getFactorIndex(char character);

    float getValue() const;

    std::vector<float> m_factors ;

    void setTvalue(float * t_t_value);

    void setRvalue(float * r_t_value);

    void setValue(char varName, float value);

    float * t_value;

    float * r_value;

};


}