#ifndef SOLVER_H
#define SOLVER_H

#include "board.h"
#include <list>
#include <queue>

using namespace std;

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

	int generateNodes(Node* current, queue<Node*> &openList, list<Node*> &closedList);
	int moveState(vector<vector<int>> &state, int direction);
	int compareStates(const vector<vector<int>> &s1, const vector<vector<int>> &s2);
	int checkSuccess(Node* Node);
	vector<vector<int>> copyState(vector<vector<int>> &state);

public:
	Solver();
	int solve(Board* board);


};

#endif
