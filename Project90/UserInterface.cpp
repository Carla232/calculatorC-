#include "UserInterface.h"
#include "CalculatorEngine.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <string>
#include <fstream>
#include "ExpressionParser.h"
#include "AdvancedUserInterface.h"
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
    std::cout << "Bine ai venit la CalculatorEngine!\n";
    std::cout << "Pentru a efectua un calcul, introdu o expresie matematică validă și apasă Enter.\n";
    std::cout << "Pentru a încheia sesiunea, introdu comanda 'exit' și apasă Enter.\n";
    CalculatorEngine engine;
    std::string expression;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, expression);
        if (expression == "exit") {
            std::cout << "La revedere!\n";
            break;
        }
        try {
            double result = engine.calculate(expression);

            displayResult(result);
            setLastResult(result);
        }
        catch (std::exception& e) {
            std::cout << "Eroare: " << e.what() << "\n";
        }
    }
}

void UserInterface::displayResult(double result) {
    std::stringstream stream;
    stream << result;
    std::string resultStr = stream.str();
    size_t dotPosition = resultStr.find('.');
    int precision = 0;
    if (dotPosition != std::string::npos) {
        precision = resultStr.length() - dotPosition - 1;
    }
    std::cout << "Rezultat: " << std::fixed << std::setprecision(precision) << result << std::endl;
}

std::istream& operator>>(std::istream& is, UserInterface& ui) {
    double result;
    std::cout << "Introduceți un rezultat: ";
    if (is >> result) {
        UserInterface::setLastResult(result);
    }
    else {
        is.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const UserInterface& ui) {
    os << "Ultimul rezultat valid: " << UserInterface::lastResult;
    return os;
}
bool operator==(const UserInterface& ui, double rhs) {
    return UserInterface::lastResult == rhs; 
}

bool operator!=(const UserInterface& ui, double rhs) {
    return UserInterface::lastResult != rhs;
}
void UserInterface::processFile(const std::string& filePath, const std::string& outputOption) {
    std::ifstream inputFile(filePath);
    std::string line;
    CalculatorEngine engine;

    if (outputOption == "console") {
        while (std::getline(inputFile, line)) {
            try {
                double result = engine.calculate(line);
                displayResult(result);
                setLastResult(result);
            }
            catch (std::exception& e) {
                std::cout << "Eroare: " << e.what() << "\n";
            }
        }
    }
    else if (outputOption == "file") {
        std::ofstream outputFile("results.txt");
        while (std::getline(inputFile, line)) {
            try {
                double result = engine.calculate(line);
                outputFile << result << "\n";
                setLastResult(result);
            }
            catch (std::exception& e) {
                outputFile << "Eroare: " << e.what() << "\n";
            }
        }
    }
}
void UserInterface::saveResultToBinaryFile(const std::string& fileName) {
    std::ofstream outFile(fileName, std::ios::binary);
    outFile.write(reinterpret_cast<const char*>(&lastResult), sizeof(lastResult));
    outFile.close();
}
void UserInterface::readResultFromBinaryFile(const std::string& fileName) {
    std::ifstream inFile(fileName, std::ios::binary);
    double result;
    if (inFile.read(reinterpret_cast<char*>(&result), sizeof(result))) {
        std::cout << "Rezultatul citit din fisierul binar este: " << result << std::endl;
    }
    else {
        std::cout << "Nu s-a putut citi fisierul." << std::endl;
    }
    inFile.close();
}
void UserInterface::displayMenu() {
    std::cout << "\nMeniu:\n";
    std::cout << "1. Introducere ecuație\n";
    std::cout << "2. Salvează rezultat curent\n";
    std::cout << "3. Citește ecuații din fișier\n";
    std::cout << "4. Afișează rezultatul curent din fișierul binar\n";
    std::cout << "5. Accesează meniul secundar\n"; // Noua opțiune pentru meniul secundar
    std::cout << "6. Ieșire\n"; // Noua opțiune pentru ieșire
    std::cout << "Selectați o opțiune: ";
}
void UserInterface::handleMenuSelection() {
    int choice = 0;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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
        std::cout << "Introduceți numele fișierului: ";
        std::string filePath;
        std::getline(std::cin, filePath);
        processFile(filePath, "console");
        break;
    }
    case 4: {
        readResultFromBinaryFile("lastResult.bin");
        break;
    }
    case 5: {
        displayAdvancedMenu(); // Afișează meniul secundar
        break;
    }
    case 6: {
        std::cout << "Ieșire...\n";
        exit(0);
    }
    default: {
        std::cout << "Opțiune invalidă.\n";
        break;
    }
    }
}
void UserInterface::displayAdvancedMenu() {
    AdvancedUserInterface advancedUI;
    advancedUI.displayMenu(); // Afișează meniul secundar
    advancedUI.handleMenuSelection(); // Gestionează selecția din meniul secundar
}
void UserInterface::run() { while (true) { displayMenu(); handleMenuSelection(); } }