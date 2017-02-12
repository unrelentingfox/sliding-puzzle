#ifndef PUZZLE_H
#define PUZZLE_H

#include <iostream>
#include "board.h"
#include "solver.h"

using namespace std;

class Puzzle 
{
	Board *board;

public:
	int start();

};

#endif