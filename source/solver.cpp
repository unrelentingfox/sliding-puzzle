#include "solver.h"


/**
 * @brief      Main solver function that handles the Breadth first search
 *             algorithm
 *
 * @param      board  The board that is to be solved
 */
void Solver::BFSSolve(Board* board) {
	list<Node*> openList;
	unordered_set<long> closedList;
	list<int> solution;
	bool success = false;
	Node* start = new Node();
	start->state = board->getCurrState();
	openList.push_back(start);
	int nodes;
	clock_t before = clock();

	for (nodes = 0; success == false; nodes++) {
		generateNodes(openList.front(), openList, closedList);

		if (compareStates(openList.front()->state, board->getGoalState())) {
			success = true;
		}
		else {
			// cout << "Nodes visited: " << nodes << endl;
			closedList.insert(hashFunction(openList.front()->state));
			openList.pop_front();
		}
	}

	clock_t after = clock();
	float time = ((float)after - (float)before) / CLOCKS_PER_SEC;
	Node* temp = openList.front();
	int moves;

	for (moves = 0; temp->parent != NULL; moves++) {
		solution.push_back(temp->parentMove);
		temp = temp->parent;
	}

	cout << "---------------------------SOLVER---------------------------\n";
	board->print();

	while (!solution.empty()) {
		usleep(500000);
		board->move(solution.back());
		cout << "---------------------------SOLVER---------------------------\n";
		board->print();
		solution.pop_back();
	}

	cout << "------------------------SOLVER-STATS------------------------\n";
	cout << "Runtime: " << time << " seconds." << endl;
	cout << "Checked: " << nodes << " nodes." << endl;
	cout << "Moves: " << moves << " moves." << endl;
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

	// cout << returnVal << endl;
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
 * @brief      Generates all of the possible neighboring states for the current
 *             state, not including any states that are on the closed list.
 *
 * @param      current     The current state
 * @param      openList    The open list
 * @param      closedList  The closed list
 */
void Solver::generateNodes(Node* current, list<Node*>& openList, unordered_set<long>& closedList) {
	Node* temp;

	for (int i = 0; i < 4; i++) {
		temp = new Node(current);
		moveState(temp, i);
		bool unique = true;

		if (closedList.find(hashFunction(temp->state)) != closedList.end()) {
			unique = false;
		}

		if (unique == true) {
			openList.push_back(temp);
		}
		else {
			delete temp;
		}
	}
}


/**
 * @brief      Main solver function that handles the A* Search algorithm
 *
 * @param      board  The board that is to be solved
 */
void Solver::AStarSolve(Board* board) {
	list<Node*> openList;
	unordered_set<long> closedList;
	list<int> solution;
	bool success = false;
	Node* start = new Node();
	Node* temp;
	start->state = board->getCurrState();
	start->estimateToGoal = manhattanDistance(start->state, board->getGoalState());
	openList.push_front(start);
	int nodes; //Counter to see how many nodes are checked by the algorithm before finding the goal
	clock_t before = clock();

	//Main Loop that handles the search
	for (nodes = 0; success == false; nodes++) {
		generateNodesAStar(openList.front(), openList, closedList, board->getGoalState());

		//Check if the next state on the open list is the goal state
		if (compareStates(openList.front()->state, board->getGoalState())) {
			success = true;
		}
		else {
			cout << "Nodes visited: " << nodes << endl;
			openList.pop_front();
		}
	}

	clock_t after = clock();
	float time = ((float)after - (float)before) / CLOCKS_PER_SEC;
	temp = openList.front();
	int moves;

	for (moves = 0; temp->parent != NULL; moves++) {
		solution.push_back(temp->parentMove);
		temp = temp->parent;
	}

	cout << "---------------------------SOLVER---------------------------\n";
	board->print();

	while (!solution.empty()) {
		usleep(500000);
		board->move(solution.back());
		cout << "---------------------------SOLVER---------------------------\n";
		board->print();
		solution.pop_back();
	}

	cout << "------------------------SOLVER-STATS------------------------\n";
	cout << "Runtime: " << time << " seconds." << endl;
	cout << "Checked: " << nodes << " nodes." << endl;
	cout << "Moves: " << moves << " moves." << endl;
}


/**
 * @brief      Generates all of the possible neighboring states for the current
 *             state, not including any states that are on the closed list.
 *
 * @param      current     The current state
 * @param      openList    The open list
 * @param      closedList  The closed list
 */
void Solver::generateNodesAStar(Node* current, list<Node*>& openList, unordered_set<long>& closedList, vector<vector<int> > goalState) {
	Node* temp;
	Node* closedListState;
	long tempKey;
	bool unique;
	bool inserted;
	list<Node*>::iterator it;

	//Create a new state for each possible move
	for (int i = 0; i < 4; i++) {
		temp = new Node(current);
		moveState(temp, i);
		temp->estimateToGoal = manhattanDistance(temp->state, goalState);
		tempKey = hashFunction(temp->state);
		unique = true;
		cout << tempKey << endl;
		cout << temp->estimateToGoal << " " << temp->totalMoves << endl;
		cout << temp->parentMove << endl;

		if (closedList.find(tempKey) != closedList.end()) {
			cout << "Not unique\n";
			unique = false;
		}
		else {
			closedList.insert(tempKey);
		}

		//sort the new node into the open list based on distance
		if (unique == true) {
			inserted = false;

			// usleep(50000);
			for (it = openList.begin(); inserted == false && it != openList.end(); it++) {
				if ((temp->totalMoves + temp->estimateToGoal) < ((*it)->totalMoves + (*it)->estimateToGoal)) {
					cout << (temp->estimateToGoal + temp->totalMoves) << "is less than" << ((*it)->estimateToGoal + (*it)->totalMoves) << endl;
					openList.insert(it, temp);
					inserted = true;
					cout << "inserted inside\n";
				}
			}

			if (inserted == false) {
				cout << "inserted outside\n";
				openList.push_back(temp);
			}
		}
		else {
			delete temp;
		}
	}

	cout << "made it out\n";
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


void Solver::BFSSolveNoClosed(Board* board) {
	list<Node*> openList;
	unordered_set<long> closedList;
	list<int> solution;
	bool success = false;
	Node* start = new Node();
	start->state = board->getCurrState();
	openList.push_back(start);
	int nodes;
	clock_t before = clock();

	for (nodes = 0; success == false; nodes++) {
		generateNodes(openList.front(), openList, closedList);

		if (compareStates(openList.front()->state, board->getGoalState())) {
			success = true;
		}
		else {
			// cout << "Nodes visited: " << nodes << endl;
			// closedList.insert(hashFunction(openList.front()->state));
			openList.pop_front();
		}
	}

	clock_t after = clock();
	float time = ((float)after - (float)before) / CLOCKS_PER_SEC;
	Node* temp = openList.front();
	int moves;

	for (moves = 0; temp->parent != NULL; moves++) {
		solution.push_back(temp->parentMove);
		temp = temp->parent;
	}

	cout << "---------------------------SOLVER---------------------------\n";
	board->print();

	while (!solution.empty()) {
		usleep(500000);
		board->move(solution.back());
		cout << "---------------------------SOLVER---------------------------\n";
		board->print();
		solution.pop_back();
	}

	cout << "------------------------SOLVER-STATS------------------------\n";
	cout << "Runtime: " << time << " seconds." << endl;
	cout << "Checked: " << nodes << " nodes." << endl;
	cout << "Moves: " << moves << " moves." << endl;
}


void Solver::generateNodesNoClosed(Node* current, list<Node*>& openList) {
	Node* temp;

	for (int i = 0; i < 4; i++) {
		temp = new Node(current);
		moveState(temp, i);
		bool unique = true;

		if (compareStates(current->state, temp->state)) {
			unique = false;
		}

		if (unique == true) {
			openList.push_back(temp);
		}
		else {
			delete temp;
		}
	}
}