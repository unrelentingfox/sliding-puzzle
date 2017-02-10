#include "solver.h"

Solver::Solver(){

}


int Solver::generateNodes(Node* current, queue<Node*> *openList, list<Node*> *closedList){
	Node *temp;
	for(int i = 0; i < 4; i++){
		temp = new Node;
		temp->state = copyState(current->state, current->stateSize);
		moveState(temp->state, i, current->stateSize);
		for(std::list<Node*>::iterator iterator=closedList->begin(); iterator != closedList->end(); ++iterator)
    	{
    		if(compareNodes((*iterator)->state, temp->state, current->stateSize))
    		{
    			delete temp;
    		} else {
    			openList->push(temp);
    		}
    	}
	}
}

int Solver::moveState(int **state, int direction, int size){

	int emptyX = 0;
	int emptyY = 0;

	//find the empty puzzle peice
	for(int y = 0; y < size; y++)
	{
		for(int x = 0; x < size; x++)
		{
			if(state[y][x] == 0){
				emptyY = y;
				emptyX = x;
			}
		}
	}

	switch (direction){
		case 0:
			if(emptyY < size-1){
				state[emptyY][emptyX] = state[emptyY+1][emptyX];
				state[emptyY+1][emptyX] = 0;
			}
			break;
		case 1:
			if(emptyX < size-1){
				state[emptyY][emptyX] = state[emptyY][emptyX+1];
				state[emptyY][emptyX+1] = 0;
			}
			break;
		case 2:
			if(emptyY > 0){
				state[emptyY][emptyX] = state[emptyY-1][emptyX];
				state[emptyY-1][emptyX] = 0;
			}
			break;
		case 3:
			if(emptyX > 0){
				state[emptyY][emptyX] = state[emptyY][emptyX-1];
				state[emptyY][emptyX-1] = 0;
			}
			break;
		default:
			break;
	}
}


int** Solver::copyState(int** state, int size){
	int **copy = new int*[size];

	for (int y = 0; y < size; y++)
	{
		copy[y] = new int[size];

		for (int x = 0; x < size; x++)
		{
			copy[y][x] = state[y][x];
	   }
	}
	return copy;
}


int Solver::compareNodes(int** n1, int** n2, int size){
	for (int y = 0; y < size; y++)
	{
		for(int x = 0; x < size; x++)
		{
			if(n1[y][x] != n2[y][x])
				return false;
		}
	}
	return true;
}



int Solver::solve(Board* board){

	queue<Node*> *openList;
	list<Node*> *closedList;

	Node *start = new Node;
	start->parent = NULL;
	start->parentMove = "";
	start->stateSize = board->puzzleSize();
	start->state = board->copyState();
	
	openList->push(start);

	for(int i=0; i<10000; i++){
		if(compareNodes(openList->front()->state, board->getGoalState(), board->puzzleSize())){
			cout << "victory";
			i = 9999;
		} else {
			closedList->push_front(openList->front());
			openList->pop();
			generateNodes(openList->front(), openList, closedList);
		}
	}
}