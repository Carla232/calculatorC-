#ifndef ICALCULATORENGINE_H
#define ICALCULATORENGINE_H
#include <string>
class ICalculatorEngine {
public:
    virtual double calculate(const std::string& expression) = 0; 
    virtual ~ICalculatorEngine() {} 
};
#endif 