#include "bfssolver.h"


/**
 * @brief      Main solver function that handles the Breadth first search
 *
 * @param      board  The board that is to be solved
 */
void BFSSolver::solve(Board* board)
{
	deque<Node*> openList;
	deque<Node*> closedList;
	deque<int> solution;
	bool success = false;
	Node* start = new Node(NULL, board->getCurrState(), 4);
	openList.push_back(start);
	int nodes;
	clock_t before = clock();

	for (nodes = 0; success == false; nodes++)
	{
		generateNodes(openList.front(), openList, closedList);

		if (compareStates(openList.front()->state, board->getGoalState()))
		{
			success = true;
		}

		else
		{
			// cout << "Nodes visited: " << nodes << endl;
			closedList.push_back(openList.front());
			openList.pop_front();
		}
	}

	clock_t after = clock();
	float time = ((float)after - (float)before) / CLOCKS_PER_SEC;
	Node* temp = openList.front();
	int moves;

	for (moves = 0; temp->parent != NULL; moves++)
	{
		solution.push_back(temp->parentMove);
		temp = temp->parent;
	}

	cout << "---------------------------SOLVER---------------------------\n";
	board->print();

	while (!solution.empty())
	{
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
 * @brief      Compares the contents of two 2D vectors.
 *
 * @param[in]  s1    vector 1
 * @param[in]  s2    vector 2
 *
 * @return     Returns true if the vectors are the same and false if they are
 *             different.
 */
bool BFSSolver::compareStates(const vector<vector<int> >& s1, const vector<vector<int> >& s2)
{
	if (s1.size() != s2.size() || s1[0].size() != s2[0].size())
	{
		return false;
	}

	for (int y = 0; y < s1.size(); y++)
	{
		for (int x = 0; x < s1[y].size(); x++)
		{
			if (s1[y][x] != s2[y][x])
			{ return false; }
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
void BFSSolver::generateNodes(Node* current, deque<Node*>& openList, deque<Node*>& closedList)
{
	Node* temp;

	for (int i = 0; i < 4; i++)
	{
		temp = new Node(current, current->state, i);
		moveState(temp->state, i);
		bool unique = true;

		for (std::deque<Node*>::iterator iterator = closedList.begin(); iterator != closedList.end();
		        ++iterator)
		{
			if (compareStates(current->state, temp->state))
			{
				unique = false;
			}

			else if (compareStates((*iterator)->state, temp->state))
			{
				unique = false;
			}
		}

		if (unique == true)
		{
			openList.push_back(temp);
		}

		else
		{
			delete temp;
		}
	}
}

/**
 * @brief      Applies a single "move" to the state that is passed into it. This
 *             function is used in the generateNodes
 *
 * @param      state      The state
 * @param[in]  direction  The direction
 */
void BFSSolver::moveState(vector<vector<int> >& state, int direction)
{
	int emptyX = 0;
	int emptyY = 0;

	//find the empty puzzle peice
	for (int y = 0; y < state.size(); y++)
	{
		for (int x = 0; x < state[y].size(); x++)
		{
			if (state[y][x] == 0)
			{
				emptyY = y;
				emptyX = x;
			}
		}
	}

	switch (direction)
	{
	case 0:
		if (emptyY < state.size() - 1)
		{
			state[emptyY][emptyX] = state[emptyY + 1][emptyX];
			state[emptyY + 1][emptyX] = 0;
		}

		break;

	case 1:
		if (emptyX < state[0].size() - 1)
		{
			state[emptyY][emptyX] = state[emptyY][emptyX + 1];
			state[emptyY][emptyX + 1] = 0;
		}

		break;

	case 2:
		if (emptyY > 0)
		{
			state[emptyY][emptyX] = state[emptyY - 1][emptyX];
			state[emptyY - 1][emptyX] = 0;
		}

		break;

	case 3:
		if (emptyX > 0)
		{
			state[emptyY][emptyX] = state[emptyY][emptyX - 1];
			state[emptyY][emptyX - 1] = 0;
		}

		break;

	default:
		break;
	}
}