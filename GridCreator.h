//
//  GridCreator.h
//  life
//
//  Copyright 2012 <EB>

#ifndef GRIDCREATOR_H_
#define GRIDCREATOR_H_

#include <grid.h>
#include <iostream>
#include <string>
#include "InputSetup.h"

class GridCreator {
 public:
    explicit GridCreator(const InputSetupChoice &iSetupChoice);
    Grid<int> getLoadedGrid();
    bool isValidGridLoaded();

 private:
    Grid<int> newGrid;
    std::string gridFileName;
    bool validGridLoaded = false;
    void openFile(const InputSetupChoice &iSetupChoice);
    void parseGridFile(ifstream &infile);
    void createRandomGrid();
};

#endif  // GRIDCREATOR_H_
