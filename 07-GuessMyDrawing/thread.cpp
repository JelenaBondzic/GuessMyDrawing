#include "thread.h"
#include <iostream>

Thread::Thread(qintptr ID, QObject *parent) : QThread(parent) {
    this->socketDescriptor = ID;
}

void Thread::readyRead() {
    QByteArray data = socket->readAll();
    std::cout << socketDescriptor << ": " << data.toStdString() << std::endl;
    socket->write(data);
}

void Thread::disconnected() {
    std::cout << socketDescriptor << " disconnected! " << std::endl;
    socket->deleteLater();
    exit(0);
}

void Thread::run() {
    std::cout << "Starting thread " << socketDescriptor << std::endl;
    socket = new QTcpSocket();

    if (!socket->setSocketDescriptor(this->socketDescriptor)) {
        // emit error(socket->error());
        std::cout << socket->error();
        return;
    }
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection);
    std::cout << socketDescriptor << " Client connected!" << std::endl;

    exec(); // This makes sure that out thread stays alive until we disconnect it
}

