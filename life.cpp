/**
 * File: life.cpp
 * --------------
 * Implements the Game of Life.
 * Copyright 2012 - EB
 */

#include <iostream>  // for cout
#include <string>
using namespace std;

#include "./StanfordCPPLib/console.h"  // required of all files that contain the main function
#include "./StanfordCPPLib/simpio.h"  // for getLine

#include "./life-constants.h"  // for kMaxAge
#include "./life-graphics.h"  // for class LifeDisplay

#include "./InputSetup.h"  // initial setup (random board or file)

#include "./grid-constants.h"  // grid management
#include "./GridCreator.h"
#include "./GridManager.h"

static void waitForEnter(string message) {
    cout << message;
    (void) getLine();
}

static void welcome() {
    cout << "Welcome to the game of Life, a simulation of the lifecycle of a "
      "bacteria colony." << endl;
    cout << "Cells live and die by the following rules:" << endl << endl;
    cout << "\tA cell with 1 or fewer neighbors dies of loneliness" << endl;
    cout << "\tLocations with 2 neighbors remain stable" << endl;
    cout << "\tLocations with 3 neighbors will spontaneously create "
      "life" << endl;
    cout << "\tLocations with 4 or more neighbors die of "
      "overcrowding" << endl << endl;
    cout << "In the animation, new cells are dark and fade to gray as "
      "they age." << endl << endl;
    waitForEnter("Hit [enter] to continue....   ");
}

int main() {
    LifeDisplay display;
    display.setTitle("Game of Life");
    display.setDimensions(GRID_WIDTH, GRID_HEIGHT);
    welcome();

    // GET GRID TYPE FROM USER AND LOAD IT
    InputSetup iSetup;
    Grid<int> loadedGrid = iSetup.getLoadedGrid();

    // LOAD GRID
    GridManager manager(loadedGrid, display);
    manager.displayCurrentGrid();

    // GET SIMULATION SPEED
    SimulationSpeedSelection simulationSpeedSelector;
    SimulationSpeed speed = simulationSpeedSelector.getSelectedSiulationSpeed();
    manager.setSimulationSpeed(speed);

    // START SIMULATION
    manager.runSimulation();
    return 0;
}
