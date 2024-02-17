#ifndef EXPRESSIONPARSER_H
#define EXPRESSIONPARSER_H
#include <iostream>
#include <string>
#include <vector>
class ExpressionParser {
private:
    char* expression; 
    static const std::string validChars;
public:
    ExpressionParser();
    ExpressionParser(const std::string& expr);
    ExpressionParser(const ExpressionParser& other); 
    ~ExpressionParser();
    void setExpression(const std::string& expr);
    const char* getExpression() const;
    static bool validateExpression(const std::string& expr);
    std::vector<std::string> parseExpression();
    ExpressionParser& operator=(const ExpressionParser& other); 
    friend std::ostream& operator<<(std::ostream& os, const ExpressionParser& parser); 
    friend std::istream& operator>>(std::istream& is, ExpressionParser& parser);
    bool operator!() const; 
    char operator[](size_t index) const; 
};
#endif 