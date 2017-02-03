#include "puzzle.h"

Puzzle::Puzzle()
{
	int i = 1;
	for (int y = 0; y < PUZZLE_SIZE; y++)
	{
		for(int x = 0; x< PUZZLE_SIZE; x++)
		{
			board[y][x]= i;
			if(i < (PUZZLE_SIZE*PUZZLE_SIZE-1))
				i++;
			else
				i = 0;
		}
	}
}


int Puzzle::start(){
	this->print();
	char input;

	while(input != 'q'){
		cin >> input;
	
		if(input == 'w' || input == 'a' || input == 's' || input == 'd')
			move(input);

		this->print();
	}
}


char Puzzle::getInput(){
}

int Puzzle::move(char direction){

	int emptyX = 0;
	int emptyY = 0;

	for(int y = 0; y < PUZZLE_SIZE; y++)
	{
		for(int x = 0; x < PUZZLE_SIZE; x++)
		{
			if(board[y][x] == 0)
				emptyY = y;
				emptyX = x;
		}
	}

	switch (direction){
		case 'w':
			if(emptyY < PUZZLE_SIZE-1){
				board[emptyY][emptyX] = board[emptyY+1][emptyX];
				board[emptyY+1][emptyX] = 0;
			}
			break;
		case 'a':
			if(emptyX < PUZZLE_SIZE-1){
				board[emptyY][emptyX] = board[emptyY][emptyX+1];
				board[emptyY][emptyX+1] = 0;
			}
			break;
		case 's':
			if(emptyY > 0){
				board[emptyY][emptyX] = board[emptyY-1][emptyX];
				board[emptyY-1][emptyX] = 0;
			}
			break;
		case 'd':
			if(emptyX > 0){
				board[emptyY][emptyX] = board[emptyY][emptyX-1];
				board[emptyY][emptyX-1] = 0;
			}
			break;
		default:
			break;
	}
}


int Puzzle::scramble(){}


bool checkSuccess(){}


int Puzzle::print()
{
	for (int y = 0; y < PUZZLE_SIZE; y++)
	{
		for(int x = 0; x< PUZZLE_SIZE; x++)
		{
			if(board[y][x] == 0)
				cout << "  ";
			else
				cout << board[y][x] << " ";
		}
		cout << endl;
	}
}