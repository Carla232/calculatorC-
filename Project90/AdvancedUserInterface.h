#ifndef ADVANCEDUSERINTERFACE_H
#define ADVANCEDUSERINTERFACE_H
#include "UserInterface.h"

class AdvancedUserInterface : public UserInterface {
public:
    void handleMenuSelection() override;
    void displayMenu() override;
};
#endif