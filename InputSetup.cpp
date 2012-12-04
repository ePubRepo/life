//
//  InputSetup.cpp
//  life
//
//  Copyright 2012 <EAB>

#include <iostream>  // for cout
#include <string>
using namespace std;

#include "InputSetup.h"

#include "console.h"  // required of all files that contain the main function
#include "simpio.h"  // for getLine

#include "GridCreator.h"

InputSetup::InputSetup() {
    this->setInputSetupChoice();
}

InputSetupChoice InputSetup::processUserSetupInput(const string &userInput) {
    InputSetupChoice userChoice;
    if (userInput == "") {
        userChoice.usetInputSetupChoiceSelection = SEED_RANDOMLY;
    } else {
        userChoice.usetInputSetupChoiceSelection = INPUT_FILE;
        userChoice.filePath = userInput;
    }
    return userChoice;
}

void InputSetup::setInputSetupChoice() {
    bool validBoardSetup = false;
    InputSetupChoice userChoice;

    while (!validBoardSetup) {
        string userInput = this->getUserSelection();
        userChoice = this->processUserSetupInput(userInput);
        GridCreator myCreator(userChoice);
        if (myCreator.isValidGridLoaded()) {
            validBoardSetup = true;
            this->loadedGrid = myCreator.getLoadedGrid();
        } else {
            cout << "Please enter a valid file." << endl;
        }
    }
}

string InputSetup::getUserSelection() {
    cout << "You can start your colony with random cells or "
    "read from a prepared file." << endl;

    string prompt = "Enter name of colony file (or RETURN to seed randomly): ";
    return getLine(prompt);
}

Grid<int> InputSetup::getLoadedGrid() {
    return this->loadedGrid;
}
