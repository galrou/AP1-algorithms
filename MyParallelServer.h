//
// Created by gal on 17/01/2020.
//

#ifndef EX4_MYPARALLELSERVER_H
#define EX4_MYPARALLELSERVER_H

#include "Server.h"

class MyParallelServer:public server_side::Server{
public:
    virtual void open(int port,ClientHandler *clientHandler);
    void helper(int client_socket, ClientHandler *clientHandler);


};


#endif //EX4_MYPARALLELSERVER_H
