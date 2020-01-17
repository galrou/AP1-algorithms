//
// Created by idanbazel on 11/01/2020.
//

#ifndef EX4_ISEARCHER_H
#define EX4_ISEARCHER_H

#include "ISearchable.h"

/*
 * * * * * * * * * * * * * * * * * * * *
 * An interface for a search algorithm *
 * * * * * * * * * * * * * * * * * * * *
 */
class ISearcher {

public:

    // The search method
    virtual vector<State*> search(ISearchable* searchable) = 0;

    // Get how many nodes were evaluated by the algorithm
    virtual int getNumberOfNodesEvaluated() = 0;

    // A destructor
    virtual ~ISearcher() {}

};


#endif //EX4_ISEARCHER_H
