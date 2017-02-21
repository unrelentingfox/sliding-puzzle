#include "puzzle.h"

/**
 * @brief      Function that hangles all of the IO
 */
void Puzzle::start() {
	board = new Board(3);
	cout << "Use the WASD keys to slide tiles surrounding the empty tile.\n";
	cout << "Quit (q)   Randomize(1)   Solve(0)\n";
	board->print();
	char input;
	Solver* solver = new Solver;

	while (input != 'q') {
		cout << "------------------------------------------------------------\n";
		cout << "Use the WASD keys to slide tiles surrounding the empty tile.\n";
		cout << "Quit (q)  Shuffle(1)  BFS1(6)  BFS2(7)  DFS(8)  A*1(9)  A*2(0)   \n";
		cout << "------------------------------------------------------------\n";
		board->print();
		cout << "------------------------------------------------------------\n";
		cout << "Input: ";
		cin >> input;

		if (input == 'w')
			board->moveUp();
		else if (input == 'a')
			board->moveLeft();
		else if (input == 's')
			board->moveDown();
		else if (input == 'd')
			board->moveRight();
		else if (input == '1')
			board->scramble(1000);
		else if (input == '6')
			solver->BFSSolve(board);
		else if (input == '7')
			solver->BFSClosedListSolve(board);
		else if (input == '8')
			solver->DFSSolve(board);
		else if (input == '9')
			solver->AStarSolveManhattanDist(board);
		else if (input == '0')
			solver->AStarSolveStraightLineDist(board);
	}
}