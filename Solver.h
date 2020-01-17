//
// Created by gal on 06/01/2020.
//

#ifndef EX4_SOLVER_H
#define EX4_SOLVER_H

/**
 * a Solver interface
 */
#include <string>
#include "ClientHandler.h"

//Solver<Problem, Solution>
//every class that will implement Solver will be able to choose the
//type of the problem an the type of the solution
template<typename Problem, typename Solution>
class Solver {
public:
    /**
     * solves a problem
     * @param p
     */
    virtual Solution solve(Problem p)=0;
    virtual Solver* getClone()=0;


};


#endif //EX4_SOLVER_H
