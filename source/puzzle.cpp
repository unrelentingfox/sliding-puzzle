/**
 * puzzle.cpp
 */
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
	bool printMoves = true;

	while (input != 'q') {
		cout << "-------------------------------------------------------------=\n";
		cout << "Use the WASD keys to slide tiles surrounding the empty tile. |\n";
		cout << "                                                             |\n";
		cout << "Quit (q)  Shuffle(1)    BFS1(5) BFS2(6) DFS(7) A*1(8) A*2(9) |\n";
		cout << "-------------------------------------------------------------|\n";
		cout << "Print Moves? ";

		if (printMoves)
			cout << "<On >";
		else
			cout << "<Off>";

		cout << " Toggle(p) |  Solve with ALL algorithms(0) |\n";
		cout << "-------------------------------------------------------------=\n";
		board->print();
		cout << "------------------------------------------------------------->>\n";
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
		else if (input == 'p') //toggle whether or not to print out moves to solution.
			switch (printMoves) {
			case true:
				printMoves = false;
				break;

			case false:
				printMoves = true;
				break;
			}
		else if (input == '1')
			board->scramble(100);
		else if (input == '5')
			solver->BFSSolve(board, printMoves);
		else if (input == '6')
			solver->BFSClosedListSolve(board, printMoves);
		else if (input == '7')
			solver->DFSSolve(board, printMoves);
		else if (input == '8')
			solver->AStarSolveManhattanDist(board, printMoves);
		else if (input == '9')
			solver->AStarSolveStraightLineDist(board, printMoves);
		else if (input == '0') { //solve with all algorithms
			Board* temp = new Board();
			//BFS
			temp->manualSet(board->getCurrState(), board->getGoalState());
			solver->BFSSolve(temp, false);
			//BFS with closed list
			temp->manualSet(board->getCurrState(), board->getGoalState());
			solver->BFSClosedListSolve(temp, false);
			//DFS
			temp->manualSet(board->getCurrState(), board->getGoalState());
			solver->DFSSolve(temp, false);
			//A* Manhattan distance
			temp->manualSet(board->getCurrState(), board->getGoalState());
			solver->AStarSolveManhattanDist(temp, false);
			//A* straight line distance
			solver->AStarSolveStraightLineDist(board, false);
		}
	}
}