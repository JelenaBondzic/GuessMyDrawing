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
    connect(thread, SIGNAL(messageReceived(QJsonObject, Thread*)), this, SLOT(parseMessage(QJsonObject, Thread*)));
    _clients.append(thread);
}

void Server::broadcast(const QJsonObject& message) {

    for (Thread* thread : _clients) {
        auto msg = QJsonDocument(message).toJson(QJsonDocument::Compact);
        thread->send(message);
    }
}

void Server::sendMessage(Thread *thread, QByteArray message) {
    thread->receiveMessage(message);
}

void Server::parseMessage(const QJsonObject& message, Thread* thread) {
    const QJsonValue type = message.value(MessageType::TYPE);
    if (type.toString().compare(MessageType::TEXT_MESSAGE) == 0) {
        const QJsonValue text = message.value(MessageType::CONTENT);
        const QJsonValue sender = message.value(MessageType::MESSAGE_SENDER);
        std::cout << "Stiglo od: " << sender.toString().toStdString() <<
                  ": " << text.toString().toStdString() << std::endl;
        broadcast(message);
    }

    if (type.toString().compare(MessageType::CREATE_ROOM) == 0) {
        const QJsonValue username = message.value(MessageType::USERNAME);
        const QJsonValue room_name = message.value(MessageType::ROOM_NAME);
        const QJsonValue duration = message.value(MessageType::DURATION);
        QString broadcast_message = username.toString() + " created room " + room_name.toString();
        QJsonDocument doc = QJsonDocument::fromJson(broadcast_message.toUtf8());
        broadcast(doc.object());
        createRoom(username.toString(), room_name.toString(), duration.toInt());
    }

    if (type.toString().compare(MessageType::JOIN_ROOM) == 0) {
        const QJsonValue username = message.value(MessageType::USERNAME);
        const QJsonValue room_name = message.value(MessageType::ROOM_NAME);
        QString broadcast_message = username.toString() + " joined room " + room_name.toString();
        QJsonDocument doc = QJsonDocument::fromJson(broadcast_message.toUtf8());
        broadcast(doc.object());
        joinRoom(username.toString(), room_name.toString(), thread);
    }

    if (type.toString().compare(MessageType::LEAVE_ROOM) == 0) {
        const QJsonValue username = message.value(MessageType::USERNAME);
        const QJsonValue room_name = message.value(MessageType::ROOM_NAME);
        QString broadcast_message = username.toString() + " left room " + room_name.toString();
        QJsonDocument doc = QJsonDocument::fromJson(broadcast_message.toUtf8());
        broadcast(doc.object());
        leaveRoom(username.toString(), room_name.toString());
    }

    if (type.toString().compare(MessageType::CHOOSE_WORD) == 0) {
        const QJsonValue username = message.value(MessageType::USERNAME);
        const QJsonValue word = message.value(MessageType::CONTENT);
        QString broadcast_message = username.toString() + " choose word" + word.toString();
        QJsonDocument doc = QJsonDocument::fromJson(broadcast_message.toUtf8());
        broadcast(doc.object());
        // make method in room class for choosing a word
    }

    if (type.toString().compare(MessageType::GET_ROOMS) == 0) {
        QString broadcast_message = "Get rooms...";
        QJsonDocument doc = QJsonDocument::fromJson(broadcast_message.toUtf8());
        broadcast(doc.object());
        getRooms();
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

    room->joinClient(username, thread);
}

void Server::createRoom(QString username, QString room_name, int duration) {
    Room* room = new Room(username, room_name, duration);
    _rooms.insert(room_name, room);
}

void Server::leaveRoom(QString username, QString room_name) {
    if (_rooms.contains(room_name)) {
        Room* room = _rooms.value(room_name);
        room->leaveRoom(username);
    } else {
        std::cerr << "Can't find a room with the name " << room_name.toStdString() << std::endl;
    }
}

void Server::getRooms() {}
