#include "client.h"
#include "MessageType.h"
#include <iostream>

#include <iomanip>

Client::Client(QString name, QObject *parent):
  QObject(parent),
  mName(name),
  imHost(false),
  messageSocket(new QTcpSocket(this))
{
  // connect and disconnect
  connect(messageSocket, &QTcpSocket::connected, this, &Client::connectedMessage);
  connect(messageSocket, &QTcpSocket::disconnected, this, &Client::disconnectedMessage);


  // slot to take care of Reading messsages
  connect(messageSocket, &QTcpSocket::readyRead, this, &Client::MessageReadyRead);

  connect(messageSocket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));
}

void Client::connectToServer(const QHostAddress &adress, quint16 port)
{
  messageSocket->connectToHost(adress, port);
  this->adress = adress;
  this->port = port;
}

void Client::disconnectFromHost()
{
  messageSocket->disconnectFromHost();
}

void Client::send(const QString &text)
{
  if (text.isEmpty())
      return;
  QJsonObject message;
  message[MessageType::TYPE] = QString(MessageType::TEXT_MESSAGE);
  message[MessageType::CONTENT] = QString(text);
  message[MessageType::MESSAGE_SENDER] = QString(mName);
  sendMessage(message);
}

void Client::joinRoom(QString username, QString roomName)
{
  QJsonObject message;
  message[MessageType::TYPE] = QString(MessageType::JOIN_ROOM);
  message[MessageType::ROOM_NAME] = roomName;
  message[MessageType::USERNAME] = username;
  this->mName = username;
  sendMessage(message);
}

void Client::createRoom(QString username, QString room_name, int duration)
{
  QJsonObject message;
  message[MessageType::TYPE] = QString(MessageType::CREATE_ROOM);
  message[MessageType::USERNAME] = username;
  message[MessageType::ROOM_NAME] = room_name;
  message[MessageType::DURATION] = QString::number(duration);
  this->mName = username;
  sendMessage(message);
}

void Client::leaveRoom()
{
  QJsonObject message;
  message[MessageType::TYPE] = QString(MessageType::LEAVE_ROOM);
  sendMessage(message);
  this->imHost = false;
}


void Client::chooseWord(QString word)
{
  std::cout << "Choosing word " << word.toStdString() << " " << MessageType::CHOOSE_WORD.toStdString()  << std::endl;
  QJsonObject message;
  message[MessageType::TYPE] = QString(MessageType::CHOOSE_WORD);
  message[MessageType::CONTENT] = word;
  sendMessage(message);
}

void Client::getRooms()
{
  QJsonObject message;
  message[MessageType::TYPE] = QString(MessageType::GET_ROOMS);
  sendMessage(message);
}

void Client::sendCanvas(QByteArray &canvas)
{
  QJsonObject message;
  message[MessageType::TYPE] = MessageType::CANVAS_MESSAGE;
  message[MessageType::CONTENT] = QString(canvas.toBase64());
  sendMessage(message);
}

void Client::reconnect()
{
  // TODO chceck
  connectToServer(this->adress, this->port);
}


void Client::MessageReadyRead()
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

void Client::connectedMessage()
{
   std::cout << "message socket connected" << std::endl;
}

void Client::disconnectedMessage()
{
  std::cout << "message socket disconnected" << std::endl;
}

void Client::error(QAbstractSocket::SocketError socketError)
{
  QString *s = new QString("Something went wrong with cnnnection. Please try again.");
  emit errorConnecting(s);
}

void Client::jsonReceived(const QJsonObject &doc)
{
  const QJsonValue typeVal = doc.value(MessageType::TYPE);

  if (typeVal.toString().compare(MessageType::CANVAS_MESSAGE)!=0)
    std::cout << "Primljen tip: " << typeVal.toString().toStdString() << std::endl;

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
    std::cout << room.toString().toStdString() << std::endl;
    bool b = true;
    if (!fieldIsValid(room) || room.toString().isEmpty()){
        b=false;
        // neuspelo prikljucivanje sobi ako je null ili prazno
      }
    std::cout << b << std::endl;
    imHost = false;
    emit joinedRoom(b); // TODO proveriti prenos argumenata
    }
  else if(typeVal.toString().compare(MessageType::GET_ROOMS) == 0){
    const QJsonValue rooms = doc.value(MessageType::CONTENT);
    if (!fieldIsValid(rooms)){
        return; // nema liste soba
      }

    // TODO check copy and memory
    QVector<QString> *room_list = new QVector<QString>;
    auto room_split = rooms.toString().split(",");
    for(QString& r : room_split){
        room_list->push_back(r);
      }
    emit roomList(room_list);
    }
  else if(typeVal.toString().compare(MessageType::NEW_HOST) == 0){
//    imHost = true;
      shouldBecomeHost = true;
    std::cout << "IM NEW HOST" << std::endl;
    emit youAreNewHost();
    }
  else if(typeVal.toString().compare(MessageType::GAME_OVER) == 0){
    std::cout << "I am not host anymore" << std::endl;
    imHost = false; // if was host i won't be anymore, and next host will get message later
    emit gameOver();
    }
  else if(typeVal.toString().compare(MessageType::START) == 0){
      if (shouldBecomeHost){
        imHost = true;
        shouldBecomeHost = false;
        }
    emit startGame();
    }
  // CANVAS
  else if(typeVal.toString().compare(MessageType::CANVAS_MESSAGE)==0){
      const QJsonValue canvas_content = doc.value(MessageType::CONTENT);
      if (!fieldIsValid(canvas_content)){
        return;
        }

      QByteArray b = QByteArray::fromBase64(canvas_content.toString().toUtf8());
      emit canvasReceived(b);
    }
}

// valid value in QJSonValue isn't null and it's type String
bool Client::fieldIsValid(QJsonValue value)
{
  return !value.isNull() || value.isString();
}

void Client::sendMessage(QJsonObject message)
{
  auto msg = QJsonDocument(message).toJson(QJsonDocument::Compact);
  messageSocket->write(msg);
  messageSocket->flush();
}
