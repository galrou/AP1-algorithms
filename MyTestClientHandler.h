//
// Created by gal on 06/01/2020.
//

#ifndef EX4_MYTESTCLIENTHANDLER_H
#define EX4_MYTESTCLIENTHANDLER_H


#include "CacheManager.h"
#include "Solver.h"
#include "ClientHandler.h"

class MyTestClientHandler: public ClientHandler {
private:
    CacheManager<string, string>* cacheManager;
    Solver<string, string>* solver;
public:
    MyTestClientHandler(CacheManager<string, string>*, Solver<string, string>*);
    void handleClient(int);
    string readLineFromSocket(int clientSocket);
    ClientHandler* getClone();

};


#endif //EX4_MYTESTCLIENTHANDLER_H