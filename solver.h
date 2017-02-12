#ifndef SOLVER_H
#define SOLVER_H

#include "board.h"
#include <deque>
#include <stack>
#include <unistd.h>
#include <time.h>

using namespace std;

/**
 * @brief      Class for solver.
 */
class Solver {

	struct Node {
		vector<vector<int>> state;
		Node *parent;
		int parentMove;

		Node(){}
		Node(Node* p,vector<vector<int>> s, int pm){
			state = s;
			parent = p;
			parentMove = pm;
		}
	};

	void generateNodes(Node* current, deque<Node*> &openList, deque<Node*> &closedList);
	void moveState(vector<vector<int>> &state, int direction);
	bool compareStates(const vector<vector<int>> &s1, const vector<vector<int>> &s2);
	vector<vector<int>> copyState(vector<vector<int>> &state);

public:
	void solve(Board* board);


};

#endif
