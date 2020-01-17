//
// Created by gal on 17/01/2020.
//

#include <thread>
#include "MyParallelServer.h"
#include "MyTestClientHandler.h"

void MyParallelServer::open(int port, ClientHandler *clientHandler) {
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    socketfdd=socketfdd;
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        exit(0);
    }

    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(port);
    //we need to convert our number
    // to a number that the network understands.

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr<<"Could not bind the socket to an IP"<<std::endl;
        exit(0);
    }
    //making socket listen to the port
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        std::cerr<<"Error during listening command"<<std::endl;
        exit(0);
    }
    int addrLenn = sizeof(address);
    //this->addrLen=addrLenn;
    // accepting a client
//    int client_socket = accept(socketfd, (struct sockaddr *)&address,(socklen_t*)&addrLenn);
//    if (client_socket == -1) {
//        std::cerr<<"Error accepting client"<<std::endl;
//        exit(0);
//    }
    timeval timeout;
    int client_socket;
    //rememeber to set to 2 mins
    timeout.tv_sec = 120;
    timeout.tv_usec = 0;

    setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));

    while(!shouldStop){
        //cout<<"inside whil"<<endl;
        timeout.tv_sec = 120;
        setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));
        client_socket=accept(socketfd, (struct sockaddr *)&address,(socklen_t*)&addrLenn);
        // cout<<client_socket<<endl;
        if (client_socket < 0) {
            //timeout
            if (errno == EWOULDBLOCK) {
                stop();
                cout << "timeout!" << endl;
                break;
            }
            else {
                perror("other error");
                break;
            }
        }
        //create thread for each client
       // thread serverThread(&ClientHandler::handleClient,this, client_socket);
       // std::thread t(&MySerialServer::start,this,port);
        //serverThread.detach();
        //ClientHandler*handle=new ClientHandler();
        std::thread t(&MyParallelServer::helper ,this,client_socket,clientHandler);
        t.detach();
        //handle the client when you finish handle the next
        //clientHandler->handleClient(client_socket);
    }

}

void MyParallelServer::helper(int client_socket, ClientHandler *clientHandler) {
    clientHandler->getClone()->handleClient(client_socket);

}


