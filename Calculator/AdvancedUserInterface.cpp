#include "AdvancedUserInterface.h"
#include <iomanip>
#include "CalculatorEngine.h"
#include "ExpressionParser.h"
using namespace std;

void AdvancedUserInterface::displayMenu() {
    cout << "\nMeniu Secundar:\n";
    cout << "1. Compara ultimul rezultat cu o valoare\n";
    cout << "2. Verifica daca ultimul rezultat este diferit de o valoare\n";
    cout << "3. Introdu un nou rezultat\n";
    cout << "4. Afiseaza ultimul rezultat valid\n";
    cout << "5. Afiseaza ultimul rezultat folosind getLastResult()\n";
    cout << "6. Aduna doua obiecte CalculatorEngine\n";
    cout << "7. Inmulteste doua obiecte CalculatorEngine\n";
    cout << "8. Adauga un '+' la sfarsitul expresiei curente\n";
    cout << "9. Adauga un '+' si afisati starea anterioara a expresiei\n";
    cout << "10. Elimina ultimul caracter din expresia curenta\n";
    cout << "11. Elimina ultimul caracter si afisati starea anterioara a expresiei\n";
    cout << "12. Iesire\n";
    cout << "Selectati o optiune: ";
}

void AdvancedUserInterface::handleMenuSelection() {
    int choice = 0;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    CalculatorEngine calculatorEngine;
    ExpressionParser expressionParser;
    switch (choice) {
    case 1: {
        double value;
        cout << "Introduceti o valoare pentru comparatie: ";
        cin >> value;
        if (*this == value) {
            cout << "Ultimul rezultat este egal cu " << value << ".\n";
        }
        else {
            cout << "Ultimul rezultat nu este egal cu " << value << ".\n";
        }
        break;
    }
    case 2: {
        double value;
        cout << "Introduceti o valoare pentru verificare: ";
        cin >> value;
        if (*this != value) {
            cout << "Ultimul rezultat este diferit de " << value << ".\n";
        }
        else {
            cout << "Ultimul rezultat nu este diferit de " << value << ".\n";
        }
        break;
    }
    case 3: {
        cout << "Introduceti un nou rezultat: ";
        cin >> *this;
        break;
    }
    case 4: {
        cout << *this;
        break;
    }
    case 5: {
        double lastResult = getLastResult();
        cout << "Ultimul rezultat folosind getLastResult(): " << lastResult << endl;
        break;
    }
    case 6: {
        CalculatorEngine engine1, engine2, engineResult;
        string expression1, expression2;
        cout << "Introduceti prima expresie: ";
        getline(cin, expression1);
        double result1 = engine1.calculate(expression1);
        engine1.addResult(result1);
        cout << "Introduceti a doua expresie: ";
        getline(cin, expression2);
        double result2 = engine2.calculate(expression2);
        engine2.addResult(result2);
        engineResult = engine1 + engine2;
        cout << "Rezultatul adunarii: " << engineResult.getResultAt(0) << endl;
        break;
    }
    case 7: {
        CalculatorEngine engine1, engine2, engineResult;
        string expression1, expression2;
        cout << "Introduceti prima expresie: ";
        getline(cin, expression1);
        double result1 = engine1.calculate(expression1);
        engine1.addResult(result1);
        cout << "Introduceti a doua expresie: ";
        getline(cin, expression2);
        double result2 = engine2.calculate(expression2);
        engine2.addResult(result2);
        engineResult = engine1 * engine2;
        cout << "Rezultatul inmultirii: " << engineResult.getResultAt(0) << endl;
        break;
    }
    case 8: {
        string expression;
        cout << "Introduceti o expresie: ";
        getline(cin, expression);
        expressionParser.setExpression(expression);
        ++expressionParser;
        cout << "Expresia dupa adaugarea '+': " << expressionParser.getExpression() << endl;
        break;
    }
    case 9: {
        string expression;
        cout << "Introduceti o expresie: ";
        getline(cin, expression);
        expressionParser.setExpression(expression);
        ExpressionParser previousState = expressionParser++;
        cout << "Starea anterioara: " << previousState.getExpression() << endl;
        cout << "Starea actuala dupa adaugarea '+': " << expressionParser.getExpression() << endl;
        break;
    }
    case 10: {
        string expression;
        cout << "Introduceti o expresie: ";
        getline(cin, expression);
        expressionParser.setExpression(expression);
        --expressionParser;
        cout << "Expresia dupa eliminarea ultimului caracter: " << expressionParser.getExpression() << endl;
        break;
    }
    case 11: {
        string expression;
        cout << "Introduceti o expresie: ";
        getline(cin, expression);
        expressionParser.setExpression(expression);
        ExpressionParser previousState = expressionParser--;
        cout << "Starea anterioara: " << previousState.getExpression() << endl;
        cout << "Starea actuala dupa eliminarea ultimului caracter: " << expressionParser.getExpression() << endl;
        break;
    }
    case 12:
        return;
    default:
        cout << "Optiune invalida.\n";
        break;
    }
}
