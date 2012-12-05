//
//  GridManager.cpp
//  life
//
//  Copyright 2012 <EB>

#include "./GridManager.h"
#include "./simpio.h"

GridManager::GridManager(Grid<int> initialGrid, LifeDisplay &lDisplay) {
    this->currentGrid = initialGrid;
    this->display = &lDisplay;
}

void GridManager::setSimulationSpeed(SimulationSpeed speed) {
    this->speed = speed;
}

void GridManager::printConsoleRepresentationOfGrid() {
    for (int rowNum = 0; rowNum < this->currentGrid.numRows(); rowNum++) {
        for (int colNum = 0; colNum < this->currentGrid.numCols(); colNum++) {
            if (this->currentGrid.get(rowNum, colNum) > 0)
                cout << this->currentGrid.get(rowNum, colNum);
            else
                cout << "-";
        }
        cout << endl;
    }
}

void GridManager::displayCurrentGrid() {
    this->display->setDimensions(this->currentGrid.numRows(),
                                 this->currentGrid.numCols());

    for (int rNum = 0; rNum < this->currentGrid.numRows(); rNum++) {
        for (int cNum = 0; cNum < this->currentGrid.numCols(); cNum++) {
            this->display->drawCellAt(rNum, cNum,
                                      this->currentGrid.get(rNum, cNum));
        }
    }
}

void GridManager::runSimulation() {
    bool continueSimulation = true;

    while (continueSimulation) {
        switch (this->speed) {
            case FAST:
                break;
            case MEDIUM:
                sleep(5000*1);
                break;
            case SLOW:
                sleep(1000*1);
                break;
            case MANUAL:
                waitForEnter();
                break;
        }
        this->advanceGeneration();
        this->displayCurrentGrid();
    }
}

void GridManager::waitForEnter() {
    getLine();
}

void GridManager::advanceGeneration() {
    Grid<int> newGrid(this->currentGrid.numRows(),
                      this->currentGrid.numCols());

    // copy old grid to new grid, incrementing age by 1 and adjusting each spot
    this->calculateNewCellsAge(this->currentGrid, newGrid);

    // reassign new grid and delete old grid
    this->currentGrid = newGrid;  // WARNING OF MEMORY LEAK
}

void GridManager::calculateNewCellsAge(Grid<int> &oldGrid, Grid<int> &newGrid) {
    // calculate number of neighbors of each cell
    Grid<int> numNeighboringCells(this->currentGrid.numRows(),
                  this->currentGrid.numCols());
    this->calculateNumNeighboringCells(oldGrid, numNeighboringCells);

    // calculate new grid of cells
    for (int rNum = 0; rNum < oldGrid.numRows(); rNum++) {
        for (int cNum = 0; cNum < oldGrid.numCols(); cNum++) {
            switch (numNeighboringCells.get(rNum, cNum)) {
                case 0:
                case 1:
                    newGrid.set(rNum, cNum, GridManager::AGE_DEAD_DNE_CELL);
                    break;
                case 2:
                    newGrid.set(rNum, cNum,
                                (oldGrid.get(rNum, cNum) ==
                                 GridManager::AGE_DEAD_DNE_CELL) ?
                                GridManager::AGE_DEAD_DNE_CELL :
                                oldGrid.get(rNum, cNum) + 1);
                    break;
                case 3:
                    newGrid.set(rNum, cNum, (oldGrid.get(rNum, cNum) + 1));
                    break;
                case 4:
                    newGrid.set(rNum, cNum, GridManager::AGE_DEAD_DNE_CELL);
                    break;
            }
        }
    }
}

void GridManager::calculateNumNeighboringCells(Grid<int> &oldGrid,
                                               Grid<int> &numNeighboringCells) {
    for (int rNum = 0; rNum < oldGrid.numRows(); rNum++) {
        for (int cNum = 0; cNum < oldGrid.numCols(); cNum++) {
            int numNeighbors = 0;

            for (int xDelta = -1; xDelta <= 1; xDelta++) {
                for (int yDelta = -1; yDelta <= 1; yDelta++) {
                    if (xDelta == 0 && yDelta == 0)
                        continue;
                    int xCordinateToCheck = rNum - xDelta;
                    int yCordinateToCheck = cNum - yDelta;
                    if (oldGrid.inBounds(xCordinateToCheck,
                                         yCordinateToCheck)
                        && oldGrid.get(xCordinateToCheck,
                                       yCordinateToCheck) > 0) {
                            // a neighbor exists
                            numNeighbors++;
                    }
                }
            }
            numNeighboringCells.set(rNum, cNum, numNeighbors);
        }
    }
}
