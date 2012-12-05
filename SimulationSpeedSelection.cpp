//
//  SpeedSimulationSelection.cpp
//  life
//
//  Copyright 2012 <EAB>

#include <iostream>
using namespace std;

#include "./SimulationSpeedSelection.h"
#include "./StanfordCPPLib/console.h"
#include "./StanfordCPPLib/simpio.h"

SimulationSpeedSelection::SimulationSpeedSelection() {
    this->getSimulationSpeed();
}

SimulationSpeed SimulationSpeedSelection::getSelectedSiulationSpeed() {
    return this->selectedSimulationSpeed;
}

void SimulationSpeedSelection::getSimulationSpeed() {
    bool validSpeedSelected = false;

    cout << "You choose how fast to run the simulation." << endl;
    cout << "1 = As fast as this chip can go!" << endl;
    cout << "2 = Not too fast, this is a school zone." << endl;
    cout << "3 = Nice and slow so I can watch everything that happens." << endl;
    cout << "4 = Require enter key be pressed before advancing to next "
      "generation." << endl;

    while (!validSpeedSelected) {
        cout << "Your choice: ";
        int userSelection = getInteger();
        validSpeedSelected = true;  // assume its true to save lines

        switch (userSelection) {
            case FAST:
                this->selectedSimulationSpeed = FAST;
                break;
            case MEDIUM:
                this->selectedSimulationSpeed = MEDIUM;
                break;
            case SLOW:
                this->selectedSimulationSpeed = SLOW;
                break;
            case MANUAL:
                this->selectedSimulationSpeed = MANUAL;
                break;
            default:
                validSpeedSelected = false;
                cout << "Please enter a number between 1 and 4!" << endl;
                break;
        }
    }
}
