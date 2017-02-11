#ifndef SOLVER_H
#define SOLVER_H

#include "board.h"
#include <list>
#include <queue>

using namespace std;

class Solver {

	struct Node {
		int stateSize;
		int **state;
		Node *parent;
		string parentMove;
	};

	int generateNodes(Node* current, queue<Node*> *openList, list<Node*> *closedList);
	int moveState(int **state, int direction, int size);
	int compareNodes(int** n1, int** n2, int size);
	int checkSuccess(Node* Node);
	int** copyState(int** state, int size);

public:
	Solver();
	int solve(Board* board);


};

#endif
