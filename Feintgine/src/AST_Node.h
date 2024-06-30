#pragma once


#include <iostream>

#include <math.h>
#include <string>
#include <stack>
#include <vector>


#define A 3
#define B 4
#define C 2


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


struct Node {

    void parseData(const std::string & data);
   
    std::vector<std::stack <int>> bracketStackVector;
    std::stack <int> bracketStack;
    std::stack<clause> clauseStack;
    std::vector<std::stack<clause>> clauses;
    
    float value = 0.0;
    Node * left;
    Node * right;
    Operator op = NONE;

    float getValue() const;

};

}