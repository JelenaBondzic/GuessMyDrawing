#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QByteArray>

#include "canvas.h"



class Room; // forward declaration so we don't have circular dependency

class Client : public QObject
{
  Q_OBJECT
  Q_DISABLE_COPY(Client)
public:
  explicit Client(QString name, QObject *parent=nullptr);

  void connectToServer(const QHostAddress &adress, quint16 port);
  void disconnectFromHost();
  void send(const QString &text);

  void joinRoom(Room *newRoom);

private slots:
  void onReadyRead();

signals:
  void connected();
  void disconnected();
  void messageReacieved(const QString &sender, const QString &test);
  void userJoined(const QString &username);
  void userLeft(const QString &username);
  void error(QAbstractSocket::SocketError socketError);

private:
  QString mName;
  Room* room;
  int points;
  Canvas* canvas;

  QTcpSocket *messageIn;
  QTcpSocket *messageOut;
  QTcpSocket *canvasSocket;

  void jsonRecieved(const QJsonObject &doc);
};

#endif // CLIENT_H
