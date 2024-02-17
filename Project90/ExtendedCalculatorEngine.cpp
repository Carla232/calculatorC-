#include "ExtendedCalculatorEngine.h"
#include <vector>
void ExtendedCalculatorEngine::addToHistory(double result) {
    history.push_back(result);
}

void ExtendedCalculatorEngine::displayHistory() const {
    std::cout << "Istoric rezultate:\n";
    for (double result : history) {
        std::cout << result << "\n";
    }
}