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
    connect(thread, SIGNAL(messageReceived(QJsonObject)), this, SLOT(broadcast(QJsonObject)));
    _clients.append(thread);
}

void Server::broadcast(QJsonObject message) {
    for (Thread* thread : _clients) {
        sendMessage(thread, message);
    }
}

void Server::sendMessage(Thread *thread, QJsonObject message) {
    QJsonDocument doc(message);
    QByteArray data = doc.toJson();
    thread->receiveMessage(data);
}

void Server::joinRoom(QString room_name) {

}

Room* Server::createRoom(QString room_name) {}
