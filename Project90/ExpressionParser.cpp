#include "ExpressionParser.h"
#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <cctype>
#include <string>
#include <stdexcept>
const std::string ExpressionParser::validChars = "0123456789+-*/^()[]";

ExpressionParser::ExpressionParser() : expression(nullptr) {}

ExpressionParser::ExpressionParser(const std::string& expr) {
    expression = new char[expr.length() + 1];
    std::copy(expr.begin(), expr.end(), expression);
    expression[expr.length()] = '\0'; 
}

ExpressionParser::ExpressionParser(const ExpressionParser& other) {
    if (other.expression != nullptr) {
        expression = new char[strlen(other.expression) + 1];
        std::copy(other.expression, other.expression + strlen(other.expression), expression);
        expression[strlen(other.expression)] = '\0';
    }
    else {
        expression = nullptr;
    }
}

ExpressionParser::~ExpressionParser() {
    delete[] expression;
}

ExpressionParser& ExpressionParser::operator=(const ExpressionParser& other) {
    if (this != &other) {
        delete[] expression;
        if (other.expression != nullptr) {
            expression = new char[strlen(other.expression) + 1];
            std::copy(other.expression, other.expression + strlen(other.expression), expression);
            expression[strlen(other.expression)] = '\0';
        }
        else {
            expression = nullptr;
        }
    }
    return *this;
}
void ExpressionParser::setExpression(const std::string& expr) {
    if (!validateExpression(expr)) {
        std::cout << "Expresie invalidă." << std::endl;
        return;
    }
    delete[] expression;
    expression = new char[expr.length() + 1];
    strcpy_s(expression, expr.length() + 1, expr.c_str());
}

const char* ExpressionParser::getExpression() const {
    return expression;
}
bool ExpressionParser::validateExpression(const std::string& expr) {
    for (char c : expr) {
        if (validChars.find(c) == std::string::npos) {
            return false; 
        }
    }
    return true; 
}
std::map<char, int> opPrecedence = {
    {'+', 1}, {'-', 1},
    {'*', 2}, {'/', 2},
    {'^', 3}, {'#', 3}
};
std::vector<std::string>ExpressionParser:: parseExpression() {
    std::stack<char> opStack;
    std::vector<std::string> outputQueue;
    for (size_t i = 0; expression[i] != '\0'; ++i) {
        char c = expression[i];
        if (isspace(c)) continue;
        else if (isdigit(c) || c == '.') {
            std::string numberStr = "";
            int dotCount = 0; 
            while (expression[i] != '\0' && (isdigit(expression[i]) || expression[i] == '.')) {
                if (expression[i] == '.') {
                    dotCount++;
                    if (dotCount > 1) {
                        throw std::runtime_error("Număr invalid: prea multe puncte.");
                    }
                }
                numberStr += expression[i++];
            }
            --i;
            outputQueue.push_back(numberStr);
        }
        else if (c == '(' || c == '[') {
            opStack.push(c);
        }
        else if (c == ')' || c == ']') {
            char expectedOpen = c == ')' ? '(' : '[';
            while (!opStack.empty() && opStack.top() != expectedOpen) {
                outputQueue.push_back(std::string(1, opStack.top()));
                opStack.pop();
            }
            if (opStack.empty()) {
                throw std::runtime_error("Expresie invalidă: paranteză închisă fără o paranteză deschisă corespunzătoare.");
            }
            opStack.pop(); 
        }
        else {
            if (opPrecedence.find(c) != opPrecedence.end()) {
                while (!opStack.empty() && opPrecedence[opStack.top()] >= opPrecedence[c]) {
                    outputQueue.push_back(std::string(1, opStack.top()));
                    opStack.pop();
                }
            }
            opStack.push(c);
        }
    }
    while (!opStack.empty()) {
        if (opStack.top() == '(' || opStack.top() == '[') {
            throw std::runtime_error("Expresie invalidă: paranteză deschisă fără a fi închisă.");
        }
        outputQueue.push_back(std::string(1, opStack.top()));
        opStack.pop();
    }
    return outputQueue;
}


std::ostream& operator<<(std::ostream& os, const ExpressionParser& parser) {
    if (parser.expression != nullptr) {
        os << parser.expression;
    }
    return os;
}
std::istream& operator>>(std::istream& is, ExpressionParser& parser) {
    std::string temp;
    is >> temp;
    parser.setExpression(temp);
    return is;
}
bool ExpressionParser::operator!() const {
    return expression == nullptr || std::strlen(expression) == 0;
}

char ExpressionParser::operator[](size_t index) const {
    if (expression != nullptr && index < std::strlen(expression)) {
        return expression[index];
    }
    throw std::out_of_range("Index out of range");
}