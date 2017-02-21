/**
 * solver.cpp
 */
#include "solver.h"

void Solver::BFSSolve(Board* board, bool printMoves) {
	Solve(board, 1, printMoves);
}

void Solver::BFSClosedListSolve(Board* board, bool printMoves) {
	Solve(board, 2, printMoves);
}

void Solver::DFSSolve(Board* board, bool printMoves) {
	//depth first search traverses too many nodes to print.
	Solve(board, 3, false);
}

void Solver::AStarSolveManhattanDist(Board* board, bool printMoves) {
	Solve(board, 4, printMoves);
}

void Solver::AStarSolveStraightLineDist(Board* board, bool printMoves) {
	Solve(board, 5, printMoves);
}


/**
 * @brief      Main solver function that handles the Breadth first search
 *             algorithm
 *
 * @param      board  The board that is to be solved
 * @param[in]  type   The type of algorithm to use (DFS, BFS, ASTAR)
 */
void Solver::Solve(Board* board, int type, bool printMoves) {
	list<Node*> openList;
	unordered_set<long> closedList;
	bool success = false;
	Node* current = new Node();
	current->state = board->getCurrState();

	//If we are doing A* then calculate the estimate.
	if (type == 4)
		current->estimateToGoal = manhattanDistance(current->state, board->getGoalState());
	else if (type == 5)
		current->estimateToGoal = straightLineDistance(current->state, board->getGoalState());

	openList.push_back(current);
	int nodes;
	clock_t before = clock();

	for (nodes = 0; success == false && nodes < 3000000; nodes++) {
		//Pop the current state off of the openlist.
		current = openList.front();
		openList.pop_front();

		//Check if OpenList.front is goal state.
		if (compareStates(current->state, board->getGoalState())) {
			success = true;
		}

		//Generate child nodes.
		if (success == false) {
			generateNodes(current, openList, closedList, board, type);

			//Add current node to closed list if the algorithm uses a closed list
			//DFS1 does not use the closed list (1)
			if (type != 1)
				closedList.insert(hashFunction(current->state));
		}
	}

	clock_t after = clock();
	float time = ((float)after - (float)before) / CLOCKS_PER_SEC;
	PrintResult(current, time, nodes, board, type, printMoves);
}


/**
 * @brief      Generates all of the possible neighboring states for the current
 *             state, not including any states that are on the closed list.
 *
 * @param      current     The current state
 * @param      openList    The open list
 * @param      closedList  The closed list
 */
void Solver::generateNodes(Node* current, list<Node*>& openList, unordered_set<long>& closedList, Board* board, int type) {
	Node* child;
	long childKey;

	for (int i = 0; i < 4; i++) {
		child = new Node(current);
		moveState(child, i);

		//If we are doing A* then calculate the estimate.
		if (type == 4)
			child->estimateToGoal = manhattanDistance(child->state, board->getGoalState());
		else if (type == 5)
			child->estimateToGoal = straightLineDistance(child->state, board->getGoalState());

		childKey = hashFunction(child->state);
		bool unique = true;

		//Check if child is actually different than current
		if (compareStates(current->state, child->state)) {
			unique = false;
		}

		//If the algorithm uses a closed list then check to make sure the child is not in the closed list.
		//The BFS algorithm (1) does not use the closed list.
		if (type != 1 && closedList.find(childKey) != closedList.end()) {
			unique = false;
		}

		//Add the child to the open List (varies with each algorithm).
		if (unique == true) {
			if (type == 1 || type == 2) { //BFS algorithm
				openList.push_back(child);
			}
			else if (type == 3) { //DFS algorthm
				openList.push_front(child);
			}
			else if (type == 4 || type == 5) { //A* algorithm
				bool inserted = false;
				list<Node*>::iterator it;

				for (it = openList.begin(); inserted == false && it != openList.end(); it++) {
					if ((child->totalMoves + child->estimateToGoal) <= ((*it)->totalMoves + (*it)->estimateToGoal)) {
						openList.insert(it, child);
						inserted = true;
					}
				}

				//If the child was not better than anything on the openList then insert at the end.
				if (inserted == false) {
					openList.push_back(child);
				}
			}
		}
		else {
			delete child;
		}
	}
}


