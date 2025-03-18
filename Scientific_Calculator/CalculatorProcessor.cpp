#define _USE_MATH_DEFINES

#include "CalculatorProcessor.h"
#include <stack>
#include <queue>
#include <wx/tokenzr.h>
#include <unordered_map>
#include <cmath>

// Initialize the instance to nullptr
CalculatorProcessor* CalculatorProcessor::instance = nullptr;

void CalculatorProcessor::CleanUpInstance()
{
    delete instance;
    instance = nullptr;
}

CalculatorProcessor* CalculatorProcessor::GetInstance()
{
    if (!instance) {
        instance = new CalculatorProcessor();
    }

    return instance;
}

// Operator precedence map
std::unordered_map<std::string, int> precedence = {
    {"sin", 4}, {"cos", 4}, {"tan", 4},
    {"*", 3}, {"/", 3}, {"%", 3},
    {"+", 2}, {"-", 2}
};

float CalculatorProcessor::Calculate(const std::string& expression)
{
    std::queue<std::string> outputQueue;
    std::stack<std::string> operatorStack;

    wxStringTokenizer tokenizer(wxString(expression), " ", wxTOKEN_STRTOK);
    
    // Tracks whether the last token was an operator (for negation numbers)
    bool prevOperator = true;

    // While there are tokens to be read
    while (tokenizer.HasMoreTokens()) {
        // Read token
        wxString token = tokenizer.GetNextToken();
        // Convert token to string
        std::string tokenStr = std::string(token.mb_str());
        
        // If token is a number, put it into the output queue
        if (isdigit(tokenStr[0]) || (tokenStr[0] == '-' && tokenStr.size() > 1)) {
            outputQueue.push(tokenStr);
            prevOperator = false;
        }
        // If token is a function, put it into the operator stack 
        else if (tokenStr == "sin" || tokenStr == "cos" || tokenStr == "tan") {
            operatorStack.push(tokenStr);
            prevOperator = true;
        }
        // If token is an operator
        else if (precedence.count(tokenStr)) {
            // Handle unary negative
            if (tokenStr == "-" && prevOperator) {
                outputQueue.push("-1");
                operatorStack.push("*");
                continue;
            }

            // While operatorstack isn't empty, doesn't start with ( and precedence of the current top operatorstack is greater than the curren token
            while ( !operatorStack.empty() && operatorStack.top() != "(" && (precedence[operatorStack.top()] > precedence[tokenStr] ||
                (precedence[operatorStack.top()] == precedence[tokenStr] && tokenStr != "^")) ) {
                // Pop current top of operatorstack from the operator stack into the output queue
                outputQueue.push(operatorStack.top());
                operatorStack.pop();
            }

            // Push tokenStr onto the operator stack
            operatorStack.push(tokenStr);
            prevOperator = true;
        }
        // If tokenStr is a (
        else if (tokenStr == "(") {
            // Push it onto the operator stack
            operatorStack.push(tokenStr);
            prevOperator = true;
        }
        // If tokenStr is )
        else if (tokenStr == ")") {
            // Pop until left parenthesis is found
            while (!operatorStack.empty() && operatorStack.top() != "(") {
                // Pop the operator from the operator stack into the output queue
                outputQueue.push(operatorStack.top());
                operatorStack.pop();
            }

            // Pop the left parenthesis from the operator stack and discard it
            if (!operatorStack.empty()) {
                operatorStack.pop();
                prevOperator = false;
            }
        }
    }

    // While there are tokens on the operator stack
    while (!operatorStack.empty()) {
        // Pop the operator from the operator stack onto the output queue
        outputQueue.push(operatorStack.top());
        operatorStack.pop();
    }

    std::stack<float> evaluationStack;

    // Loop through the outputQueue
    while (!outputQueue.empty()) {
        // Set current tokenStr to first in outputQueue
        std::string tokenStr = outputQueue.front();
        // Remove last from outputQueue
        outputQueue.pop();

        // If the token is a number, push it onto the eval stack
        if (isdigit(tokenStr[0]) || (tokenStr[0] == '-' && tokenStr.size() > 1)) {
            evaluationStack.push(std::stof(tokenStr));
        }
        // If token is a function
        else if (tokenStr == "sin" || tokenStr == "cos" || tokenStr == "tan") {
            if (evaluationStack.empty()) return std::nanf("ERR");
            
            float operand = evaluationStack.top();
            evaluationStack.pop();

            // Trigonometric functions - radians
            if (tokenStr == "sin") evaluationStack.push(sin(operand));
            else if (tokenStr == "cos") evaluationStack.push(cos(operand));
            else if (tokenStr == "tan") {
                if (fmod(operand, M_PI / 2) == 0 && fmod(operand, M_PI) != 0) return std::nanf("UNDEFINED");
                evaluationStack.push(tan(operand));
            }
        }
        // If token is an operator
        else if (precedence.count(tokenStr)) {
            if (evaluationStack.size() < 2) return std::nanf("ERR");

            float b = evaluationStack.top(); evaluationStack.pop();
            float a = evaluationStack.top(); evaluationStack.pop();
            float result = 0;

            // Calculate
            if (tokenStr == "+") result = a + b;
            else if (tokenStr == "-") result = a - b;
            else if (tokenStr == "*") result = a * b;
            else if (tokenStr == "/") {
                // Division by zero
                if (b == 0) return std::nanf("UNDEFINED");

                result = a / b;
            }
            else if (tokenStr == "%") {
                // Modulo by zero
                if (b == 0) return std::nanf("UNDEFINED");

                result = fmod(a, b);
            }

            evaluationStack.push(result);
        }
    }

    return evaluationStack.empty() ? 0.0f : evaluationStack.top();
}
