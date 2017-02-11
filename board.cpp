#include "board.h"

Board::Board(int size) {

	PUZZLE_SIZE = size;
	currState.resize(PUZZLE_SIZE, vector<int>(PUZZLE_SIZE));
	goalState.resize(PUZZLE_SIZE, vector<int>(PUZZLE_SIZE));

	int i = 1;
	for (int y = 0; y < currState.size(); y++)
	{
		for (int x = 0; x < currState[y].size(); x++)
		{
			currState[y][x] = i;
			goalState[y][x] = i;
			if(i < (PUZZLE_SIZE*PUZZLE_SIZE-1))
				i++;
			else
				i = 0;
	   }
	}
}


int Board::moveUp(){
	this->move(0);
}

int Board::moveLeft(){
	this->move(1);
}

int Board::moveDown(){
	this->move(2);
}
int Board::moveRight(){
	this->move(3);
}


int Board::move(int direction){

	int emptyX = 0;
	int emptyY = 0;

	//find the empty puzzle peice
	for(int y = 0; y < PUZZLE_SIZE; y++)
	{
		for(int x = 0; x < PUZZLE_SIZE; x++)
		{
			if(currState[y][x] == 0){
				emptyY = y;
				emptyX = x;
			}
		}
	}

	switch (direction){
		case 0:
			if(emptyY < PUZZLE_SIZE-1){
				currState[emptyY][emptyX] = currState[emptyY+1][emptyX];
				currState[emptyY+1][emptyX] = 0;
			}
			break;
		case 1:
			if(emptyX < PUZZLE_SIZE-1){
				currState[emptyY][emptyX] = currState[emptyY][emptyX+1];
				currState[emptyY][emptyX+1] = 0;
			}
			break;
		case 2:
			if(emptyY > 0){
				currState[emptyY][emptyX] = currState[emptyY-1][emptyX];
				currState[emptyY-1][emptyX] = 0;
			}
			break;
		case 3:
			if(emptyX > 0){
				currState[emptyY][emptyX] = currState[emptyY][emptyX-1];
				currState[emptyY][emptyX-1] = 0;
			}
			break;
		default:
			break;
	}
}


int Board::scramble()
{
	int randomNumber;
	mt19937 randomGenerator(time(0));
	uniform_int_distribution<int> roll(0,3);
	for(int i = 0; i < 1000; i++)
	{
		randomNumber = roll(randomGenerator);
		switch(randomNumber){
			case 0:
				move(0);
				break;
			case 1:
				move(1);
				break;
			case 2:
				move(2);
				break;
			case 3:
				move(3);
				break;
			default:
				break;
		}
	}
}


int Board::print()
{
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	for (int y = 0; y < currState.size(); y++)
	{
		for(int x = 0; x< currState[y].size(); x++)
		{
			if(currState[y][x] == 0)
				cout << "  ";
			else
				cout << currState[y][x] << " ";
		}
		cout << endl;
	}
	if(this->checkSuccess())
		cout << "!!VICTORY!!\n";
}


vector<vector<int>> Board::copyState(){
	vector<vector<int>> copy;

	copy.resize(PUZZLE_SIZE, vector<int>(PUZZLE_SIZE));

	for (int y = 0; y < currState.size(); y++)
	{
		for (int x = 0; x < currState[y].size(); x++)
		{
			copy[y][x] = currState[y][x];
	   }
	}
}


bool Board::checkSuccess(){
	for (int y = 0; y < PUZZLE_SIZE; y++)
	{
		for(int x = 0; x < PUZZLE_SIZE; x++)
		{
			if(goalState[y][x] != currState[y][x])
				return false;
		}
	}
	return true;
}


int Board::puzzleSize(){
	return PUZZLE_SIZE;
}

vector<vector<int>> Board::getGoalState(){
	return goalState;
}

vector<vector<int>> Board::getCurrState(){
	return currState;
}