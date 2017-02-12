#ifndef PUZZLE_H
#define PUZZLE_H

#include <iostream>
#include <stdio.h>
#include <random>
#include <ctime>
#include "board.h"
#include "solver.h"

using namespace std;

class Puzzle 
{
	Board *board;

public:
	Puzzle();
	~Puzzle();
	int start();

};

#endif