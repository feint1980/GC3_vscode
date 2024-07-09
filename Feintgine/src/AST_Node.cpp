#include "AST_Node.h"


namespace Feintgine
{

    void AST_Node::parseData(const std::string & data)
    {
        // data is a string of a fomula defined by user
        // from the data string

        std::string processData = data;
        std::vector<int> removeIndicies;
        // remove whitespace
        for(int i = 0; i < processData.size(); ++i)
        {
            if(processData[i] == ' ')
            {
                removeIndicies.push_back(i);
            }
        }
        for(int i = 0; i < removeIndicies.size(); ++i)
        {
            processData.erase(removeIndicies[i] - i, 1);
        }

        int openCracketCount = 0;
        int closeCracketCount = 0;
        bool isSpecialMath = false;
        for(int i = 0; i < processData.size(); ++i)
        {

            if(processData[i] == '(')
            {
                int foundIndex = i ;
                if(i > 3 )
                {
                    // check if before the '(' is cos or sin
                    // if yes, then pushback the letter c(cos) or s(sin)
                    std::string cutprocessData = processData.substr(i - 3, 3);
                    if(cutprocessData == "cos" || cutprocessData == "sin")
                    {
                        foundIndex = i - 3;
                        isSpecialMath = true;
                    }

                }
                bracketStack.push(foundIndex);
                openCracketCount++;

            }
            else if(processData[i] == ')')
            {
                std::string tClause = processData.substr(bracketStack.top(), i - bracketStack.top() + 1);

                bracketStack.pop();
                clauseStack.push(clause(tClause, i));
                closeCracketCount++;
                if(bracketStack.empty())
                {
                    clauses.push_back(clauseStack);
                    while(!clauseStack.empty())
                    {
                        clauseStack.pop();
                    }
                }
            }
        }
        // first rule, open bracket should be equal to close bracket
        if (openCracketCount != closeCracketCount)
        {
            std::cout << "parse error !!! \n";
            return;
        }

        int middleOperator = 0;
        if(clauses.size() >= 2)
        {
            auto copyClauseStack = clauses;

            for(int i = 0; i < copyClauseStack.size(); ++i)
            {
                int tab = 0;
                while(!copyClauseStack[i].empty())
                {
                    copyClauseStack[i].pop();
                    tab++;
                }

            }
            // find the operators among the clauses

            std::vector<operationSign> operatorSignsLocation;

            for(int i = 0; i < clauses.size() -1; ++i)
            {
                clause firstClause = clauses[i].top();
                int start = firstClause.originalIndex;
                std::string tOp = processData.substr(start + 1,1);
                operatorSignsLocation.emplace_back(operationSign(tOp[0], start+1));
            }

                // look for * and / first
            for(int i = 0; i < operatorSignsLocation.size(); ++i)
            {
                if (operatorSignsLocation[i].sign == '*' || operatorSignsLocation[i].sign == '/')
                {
                    middleOperator = operatorSignsLocation[i].index;
                    break;
                }
            }
            // overwrite the middle operator if there is + or - (math things)
            for(int i = 0; i < operatorSignsLocation.size(); ++i)
            {
                if (operatorSignsLocation[i].sign == '+' || operatorSignsLocation[i].sign == '-')
                {
                    middleOperator = operatorSignsLocation[i].index;
                    break;
                }
            }

            char middleOperatorChar = processData[middleOperator];
            if(middleOperatorChar == '+')
            {
                op = ADD;
            }
            else if(middleOperatorChar == '-')
            {
                op = SUB;
            }
            else if(middleOperatorChar == '*')
            {
                op = MUL;
            }
            else if(middleOperatorChar == '/')
            {
                op = DIV;
            }

            std::string leftClause = processData.substr(0, middleOperator);
            std::string rightClause = processData.substr(middleOperator + 1, processData.size() - middleOperator );

            left = new AST_Node();
            right = new AST_Node();
            left->setFactors(m_factors);
            right->setFactors(m_factors);
            left->setRvalue(r_value);
            right->setRvalue(r_value);
            left->setTvalue(t_value);
            right->setTvalue(t_value);
            left->parseData(leftClause);
            right->parseData(rightClause);
            
        }
        else
        {

            std::vector<operationSign> operatorSignsLocation;

            std::string singleClause = clauses[0].top().data;

            for(int i = 0; i < singleClause.size(); ++i)
            {
                // find * and / first
                if (singleClause[i] == '*' || singleClause[i] == '/')
                {
                    middleOperator = i;
                    break;

                }
                if(singleClause[i] == '+' || singleClause[i] == '-')
                {
                    middleOperator = i;
                    break;
                }
            }
            if(middleOperator == 0)
            {
                if(!isSpecialMath)
                {

                    std::string strValue = singleClause.substr(1, singleClause.size() - 2);
                    if(strValue == "a")
                    {

                        //value = getFactorIndex('a');
                        value = m_factors[0];
                        std::cout << "a value found \n";

                    }
                    else if(strValue == "b")
                    {
                        value = m_factors[1];
                        std::cout << "b value found \n";
                        
                    }
                    else if(strValue == "c")
                    {
                        value = m_factors[2];
                        std::cout << "c value found \n";
                    }
                    else if(strValue == "d")
                    {
                        value = m_factors[3];
                        std::cout << "d value found \n";
                    }
                    else if(strValue == "t")
                    {
                        value = * t_value;
                        std::cout << "t value found \n";
                    }
                    else if(strValue == "r")
                    {
                        value = * r_value;
                        std::cout << "r value found \n";
                    }
                    else
                    {
                        value = std::stof(strValue);
                    }
                }
                else
                {
                    int is_cos_sin = 0;
                    // if keyword cos found in the clause
                    if(singleClause.find("cos") != std::string::npos)
                    {
                        is_cos_sin = 1;

                    }
                    else if(singleClause.find("sin") != std::string::npos)
                    {
                        is_cos_sin = 2;
                    }
                    else if (singleClause.find("tan") != std::string::npos)
                    {
                        is_cos_sin = 3;
                    }
                    std::string strValue = singleClause.substr(5, singleClause.size() - 7);

                    if(strValue == "a")
                    {

                        //value = getFactorIndex('a');
                        value = m_factors[0];
                        std::cout << "a value found \n";

                    }
                    else if(strValue == "b")
                    {
                        value = m_factors[1];
                        std::cout << "b value found \n";
                    }
                    else if(strValue == "c")
                    {
                        value = m_factors[2];
                        std::cout << "c value found \n";
                    }
                    else if(strValue == "d")
                    {

                        value = m_factors[3];
                        std::cout << "d value found \n";
                    }
                    else if(strValue == "t")
                    {
                        value = * t_value;
                        std::cout << "t value found \n";
                    }
                    else if(strValue == "r")
                    {

                        value = * r_value;
                        std::cout << "r value found \n";
                    }
                    else
                    {
                        value = std::stof(strValue);
                    }

                    if(is_cos_sin == 1)
                    {
                        value = std::cos(value);

                    }
                    else if(is_cos_sin == 2)
                    {
                        value = std::sin(value);

                    }
                    else if(is_cos_sin == 3)
                    {
                        value = std::tan(value);
                    }

                    //value = std::stof(strValue);
                }
            }
            else
            {

                char middleOperatorChar = singleClause[middleOperator];

                if(middleOperatorChar == '+')
                {
                    op = ADD;
                }
                else if(middleOperatorChar == '-')
                {
                    op = SUB;
                }
                else if(middleOperatorChar == '*')
                {
                    op = MUL;
                }
                else if(middleOperatorChar == '/')
                {
                    op = DIV;
                }

                std::string leftClause = singleClause.substr(1, middleOperator - 1); // left out the opening bracket
                std::string rightClause = singleClause.substr(middleOperator + 1, singleClause.size() - leftClause.size());
                rightClause = rightClause.substr(0, rightClause.size() - 1); // left out the closing bracket
                bool isLast = rightClause.size() == 0;
                if(isLast)
                {
                    leftClause = leftClause.substr(0, leftClause.size() - 1);
                }

                left = new AST_Node();
                left->setFactors(m_factors);
                left->setRvalue(r_value);
                left->setTvalue(t_value);
                left->parseData( "(" + leftClause + ")");
               
                if(!isLast)
                {
                    right = new AST_Node();
                    right->setRvalue(r_value);
                    right->setTvalue(t_value);
                    right->setFactors(m_factors);
                    right->parseData("("+rightClause +")");
                   
                }

            }

        }

    }

