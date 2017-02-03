#include "puzzle.h"

Puzzle::Puzzle()
{
	int i = 1;
	for (int y = 0; y < PUZZLE_SIZE; y++)
	{
		for(int x = 0; x< PUZZLE_SIZE; x++)
		{
			board[y][x]= i;
			controlBoard[y][x]=i;
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
	
		if(input == 'w')
			move('w');
		else if(input == 'a')
			move('a');
		else if(input == 's')
			move('s');
		else if(input == 'd')
			move('d');

		this->print();
	}
}


char Puzzle::getInput(){
}

int Puzzle::move(char direction){

	int emptyX = 0;
	int emptyY = 0;

	//find the empty puzzle peice
	for(int y = 0; y < PUZZLE_SIZE; y++)
	{
		for(int x = 0; x < PUZZLE_SIZE; x++)
		{
			if(board[y][x] == 0){
				emptyY = y;
				emptyX = x;
			}
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


int Puzzle::scramble()
{

}


bool Puzzle::checkSuccess()
{
	for (int y = 0; y < PUZZLE_SIZE; y++)
	{
		for(int x = 0; x < PUZZLE_SIZE; x++)
		{
			if(board[y][x] != controlBoard[y][x])
				return false;
		}
	}
	return true;
}


int Puzzle::print()
{
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
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
	if(this->checkSuccess())
		cout << "!!VICTORY!!\n";
}