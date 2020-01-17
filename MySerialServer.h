//
// Created by gal on 06/01/2020.
//

#ifndef EX4_MYSERIALSERVER_H
#define EX4_MYSERIALSERVER_H

#include "Server.h"

class MySerialServer: public server_side::Server {
private:
    ClientHandler*clientHandler;
public:
    virtual void start(int port);

    void open(int port, ClientHandler *clientHandler);
};


#endif //EX4_MYSERIALSERVER_H
