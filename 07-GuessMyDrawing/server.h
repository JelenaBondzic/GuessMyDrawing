#ifndef SERVER_H
#define SERVER_H

#include "QString"
#include "room.h"
#include <map>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include "thread.h"

class Server : public QTcpServer {
 Q_OBJECT
 public:
    explicit Server(QObject *parent = 0);
    void startServer();
    void broadcast(QString/*Message*/ message);
    void joinRoom(QString room_name);
    Room* createRoom(QString room_name);

 signals:

 public slots:

 protected:
    void incomingConnection(qintptr socketDescriptor);
 private:
    std::map<QString, Room*> _rooms;
};

#endif // SERVER_H
