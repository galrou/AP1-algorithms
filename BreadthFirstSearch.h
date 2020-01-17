//
// Created by gal on 13/01/2020.
//

#ifndef Ex4_BREADTHFIRSTSEARCH_H
#define Ex4_BREADTHFIRSTSEARCH_H

#include "Searcher.h"

class BreadthFirstSearch:public Searcher {

private:
    vector<State*> visited;
    queue<State*> statesQueue;

public:
    virtual vector<State*> search(ISearchable* searchable) {

        vector<State*>path;

        State *startingPoint = searchable->getInitialState();
        State *currState;
        vector<State *> children;
        this->statesQueue.push(startingPoint);
        this->numberOfNodesEvaluated++;

        // while q is not empty
        while (!this->statesQueue.empty()) {
            // Remove the first state from q
            State *currState = this->statesQueue.front();
            this->statesQueue.pop();



            if (*currState == *(searchable->getGoalState())) {

                vector<State *> path = this->reversePath(this->backTrace(searchable, currState));

                //this->resetSearcher();

                return path;
            }

            //check if the state contains in visited
            if(isContainedInVisited(currState)){
                continue;
            }

            this->visited.push_back(currState);

            vector<State*> children = searchable->getAllPossibleStates(currState);

            for (State *child : children) {

                if (!isContainedInVisited(child)) {
                    this->numberOfNodesEvaluated++;
                    child->setCameFrom(currState);
                    child->setCost(child->getCost() + child->getCameFrom()->getCost()); // initial the  cost
                    this->statesQueue.push(child);
                }
            }
        }

        return path;
    }

    void resetSearcher(){
        this->numberOfNodesEvaluated=0;
    }

    bool isContainedInVisited(State* currState){
        for(State* state: visited) {
            if(*state == *currState){
                return true;
            }
        }
        return false;
    }


};


#endif //Ex4_BREADTHFIRSTSEARCH_H