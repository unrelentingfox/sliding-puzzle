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
		float estimateToGoal;

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

	void Solve(Board* board, int type, bool printMoves = true);
	void generateNodes(Node* current, list<Node*>& openList, unordered_set<long>& closedList, Board* board, int type);
	long hashFunction(vector<vector<int> >);
	void moveState(Node*& state, int direction);
	bool compareStates(const vector<vector<int> >& s1, const vector<vector<int> >& s2);
	float manhattanDistance(vector<vector<int> > state, vector<vector<int> > goal);
	float straightLineDistance(vector<vector<int> > state, vector<vector<int> > goal);
	void PrintResult(Node* current, float time, int nodes, Board* board, int type, bool printMoves);


public:

	void BFSSolve(Board* board, bool printMoves = true);
	void BFSClosedListSolve(Board* board, bool printMoves = true);
	void DFSSolve(Board* board, bool printMoves = false);
	void AStarSolveManhattanDist(Board* board, bool printMoves = true);
	void AStarSolveStraightLineDist(Board* board, bool printMoves = true);
};

#endif
