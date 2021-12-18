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
    void sendMessage(Thread *thread, QByteArray message);
    void broadcast(const QJsonObject& message);
 signals:

 public slots:
    void parseMessage(const QJsonObject& message, Thread* thread);
 protected:
    void incomingConnection(qintptr socketDescriptor);
 private:
    void createRoom(QString username, QString room_name, int duration);
    void joinRoom(QString username, QString room_name, Thread* thread);
    void leaveRoom(QString username, QString room_name);
    void getRooms();
    QMap<QString, Room*> _rooms;
    QVector<Thread*> _clients;
};

#endif // SERVER_H

