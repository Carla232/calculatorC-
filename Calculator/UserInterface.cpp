#include "UserInterface.h"
#include "CalculatorEngine.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include "ExpressionParser.h"
#include "AdvancedUserInterface.h"
using namespace std;
double UserInterface::lastResult = 0;

UserInterface::UserInterface() {}

UserInterface::~UserInterface() {
}

double UserInterface::getLastResult() {
    return lastResult;
}

void UserInterface::setLastResult(double result) {
    lastResult = result;
}

UserInterface::UserInterface(double initialResult) {
    UserInterface::setLastResult(initialResult);
}

void UserInterface::startSession() {
    cout << "Bine ai venit la CalculatorEngine!\n";
    cout << "Pentru a efectua un calcul, introdu o expresie matematica valida si apasa Enter.\n";
    cout << "Pentru a incheia sesiunea, introdu comanda 'exit' si apasa Enter.\n";
    CalculatorEngine engine;
    string expression;
    while (true) {
        cout << "> ";
        getline(cin, expression);
        if (expression == "exit") {
            cout << "La revedere!\n";
            break;
        }
        try {
            double result = engine.calculate(expression);

            displayResult(result);
            setLastResult(result);
        }
        catch (exception& e) {
            cout << "Eroare: " << e.what() << "\n";
        }
    }
}

void UserInterface::displayResult(double result) {
    stringstream stream;
    stream << result;
    string resultStr = stream.str();
    size_t dotPosition = resultStr.find('.');
    int precision = 0;
    if (dotPosition != string::npos) {
        precision = resultStr.length() - dotPosition - 1;
    }
    cout << "Rezultat: " << fixed << setprecision(precision) << result << endl;
}

istream& operator>>(istream& is, UserInterface& ui) {
    double result;
    cout << "Introduceti un rezultat: ";
    if (is >> result) {
        UserInterface::setLastResult(result);
    }
    else {
        is.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return is;
}

ostream& operator<<(ostream& os, const UserInterface& ui) {
    os << "Ultimul rezultat valid: " << UserInterface::lastResult;
    return os;
}

bool operator==(const UserInterface& ui, double rhs) {
    return UserInterface::lastResult == rhs;
}

bool operator!=(const UserInterface& ui, double rhs) {
    return UserInterface::lastResult != rhs;
}

void UserInterface::processFile(const string& filePath, const string& outputOption) {
    ifstream inputFile(filePath);
    string line;
    CalculatorEngine engine;

    if (outputOption == "console") {
        while (getline(inputFile, line)) {
            try {
                double result = engine.calculate(line);
                displayResult(result);
                setLastResult(result);
            }
            catch (exception& e) {
                cout << "Eroare: " << e.what() << "\n";
            }
        }
    }
    else if (outputOption == "file") {
        ofstream outputFile("results.txt");
        while (getline(inputFile, line)) {
            try {
                double result = engine.calculate(line);
                outputFile << result << "\n";
                setLastResult(result);
            }
            catch (exception& e) {
                outputFile << "Eroare: " << e.what() << "\n";
            }
        }
    }
}

void UserInterface::saveResultToBinaryFile(const string& fileName) {
    ofstream outFile(fileName, ios::binary);
    outFile.write(reinterpret_cast<const char*>(&lastResult), sizeof(lastResult));
    outFile.close();
}

void UserInterface::readResultFromBinaryFile(const string& fileName) {
    ifstream inFile(fileName, ios::binary);
    double result;
    if (inFile.read(reinterpret_cast<char*>(&result), sizeof(result))) {
        cout << "Rezultatul citit din fisierul binar este: " << result << endl;
    }
    else {
        cout << "Nu s-a putut citi fisierul." << endl;
    }
    inFile.close();
}

void UserInterface::displayMenu() {
    cout << "\nMeniu:\n";
    cout << "1. Introducere ecuatie\n";
    cout << "2. Salveaza rezultat curent\n";
    cout << "3. Citeste ecuatii din fisier\n";
    cout << "4. Afiseaza rezultatul curent din fisierul binar\n";
    cout << "5. Acceseaza meniul secundar\n";
    cout << "6. Iesire\n";
    cout << "Selectati o optiune: ";
}

void UserInterface::handleMenuSelection() {
    int choice = 0;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (choice) {
    case 1: {
        startSession();
        break;
    }
    case 2: {
        saveResultToBinaryFile("lastResult.bin");
        break;
    }
    case 3: {
        cout << "Introduceti numele fisierului: ";
        string filePath;
        getline(cin, filePath);
        processFile(filePath, "console");
        break;
    }
    case 4: {
        readResultFromBinaryFile("lastResult.bin");
        break;
    }
    case 5: {
        displayAdvancedMenu();
        break;
    }
    case 6: {
        cout << "Iesire...\n";
        exit(0);
    }
    default: {
        cout << "Optiune invalida.\n";
        break;
    }
    }
}

void UserInterface::displayAdvancedMenu() {
    AdvancedUserInterface advancedUI;
    advancedUI.displayMenu();
    advancedUI.handleMenuSelection();
}

void UserInterface::run() {
    while (true) {
        displayMenu();
        handleMenuSelection();
    }
}
