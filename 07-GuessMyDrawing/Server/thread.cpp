#include "thread.h"
#include <iostream>


Thread::Thread(qintptr ID, QObject *parent) : QObject(parent), socketMessage(new QTcpSocket(this)) {
    this->socketDescriptor = ID;
    if (!socketMessage->setSocketDescriptor(this->socketDescriptor)) {
        // emit error(socket->error());
        std::cout << socketMessage->error();
        return;
    }
    connect(socketMessage, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socketMessage, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection);
    std::cout << socketDescriptor << " Client connected!" << std::endl;
}

void Thread::send(QJsonObject message)
{

}

void Thread::readyRead() {
    QByteArray data = socketMessage->readAll();
    std::cout << "READY READ: " << socketDescriptor << ": " << data.toStdString() << std::endl;
    socketMessage->flush();
    socketMessage->write(data);
    socketMessage->flush();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    emit messageReceived(doc.object());
}

void Thread::disconnected() {
    std::cout << socketDescriptor << " disconnected! " << std::endl;
    socketMessage->deleteLater();
    exit(0);
}

void Thread::receiveMessage(QByteArray message) {

    std::cout << "RECEIVE MESSAGE: " << socketDescriptor << "Strilo u tred : " << message.toStdString() << std::endl;
    socketMessage->write(message);
    socketMessage->flush();
}