/**
 * @brief      Takes the vector and converts it to an int based upon the tile
 *             positions
 *
 * @return     the int representation of the state
 */
long Solver::hashFunction(vector<vector<int> > matrix) {
	int n = matrix.size();
	long returnVal = 0;
	long p;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n;  j++) {
			p = 10;

			while (matrix[i][j] >= p)
				p *= 10;

			returnVal *= p;
			returnVal += matrix[i][j];
		}
	}

	return returnVal;
}


/**
 * @brief      Compares the contents of two 2D vectors.
 *
 * @param[in]  s1    vector 1
 * @param[in]  s2    vector 2
 *
 * @return     Returns true if the vectors are the same and false if they are
 *             different.
 */
bool Solver::compareStates(const vector<vector<int> >& s1, const vector<vector<int> >& s2) {
	if (s1.size() != s2.size() || s1[0].size() != s2[0].size()) {
		return false;
	}

	for (int y = 0; y < s1.size(); y++) {
		for (int x = 0; x < s1[y].size(); x++) {
			if (s1[y][x] != s2[y][x])
				return false;
		}
	}

	return true;
}


/**
 * @brief      Takes the Board object and applies all of the moves that the
 *             algorithm suggests and prints them out if the printMoves flag is
 *             set. Also prints out statistics on how the algorithm performed.
 *
 * @param      current     The Node the pointer to the goal state and all of the
 *                         moves that the algorithm made to reach the goal
 *                         state.
 * @param[in]  time        The time in seconds that the algorithm took to
 *                         compute the solution.
 * @param[in]  nodes       The number of nodes that the algorithm traversed
 * @param      board       The board the board that the moves should be applied
 *                         to.
 * @param[in]  type        The type of algorithm (1,2,3,4,5).
 * @param[in]  printMoves  The flag that determines whether or not each move
 *                         will be individually printed out or not.
 */
void Solver::PrintResult(Node* current, float time, int nodes, Board* board, int type, bool printMoves) {
	list<int> solution;
	int moves;

	for (moves = 0; current->parent != NULL; moves++) {
		solution.push_back(current->parentMove);
		current = current->parent;
	}

	if (printMoves) {
		cout << "---------------------------SOLVER----------------------------*\n";
		board->print();
	}

	while (!solution.empty()) {
		board->move(solution.back());
		solution.pop_back();

		if (printMoves) {
			cout << "---------------------------SOLVER----------------------------*\n";
			board->print();
			usleep(500000);
		}
	}

	cout << "------------------------SOLVER-STATS-------------------------*\n";
	cout << "Algorithm: ";

	switch (type) {
	case 1:
		cout << "Breadth First Search (no closed list)" << endl;
		break;

	case 2:
		cout << "Breadth First Search (with closed list)" << endl;
		break;

	case 3:
		cout << "Depth First Search (with closed list)" << endl;
		break;

	case 4:
		cout << "A* (Manhattan Distance)" << endl;
		break;

	case 5:
		cout << "A* (Straight Line Distance)" << endl;
		break;
	}

	cout << "  Runtime: " << time << " seconds." << endl;
	cout << "  Checked: " << nodes << " nodes." << endl;
	cout << " Executed: " << moves << " moves." << endl;
}


/**
 * @brief      Generates the total straight line distance between each tile in
 *             the goal versus the state.
 *
 * @param[in]  state  The current state 
 * @param[in]  goal   The goal state
 *
 * @return     The total distance
 */
