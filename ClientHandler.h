//
// Created by gal on 06/01/2020.
//

#ifndef EX4_CLIENTHANDLER_H
#define EX4_CLIENTHANDLER_H

#include <fstream>

using namespace std;
class ClientHandler {
public:
    virtual void handleClient(int clientSocket)=0;
    virtual ClientHandler* getClone()=0;

};


#endif //EX4_CLIENTHANDLER_H