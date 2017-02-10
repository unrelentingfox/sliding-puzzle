#ifndef PUZZLE_H
#define PUZZLE_H

#include <vector>
#include <ncurses.h>
#include <iostream>
#include <stdio.h>
#include <random>
#include <ctime>
#include "board.h"

using namespace std;

class Puzzle 
{

public:
	Puzzle();
	~Puzzle();
	int start();

private:
	Board *board;

};

#endif