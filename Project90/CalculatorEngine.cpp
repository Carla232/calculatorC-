#include "CalculatorEngine.h"
#include <string>
#include <sstream>
#include <vector>
#include <cmath> 
#include <stack>
#include <queue>
#include <map>
#include <cmath> 
#include <stdexcept> 
#include "ExpressionParser.h"

CalculatorEngine::CalculatorEngine() {
    results = nullptr;
}
CalculatorEngine::CalculatorEngine(const CalculatorEngine& other) {
    size_t size = sizeof(other.results) / sizeof(other.results[0]);
    setResultsSize(size);
    for (size_t i = 0; i < size; i++) {
        results[i] = other.results[i];
    }
}

CalculatorEngine::~CalculatorEngine() {
    delete[] results;
}

void CalculatorEngine::setResultsSize(size_t size) {
    if (results != nullptr) {
        delete[] results;
    }
    results = new double[size];
}

double CalculatorEngine::getResultAt(size_t index) const {
    if (index < sizeof(results) / sizeof(results[0])) {
        return results[index];
    }
    else {
        throw std::out_of_range("Index invalid");
    }
}
double applyOp(double a, double b, char op) {
    double result = 0;
    switch (op) {
    case '+': result = a + b; break;
    case '-': result = a - b; break;
    case '*': result = a * b; break;
    case '/':
        if (b == 0) throw std::runtime_error("Împărțire la zero");
        result = a / b; break;
    case '^': result = std::pow(a, b); break;
    case '#':
        if (a < 0 && static_cast<int>(b) % 2 == 0) {
            throw std::runtime_error("Rădăcină dintr-un număr negativ pentru grad par nu este suportată");
        }
        result = std::pow(a, 1.0 / b); break;
    default: throw std::runtime_error("Operator necunoscut");
    }
    if (result == -0) return 0; 
    return result;
}

double CalculatorEngine::calculate(const std::string& expression) {
    ExpressionParser parser(expression); 
    auto postfix = parser.parseExpression(); 
    std::stack<double> values;
    for (const auto& token : postfix) { 
        if (isdigit(token[0]) || token[0] == '.') { 
            values.push(std::stod(token));
        }
        else { 
            double val2 = values.top(); values.pop();
            double val1 = values.top(); values.pop();
            char op = token[0];
            values.push(applyOp(val1, val2, op));
        }
    }
    return values.top(); 
}

std::ostream& operator<<(std::ostream& os, const CalculatorEngine& engine) {
    // Afișează numărul de rezultate și un separator
    size_t size = sizeof(engine.results) / sizeof(engine.results[0]);
    os << "Număr de rezultate: " << size << "\n";
    os << "-------------------\n";
    for (size_t i = 0; i < size; i++) {
        os << std::fixed <<  engine.results[i] << "\n";
    }
    return os;
}

std::istream& operator>>(std::istream& is, CalculatorEngine& engine) {
    std::string expression;
    std::getline(is, expression);
    double result = engine.calculate(expression);
    std::cout << "Rezultat: " << result << std::endl;
    return is;
}
CalculatorEngine CalculatorEngine::operator+(const CalculatorEngine& other) const {
    CalculatorEngine result;
    size_t size1 = sizeof(this->results) / sizeof(this->results[0]);
    size_t size2 = sizeof(other.results) / sizeof(other.results[0]);
    if (size1 != size2) {
        throw std::invalid_argument("Numărul de rezultate este diferit");
    }
    result.setResultsSize(size1);
    for (size_t i = 0; i < size1; i++) {
        result.results[i] = this->results[i] + other.results[i];
    }
    return result;
}

CalculatorEngine CalculatorEngine::operator*(const CalculatorEngine& other) const {
    CalculatorEngine result;
    size_t size1 = sizeof(this->results) / sizeof(this->results[0]);
    size_t size2 = sizeof(other.results) / sizeof(other.results[0]);
    if (size1 != size2) {
        throw std::invalid_argument("Numărul de rezultate este diferit");
    }
    result.setResultsSize(size1);
    for (size_t i = 0; i < size1; i++) {
        result.results[i] = this->results[i] * other.results[i];
    }
    return result;
}