float Solver::manhattanDistance(vector<vector<int> > state, vector<vector<int> > goal) {
	//[tileNumber].first == x coordinate, [tileNumber].second == y coordinate
	vector<pair<int, int>> stateCoords(state.size()*state[0].size());
	vector<pair<int, int>> goalCoords(goal.size()*goal[0].size());
	float totalDistance = 0;

	//Iterate through each tile of the goal state and record the coordinates of each tile
	for (int y = 0; y < goal.size(); y++) {
		for (int x = 0; x < goal[0].size(); x++) {
			goalCoords[goal[y][x]].first = x;
			goalCoords[goal[y][x]].second = y;
		}
	}

	//Iterate through each tile of the current state and record the coordingates of each tile
	for (int y = 0; y < state.size(); y++) {
		for (int x = 0; x < state[0].size(); x++) {
			stateCoords[state[y][x]].first = x;
			stateCoords[state[y][x]].second = y;
		}
	}

	//Iterate through all the tiles and find the Manhattan distance between them
	for (int i = 0; i < goalCoords.size() && i < stateCoords.size(); i++) {
		totalDistance += abs(stateCoords[i].first - goalCoords[i].first) + abs(stateCoords[i].second - goalCoords[i].second);
	}

	return totalDistance;
}


/**
 * @brief      Generates the total straight line distance between each tile in
 *             the goal versus the state.
 *
 * @param[in]  state  The current state
 * @param[in]  goal   The goal state
 *
 * @return     The total distance
 */
float Solver::straightLineDistance(vector<vector<int> > state, vector<vector<int> > goal) {
	//[tileNumber].first == x coordinate, [tileNumber].second == y coordinate
	vector<pair<int, int>> stateCoords(state.size()*state[0].size());
	vector<pair<int, int>> goalCoords(goal.size()*goal[0].size());
	float totalDistance = 0;

	//Iterate through each tile of the goal state and record the coordinates of each tile
	for (int y = 0; y < goal.size(); y++) {
		for (int x = 0; x < goal[0].size(); x++) {
			goalCoords[goal[y][x]].first = x;
			goalCoords[goal[y][x]].second = y;
		}
	}

	//Iterate through each tile of the current state and record the coordingates of each tile
	for (int y = 0; y < state.size(); y++) {
		for (int x = 0; x < state[0].size(); x++) {
			stateCoords[state[y][x]].first = x;
			stateCoords[state[y][x]].second = y;
		}
	}

	//Iterate through all the tiles and find the Manhattan distance between them
	for (int i = 0; i < goalCoords.size() && i < stateCoords.size(); i++) {
		totalDistance += sqrt(pow(stateCoords[i].first - goalCoords[i].first, 2) + pow(stateCoords[i].second - goalCoords[i].second, 2));
	}

	return totalDistance;
}


/**
 * @brief      Applies a single "move" to the state that is passed into it. This
 *             function is used in the generateNodes
 *
 * @param      state      The state
 * @param[in]  direction  The direction
 */
void Solver::moveState(Node*& node, int direction) {
	int emptyX = 0;
	int emptyY = 0;

	//Iterate to find 0
	for (int y = 0; y < node->state.size(); y++) {
		for (int x = 0; x < node->state[y].size(); x++) {
			if (node->state[y][x] == 0) {
				emptyY = y;
				emptyX = x;
			}
		}
	}

	switch (direction) {
	case 0:
		if (emptyY < node->state.size() - 1) {
			node->state[emptyY][emptyX] = node->state[emptyY + 1][emptyX];
			node->state[emptyY + 1][emptyX] = 0;
		}

		break;

	case 1:
		if (emptyX < node->state[0].size() - 1) {
			node->state[emptyY][emptyX] = node->state[emptyY][emptyX + 1];
			node->state[emptyY][emptyX + 1] = 0;
		}

		break;

	case 2:
		if (emptyY > 0) {
			node->state[emptyY][emptyX] = node->state[emptyY - 1][emptyX];
			node->state[emptyY - 1][emptyX] = 0;
		}

		break;

	case 3:
		if (emptyX > 0) {
			node->state[emptyY][emptyX] = node->state[emptyY][emptyX - 1];
			node->state[emptyY][emptyX - 1] = 0;
		}

		break;

	default:
		break;
	}

	//iterate the move counter on the Node and record the direction
	node->parentMove = direction;
	node->totalMoves++;
}