    int AST_Node::getFactorIndex(char character)
    {
        if(character == 'a')
        {
            return 0;
        }
        else if(character == 'b')
        {
            return 1;
        }
        else if(character == 'c')
        {
            return 2;
        }
        else if(character == 'd')
        {
            return 3;
        }
        else if (character == 't')
        {
            return 10;
        }
        else if (character == 'r')
        {
            return 11;
        }
        else
        {
            return -1;
        }
    }

    void AST_Node::setRvalue(float * r_t_value)
    {
        r_value = r_t_value;
    }


    void AST_Node::setValue(char varName, float value)
    {
        int index = getFactorIndex(varName);
        if(index == 10) // t
        {
            *t_value = value;
        }
        else if(index == 11) // r
        {
            *r_value = value;
        }
        else if(index != -1 && index < m_factors.size())
        {
            m_factors[index] = value;
        }
        else
        {
            std::cout << "Waning:  variable not found or out of reach " << index << " \n";
        }
    }


    void AST_Node::setTvalue(float * t_t_value)
    {
        t_value = t_t_value;
    }

    float AST_Node::getValue() const
    {
        //std::cout << "get value called \n";

        switch (op) {
            case ADD:

                return value + (left->getValue() + right->getValue());
            case SUB:

                return value +  (left->getValue() - right->getValue());
            case MUL:

                return value +  (left->getValue() * right->getValue());
            case DIV:

                return value +  (left->getValue() / right->getValue());
            default:

                return value;
        }
       // std::cout << "value after add : " << value << "\n";
    }

}