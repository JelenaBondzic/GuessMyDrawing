#include "server.h"
#include <iostream>

Server::Server(QObject* parent):
    QTcpServer(parent),
    _serverMessageParser(new ServerMessageParser()) {}

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
    ServerMessageType type = _serverMessageParser->getTypeFromMessage(message);

    switch(type) {
    case ServerMessageType::TEXT_MESSAGE: {
        std::cout<<"Text message"<<std::endl;
        broadcastMessage(message, thread);
        return;
    }
    case ServerMessageType::CREATE_ROOM: {
        std::cout<<"CREATE_ROOM"<<std::endl;
        QVector<QString> ret = _serverMessageParser->fromCreateRoomMessage(message);
        createRoom(ret[0], ret[1], ret[2].toInt());
        joinRoom(ret[0], ret[1], thread);
        return;
    }
    case ServerMessageType::JOIN_ROOM: {
        std::cout<<"JOIN_ROOM"<<std::endl;
        QVector<QString> ret = _serverMessageParser->fromJoinRoomMessage(message);
        joinRoom(ret[0], ret[1], thread);
        return;
    }
    case ServerMessageType::LEAVE_ROOM: {
        std::cout<<"LEAVE_ROOM"<<std::endl;
        leaveRoom(thread);
        return;
    }
    case ServerMessageType::CHOOSE_WORD: {
        std::cout<<"CHOOSE_WORD"<<std::endl;
        QVector<QString> ret = _serverMessageParser->fromChooseWordMessage(message);
        chooseWord(ret[0], thread);
        return;
    }
    case ServerMessageType::GET_ROOMS: {
        std::cout<<"GET_ROOMS"<<std::endl;
        QString rooms = getRooms();
        QJsonObject return_message = _serverMessageParser->toGetRoomsMessage(rooms);
        thread->send(return_message);
        return;
    }
    case ServerMessageType::CANVAS_MESSAGE: {
        broadcastCanvas(message, thread);
        return;
    }
    case ServerMessageType::ERROR: {
        std::cout<<"ERROR"<<std::endl;
        std::cerr << "Message type is not valid" << std::endl;
        return;
    }
    }
}

Room* Server::getRoomFromThread(Thread* thread) {
    if (thread->getRoomName() == "") {
        return nullptr;
    }
    QString room_name = thread->getRoomName();
    return _rooms.value(room_name);
}

void Server::broadcastMessage(const QJsonObject& message, Thread* thread) {
    Room* room = getRoomFromThread(thread);
    if (room == nullptr) {
        std::cerr << "This client is not in any room";
        return;
    }
    room->broadcastMessage(message, thread);
}

void Server::createRoom(const QString& username, const QString& room_name, int duration) {
    Room* room = new Room(username, room_name, duration);
    _rooms.insert(room_name, room);
    std::cout << "Room created" << std::endl;
}

void Server::joinRoom(const QString& username, const QString& room_name, Thread* thread) {
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

void Server::leaveRoom(Thread* thread) {
  Room *room = getRoomFromThread(thread);

  if (room == nullptr) {
      // izlazi iz igre
      std::cout << "Izlazenje iz igre" << std::endl;
      thread->disconnect();
      return;
  }
  room->leaveRoom(thread);
  thread->setRoomName("");
}

void Server::chooseWord(const QString& word, Thread* thread) {
    Room* room = getRoomFromThread(thread);
    if (room == nullptr) {
        std::cerr << "This client is not in any room";
        return;
    }
    room->setWordAndStartGame(word);
    std::cout << "Room word: " << room->getWord().toStdString() << std::endl;
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

void Server::broadcastCanvas(const QJsonObject& message, Thread* thread) {
    Room* room = getRoomFromThread(thread);
    if (room == nullptr) {
        std::cerr << "This client is not in any room";
        return;
    }
    room->broadcastCanvas(message, thread);
}

Server::~Server() {
    qDeleteAll(_clients.begin(), _clients.end());
    _clients.clear();
    qDeleteAll(_rooms);
    _rooms.clear();
    delete _serverMessageParser;
}
