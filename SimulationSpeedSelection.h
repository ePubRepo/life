//
//  SpeedSimulationSelection.h
//  life
//
//  Copyright 2012 <EB>
//

#ifndef SIMULATIONSPEEDSELECTION_H_
#define SIMULATIONSPEEDSELECTION_H_

#include <iostream>

enum SimulationSpeed {
    FAST = 1,
    MEDIUM = 2,
    SLOW = 3,
    MANUAL = 4
};

class SimulationSpeedSelection {
 public:
    SimulationSpeedSelection();
    SimulationSpeed getSelectedSiulationSpeed();

 private:
    void getSimulationSpeed();
    SimulationSpeed selectedSimulationSpeed;
};

#endif  // SIMULATIONSPEEDSELECTION_H_
