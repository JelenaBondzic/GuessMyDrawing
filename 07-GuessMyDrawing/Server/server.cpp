#include "server.h"
#include <iostream>

Server::Server(QObject* parent): QTcpServer(parent) {}

void Server::startServer() {
    if (!this->listen(QHostAddress::Any, 1234)) {
        std::cout << "Server could not start!" << std::endl;
    } else {
        std::cout << "Server started..." << std::endl;
    }
}

void Server::incomingConnection(qintptr socketDescriptor) {
    std::cout << socketDescriptor << " connecting..." << std::endl;
    Thread* thread = new Thread(socketDescriptor, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

//void Server::newConnection() {
//    QTcpSocket* socket = _server->nextPendingConnection();

//    socket->write("Hello!\r\n");
//    socket->flush();

//    socket->waitForBytesWritten(3000);

//    socket->close();
//}

void Server::broadcast(QString/*Message**/ message) {

}

void Server::joinRoom(QString room_name) {

}

Room* Server::createRoom(QString room_name) {}
