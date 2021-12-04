#include "client.h"
#include <iostream>


Client::Client(QString name, QObject *parent):
  QObject(parent),
  mName(name),
  messageIn(new QTcpSocket(this)),
  messageOut(new QTcpSocket(this))
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
  messageIn->connectToHost(adress, 12345);
//  messageOut->connectToHost(adress, 23456);
  // TODO obrada greske?
  if (messageIn->state() != QAbstractSocket::ConnectedState /*|| messageOut->state() != QAbstractSocket::ConnectedState*/)
    std::cout << "NOT CONNECTED" << std::endl;
}

void Client::disconnectFromHost()
{
  messageIn->disconnectFromHost();
//  messageOut->disconnectFromHost();
  std::cout << "disconected" <<std::endl;
  // TODO obrada greske?
}

void Client::send(const QString &text)
{
  std::cout << "SENDING " << std::endl;
  if (text.isEmpty())
      return;

//  QDataStream clientStream(messageIn);
//  clientStream.setVersion(QDataStream::Qt_DefaultCompiledVersion);

  QJsonObject message;
  message["type"] = QString("message");
  message["text"] = QString(text);
  message["sender"] = QString(mName);

//  clientStream << QJsonDocument(message).toJson(QJsonDocument::Compact);

  messageIn->write(QJsonDocument(message).toJson(QJsonDocument::Compact));
  //  messageOut->write(QJsonDocument(message).toJson(QJsonDocument::Compact));
}

void Client::joinRoom(Room *newRoom)
{
  this->room = newRoom;
}

void Client::onReadyRead()
{
  std::cout << "READING " << std::endl;

  QByteArray jsonData;
//  QDataStream socketStream(messageIn);
//  socketStream.setVersion(QDataStream::Qt_DefaultCompiledVersion);

  jsonData = messageIn->readAll();
  std::cout << "Received: " <<jsonData.toStdString() << std::endl;

  QJsonParseError parseError;
  const QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parseError);
  if(parseError.error == QJsonParseError::NoError){
      // data is valid json
      if (doc.isObject()) // if it's json object we can recieve it
        jsonRecieved(doc.object());
      else
        std::cout << "DOC IS NOT OBJECT" << std::endl;
    }
  else{
    std::cout << "PARSING JSON ERR " << parseError.errorString().toStdString() << std::endl;
  }
  /*
  for(;;){
      // we start transaction so we can go back to previous state if error occurs
      socketStream.startTransaction();

       if(messageIn->state() == QAbstractSocket::ConnectedState)
           std::cout << "CONECTED" << std::endl;
       else
         std::cout << "NOT CONECTED" << std::endl;


      if(socketStream.status() == QDataStream::Ok)
          std::cout << "OK" << std::endl;
      else
          std::cout << "NOT OK " << std::endl;

//      socketStream >> jsonData;

//      char* s = new char;
//      std::cout << socketStream.readRawData(s, 200) << std::endl;
//      std::cout << s << std::endl;

      jsonData = messageIn->readAll();
      std::cout << jsonData.toStdString() << std::endl;

      break;
//      std::cout << jsonData.toStdString() << std::endl;

      if(socketStream.status() == QDataStream::Ok)
          std::cout << "OK" << std::endl;
      else
          std::cout << "NOT OK " << std::endl;

      if(socketStream.commitTransaction()){
          // successfully read data, checking valid format
          QJsonParseError parseError;
          const QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parseError);
          if(parseError.error == QJsonParseError::NoError){
              // data is valid json
              if (doc.isObject()) // if it's json object we can recieve it
                jsonRecieved(doc.object());
            }
          // after this loop will try to read more data
        }
      else {
          std::cout << "Failed" << std::endl;
          //read failed, socket goes to state it was before transaction started
          break;
        }

    }
    */
}

void Client::jsonRecieved(const QJsonObject &doc)
{
  const QJsonValue typeVal = doc.value(QLatin1String("type"));

  if (typeVal.isNull() || !typeVal.isString()){
      return; // empty or unknown message recieved
    }

  if(typeVal.toString().compare(QLatin1String("message"), Qt::CaseInsensitive) == 0){
      const QJsonValue text = doc.value(QLatin1String("text"));
      if (text.isNull() || !text.isString()){
          return; // no text
        }
      const QJsonValue sender = doc.value(QLatin1String("sender"));
      if (sender.isNull() || !sender.isString()){
          return; // sender missing
        }
      emit messageReacieved(sender.toString(), text.toString());
    }
  else if(typeVal.toString().compare(QLatin1String("newuser"), Qt::CaseInsensitive) == 0){
    const QJsonValue username = doc.value(QLatin1String("username"));
    if (username.isNull() || !username.isString()){
        return; // username missing or invalid
      }
    emit userJoined(username.toString());
    }
  else if(typeVal.toString().compare(QLatin1String("userdisconnected"), Qt::CaseInsensitive) == 0){
    const QJsonValue username = doc.value(QLatin1String("username"));
    if (username.isNull() || !username.isString()){
        return; // username missing or invalid
      }
    emit userLeft(username.toString());
    }

}
