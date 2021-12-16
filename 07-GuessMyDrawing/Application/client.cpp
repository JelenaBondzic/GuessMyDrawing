#include "client.h"
#include "MessageType.h"
#include <iostream>

#include <iomanip>

Client::Client(QString name, QObject *parent):
  QObject(parent),
  mName(name),
  messageSocket(new QTcpSocket(this)),
  canvasSocket(new QTcpSocket(this))
{
  // connect and disconnect
  connect(messageSocket, &QTcpSocket::connected, this, &Client::connectedMessage);
  connect(messageSocket, &QTcpSocket::disconnected, this, &Client::disconnectedMessage);

  connect(canvasSocket, &QTcpSocket::connected, this, &Client::connectedCanvas);
  connect(canvasSocket, &QTcpSocket::disconnected, this, &Client::disconnectedCanvas);

  // slot to take care of Reading messsages
  connect(messageSocket, &QTcpSocket::readyRead, this, &Client::onMessageReadyRead);
  connect(messageSocket, &QTcpSocket::readyRead, this, &Client::onCanvasReadyRead);

  connect(messageSocket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));
}

void Client::connectToServer(const QHostAddress &adress, quint16 port)
{
  messageSocket->connectToHost(adress, port);
  canvasSocket->connectToHost(adress, port);
  // TODO obrada greske?
 }

void Client::disconnectFromHost()
{
  messageSocket->disconnectFromHost();
  canvasSocket->disconnectFromHost();
  std::cout << "disconected" <<std::endl;
}

void Client::send(const QString &text)
{
//  std::cout << "SENDING " << std::endl;
  if (text.isEmpty())
      return;


  QJsonObject message;

  message[MessageType::TYPE] = QString(MessageType::TEXT_MESSAGE);
  message[MessageType::CONTENT] = QString(text);
  message[MessageType::MESSAGE_SENDER] = QString(mName);

  auto msg = QJsonDocument(message).toJson(QJsonDocument::Compact);

  messageSocket->write(msg);
}

void Client::joinRoom(QString username, QString roomName)
{
  QJsonObject message;
  message[MessageType::TYPE] = QString(MessageType::JOIN_ROOM);
  message[MessageType::USERNAME] = username;
  message[MessageType::ROOM_NAME] = roomName;
  messageSocket->write(QJsonDocument(message).toJson(QJsonDocument::Compact));
}

void Client::leaveRoom()
{
  QJsonObject message;
  message[MessageType::TYPE] = QString(MessageType::LEAVE_ROOM);
  messageSocket->write(QJsonDocument(message).toJson(QJsonDocument::Compact));
}

void Client::chooseWord(QString word)
{
  QJsonObject message;
  message[MessageType::TYPE] = QString(MessageType::CHOOSE_WORD);
  message[MessageType::CONTENT] = word;
  messageSocket->write(QJsonDocument(message).toJson(QJsonDocument::Compact));
}

void Client::getRooms()
{
  QJsonObject message;
  message[MessageType::TYPE] = QString(MessageType::GET_ROOMS);
  messageSocket->write(QJsonDocument(message).toJson(QJsonDocument::Compact));
}



void Client::onMessageReadyRead()
{
//  std::cout << "READING " << std::endl;

  QByteArray jsonData;
  jsonData = messageSocket->readAll();

  QJsonParseError parseError;
  const QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parseError);
  if(parseError.error == QJsonParseError::NoError){
      // data is valid json
      if (doc.isObject()) // if it's json object we can recieve it
        jsonReceived(doc.object());
      else
        std::cerr << "DOC IS NOT JSON OBJECT" << std::endl;
    }
  else{
    std::cerr << "PARSING JSON ERR " << parseError.errorString().toStdString() << std::endl;
    }
}

void Client::onCanvasReadyRead()
{
  // canvas
}

void Client::connectedCanvas()
{
  QJsonObject message;
  message[MessageType::TYPE] = QString(MessageType::CANVAS_SOCKET);
  messageSocket->write(QJsonDocument(message).toJson(QJsonDocument::Compact));
}

void Client::disconnectedCanvas()
{
  std::cout << "canvas disconnected" << std::endl;

//  send("Canvas disonnected");
}

void Client::connectedMessage()
{
    QJsonObject message;
   message[MessageType::TYPE] = QString(MessageType::MESSAGE_SOCKET);
   messageSocket->write(QJsonDocument(message).toJson(QJsonDocument::Compact));
}

void Client::disconnectedMessage()
{
  std::cout << "message disconnected" << std::endl;
}

void Client::error(QAbstractSocket::SocketError socketError)
{
  std::cout << "Error ocurred " << socketError << std::endl;
  emit error("Something went wrong with cnnnection. Try again");
}

void Client::jsonReceived(const QJsonObject &doc)
{
  const QJsonValue typeVal = doc.value(MessageType::TYPE);

  if (!fieldIsValid(typeVal)){
      return; // empty or unknown message recieved
    }

  if(typeVal.toString().compare(MessageType::TEXT_MESSAGE) == 0){
      const QJsonValue text = doc.value(MessageType::CONTENT);
      if (!fieldIsValid(text)){
          return; // no text
        }
      const QJsonValue sender = doc.value(MessageType::MESSAGE_SENDER);
      if (!fieldIsValid(sender)){
          return; // sender missing
        }
      emit messageReceived(sender.toString(), text.toString());
    }
  else if(typeVal.toString().compare(MessageType::USER_JOINED) == 0){
    const QJsonValue username = doc.value(MessageType::USERNAME);
    if (!fieldIsValid(username)){
        return; // username missing or invalid
      }
    emit userJoined(username.toString());
    }
  else if(typeVal.toString().compare(MessageType::USER_LEFT) == 0){
    const QJsonValue username = doc.value(MessageType::USERNAME);
    if (!fieldIsValid(username)){
        return; // username missing or invalid
      }
    emit userLeft(username.toString());
    }
  else if(typeVal.toString().compare(MessageType::JOIN_ROOM) == 0){
    const QJsonValue room = doc.value(MessageType::ROOM_NAME);
    if (!fieldIsValid(room)){
        emit joinedRoom(false);
        return; // neuspelo prikljucivanje sobi ako je null ili prazno
      }
    emit joinedRoom(true);
    }
  else if(typeVal.toString().compare(MessageType::GET_ROOMS) == 0){
    const QJsonValue rooms = doc.value(MessageType::CONTENT);
    if (!fieldIsValid(rooms)){
        return; // neuspelo prikljucivanje sobi ako je null ili prazno
      }

    // TODO check copy and memory
    QVector<QString> *room_list = new QVector<QString>;
    for(QString r : rooms.toString().split(","))
        room_list->push_back(r);

    emit roomList(room_list);
    }
}

// valid value in QJSonValue isn't null and it's type String
bool Client::fieldIsValid(QJsonValue value)
{
  return !value.isNull() || value.isString();
}
