#ifndef PUZZLE_H
#define PUZZLE_H

#include <iostream>
#include "board.h"
#include "bfssolver.h"

using namespace std;

/**
 * @brief      Class for puzzle.
 */
class Puzzle 
{
	Board *board;

public:
	void start();

};

#endif