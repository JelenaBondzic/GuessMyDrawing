#include "thread.h"
#include <iostream>
#include <QJsonObject>

Thread::Thread(qintptr ID, QObject *parent) : QObject(parent), socket(new QTcpSocket(this)) {
    this->socketDescriptor = ID;
    if (!socket->setSocketDescriptor(this->socketDescriptor)) {
        // emit error(socket->error());
        std::cout << socket->error();
        return;
    }
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection);
    std::cout << socketDescriptor << " Client connected!" << std::endl;
}

void Thread::send(QJsonObject message)
{

}

void Thread::readyRead() {
    QByteArray data = socket->readAll();
    std::cout << socketDescriptor << ": " << data.toStdString() << std::endl;
    socket->write(data);
    emit messageReceived(data);
}

void Thread::disconnected() {
    std::cout << socketDescriptor << " disconnected! " << std::endl;
    socket->deleteLater();
    exit(0);
}

void Thread::receiveMessage(QByteArray message) {
    std::cout << socketDescriptor << ": " << message.toStdString() << std::endl;
    socket->write(message);
}

