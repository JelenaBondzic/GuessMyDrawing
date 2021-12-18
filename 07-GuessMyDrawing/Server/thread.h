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

    void send(QJsonObject message); //napravi ovo
signals:
    void error(QTcpSocket::SocketError socket_error);
    void messageReceived(QJsonObject message);
    void finished();
public slots:
    void readyRead();
    void disconnected();
    void receiveMessage(QByteArray message);

 private:
    QTcpSocket* socketMessage;
    QTcpSocket* socketCanvas;
    qintptr socketDescriptor; // Socket ID from OS
};

#endif // THREAD_H
