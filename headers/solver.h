#ifndef BFSSOLVER_H
#define BFSSOLVER_H

#include "board.h"
#include <list>
#include <unordered_set>
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

	void Solve(Board* board, string type);
	void generateNodes(Node* current, list<Node*>& openList, unordered_set<long>& closedList, Board* board, string type);
	long hashFunction(vector<vector<int> >);
	void moveState(Node*& state, int direction);
	bool compareStates(const vector<vector<int> >& s1, const vector<vector<int> >& s2);
	int manhattanDistance(vector<vector<int> > state, vector<vector<int> > goal);
	void PrintResult(Node* current, float time, int nodes, Board* board, string type);


public:

	void DFSSolve(Board* board) {
		Solve(board, "DFS");
	};
	void BFSSolve(Board* board) {
		Solve(board, "BFS");
	};
	void AStarSolve(Board* board) {
		Solve(board, "ASTAR");
	};
};

#endif
