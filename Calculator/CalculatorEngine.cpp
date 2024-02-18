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
using namespace std;

CalculatorEngine::CalculatorEngine() {
    results = nullptr;
    resultsSize = 0;
}

CalculatorEngine::CalculatorEngine(const CalculatorEngine& other) {
    size_t size = sizeof(other.results) / sizeof(other.results[0]);
    setResultsSize(size);
    for (size_t i = 0; i < size; i++) {
        results[i] = other.results[i];
    }
}

CalculatorEngine& CalculatorEngine::operator=(const CalculatorEngine& other) {
    if (this != &other) {
        delete[] results;
        resultsSize = other.resultsSize;
        results = new double[resultsSize];
        for (size_t i = 0; i < resultsSize; i++) {
            results[i] = other.results[i];
        }
    }
    return *this;
}

void CalculatorEngine::addResult(double result) {
    double* newResults = new double[resultsSize + 1];
    for (size_t i = 0; i < resultsSize; ++i) {
        newResults[i] = results[i];
    }
    newResults[resultsSize] = result;
    delete[] results;
    results = newResults;
    ++resultsSize;
}

CalculatorEngine::~CalculatorEngine() {
    delete[] results;
}

void CalculatorEngine::setResultsSize(size_t size) {
    if (results != nullptr) {
        delete[] results;
    }
    results = new double[size];
    resultsSize = size;
}

double CalculatorEngine::getResultAt(size_t index) const {
    if (index >= resultsSize) {
        throw out_of_range("Index invalid");
    }
    return results[index];
}

double applyOp(double a, double b, char op) {
    double result = 0;
    switch (op) {
    case '+': result = a + b; break;
    case '-': result = a - b; break;
    case '*': result = a * b; break;
    case '/':
        if (b == 0) throw runtime_error("Impartire la zero");
        result = a / b; break;
    case '^': result = pow(a, b); break;
    case '#':
        if (a < 0 && static_cast<int>(b) % 2 == 0) {
            throw runtime_error("Radacina dintr-un numar negativ pentru grad par nu este suportata");
        }
        result = pow(a, 1.0 / b); break;
    default: throw runtime_error("Operator necunoscut");
    }
    if (result == -0) return 0;
    return result;
}

double CalculatorEngine::calculate(const string& expression) {
    ExpressionParser parser(expression);
    auto postfix = parser.parseExpression();
    stack<double> values;
    for (const auto& token : postfix) {
        if (isdigit(token[0]) || token[0] == '.') {
            values.push(stod(token));
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

ostream& operator<<(ostream& os, const CalculatorEngine& engine) {
    if (engine.resultsSize > 0 && engine.results != nullptr) {
        os << "Numar de rezultate: " << engine.resultsSize << "\n";
        os << "-------------------\n";
        for (size_t i = 0; i < engine.resultsSize; i++) {
            os << fixed << engine.results[i] << "\n";
        }
    }
    else {
        os << "Nu exista rezultate disponibile.\n";
    }
    return os;
}

istream& operator>>(istream& is, CalculatorEngine& engine) {
    string expression;
    cout << "Introduceti expresia: ";
    getline(is, expression);
    if (!expression.empty()) {
        double result = engine.calculate(expression);
        engine.addResult(result);
        cout << "Rezultat: " << result << endl;
    }
    return is;
}

CalculatorEngine CalculatorEngine::operator+(const CalculatorEngine& other) const {
    CalculatorEngine result;
    size_t size1 = sizeof(this->results) / sizeof(this->results[0]);
    size_t size2 = sizeof(other.results) / sizeof(other.results[0]);
    if (size1 != size2) {
        throw invalid_argument("Numarul de rezultate este diferit");
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
        throw invalid_argument("Numarul de rezultate este diferit");
    }
    result.setResultsSize(size1);
    for (size_t i = 0; i < size1; i++) {
        result.results[i] = this->results[i] * other.results[i];
    }
    return result;
}
