#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <random>
#include <ctime>
#include <vector>

using namespace std;

class Board 
{
	vector<vector<int>> goalState;
	vector<vector<int>> currState;

	int move(int direction);
	bool checkSuccess();
	int PUZZLE_SIZE;

public:
	Board(int size = 3);
	int moveUp();
	int moveLeft();
	int moveDown();
	int moveRight();
	int scramble();
	int print();
	vector<vector<int>> copyState();
	int puzzleSize();
	vector<vector<int>> getGoalState();
	vector<vector<int>> getCurrState();

};

#endif