#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <iostream>
#include <string>
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
    void processFile(const std::string& filePath, const std::string& outputOption);
    void saveResultToBinaryFile(const std::string& fileName);
    void readResultFromBinaryFile(const std::string& fileName);
    virtual void handleMenuSelection();
    void displayAdvancedMenu();
    void run();
    void handleSecondaryMenuSelection();
    void displaySecondaryMenu();
    virtual void displayMenu();
    friend std::istream& operator>>(std::istream& is, UserInterface& ui);
    friend std::ostream& operator<<(std::ostream& os, const UserInterface& ui); 
    friend bool operator==(const UserInterface& ui, double rhs);
    friend bool operator!=(const UserInterface& ui, double rhs);
};
#endif 
