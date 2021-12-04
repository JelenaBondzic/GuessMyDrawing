#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QTcpSocket>

class Thread : public QThread {
 Q_OBJECT
 public:
    explicit Thread(qintptr ID, QObject *parent = 0);
    void run();
signals:
    void error(QTcpSocket::SocketError socket_error);
public slots:
    void readyRead();
    void disconnected();
 private:
    QTcpSocket* socket;
    qintptr socketDescriptor; // Socket ID from OS
};

#endif // THREAD_H
