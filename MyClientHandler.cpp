//
// Created by gal on 17/01/2020.
//

#include "MyClientHandler.h"


MyClientHandler::ClientHandler *MyClientHandler::getClone() {
    return new MyClientHandler(this->cacheManager->getClone(),this->solver->getClone());
}
void MyClientHandler::handleClient(int) {

}