//
// Created by gal on 13/01/2020.
//

#ifndef Ex4_DEPTHFIRSTSEARCH_H
#define Ex4_DEPTHFIRSTSEARCH_H

#include <stack>
#include <algorithm>
#include "Searcher.h"

/**
 * a class that implements dfs
 * @tparam T
 */
class DepthFirstSearch: public Searcher {
private:
    stack<State*> statesStack;
    vector<State*> visited;




public:
    DepthFirstSearch(){}

    virtual vector<State*> search(ISearchable* searchable) {
        vector<State*> path;

        State* startingPoint = searchable->getInitialState();
        State* currState;
        vector<State*> children;
        this->numberOfNodesEvaluated++;

        //if they are equal return the initial state
//     if(*((searchable)->getInitialState()) == *((searchable)->getGoalState())) {
//         return path.insert(startingPoint);
//     }

        //push the current state

        statesStack.push(startingPoint);
        while(!statesStack.empty()){
            currState = statesStack.top();//actually the parent

            statesStack.pop();




            if(*currState == *(searchable->getGoalState())){
                //back trace the path
                path = this->reversePath(this->backTrace(searchable, currState));

                //this->resetSearcher();

                return path;
            }

            //check if the state contains in visited





            this->visited.push_back(currState);
            //get the successors
            children = searchable->getAllPossibleStates(currState);
            for (State* child : children) {
                //how do we represent infinity the -1 here is infinity
                if (!isContainedInVisited(child)) {
                    child->setCameFrom(currState);
                    child->setCost(child->getCost() + child->getCameFrom()->getCost()); // initial the  cost
                    this->statesStack.push(child);
                    this->numberOfNodesEvaluated++;

                }
            }
        }

        return path;
    }


    void resetSearcher(){
        this->numberOfNodesEvaluated=0;
        this->statesStack = stack<State*>();
        this->visited = vector<State*>();
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

#endif //Ex4_DEPTHFIRSTSEARCH_H