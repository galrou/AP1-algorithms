//
// Created by gal on 17/01/2020.
//

#ifndef EX4_MYCLIENTHANDLER_H
#define EX4_MYCLIENTHANDLER_H


#include "ClientHandler.h"
#include "CacheManager.h"
#include "Solver.h"

class MyClientHandler: public ClientHandler {
private:
    CacheManager<string, string>* cacheManager;
    Solver<string, string>* solver;

public:
    /**
     * constructor
     * @param cacheManager1
     * @param solver1
     */
    MyClientHandler(CacheManager<string, string> *cacheManager1, Solver<string, string> *solver1){
        this->cacheManager = cacheManager1;
        this->solver = solver1;
    };
    /**
     * deep copy of the object
     * @return
     */
    ClientHandler* getClone();
    /**
     * handles client
     */
    void handleClient(int);


};


#endif //EX4_MYCLIENTHANDLER_H
