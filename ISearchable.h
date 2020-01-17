//
// Created by idanbazel on 11/01/2020.
//

#ifndef EX4_ISEARCHABLE_H
#define EX4_ISEARCHABLE_H

#include <vector>
#include "State.h"

using namespace std;

/*
 * * * * * * * * * * * * * * * * * * * * *
 * An interface for a searchable problem *
 * * * * * * * * * * * * * * * * * * * * *
 */
class ISearchable {

public:

    virtual State* getInitialState() = 0;

    virtual State* getGoalState() = 0;

    virtual vector<State*> getAllPossibleStates(State*) = 0;

    virtual double h(State s1) = 0;

    virtual ~ISearchable() = default;

};




#endif //EX4_ISEARCHABLE_H
