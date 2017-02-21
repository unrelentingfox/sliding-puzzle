#include "solver.h"


/**
 * @brief      Main solver function that handles the Breadth first search
 *             algorithm
 *
 * @param      board  The board that is to be solved
 * @param[in]  type   The type of algorithm to use (DFS, BFS, ASTAR)
 */
void Solver::Solve(Board* board, string type) {
	list<Node*> openList;
	unordered_set<long> closedList;
	bool success = false;
	Node* current = new Node();
	current->state = board->getCurrState();
	current->estimateToGoal = manhattanDistance(current->state, board->getGoalState());
	openList.push_back(current);
	int nodes;
	clock_t before = clock();

	for (nodes = 0; success == false; nodes++) {
		//Pop the current state off of the openlist.
		current = openList.front();
		openList.pop_front();

		//Check if OpenList.front is goal state
		if (compareStates(current->state, board->getGoalState())) {
			success = true;
		}

		//Generate child nodes
		if (success == false) {
			generateNodes(current, openList, closedList, board, type);
			// cout << "Nodes visited: " << nodes << endl;
			closedList.insert(hashFunction(current->state));
		}
	}

	clock_t after = clock();
	float time = ((float)after - (float)before) / CLOCKS_PER_SEC;
	PrintResult(current, time, nodes, board, type);
}


/**
 * @brief      Generates all of the possible neighboring states for the current
 *             state, not including any states that are on the closed list.
 *
 * @param      current     The current state
 * @param      openList    The open list
 * @param      closedList  The closed list
 */
void Solver::generateNodes(Node* current, list<Node*>& openList, unordered_set<long>& closedList, Board* board, string type) {
	Node* child;
	long childKey;

	for (int i = 0; i < 4; i++) {
		child = new Node(current);
		moveState(child, i);
		child->estimateToGoal = manhattanDistance(child->state, board->getGoalState());
		childKey = hashFunction(child->state);
		bool unique = true;

		if (compareStates(current->state, child->state)
		        || closedList.find(childKey) != closedList.end()) {
			unique = false;
		}

		if (unique == true) {
			if (type == "DFS") {
				openList.push_front(child);
			}
			else if (type == "BFS") {
				openList.push_back(child);
			}
			else if (type == "ASTAR") {
				bool inserted = false;
				list<Node*>::iterator it;

				// usleep(50000);
				for (it = openList.begin(); inserted == false && it != openList.end(); it++) {
					if ((child->totalMoves + child->estimateToGoal) < ((*it)->totalMoves + (*it)->estimateToGoal)) {
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


void Solver::PrintResult(Node* current, float time, int nodes, Board* board, string type) {
	list<int> solution;
	int moves;

	for (moves = 0; current->parent != NULL; moves++) {
		solution.push_back(current->parentMove);
		current = current->parent;
	}

	cout << "---------------------------SOLVER---------------------------\n";
	board->print();

	while (!solution.empty()) {
		if (type != "DFS") {
			usleep(500000);
		}

		board->move(solution.back());

		if (type != "DFS") {
			cout << "---------------------------SOLVER---------------------------\n";
			board->print();
		}

		solution.pop_back();
	}

	cout << "------------------------SOLVER-STATS------------------------\n";
	cout << "Algorithm Type: ";

	if (type == "ASTAR")
		cout << "A*" << endl;
	else
		cout << type << endl;

	cout << "Runtime: " << time << " seconds." << endl;
	cout << "Checked: " << nodes << " nodes." << endl;
	cout << "Moves: " << moves << " moves." << endl;
}


/**
 * @brief      { function_description }
 *
 * @param[in]  state  The state
 *
 * @return     { description_of_the_return_value }
 */
int Solver::manhattanDistance(vector<vector<int> > state, vector<vector<int> > goal) {
	//[tileNumber].first == x coordinate, [tileNumber].second == y coordinate
	vector<pair<int, int>> stateCoords(state.size()*state[0].size());
	vector<pair<int, int>> goalCoords(goal.size()*goal[0].size());
	int totalDistance = 0;
	int* coordinate;

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