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
  connect(canvasSocket, &QTcpSocket::readyRead, this, &Client::onCanvasReadyRead);

  connect(messageSocket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));
  connect(canvasSocket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));
}

void Client::connectToServer(const QHostAddress &adress, quint16 port)
{
  messageSocket->connectToHost(adress, port);
//  canvasSocket->connectToHost(adress, port);
  this->adress = adress;
  this->port = port;
}

void Client::disconnectFromHost()
{
  messageSocket->disconnectFromHost();
  canvasSocket->disconnectFromHost();
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

  auto msg = QJsonDocument(message).toJson(QJsonDocument::Compact);

  messageSocket->write(msg);
  messageSocket->flush();
}



void Client::joinRoom(QString username, QString roomName)
{
  QJsonObject message;
  message[MessageType::TYPE] = QString(MessageType::JOIN_ROOM);
  message[MessageType::ROOM_NAME] = roomName;
  message[MessageType::USERNAME] = username;
  this->mName = username;
  messageSocket->flush();
  messageSocket->write(QJsonDocument(message).toJson(QJsonDocument::Compact));
  messageSocket->flush();
}

void Client::createRoom(QString username, QString room_name, int duration)
{
  QJsonObject message;
  message[MessageType::TYPE] = QString(MessageType::CREATE_ROOM);
  message[MessageType::USERNAME] = username;
  message[MessageType::ROOM_NAME] = room_name;
  message[MessageType::DURATION] = QString::number(duration);
  this->mName = username;
  messageSocket->write(QJsonDocument(message).toJson(QJsonDocument::Compact));
  messageSocket->flush();
}

void Client::leaveRoom()
{
  QJsonObject message;
  message[MessageType::TYPE] = QString(MessageType::LEAVE_ROOM);
  messageSocket->write(QJsonDocument(message).toJson(QJsonDocument::Compact));
  messageSocket->flush();

//  emit youLeftRoom();
}


void Client::chooseWord(QString word)
{
  QJsonObject message;
  message[MessageType::TYPE] = QString(MessageType::CHOOSE_WORD);
  message[MessageType::CONTENT] = word;
  messageSocket->write(QJsonDocument(message).toJson(QJsonDocument::Compact));
  messageSocket->flush();
}

void Client::getRooms()
{
  QJsonObject message;
  message[MessageType::TYPE] = QString(MessageType::GET_ROOMS);
  messageSocket->write(QJsonDocument(message).toJson(QJsonDocument::Compact));
  messageSocket->flush();
}

void Client::sendCanvas(QByteArray &canvas)
{
  canvasSocket->write(canvas);
  messageSocket->flush();
}

void Client::reconnect()
{
  // disconnect
  connectToServer(this->adress, this->port);
}



void Client::onMessageReadyRead()
{
  QByteArray data;
  data = messageSocket->readAll();

  QList<QByteArray> dataVec = data.split('}'); // split by json end

  for (auto &jsonData: dataVec) {
      // if we don't have valid json beggining there's no point of going further
    if(jsonData.isEmpty() || jsonData[0] != '{')
      continue;
    jsonData.append('}'); // add } which we removed while splitting

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
      std::cerr << "PARSING JSON ERR : " << parseError.errorString().toStdString() << std::endl;
      }
    }
}


//const QString &Client::name() const
//{
//    return mName;
//}
void Client::onCanvasReadyRead()
{
  // canvas
  QByteArray data = canvasSocket->readAll();
  emit canvasReceived(data);
}

void Client::connectedCanvas()
{
  QJsonObject message;
  message[MessageType::TYPE] = QString(MessageType::CANVAS_SOCKET);
  message[MessageType::ID] = this->idForCanvas;
  canvasSocket->write(QJsonDocument(message).toJson(QJsonDocument::Compact));
  messageSocket->flush();
}

void Client::disconnectedCanvas()
{
  std::cout << "canvas disconnected" << std::endl;

//  send("Canvas disonnected");
}

void Client::connectedMessage()
{
  std::cout << "connected to server" << std::endl;
   QJsonObject message;
   message[MessageType::TYPE] = QString(MessageType::MESSAGE_SOCKET);
   messageSocket->write(QJsonDocument(message).toJson(QJsonDocument::Compact));
   messageSocket->flush();
}

void Client::disconnectedMessage()
{
  std::cout << "message disconnected" << std::endl;
}

void Client::error(QAbstractSocket::SocketError socketError)
{
  std::cout << "Error ocurred " << socketError << std::endl;

  QString *s = new QString("Something went wrong with cnnnection. Try again");
  emit errorConnecting(s);
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
    bool b = true;
    if (!fieldIsValid(room)){
        b=false;
        // neuspelo prikljucivanje sobi ako je null ili prazno
      }
    std::cout << "Joining room " << b << std::endl;
    emit joinedRoom(b); // TODO proveriti prenos argumenata
    }
  else if(typeVal.toString().compare(MessageType::GET_ROOMS) == 0){
    const QJsonValue rooms = doc.value(MessageType::CONTENT);
    if (!fieldIsValid(rooms)){
        return; // neuspelo prikljucivanje sobi ako je null ili prazno
      }

    // TODO check copy and memory
    QVector<QString> *room_list = new QVector<QString>;
    auto room_split = rooms.toString().split(",");
    for(QString& r : room_split){
        room_list->push_back(r);
        std::cout  << r.toStdString() << std::endl;
      }

    emit roomList(room_list);
    }
  else if(typeVal.toString().compare(MessageType::NEW_HOST) == 0){
//    const QJsonValue rooms = doc.value(MessageType::CONTENT);
    imHost = true;
    std::cout << "IM NEW HOST" << std::endl;
    emit youAreNewHost();
    }
  else if(typeVal.toString().compare(MessageType::GAME_OVER) == 0){
    imHost = false; // if was host i won't be anymore, and next host will get message later
    emit gameOver();
    }
  else if(typeVal.toString().compare(MessageType::START) == 0){
    emit startGame();
    }
  // message saying canvas can connect
  else if(typeVal.toString().compare(MessageType::CANVAS_SOCKET)){
    idForCanvas = doc.value(MessageType::ID);
  //  canvasSocket->connectToHost(adress, port);
    }
}

// valid value in QJSonValue isn't null and it's type String
bool Client::fieldIsValid(QJsonValue value)
{
  return !value.isNull() || value.isString();
}
