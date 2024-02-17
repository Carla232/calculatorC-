#ifndef ExtendedCalculatorEngine_H
#define ExtendedCalculatorEngine_H
#include <vector>
#include "CalculatorEngine.h"
class ExtendedCalculatorEngine : public CalculatorEngine {
    std::vector<double> history;
public:
    using CalculatorEngine::CalculatorEngine;
    void addToHistory(double result);
    void displayHistory() const;
};
#endif