//
// Created by idanbazel on 11/01/2020.
//

#ifndef EX4_MINHEAP_H
#define EX4_MINHEAP_H

#include <queue>
#include "State.h"

class MinHeap {

    struct Comp {
        bool operator()(State* s1, State* s2) {
            return (s1->getCost() > s2->getCost());
        }
    };

    std::priority_queue<State*, std::vector<State*>, Comp> minHeap;

public:

    void insert(State* element) {
        this->minHeap.push(element);
    }

    State* extractMin() {
        State* ansMin = this->minHeap.top();
        this->minHeap.pop();
        return ansMin;
    }

    State* topMin() {
        return this->minHeap.top();
    }

    void remove(State* element) {

        std::vector<State*> vec;

        while (!this->minHeap.empty()) {

            State* currentElem = this->minHeap.top();
            bool areEquals = (*element == *currentElem);

            if (areEquals == false) {
                vec.push_back(currentElem);
            }

            this->minHeap.pop();
        }

        for (int index = 0; index < vec.size(); index++) {
            this->minHeap.push(vec[index]);
        }
    }

    bool isExistMinHeap(State* element) {

        std::vector<State*> vec;
        bool ans = false;

        while (!this->minHeap.empty()) {

            State* currentElem = this->minHeap.top();

            if (*element == *currentElem) {
                ans = true;
                break;
            }
            vec.push_back(currentElem);
            this->minHeap.pop();
        }

        for (int index = 0; index < vec.size(); index++) {
            this->minHeap.push(vec[index]);
        }

        return ans;
    }

    bool isEmpty() {
        return this->minHeap.empty();
    }
};


#endif //EX4_MINHEAP_H
