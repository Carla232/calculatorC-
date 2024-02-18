#include "ExpressionParser.h"
#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <cctype>
#include <string>
#include <stdexcept>
using namespace std;

const string ExpressionParser::validChars = "0123456789+-*/^()[]";

ExpressionParser::ExpressionParser() : expression(nullptr) {}

ExpressionParser::ExpressionParser(const string& expr) {
    expression = new char[expr.length() + 1];
    copy(expr.begin(), expr.end(), expression);
    expression[expr.length()] = '\0';
}

ExpressionParser::ExpressionParser(const ExpressionParser& other) {
    if (other.expression != nullptr) {
        expression = new char[strlen(other.expression) + 1];
        copy(other.expression, other.expression + strlen(other.expression), expression);
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
            copy(other.expression, other.expression + strlen(other.expression), expression);
            expression[strlen(other.expression)] = '\0';
        }
        else {
            expression = nullptr;
        }
    }
    return *this;
}

void ExpressionParser::setExpression(const string& expr) {
    if (!validateExpression(expr)) {
        cout << "Expresie invalida." << endl;
        return;
    }
    delete[] expression;
    expression = new char[expr.length() + 1];
    strcpy_s(expression, expr.length() + 1, expr.c_str());
}

const char* ExpressionParser::getExpression() const {
    return expression;
}

bool ExpressionParser::validateExpression(const string& expr) {
    for (char c : expr) {
        if (validChars.find(c) == string::npos) {
            return false;
        }
    }
    return true;
}

map<char, int> opPrecedence = {
    {'+', 1}, {'-', 1},
    {'*', 2}, {'/', 2},
    {'^', 3}, {'#', 3}
};

vector<string>ExpressionParser::parseExpression() {
    stack<char> opStack;
    vector<string> outputQueue;
    for (size_t i = 0; expression[i] != '\0'; ++i) {
        char c = expression[i];
        if (isspace(c)) continue;
        else if (isdigit(c) || c == '.') {
            string numberStr = "";
            int dotCount = 0;
            while (expression[i] != '\0' && (isdigit(expression[i]) || expression[i] == '.')) {
                if (expression[i] == '.') {
                    dotCount++;
                    if (dotCount > 1) {
                        throw runtime_error("Numar invalid: prea multe puncte.");
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
                outputQueue.push_back(string(1, opStack.top()));
                opStack.pop();
            }
            if (opStack.empty()) {
                throw runtime_error("Expresie invalida: paranteza inchisa fara o paranteza deschisa corespunzatoare.");
            }
            opStack.pop();
        }
        else {
            if (opPrecedence.find(c) != opPrecedence.end()) {
                while (!opStack.empty() && opPrecedence[opStack.top()] >= opPrecedence[c]) {
                    outputQueue.push_back(string(1, opStack.top()));
                    opStack.pop();
                }
            }
            opStack.push(c);
        }
    }
    while (!opStack.empty()) {
        if (opStack.top() == '(' || opStack.top() == '[') {
            throw runtime_error("Expresie invalida: paranteza deschisa fara a fi inchisa.");
        }
        outputQueue.push_back(string(1, opStack.top()));
        opStack.pop();
    }
    return outputQueue;
}

ostream& operator<<(ostream& os, const ExpressionParser& parser) {
    if (parser.expression != nullptr) {
        os << parser.expression;
    }
    return os;
}

istream& operator>>(istream& is, ExpressionParser& parser) {
    string temp;
    is >> temp;
    parser.setExpression(temp);
    return is;
}

ExpressionParser& ExpressionParser::operator++() {
    size_t length = expression ? strlen(expression) : 0;
    char* newExpression = new char[length + 2];
    if (expression) {
        copy(expression, expression + length, newExpression);
    }
    newExpression[length] = '+';
    newExpression[length + 1] = '\0';
    delete[] expression;
    expression = newExpression;
    return *this;
}

ExpressionParser ExpressionParser::operator++(int) {
    ExpressionParser temp(*this);
    ++(*this);
    return temp;
}

ExpressionParser& ExpressionParser::operator--() {
    size_t length = expression ? strlen(expression) : 0;
    if (length > 0) {
        char* newExpression = new char[length];
        copy(expression, expression + length - 1, newExpression);
        newExpression[length - 1] = '\0';
        delete[] expression;
        expression = newExpression;
    }
    return *this;
}

ExpressionParser ExpressionParser::operator--(int) {
    ExpressionParser temp(*this);
    --(*this);
    return temp;
}
