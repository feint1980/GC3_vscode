#include <iterator>
#include <regex>
#include <string>
#include <queue>
#include <stack>
#include <math.h>
#include <iostream>

namespace Feintgine
{


class AST_Node
{
public:
    AST_Node();
    ~AST_Node();

    void init(const std::string & mathExp);

    

    float getValue()
    {
        calculateValue();
        return m_value;
    }

    void setFactors(const std::vector<float> & factors)
    {
        m_factors = factors;
    }

    void setValue(char varName, float value);


    void setTValue(float t) { m_t = t; }
    void setRadius(float radius) { m_radius = radius; }

private:

    void calculateValue();

    int getValueIndex(char c) 
    {
        if(c == 'a')
            return 0;
        if(c == 'b')
            return 1;
        if(c == 'c')
            return 2;
        if(c == 'd')
            return 3;
        if (c == 'r')
            return 11;
        if(c == 't')
            return 12;
        return -1;
    }


    std::vector<float> m_factors;
    float m_t = 0.0f;
    float m_radius = 30.0f;

    float m_value = 0.0f;

    std::string m_mathExp;
    std::queue<std::string> m_mainQueue;
    
    std::regex word_regex; 

    bool is_op(const std::string& token) 
    {
    return token == "+" || token == "-" 
        || token == "*" || token == "/" || token == "^";
    }
    bool is_math_function(const std::string& token) 
    {
        return token == "sin" || token == "cos"
            || token == "tan" || token == "sqrt";
    }
    int get_operation_order(const std::string& token) 
    {
        if(token == "+" || token == "-")
            return 2;
        if(token == "*" || token == "/")
            return 3;
        return 4;
    }
    float op_calc(const std::string& op, float a, float b) 
    {
        if(op == "+")
            return a + b;
        if(op == "-")
            return a - b;
        if(op == "*")
            return a * b;
        if(op == "/")
            return a / b;
        return 0.0f;
    }
    float func_calc(const std::string& func, float x) {
        if(func == "sin")
            return sin(x);
        if(func == "cos")
            return cos(x);
        if(func == "tan")
            return tan(x);
        if(func == "sqrt")
            return sqrt(x);
        return 0.0f;
    }

};
}