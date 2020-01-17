//
// Created by idanbazel on 17/01/2020.
//

#ifndef Ex4_ASTAR_H
#define Ex4_ASTAR_H

#include "Searcher.h"

class AStar : public Searcher {

    MinHeap minHeap;
    unordered_set<State*> closed;

public:

    /**
      * -Algorithm-
      *  A Star
      * @param searchable
      * @return The solution (A vector of states that symbols the shortest path from initial state to goal state)
     */
    virtual vector<State*> search(ISearchable* searchable) {

        vector<State*> backTraceAnsVec;

        this->minHeap.insert(searchable->getInitialState()); // Insert initial state

        // Iterations
        while (!this->minHeap.isEmpty()) {

            State* n = this->minHeap.extractMin(); // extract min

            this->closed.insert(n); // insert to closed set

            this->numberOfNodesEvaluated++; // update the number of iterations

            // If we finished (we are in the goal state)
            if (*n == *(searchable->getGoalState())) {

                backTraceAnsVec = this->reversePath(this->backTrace(searchable, n)); // get the path

                //this->restartSearcher(); // restart the Best-First-Search class

                return backTraceAnsVec; // return the path (Solution)
            }

            vector<State*> successors = searchable->getAllPossibleStates(n); // successors vector

            // Iterate over all the adj's of n
            for (State* s : successors) {
                // If we did  not visit at this element yet
                if (!this->isExistClosed(s) && !this->isExistOpen(s)) {

                    s->setCameFrom(n); // initial the father
                    s->setCost(s->getCost() + s->getCameFrom()->getCost() + searchable->h(*s)); // initial the  cost
                    this->minHeap.insert(s); // insert to the min_heap
                }

                    // Else
                else {
                    // Check if we can do the 'Relax' process
                    if (s->getCost() > s->getCost() + n->getCost() + searchable->h(*s)) {

                        this->minHeap.remove(s); // remove s from the min_heap
                        s->setCameFrom(n); // set the new father of s
                        s->setCost(s->getCost() + n->getCost() + searchable->h(*s)); // set the new cost of s (after 'relax')
                        this->minHeap.insert(s); // insert the updated s to the min_heap

                    }
                }
            }
        }

        return backTraceAnsVec;
    }

    bool isExistOpen(State* check) {
        return this->minHeap.isExistMinHeap(check);
    }

    bool isExistClosed(State* check) {

        for (State* it : this->closed) {

            if (*it == *check) {
                return true;
            }
        }
        return false;
    }

    void restartSearcher() {
        this->minHeap = MinHeap();
        this->numberOfNodesEvaluated = 0;
        this->closed.clear();
    }

};

#endif //Ex4_ASTAR_H
