#include "thread.h"
#include <iostream>


Thread::Thread(qintptr ID, QObject *parent) :
    QObject(parent),
    socketMessage(new QTcpSocket(this)),
    socketCanvas(new QTcpSocket(this)) {
    this->socketDescriptor = ID;
    if (!socketMessage->setSocketDescriptor(this->socketDescriptor)) {
        // emit error(socket->error());
      //  std::cout << socketMessage->error();
        return;
    }
    connect(socketMessage, SIGNAL(readyRead()), this, SLOT(onMessageReadyRead()), Qt::DirectConnection);
    connect(socketMessage, SIGNAL(disconnected()), this, SLOT(onDisconnectedMessage()), Qt::DirectConnection);

    connect(socketCanvas, SIGNAL(readyRead()), this, SLOT(onCanvasReadyRead()), Qt::DirectConnection);
    connect(socketCanvas, SIGNAL(disconnected()), this, SLOT(onDisconnectedCanvas()), Qt::DirectConnection);

    room_name = "";
   // std::cout << socketDescriptor << " Client connected!" << std::endl;
}

void Thread::send(QJsonObject message)
{
  auto msg = QJsonDocument(message).toJson(QJsonDocument::Compact);
  socketMessage->write(msg);
  socketMessage->flush();
}

void Thread::onMessageReadyRead() {
    QByteArray data = socketMessage->readAll();
//    socketMessage->write(data);
//    socketMessage->flush();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    emit messageReceived(doc.object(), this);
}

void Thread::onCanvasReadyRead() {
    QByteArray data = socketCanvas->readAll();
    socketCanvas->write(data);
    socketCanvas->flush();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    emit messageReceived(doc.object(), this);
}

void Thread::onDisconnectedMessage() {
//    std::cout << socketDescriptor << " disconnected! " << std::endl;
    socketMessage->deleteLater();
    exit(0);
}

void Thread::onDisconnectedCanvas() {
  //  std::cout << socketDescriptor << " disconnected! " << std::endl;
    socketCanvas->deleteLater();
    exit(0);
}

quintptr Thread::getSocketDescriptor() {
    return socketDescriptor;
}

void Thread::setRoomName(QString name) {
    this->room_name = name;
}

QString Thread::getRoomName() {
    return room_name;
}

