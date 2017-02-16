#include "puzzle.h"

/**
 * @brief      Function that hangles all of the IO
 */
void Puzzle::start(){
	board = new Board(3);
	cout << "Use the WASD keys to slide tiles surrounding the empty tile.\n";
	cout << "Quit (q)   Randomize(1)   Solve(0)\n";
	board->print();
	char input;
	BFSSolver *solver = new BFSSolver;

	while(input != 'q'){
		cout << "------------------------------------------------------------\n";
		cout << "Use the WASD keys to slide tiles surrounding the empty tile.\n";
		cout << "Quit (q)   Randomize(1)   Solve(0)\n";
		cout << "------------------------------------------------------------\n";
		board->print();
		cout << "------------------------------------------------------------\n";
		cout << "Input: ";
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
			board->scramble(100);
		else if(input == '0')
			solver->solve(board);
	}
}