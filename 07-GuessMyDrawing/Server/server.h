#ifndef SERVER_H
#define SERVER_H

#include "QString"
#include "room.h"
#include <QMap>
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
    //void broadcast(const QJsonObject& message);
 signals:

 public slots:
    void parseMessage(const QJsonObject& message, Thread* thread);
 protected:
    void incomingConnection(qintptr socketDescriptor);
 private:
    void createRoom(QString username, QString room_name, int duration);
    void joinRoom(QString username, QString room_name, Thread* thread);
    void leaveRoom(Thread* thread);
    QString getRooms();
    Room* getRoomFromThread(Thread* thread);
    Thread* getThreadFromId(quintptr id);
    QMap<QString, Room*> _rooms;
    QVector<Thread*> _clients;
};

#endif // SERVER_H

