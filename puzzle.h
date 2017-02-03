#ifndef PUZZLE_H
#define PUZZLE_H

#define PUZZLE_SIZE 3

#include <vector>
#include <ncurses.h>
#include <iostream>
#include <stdio.h>

using namespace std;

class Puzzle 
{

public:
	Puzzle();
	~Puzzle();
	int start(); //function that starts up ncurses and begins accepting inputs

private:
	int board[PUZZLE_SIZE][PUZZLE_SIZE];

	char getInput();
	int move(char direction);
	int scramble();
	bool checkSuccess();
	int print();

};

#endif