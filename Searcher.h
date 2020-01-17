//
// Created by idanbazel on 11/01/2020.
//

#ifndef EX4_SEARCHER_H
#define EX4_SEARCHER_H

#include <unordered_set>
#include "ISearcher.h"
#include "MinHeap.h"

/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * An abstract class for a search algorithm. * * * * * * * * * * * * * *
 * This abstract class implements the 'ISearcher' interface, * * * * * *
 * by the solution of: Vector of State<T>*, that will tell us  * * * * *
 * what our states in our way to the goal(target) state in the * * * * *
 * solution of the problem. In addition, we puts the T object in order *
 * to use it in our Min_Heap and our algorithms. * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
class Searcher : public ISearcher {

protected:


    int numberOfNodesEvaluated = 0; // Initialize this number to be 0 at the first

public:

    virtual vector<State*> search(ISearchable* searchable) = 0;

    virtual int getNumberOfNodesEvaluated() {
        return this->numberOfNodesEvaluated;
    }

    virtual vector<State*> backTrace(ISearchable* searchable, State* goal) {

        vector<State*> ansVec;

        State* father = goal;

        while (!((*father) == (*searchable->getInitialState()))) {

            ansVec.push_back(father);
            father = father->getCameFrom();
        }

        ansVec.push_back(father);

        return ansVec;
    }

    virtual vector<State *> reversePath(vector<State *> vec) {

        vector<State*> ansVec;

        unsigned int vectorSize = vec.size();

        for (unsigned int index = vectorSize - 1; index >= 0; index--) {
            ansVec.push_back(vec[index]);

            if (index == 0)
                break;
        }
        return ansVec;
    }

    virtual void resetSearcher() {
        this->numberOfNodesEvaluated = 0;
    }
};
#endif //EX4_SEARCHER_H
