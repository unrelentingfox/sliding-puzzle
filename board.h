#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <random>
#include <ctime>

using namespace std;

class Board 
{
	int** currState;

	int move(int direction);
	bool checkSuccess();
	int PUZZLE_SIZE;

public:
	int** startState;
	Board(int size=3);
	~Board();
	int moveUp();
	int moveLeft();
	int moveDown();
	int moveRight();
	int scramble();
	int print();
	int** copyState();
	int puzzleSize();
	int** getGoalState();

};

#endif