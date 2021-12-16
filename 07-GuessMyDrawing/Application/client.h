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
#include "MessageType.h"


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

  void joinRoom(QString username, QString room);
  void leaveRoom();
  void chooseWord(QString word);
  void getRooms();

private slots:
  void onMessageReadyRead();
  void onCanvasReadyRead();

  void connectedCanvas();
  void disconnectedCanvas();
  void connectedMessage();
  void disconnectedMessage();

  void error(QAbstractSocket::SocketError socketError);


signals:

  void messageReceived(const QString &sender, const QString &test);
  void userJoined(const QString &username);
  void userLeft(const QString &username);

private:
  QString mName;
  Room* room;
  int points;
  Canvas* canvas;

  QTcpSocket *messageSocket;
  QTcpSocket *canvasSocket;

  void jsonReceived(const QJsonObject &doc);
  bool fieldIsValid(QJsonValue);
};

#endif // CLIENT_H
