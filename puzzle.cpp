#include "puzzle.h"

Puzzle::Puzzle()
{
	board = new Board(3);
}


int Puzzle::start(){
	board->print();
	char input;
	Solver *solver = new Solver;

	while(input != 'q'){
		cin >> input;
	
		if(input == 'w')
			board->moveUp();
		else if(input == 'a')
			board->moveLeft();
		else if(input == 's')
			board->moveDown();
		else if(input == 'd')
			board->moveRight();
		else if(input == '1')
			board->scramble();
		else if(input == '0');
			{
				solver->solve(board);
			}

		board->print();
	}
}