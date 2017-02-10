#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <random>
#include <ctime>

using namespace std;

class Board 
{

public:
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
private:
	int** currState;
	int** startState;
	int move(int direction);
	bool checkSuccess();
	int PUZZLE_SIZE;

};

#endif