#ifndef EXPRESSIONPARSER_H
#define EXPRESSIONPARSER_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class ExpressionParser {
private:
    char* expression; 
    static const string validChars;
public:
    ExpressionParser();
    ExpressionParser(const string& expr);
    ExpressionParser(const ExpressionParser& other); 
    ~ExpressionParser();
    void setExpression(const string& expr);
    const char* getExpression() const;
    static bool validateExpression(const string& expr);
    vector<string> parseExpression();
    ExpressionParser& operator=(const ExpressionParser& other); 
    friend ostream& operator<<(ostream& os, const ExpressionParser& parser); 
    friend istream& operator>>(istream& is, ExpressionParser& parser);
    ExpressionParser& operator++();
    ExpressionParser operator++(int);
    ExpressionParser& operator--();
    ExpressionParser operator--(int);
};
#endif 