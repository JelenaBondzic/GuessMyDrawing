#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>

class Thread : public QObject {
 Q_OBJECT
 public:
    explicit Thread(qintptr ID, QObject *parent = 0);

    void send(QJsonObject message);
signals:
    void error(QTcpSocket::SocketError socket_error);
    void messageReceived(QJsonObject message, Thread* thread);
    void finished();
public slots:
    void readyRead();
    void disconnected();

 private:
    QTcpSocket* socketMessage;
    QTcpSocket* socketCanvas;
    qintptr socketDescriptor; // Socket ID from OS
};

#endif // THREAD_H
