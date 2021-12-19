#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>

class Room;

class Thread : public QObject {
 Q_OBJECT
 public:
    explicit Thread(qintptr ID, QObject *parent = 0);
    quintptr getSocketDescriptor();
    void send(QJsonObject message);
    void setRoomName(QString room_name);
    QString getRoomName();
signals:
    void error(QTcpSocket::SocketError socket_error);
    void messageReceived(QJsonObject message, Thread* thread);
    void finished();
public slots:
    void onMessageReadyRead();
    void onDisconnectedMessage();
    void onCanvasReadyRead();
    void onDisconnectedCanvas();
 private:
    QString room_name;
    QTcpSocket* socketMessage;
    QTcpSocket* socketCanvas;
    qintptr socketDescriptor; // Socket ID from OS
};

#endif // THREAD_H
