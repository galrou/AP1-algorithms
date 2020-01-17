//
// Created by idanbazel on 11/01/2020.
//

#ifndef EX4_STATE_H
#define EX4_STATE_H

#include <limits>

using namespace std;

class State {
    string state;            // The state of the current State object
    double cost;             // The cost of the current State object
    State* cameFrom;         // The father of the current State object
    double originalCost;     // The original cost

public:

    /**
     * A constructor.
     * @param state1 - The state that we will initialize
     */
     State(string state1) {
        this->state = state1;
        this->cost = -1;
        this->originalCost = -1;
        cameFrom = nullptr;
    }

    /**
     * Overriding of the == operator.
     *
     * @param other - The State object that we will check
     * @return True - If both states are equal, Else - Otherwise
     */
    bool operator==(State other) {
        return ((this->state).compare(other.getState()) == 0);
    }

    /**
     * Overriding of the < operator.
     *
     * @param other - The State object that we will check
     * @return True - If the current state is less than other's state, Else - Otherwise
     */
    bool operator<(State other) {
        return (this->cost < other.getCost());
    }

    /**
     *
     * @return The current state
     */
    string getState() {
        return this->state;
    }

    /**
     *
     * @return The current cost
     */
    double getCost() {
        return this->cost;
    }

    /**
     *
     * @return The original cost
     */
    double getOriginalCost() {
        return this->originalCost;
    }

    /**
     *
     * @return The father of the current object
     */
    State* getCameFrom() {
        return this->cameFrom;
    }

    /**
     * The method sets the current state to be 'newState'.
     * @param newState
     */
    void setState(string newState) {
        this->state = newState;
    }

    /**
     * The method sets the current cost to be 'newCost'.
     * @param newCost
     */
    void setCost(double newCost) {
        this->cost = newCost;
    }

    /**
     * The method sets the original cost to be 'originCost'.
     * @param originCost
     */
    void setOriginalCost(double originCost) {
        this->originalCost = originCost;
    }

    /**
     * The method sets the current cameFrom to be 'newFather'
     * @param newFather
     */
    void setCameFrom(State* newFather) {
        this->cameFrom = newFather;
    }
};


#endif //EX4_STATE_H
