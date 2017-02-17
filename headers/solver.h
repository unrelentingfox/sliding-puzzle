#ifndef BFSSOLVER_H
#define BFSSOLVER_H

#include "board.h"
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <unistd.h>
#include <utility>
#include <time.h>

using namespace std;

/**
 * @brief      Class for solver.
 */
class Solver {

protected:
	struct Node {
		vector<vector<int> > state;
		Node* parent;
		int parentMove;
		int totalMoves;
		int estimateToGoal;

		Node(Node* p = NULL) {
			parent = p;

			if (p) {
				state = parent->state;
				totalMoves = parent->totalMoves;
			}
			else {
				totalMoves = 0;
			}

			parentMove = 4;
			estimateToGoal = 0;
		}
		Node(vector<vector<int> > st, Node* p, int pm, int tm, int etg) {
			state = st;
			parent = p;
			parentMove = pm;
			totalMoves = tm;
			estimateToGoal = etg;
		}
	};

	void generateNodes(Node* current, list<Node*>& openList, unordered_set<long>& closedList);
	void generateNodesAStar(Node* current, list<Node*>& openList, unordered_set<long>& closedList, vector<vector<int> > goalState);
	void generateNodesNoClosed(Node* current, list<Node*>& openList);
	long hashFunction(vector<vector<int> >);
	void moveState(Node* &state, int direction);
	bool compareStates(const vector<vector<int> >& s1, const vector<vector<int> >& s2);
	int manhattanDistance(vector<vector<int> > state, vector<vector<int> > goal);
	vector<vector<int> > copyState(vector<vector<int> >& state);

public:
	void BFSSolve(Board* board);
	void AStarSolve(Board* board);
	void BFSSolveNoClosed(Board* board);


};

#endif
