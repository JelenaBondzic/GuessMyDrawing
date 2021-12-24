#include "server.h"
#include "../Application/MessageType.h"
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
    connect(thread, SIGNAL(messageReceived(QJsonObject,Thread*)), this, SLOT(parseMessage(QJsonObject,Thread*)));
    _clients.append(thread);
}


void Server::parseMessage(const QJsonObject& message, Thread* thread) { 
    const QJsonValue type = message.value(MessageType::TYPE);

    if (type.toString().compare(MessageType::CANVAS_MESSAGE) != 0){
    std::cout << "SERVER RECEIVED: " << type.toString().toStdString() << std::endl;
//    std::cout << "SERVER RECEIVED: " << message.toS << std::endl;
    for (auto it=message.begin(); it !=  message.end(); it++)
      std::cout << it.key().toStdString() << " " << it.value().toString().toStdString() << std::endl;

      }
    if (type.toString().compare(MessageType::TEXT_MESSAGE) == 0) {
        const QJsonValue text = message.value(MessageType::CONTENT);
        const QJsonValue sender = message.value(MessageType::MESSAGE_SENDER);
        Room* room = getRoomFromThread(thread);
        if (room == nullptr) {
            std::cerr << "This client is not in any room";
            return;
        }
        room->broadcastMessage(message, thread);
    }

    if (type.toString().compare(MessageType::CREATE_ROOM) == 0) {
        const QJsonValue username = message.value(MessageType::USERNAME);
        const QJsonValue room_name = message.value(MessageType::ROOM_NAME);
        const QJsonValue duration = message.value(MessageType::DURATION);
        createRoom(username.toString(), room_name.toString(), duration.toInt());
        joinRoom(username.toString(), room_name.toString(), thread);
    }

    if (type.toString().compare(MessageType::JOIN_ROOM) == 0) {
        const QJsonValue username = message.value(MessageType::USERNAME);
        const QJsonValue room_name = message.value(MessageType::ROOM_NAME);
        joinRoom(username.toString(), room_name.toString(), thread);
    }

    if (type.toString().compare(MessageType::LEAVE_ROOM) == 0) {
        leaveRoom(thread);
    }

    if (type.toString().compare(MessageType::CHOOSE_WORD) == 0) {
        const QJsonValue word = message.value(MessageType::CONTENT);
        Room* room = getRoomFromThread(thread);
        if (room == nullptr) {
            std::cerr << "This client is not in any room";
            return;
        }
        room->setWordAndStartGame(word.toString());

        std::cout << "Room word: " << room->getWord().toStdString() << std::endl;
    }

    if (type.toString().compare(MessageType::GET_ROOMS) == 0) {
        QString rooms = getRooms();
        QJsonObject return_message;
        return_message[MessageType::TYPE] = QString(MessageType::GET_ROOMS);
        return_message[MessageType::CONTENT] = rooms;

        thread->send(return_message);
    }

    if (type.toString().compare(MessageType::CANVAS_MESSAGE) == 0) {
        Room* room = getRoomFromThread(thread);
        if (room == nullptr) {
            std::cerr << "This client is not in any room";
            return;
        }
        room->broadcastCanvas(message, thread);
    }

}

void Server::joinRoom(QString username, QString room_name, Thread* thread) {
    Room* room;
    if (_rooms.contains(room_name)) {
        room = _rooms.value(room_name);
    } else {
        std::cerr << "Can't find a room with the name " << room_name.toStdString() << std::endl;
        return ;
    }

    thread->setRoomName(room_name);
    room->joinClient(username, thread);
}

void Server::createRoom(QString username, QString room_name, int duration) {
    Room* room = new Room(username, room_name, duration);
    _rooms.insert(room_name, room);
    std::cout << "Room created" << std::endl;

}

void Server::leaveRoom(Thread* thread) {
  Room *room = getRoomFromThread(thread);

  if (room == nullptr) {
      // izlazi iz igre
      std::cout << "Izlazenje iz igre" << std::endl;
      thread->deleteLater();
      return;
  }
  room->leaveRoom(thread);
  thread->setRoomName("");
}

QString Server::getRooms() {
    QString res = "";
    for (auto i = _rooms.begin(); i != _rooms.end(); i++) {
        res.append(i.key());
        res.append(",");
    }
    res.chop(1);
    return res;
}

Room* Server::getRoomFromThread(Thread* thread) {
    if (thread->getRoomName() == "") {
        //std::cerr << "This client is not in any room.";
        return nullptr;
    }
    QString room_name = thread->getRoomName();
    return _rooms.value(room_name);
}

Server::~Server() {
    qDeleteAll(_clients.begin(), _clients.end());
    _clients.clear();
    qDeleteAll(_rooms);
    _rooms.clear();
}
