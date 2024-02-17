#include "UserInterface.h"
#include "CalculatorEngine.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    UserInterface ui;
    if (argc > 1) { // Verifică dacă există argumente în linia de comandă
        std::string expression;
        for (int i = 1; i < argc; ++i) {
            expression += std::string(argv[i]) + " ";
        }
        CalculatorEngine engine;
        try {
            double result = engine.calculate(expression);
            std::cout << "Rezultatul calculului: " << result << std::endl;
        }
        catch (std::exception& e) {
            std::cout << "Eroare la calcul: " << e.what() << std::endl;
        }
        return 0; // Încheie execuția dacă a fost furnizată o ecuație
    }
    // Continuă cu interfața utilizatorului dacă nu sunt argumente în linia de comandă
    ui.run();
    return 0;
}