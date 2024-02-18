#include "UserInterface.h"
#include "CalculatorEngine.h"
#include <iostream>
#include <string>
using namespace std;
int main(int argc, char* argv[]) {
    UserInterface ui;
    if (argc > 1) { 
        string expression;
        for (int i = 1; i < argc; ++i) {
            expression += string(argv[i]) + " ";
        }
        CalculatorEngine engine;
        try {
            double result = engine.calculate(expression);
            cout << "Rezultatul calculului: " << result << endl;
        }
        catch (exception& e) {
            cout << "Eroare la calcul: " << e.what() << endl;
        }
        return 0; 
    }
    ui.run();
    return 0;
}