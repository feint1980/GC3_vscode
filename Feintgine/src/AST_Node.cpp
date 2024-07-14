#include "AST_node.h"
namespace Feintgine
{


AST_Node::AST_Node()
{
    for(int i = 0; i < 4; i++)
    {
        m_factors.push_back(i);
    }
    word_regex = std::regex("(\\w+|\\d|[+,--,*,\\/,(,)])");
}

AST_Node::~AST_Node()
{
    
}

void AST_Node::setValue(char varName, float value)
{

    int index = getValueIndex(varName);
    if(index == -1)
        return;
    if(index == 11)
    {
        m_radius = value;
        return;
    }
    if(index == 12)
    {
        m_t = value;
        return;
    }
    m_factors[index] = value;

}

void AST_Node::init(const std::string & mathExp)
{

    std::cout << "init mathExp: " << mathExp << std::endl;
    m_mathExp = mathExp;
    std::string math_exp = mathExp;// "((a - b)  cos(t) +(c  cos((a / b - 1)*t))) *r";
    std::regex word_regex("(\\w+|\\d|[+,--,*,\\/,(,)])");
    std::stack<std::string> s;
    auto words_begin = std::sregex_iterator(math_exp.begin(), math_exp.end(), word_regex);
    auto words_end = std::sregex_iterator();
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::string token = (*i).str();
        if(is_op(token)) {
            while(!s.empty() && s.top() != "(") {
                int ord1 = get_operation_order(token);
                int ord2 = get_operation_order(s.top());
                if(ord1 > ord2)
                    break;
                m_mainQueue.push(s.top());
                s.pop();
            }
            s.push(token);
            continue;
        }
        if(is_math_function(token) || token == "(") {
            s.push(token);
            continue;
        }
        if(token == ")") {
            while(!s.empty() && s.top() != "(") {
                if(is_op(s.top())) {
                    m_mainQueue.push(s.top());
                    s.pop();
                }
            }
            if(s.top() =="(") {
                s.pop();
            }
            if(!s.empty() && is_math_function(s.top())) {
                m_mainQueue.push(s.top());
                s.pop();
            }
            continue;
        }
        m_mainQueue.push(token);
    }
    while(!s.empty()) {
        std::cout << "init \n";
        m_mainQueue.push(s.top());
        s.pop();
    }


}

void AST_Node::calculateValue()
{
    //std::cout << "calculate \n";
    std::stack<float> rpn;
    std::queue<std::string> copyQueue = m_mainQueue;
    while(!copyQueue.empty()) 
    {
        //std::cout << "a \n";
        std::string token = copyQueue.front();
        if(is_op(token)) {
            float b = rpn.top();
            rpn.pop();
            float a = rpn.top();
            rpn.pop();
            rpn.push(op_calc(token, a, b));
           // std::cout << "rpn top: " << rpn.top() << std::endl;
        }
        else if(is_math_function(token)) {
            float x = rpn.top();
            rpn.pop();
            rpn.push(func_calc(token, x));
        }
        else if(token == "a") {
            rpn.push(m_factors[0]);
        }
        else if(token == "b") {
            rpn.push(m_factors[1]);
        }
        else if(token == "c") {
            rpn.push(m_factors[2]);
        }
        else if(token == "d") {
            rpn.push(m_factors[3]);
        }
        else if(token == "r") {
            rpn.push(m_radius);
        }
        else if(token == "t") {
            rpn.push(m_t);
        }
        else {
            rpn.push(std::stof(token));
        }
        copyQueue.pop();
    }
    //std::cout << rpn.top();
    m_value = rpn.top();
        
}

}