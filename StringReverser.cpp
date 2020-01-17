
// Created by idanbazel on 09/01/2020.
//

#include <algorithm>
#include <iostream>
#include "StringReverser.h"

/**
 * @param problem - The string that we want to reverse
 * @return The string 'problem' as its reverse order
 */
string StringReverser::solve(string problem) {

    reverse(problem.begin(), problem.end());
    return problem;
}

StringReverser *StringReverser::getClone() {
    cout<<"before reverser"<<endl;
    return new StringReverser();
}


