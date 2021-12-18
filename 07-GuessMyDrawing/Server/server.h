#ifndef SERVER_H
#define SERVER_H

#include "QString"
#include "room.h"
#include <map>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include "thread.h"

class Server : public QTcpServer {
 Q_OBJECT
 public:
    explicit Server(QObject *parent = 0);
    void startServer();

    void joinRoom(QString room_name);
    Room* createRoom(QString room_name);
    void sendMessage(Thread* thread, QJsonObject message);
    void parseMessage(QJsonObject message);
 signals:

 public slots:
    void broadcast(QJsonObject message);
 protected:
    void incomingConnection(qintptr socketDescriptor);
 private:
    std::map<QString, Room*> _rooms;
    QVector<Thread*> _clients;
};

#endif // SERVER_H

