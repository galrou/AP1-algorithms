//
// Created by gal on 13/01/2020.
//

#ifndef Ex4_BREADTHFIRSTSEARCH_H
#define Ex4_BREADTHFIRSTSEARCH_H

#include "Searcher.h"

class BreadthFirstSearch:public Searcher {

private:
    unordered_set<State*> visited;
    queue<State*> statesQueue;

public:
    virtual vector<State*> search(ISearchable* searchable) {

        vector<State*>path;

        State *startingPoint = searchable->getInitialState();
        this->visited = unordered_set<State*>();
        vector<State *> children;
        this->statesQueue.push(startingPoint);
        this->numberOfNodesEvaluated++;
        this->visited.insert(startingPoint);

        // while q is not empty
        while (!this->statesQueue.empty()) {
          // cout<<"jkj"<<endl;
            // Remove the first state from q
            State *currState = this->statesQueue.front();
            //cout<<"before pop"<<endl;
            this->statesQueue.pop();
           // cout<<"after pop"<<endl;


            if (*currState == *(searchable->getGoalState())) {
                vector<State *> path = this->reversePath(this->backTrace(searchable, currState));
                //this->resetSearcher();
                return path;
            }
            vector<State*> children = searchable->getAllPossibleStates(currState);

            for (auto *child : children) {
              //  cout<<"kk"<<endl;

                if (!isContainedInVisited(child)) {
                    child->setCameFrom(currState);
                    child->setCost(child->getCost() + child->getCameFrom()->getCost()); // initial the  cost
                    this->statesQueue.push(child);
                  //  cout<<"ib"<<endl;
                    this->visited.insert(child);
                    //cout<<"hh"<<endl;
                    this->numberOfNodesEvaluated++;
                }
            }
            //cout<<"jj"<<endl;
        }

        return path;
    }

    void resetSearcher(){
        this->numberOfNodesEvaluated=0;
    }

    bool isContainedInVisited(State* currState){
        for(State* state: visited) {
            if(*state == *currState){
               // cout<<"true"<<endl;
                return true;
            }
        }
       // cout<<"false"<<endl;
        return false;
    }


};


#endif //Ex4_BREADTHFIRSTSEARCH_H