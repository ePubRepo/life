//
//  GridManager.h
//  life
//
//  Copyright 2012 <EAB>

#ifndef GRIDMANAGER_H_
#define GRIDMANAGER_H_

#include <iostream>
#include <string>
#include "./grid.h"
#include "./InputSetup.h"
#include "./SimulationSpeedSelection.h"
#include "./life-graphics.h"

class GridManager {
 public:
    GridManager(Grid<int> initialGrid, LifeDisplay &lDisplay);
    void setSimulationSpeed(SimulationSpeed speed);
    void printConsoleRepresentationOfGrid();
    void runSimulation();
    void displayCurrentGrid();
    static const int AGE_DEAD_DNE_CELL = 0;

 private:
    Grid<int> currentGrid;
    LifeDisplay *display;
    SimulationSpeed speed;
    void advanceGeneration();
    void waitForEnter();
    void calculateNewCellsAge(Grid<int> &oldGrid, Grid<int> &newGrid);
    void calculateNumNeighboringCells(Grid<int> &oldGrid,
                                      Grid<int> &numNeighboringCells);
};


#endif  // GRIDMANAGER_H_
