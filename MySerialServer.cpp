//
// Created by gal on 06/01/2020.
//


#include <unistd.h>
#include <thread>
#include "MySerialServer.h"



/**
 * this method opens a thread and calls start
 * @param port
 * @param clientHandler
 */
void MySerialServer::open(int port, ClientHandler *clientHandler) {
    this->clientHandler=clientHandler;
    //cout<<"hi0"<<endl;
    std::thread t(&MySerialServer::start,this,port);
   // cout<<"hi1"<<endl;
    t.detach();
}

void MySerialServer::start(int port) {
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
   // cout<<"hi3"<<endl;
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
    timeout.tv_sec = 120000;
    timeout.tv_usec = 0;

    setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));

    while(!shouldStop){
        //cout<<"inside whil"<<endl;
        client_socket=accept(socketfd, (struct sockaddr *)&address,(socklen_t*)&addrLenn);
        cout<<client_socket<<endl;
        if (client_socket < 0) {
            if (errno == EWOULDBLOCK) {
                //cout<<"before stop"<<endl;
               // cout<<"in error"<<endl;
//                if (firstConnection) {
//                    //first Client- checking shouldStop and waiting again.
//                    continue;
//                }
                stop();
                cout << "timeout!" << endl;
                break;
            }
            else {
                perror("other error");
                break;
            }
        }
        firstConnection = false;
        //handle the client when you finish handle the next
        this->clientHandler->handleClient(client_socket);
    }
    //close(socketfd);

}

