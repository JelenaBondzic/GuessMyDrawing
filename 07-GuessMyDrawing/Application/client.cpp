#include "client.h"
#include "MessageType.h"
#include <iostream>


Client::Client(QString name, QObject *parent):
  QObject(parent),
  mName(name),
  messageIn(new QTcpSocket(this))
{
  // connect and disconnect
  connect(messageIn, &QTcpSocket::connected, this, &Client::connected);
  connect(messageIn, &QTcpSocket::disconnected, this, &Client::disconnected);

  // slot to take care of Reading messsages
  connect(messageIn, &QTcpSocket::readyRead, this, &Client::onReadyRead);

  // TODO error
//   connect(messageIn, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &Client::error);
  connect(messageIn, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));
}

void Client::connectToServer(const QHostAddress &adress, quint16 port)
{
  messageIn->connectToHost(adress, port);
  // TODO obrada greske?
 }

void Client::disconnectFromHost()
{
  messageIn->disconnectFromHost();
  std::cout << "disconected" <<std::endl;
  // TODO obrada greske?
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

  messageIn->write(QJsonDocument(message).toJson(QJsonDocument::Compact));
}

void Client::joinRoom(QString username, Room *newRoom)
{
  /*
  if (!newRoom->usernameIsValid()){
      emit notValidUsername();
      return;
    }
    */
    this->room = newRoom;
}

QList<Room*> Client::getActiveRooms()
{

    return QList<Room*>();
    //return this->activeRooms;
}

void Client::onReadyRead()
{
//  std::cout << "READING " << std::endl;

  QByteArray jsonData;
  jsonData = messageIn->readAll();

  QJsonParseError parseError;
  const QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parseError);
  if(parseError.error == QJsonParseError::NoError){
      // data is valid json
      if (doc.isObject()) // if it's json object we can recieve it
        jsonRecieved(doc.object());
      else
        std::cerr << "DOC IS NOT JSON OBJECT" << std::endl;
    }
  else{
    std::cerr << "PARSING JSON ERR " << parseError.errorString().toStdString() << std::endl;
  }
}

const QString &Client::name() const
{
    return mName;
}

void Client::jsonRecieved(const QJsonObject &doc)
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
      emit messageReacieved(sender.toString(), text.toString());
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

}

// valid value in QJSonValue isn't null and it's type String
bool Client::fieldIsValid(QJsonValue value)
{
  return !value.isNull() || value.isString();
}
