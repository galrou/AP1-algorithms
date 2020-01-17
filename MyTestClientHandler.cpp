//
// Created by gal on 06/01/2020.
//

#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include "MyTestClientHandler.h"

#define END_STRING "end" // Says that we finished to read information from the socket

/**
 * A constructor.
 *
 * @param cacheManager1 - The object of CacheManager (our cache memory [object])
 * @param solver1 - The object of Solver (gives solutions for problems)
 */
MyTestClientHandler::MyTestClientHandler(CacheManager<string, string>* cacheManager1, Solver<string, string>* solver1) {

    this->cacheManager = cacheManager1;
    this->solver = solver1;
}


/**
 * The method handles the client requests.
 *
 * @param socketClient - The socket_ID of the connection with the client
 */
void MyTestClientHandler::handleClient(int socketClient) {
   // cout<<"in handle"<<endl;

    string problem; // The information that we will get from the socket

    problem = readLineFromSocket(socketClient);
   // cout<<"after readLine"<<endl;

    // As long as you get information (problems) from the socket, find its solution
    while (problem.compare(END_STRING) != 0) {
      //  cout<<"inside problem while in mytest"<<endl;

        // If the buffer is already exists in the cache 'cm'
        if (this->cacheManager->isExists(problem)) {
            string solution = this->cacheManager->get(problem);
           // cout<<"inside first if in mytest"<<endl;
            send(socketClient, solution.c_str(), solution.length(), 0);
        }

            // When the buffer is not exists in the cache 'cm'
        else {
            string solution = this->solver->solve(problem);
            //cout<<solution<<endl;
            this->cacheManager->insert(problem, solution);
            send(socketClient, solution.c_str(), solution.length(), 0);
        }

        problem = readLineFromSocket(socketClient);
    }
   // cout<<"outside problem while in mytest"<<endl;

    // We close the scoket after using
    close(socketClient);
}

/**
 * The method reads the current line from the socket.
 *
 * @param clientSocket - The socket of the connection with the client
 * @return The current line from the socket
 */
string MyTestClientHandler::readLineFromSocket(int clientSocket) {

    string line = ""; // The current line (We will return it)
    char currentChar =  ' '; // The current char that we will read each iteration
    int numBytesRead = 0;

    while (true) {
       // cout<<clientSocket<<endl;
        numBytesRead = read(clientSocket, &currentChar, 1); // Read a character from the socket

        // If unexpected thing was wrong
        if (numBytesRead < 0) {
            cout<<"Error in reading from clientSocket. MyTestClientHandler.cpp->readLineFromSocket"<<endl;
            return nullptr;
        }

        // If we already finished to read all the data of the socket
        if (numBytesRead == 0) {
            return END_STRING;
        }

        // If we finished to read the current line from the socket
        if (currentChar == '\n')  {
            break;
        }

        line += currentChar;
    }
   // cout<<"out of while true in mytest"<<endl;

    return line;
}

ClientHandler *MyTestClientHandler::getClone() {
   // cout<<"before mytest clone"<<endl;
    return new MyTestClientHandler(this->cacheManager->getClone(),this->solver->getClone());
}
