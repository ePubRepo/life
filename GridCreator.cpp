//
//  GridCreator.cpp
//  life
//
//  Copyright 2012 <EB>

#include <regex.h>
#include <fstream>
#include <string>
using namespace std;

#include "./GridCreator.h"
#include "./grid-constants.h"
#include "./GridManager.h"
#include "./StanfordCPPLib/random.h"
#include "./InputSetup.h"
#include "./stdio.h"

GridCreator::GridCreator(const InputSetupChoice &iSetupChoice) {
    if (iSetupChoice.usetInputSetupChoiceSelection == INPUT_FILE) {
        this->openFile(iSetupChoice);
    } else {
        this->createRandomGrid();
    }
}

void GridCreator::openFile(const InputSetupChoice &iSetupChoice) {
    string relativeFilePath = "files/" + iSetupChoice.filePath;
    ifstream infile(relativeFilePath.c_str());
    if (infile.good()) {
        this->parseGridFile(infile);
    }
}

void GridCreator::parseGridFile(ifstream &infile) {
    string line;
    int rowNum = 0;
    const int UNSET = -1;
    int nRows = UNSET;
    int nCols = UNSET;
    for ( std::string line; getline(infile, line); ) {
        if (line[0] == '#')
            continue;  // ignore a commented row

        if (line.find("X") == string::npos
            && line.find("-") == string::npos) {
            if (nRows == UNSET) {
                std::stringstream(line) >> nRows;
                continue;
            }

            if (nCols == UNSET) {
                std::stringstream(line) >> nCols;
                continue;
            }
        }

        if (nCols != UNSET && nRows != UNSET
            && this->newGrid.numRows() != nRows
            && this->newGrid.numCols() != nCols) {
            // can only be set once, otherwise all extant data lost
            this->newGrid.resize(nRows, nCols);
        }

        // read line of "-" along with "X"
        for (int colNum = 0; colNum < line.length(); colNum++) {
            if (line[colNum] == 'X') {
                this->newGrid.set(rowNum, colNum, INITIAL_CELL_AGE);
            } else {
                this->newGrid.set(rowNum, colNum,
                                  GridManager::AGE_DEAD_DNE_CELL);
            }
        }
        rowNum++;
    }

    if (nRows == UNSET || nCols == UNSET)
        this->validGridLoaded = false;
    else
        this->validGridLoaded = true;
}

bool GridCreator::isValidGridLoaded() {
    return this->validGridLoaded;
}

void GridCreator::createRandomGrid() {
    int randColNums = randomInteger(MIN_RANDOM_DIMENSION,
                             MAX_RANDOM_DIMENSION);
    int randRowNums = randomInteger(MIN_RANDOM_DIMENSION,
                             MAX_RANDOM_DIMENSION);

    this->newGrid.resize(randRowNums, randColNums);

    for (int rowNum = 0; rowNum < randRowNums; rowNum++) {
        for (int colNum = 0; colNum < randColNums; colNum++) {
            if (randomInteger(0, 1) == 0) {
                this->newGrid.set(rowNum, colNum, INITIAL_CELL_AGE);
            }
        }
    }
    this->validGridLoaded = true;
}

Grid<int> GridCreator::getLoadedGrid() {
    return this->newGrid;
}
