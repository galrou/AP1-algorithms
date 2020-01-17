//
// Created by gal on 06/01/2020.
//

#ifndef EX4_SERVER_H
#define EX4_SERVER_H
/**
 * a Server interface
 */
#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "ClientHandler.h"

namespace  server_side{
    class Server {
    protected:
        bool shouldStop=false;
        int socketfdd=0;
        //int addrLen=0;
        bool firstConnection=true;
    public:
        /**
        * this sets the server's initials values
        * @param port
        */
       // virtual void start(int port)=0;
        /**
         * this method starts the server and calls start on a thread
         */
        virtual void open(int port,ClientHandler *clientHandler)=0;
        /**
         * this method stops the server
         */
        virtual void stop(){
            this->shouldStop=true;
            cout<<"in stop"<<endl;
            close(socketfdd);
        };




    };
}



#endif //EX4_SERVER_H
