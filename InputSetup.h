//
//  SetupInput.h
//  life
//
//  Copyright 2012 <EAB>

#ifndef INPUTSETUP_H_
#define INPUTSETUP_H_

#include <iostream>
#include <string>
#include "grid.h"

enum InputSetupChoiceSelection {
    SEED_RANDOMLY,
    INPUT_FILE
};

struct InputSetupChoice {
    string filePath;
    InputSetupChoiceSelection usetInputSetupChoiceSelection;
};

class InputSetup {
 public:
    InputSetup();
    Grid<int> getLoadedGrid();

 private:
    Grid<int> loadedGrid;
    void setInputSetupChoice();
    InputSetupChoice processUserSetupInput(const string &userInput);
    string getUserSelection();
    void getSimulationSpeed();
};

#endif  // INPUTSETUP_H_
