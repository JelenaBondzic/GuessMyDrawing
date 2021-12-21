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
#include <QHostAddress>
#include <QVector>
#include <QList>

#include "canvas.h"
#include "MessageType.h"

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
  void createRoom(QString username, QString room_name, int duration);
  void leaveRoom();
  void chooseWord(QString word);
  void getRooms();

  void sendCanvas(QByteArray &canvas);

  inline bool isHost() {return imHost; }

  void reconnect();

private slots:
  void MessageReadyRead();
  void CanvasReadyRead();

  void connectedCanvas();
  void disconnectedCanvas();
  void connectedMessage();
  void disconnectedMessage();
  void error(QAbstractSocket::SocketError socketError);


signals:

  void messageReceived(const QString &sender, const QString &test);
  void userJoined(const QString &username);
  void userLeft(const QString &username);
  void roomList(const QVector<QString>* rooms);
  void joinedRoom(bool &success);
  void youLeftRoom();
  void errorConnecting(QString *error);
  void youAreNewHost();

  void startGame();
  void gameOver();

  void canvasReceived(QByteArray data);

private:
  QString mName;
  int points;

  Canvas* canvas;

  bool imHost = false;

  QTcpSocket *messageSocket;
  QTcpSocket *canvasSocket;

  void jsonReceived(const QJsonObject &doc);
  bool fieldIsValid(QJsonValue);

  QHostAddress adress;
  quint16 port;

  QJsonValue idForCanvas;
};

#endif // CLIENT_H
