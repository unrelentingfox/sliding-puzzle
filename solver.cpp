#include "solver.h"

Solver::Solver(){

}


int Solver::solve(Board* board){

	queue<Node*> openList;
	list<Node*> closedList;

	Node *start = new Node(NULL, board->getCurrState(), 4);

	openList.push(start);

	 for(int i=0; i<10000; i++){
	 	generateNodes(openList.front(), openList, closedList);
	 	if(compareStates(openList.front()->state, board->getGoalState())){
	 		cout << "victory";
	 		return 0;
	 	} else {
			closedList.push_front(openList.front());
			openList.pop();
		}
	}
}

int Solver::compareStates(const vector<vector<int>> &s1, const vector<vector<int>> &s2){
	if(s1.size() != s2.size() || s1[0].size() != s2[0].size()){
		return false;
	}

	for (int y = 0; y < s1.size(); y++)
	{
		for(int x = 0; x < s1[y].size(); x++)
		{
			if(s1[y][x] != s2[y][x])
				return false;
		}
	}
	return true;
}


int Solver::generateNodes(Node* current, queue<Node*> &openList, list<Node*> &closedList){
	Node *temp;
	for(int i = 0; i < 4; i++){
		temp = new Node(current,current->state,i);
		moveState(temp->state, i);
		for(std::list<Node*>::iterator iterator=closedList.begin(); iterator != closedList.end(); ++iterator)
    	{
    		if(compareStates((*iterator)->state, temp->state))
    			delete temp;
    	}
    	if(temp){
    		openList.push(temp);
    	}
	}
}

int Solver::moveState(vector<vector<int>> &state, int direction){

	int emptyX = 0;
	int emptyY = 0;

	//find the empty puzzle peice
	for(int y = 0; y < state.size(); y++)
	{
		for(int x = 0; x < state[y].size(); x++)
		{
			if(state[y][x] == 0){
				emptyY = y;
				emptyX = x;
			}
		}
	}

	switch (direction){
		case 0:
			if(emptyY < state.size()-1){
				state[emptyY][emptyX] = state[emptyY+1][emptyX];
				state[emptyY+1][emptyX] = 0;
			}
			break;
		case 1:
			if(emptyX < state[0].size()-1){
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