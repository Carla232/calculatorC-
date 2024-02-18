#ifndef ICALCULATORENGINE_H
#define ICALCULATORENGINE_H
#include <string>
#include <string>
using namespace std;
class ICalculatorEngine {
public:
    virtual double calculate(const string& expression) = 0; 
    virtual ~ICalculatorEngine() {} 
};
#endif 