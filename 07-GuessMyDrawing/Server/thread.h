#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QTcpSocket>

class Thread : public QObject {
 Q_OBJECT
 public:
    explicit Thread(qintptr ID, QObject *parent = 0);

    void send(QJsonObject message); //napravi ovo
signals:
    void error(QTcpSocket::SocketError socket_error);
    void messageReceived(QByteArray message);
public slots:
    void readyRead();
    void disconnected();
    void receiveMessage(QByteArray message);

 private:
    QTcpSocket* socket;
    qintptr socketDescriptor; // Socket ID from OS
};

#endif // THREAD_H
