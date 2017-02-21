/**
 * board.h
 */
#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <random>
#include <ctime>
#include <vector>

using namespace std;


/**
 * @brief      Class for board.
 */
class Board {
	vector<vector<int> > goalState;
	vector<vector<int> > currState;

	bool checkSuccess();
	int PUZZLE_SIZE;

public:

	Board(int size = 3);
	int manualSet(vector<vector<int> > curr, vector<vector<int> > goal);
	void move(int direction);
	void moveUp();
	void moveLeft();
	void moveDown();
	void moveRight();
	void scramble(int n);
	void print();
	int puzzleSize();
	vector<vector<int> > getGoalState();
	vector<vector<int> > getCurrState();

};

#endif