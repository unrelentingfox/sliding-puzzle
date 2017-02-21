#include "board.h"

/**
 * @brief      Constructs the board and initializes the current state and the
 *             goal state.
 *
 * @param[in]  size  The preferred size of the board.
 */
Board::Board(int size) {
	PUZZLE_SIZE = size;
	currState.resize(PUZZLE_SIZE, vector<int>(PUZZLE_SIZE));
	goalState.resize(PUZZLE_SIZE, vector<int>(PUZZLE_SIZE));
	int i = 1;

	for (int y = 0; y < currState.size(); y++) {
		for (int x = 0; x < currState[y].size(); x++) {
			currState[y][x] = i;
			goalState[y][x] = i;

			if (i < (PUZZLE_SIZE * PUZZLE_SIZE - 1))
				i++;
			else
				i = 0;
		}
	}
}



/**
 * @brief      Reconfigures the board based upon inputs.
 *
 * @param[in]  curr  The desired current state, must be an n*n matrix the same size as goal.
 * @param[in]  goal  The desired goal state, must be an n*n matrix the same size as curr.
 */
int Board::manualSet(vector<vector<int> > curr, vector<vector<int> > goal) {
	if (curr.size() >= 3
	        && curr.size() == goal.size()
	        && curr.size() == curr[0].size()
	        && goal.size() == goal[0].size()) {
		currState = curr;
		goalState = goal;
		PUZZLE_SIZE = currState.size();
		return 1;
	}

	return 0;
}

/**
 * @brief      Wrapper function of move() with the UP input.
 */
void Board::moveUp() {
	this->move(0);
}

/**
 * @brief      Wrapper function of move() with the LEFT input.
 */
void Board::moveLeft() {
	this->move(1);
}

/**
 * @brief      Wrapper function of move() with the DOWN input.
 */
void Board::moveDown() {
	this->move(2);
}

/**
 * @brief      Wrapper function of move() with the UP input.
 */
void Board::moveRight() {
	this->move(3);
}


/**
 * @brief      Applies a move to currState based upon direction.
 *
 * @param[in]  direction  The direction of the move (0 : UP, 1 : LEFT, 2 : DOWN,
 *                        3 : RIGHT)
 */
void Board::move(int direction) {
	int emptyX = 0;
	int emptyY = 0;

	//find the empty puzzle peice
	for (int y = 0; y < PUZZLE_SIZE; y++) {
		for (int x = 0; x < PUZZLE_SIZE; x++) {
			if (currState[y][x] == 0) {
				emptyY = y;
				emptyX = x;
			}
		}
	}

	switch (direction) {
	case 0:
		if (emptyY < PUZZLE_SIZE - 1) {
			currState[emptyY][emptyX] = currState[emptyY + 1][emptyX];
			currState[emptyY + 1][emptyX] = 0;
		}

		break;

	case 1:
		if (emptyX < PUZZLE_SIZE - 1) {
			currState[emptyY][emptyX] = currState[emptyY][emptyX + 1];
			currState[emptyY][emptyX + 1] = 0;
		}

		break;

	case 2:
		if (emptyY > 0) {
			currState[emptyY][emptyX] = currState[emptyY - 1][emptyX];
			currState[emptyY - 1][emptyX] = 0;
		}

		break;

	case 3:
		if (emptyX > 0) {
			currState[emptyY][emptyX] = currState[emptyY][emptyX - 1];
			currState[emptyY][emptyX - 1] = 0;
		}

		break;

	default:
		break;
	}
}


/**
 * @brief      Applies a n number of random moves to currState.
 *
 * @param[in]  n     The number of random moves to be applied.
 */
void Board::scramble(int n) {
	int randomNumber;
	mt19937 randomGenerator(time(0));
	uniform_int_distribution<int> roll(0, 3);

	for (int i = 0; i < n; i++) {
		randomNumber = roll(randomGenerator);

		switch (randomNumber) {
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


/**
 * @brief      Prints out the currState to the terminal.
 */
void Board::print() {
	for (int y = 0; y < currState.size(); y++) {
		for (int x = 0; x < currState[y].size(); x++) {
			if (currState[y][x] == 0)
				cout << "  ";
			else
				cout << currState[y][x] << " ";
		}

		if (this->checkSuccess())
			cout << "!!VICTORY!!";

		cout << endl;
	}
}


/**
 * @brief      Checks whether the puzzle is solved or not.
 *
 * @return     True if the puzzle is solved, False if not.
 */
bool Board::checkSuccess() {
	for (int y = 0; y < PUZZLE_SIZE; y++) {
		for (int x = 0; x < PUZZLE_SIZE; x++) {
			if (goalState[y][x] != currState[y][x])
				return false;
		}
	}

	return true;
}


int Board::puzzleSize() {
	return PUZZLE_SIZE;
}

vector<vector<int> > Board::getGoalState() {
	return goalState;
}

vector<vector<int> > Board::getCurrState() {
	return currState;
}