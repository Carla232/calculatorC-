#ifndef CALCULATORENGINE_H
#define CALCULATORENGINE_H
#include "ICalculatorEngine.h"
#include <iostream>
using namespace std;
class CalculatorEngine {
private:
    double* results; 
    const double precision = 0.0001; 
    size_t resultsSize; 
public:
    CalculatorEngine();
    CalculatorEngine(const CalculatorEngine& other);
    ~CalculatorEngine();
    void setResultsSize(size_t size); 
    double getResultAt(size_t index) const;
    void addResult(double result);
    double calculate(const string& expression); 
    CalculatorEngine& operator=(const CalculatorEngine& other); 
    friend ostream& operator<<(ostream& os, const CalculatorEngine& engine); 
    friend istream& operator>>(istream& is, CalculatorEngine& engine);
    CalculatorEngine operator+(const CalculatorEngine& other) const; 
    CalculatorEngine operator*(const CalculatorEngine& other) const; 
};
#endif 