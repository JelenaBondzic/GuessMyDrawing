#ifndef CLIENT_H
#define CLIENT_H

#include "QString"
#include "QTcpSocket"

class Client
{
public:
  Client(QString name);

  void connectToServer(const QHostAddress &adress, quint16 port);
  void disconnectFromHost();
  void send(const QString &text);
  void recieve();

private:
  QString name;
//  Room* room;
  int points;
//  Canvas* canvas

  QTcpSocket messageIn;
  QTcpSocket messageOut;
  QTcpSocket canvasSocket;
};

#endif // CLIENT_H
