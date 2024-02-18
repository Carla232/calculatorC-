#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <iostream>
#include <string>
using namespace std;
class UserInterface {
private:
    static double lastResult; 
public:
    UserInterface(); 
    explicit UserInterface(double initialResult);
    ~UserInterface(); 
    static double getLastResult();
    static void setLastResult(double result);
    void startSession(); 
    void displayResult(double result);
    void processFile(const string& filePath, const string& outputOption);
    void saveResultToBinaryFile(const string& fileName);
    void readResultFromBinaryFile(const string& fileName);
    virtual void handleMenuSelection();
    void displayAdvancedMenu();
    void run();
    virtual void displayMenu();
    friend istream& operator>>(istream& is, UserInterface& ui);
    friend ostream& operator<<(ostream& os, const UserInterface& ui); 
    friend bool operator==(const UserInterface& ui, double rhs);
    friend bool operator!=(const UserInterface& ui, double rhs);
};
#endif 
