#include "AdvancedUserInterface.h"
#include <iomanip>
#include "CalculatorEngine.h"
#include "ExpressionParser.h"
void AdvancedUserInterface::displayMenu() {
    std::cout << "\nMeniu Secundar:\n";
    std::cout << "1. Compară ultimul rezultat cu o valoare\n";
    std::cout << "2. Verifică dacă ultimul rezultat este diferit de o valoare\n";
    std::cout << "3. Introduceți un nou rezultat\n";
    std::cout << "4. Afișați ultimul rezultat valid\n";
    std::cout << "5. Afișați ultimul rezultat folosind getLastResult()\n";
    std::cout << "6. Afișează un rezultat specific\n";
    std::cout << "7. Afișați toate rezultatele\n";
    std::cout << "8. Adunați două obiecte CalculatorEngine\n";
    std::cout << "9. Înmulțiți două obiecte CalculatorEngine\n";
    std::cout << "10. Afișați expresia curentă\n";
    std::cout << "11. Verificați dacă expresia curentă este goală\n";
    std::cout << "12. Accesați un caracter din expresia curentă\n";
    std::cout << "13. Ieșire\n";
    std::cout << "Selectați o opțiune: ";
}

void AdvancedUserInterface::handleMenuSelection() {
    int choice = 0;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    CalculatorEngine calculatorEngine;
    ExpressionParser expressionParser;
    switch (choice) {
    case 1: {
        double value;
        std::cout << "Introduceți o valoare pentru comparație: ";
        std::cin >> value;
        if (*this == value) {
            std::cout << "Ultimul rezultat este egal cu " << value << ".\n";
        }
        else {
            std::cout << "Ultimul rezultat nu este egal cu " << value << ".\n";
        }
        break;
    }
    case 2: {
        double value;
        std::cout << "Introduceți o valoare pentru verificare: ";
        std::cin >> value;
        if (*this != value) {
            std::cout << "Ultimul rezultat este diferit de " << value << ".\n";
        }
        else {
            std::cout << "Ultimul rezultat nu este diferit de " << value << ".\n";
        }
        break;
    }
    case 3: {
        std::cout << "Introduceți un nou rezultat: ";
        std::cin >> *this;
        break;
    }
    case 4: {
        std::cout << *this;
        break;
    }
    case 5: {
        double lastResult = getLastResult();
        std::cout << "Ultimul rezultat folosind getLastResult(): " << lastResult << std::endl;
        break;
    }
    case 6: {
        std::cout << "Introduceți indexul rezultatului: ";
        size_t index;
        std::cin >> index;
        try {
            double result = calculatorEngine.getResultAt(index);
            std::cout << "Rezultat la indexul " << index << ": " << result << std::endl;
        }
        catch (const std::out_of_range& e) {
            std::cout << "Eroare: " << e.what() << std::endl;
        }
        break;
    }
    case 7: {
        std::cout << calculatorEngine;
        break;
    }
    case 8: {
        CalculatorEngine other;
        std::cout << "Introduceți un alt obiect CalculatorEngine: \n";
        std::cin >> other;
        CalculatorEngine sum = calculatorEngine + other;
        std::cout << "Suma celor două obiecte este: \n";
        std::cout << sum;
        break;
    }
    case 9: {
        CalculatorEngine other;
        std::cout << "Introduceți un alt obiect CalculatorEngine: \n";
        std::cin >> other;
        CalculatorEngine product = calculatorEngine * other;
        std::cout << "Produsul celor două obiecte este: \n";
        std::cout << product;
        break;
    }
    case 10: {
        std::cout << expressionParser;
        break;
    }
    case 11: {
        bool isEmpty = !expressionParser;
        std::cout << "Expresia curentă este " << (isEmpty ? "goală" : "negoală") << std::endl;
        break;
    }
    case 12: {
        size_t index = 0;
        std::cout << "Introduceți un index: ";
        std::cin >> index;
        try {
            char ch = expressionParser[index];
            std::cout << "Caracterul de la indexul " << index << " este: " << ch << std::endl;
        }
        catch (std::out_of_range& e) {
            std::cout << "Eroare: " << e.what() << std::endl;
        }
        break;
    }
    case 13:
        return;
    default:
        std::cout << "Opțiune invalidă.\n";
        break;
    }
}