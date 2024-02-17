#ifndef CALCULATORENGINE_H
#define CALCULATORENGINE_H
#include "ICalculatorEngine.h"
#include <iostream>
class CalculatorEngine {
private:
    double* results; 
    const double precision = 0.0001; 
public:
    CalculatorEngine();
    CalculatorEngine(const CalculatorEngine& other);
    ~CalculatorEngine();
    void setResultsSize(size_t size); 
    double getResultAt(size_t index) const;
    double calculate(const std::string& expression); 
    CalculatorEngine& operator=(const CalculatorEngine& other); 
    friend std::ostream& operator<<(std::ostream& os, const CalculatorEngine& engine); 
    friend std::istream& operator>>(std::istream& is, CalculatorEngine& engine);
    CalculatorEngine operator+(const CalculatorEngine& other) const; 
    CalculatorEngine operator*(const CalculatorEngine& other) const; 
};
#endif 