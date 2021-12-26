#include "messageparser.h"

MessageParser::MessageParser()
{

}

QJsonObject MessageParser::textMessage(const QString &text, const QString& name)
{
    QJsonObject message;
    if (text.isEmpty())
          return message;
    message[MessageType::TYPE] = QString(MessageType::TEXT_MESSAGE);
    message[MessageType::CONTENT] = QString(text);
    message[MessageType::MESSAGE_SENDER] = QString(name);
    return message;
}

QJsonObject MessageParser::joinRoomMessage(QString &username, QString &roomName)
{
  QJsonObject message;
  message[MessageType::TYPE] = QString(MessageType::JOIN_ROOM);
  message[MessageType::ROOM_NAME] = roomName;
  message[MessageType::USERNAME] = username;
  return message;
}

QJsonObject MessageParser::createRoomMessage(QString &username, QString &room_name, int duration)
{
  QJsonObject message;
  message[MessageType::TYPE] = QString(MessageType::CREATE_ROOM);
  message[MessageType::USERNAME] = username;
  message[MessageType::ROOM_NAME] = room_name;
  message[MessageType::DURATION] = QString::number(duration);
  return message;
}

QJsonObject MessageParser::leaveRoomMessage()
{
  QJsonObject message;
  message[MessageType::TYPE] = QString(MessageType::LEAVE_ROOM);
  return message;
}

QJsonObject MessageParser::chooseWordMessage(QString &word)
{
  QJsonObject message;
  message[MessageType::TYPE] = QString(MessageType::CHOOSE_WORD);
  message[MessageType::CONTENT] = word;
  return message;
}

QJsonObject MessageParser::getRoomsMessage()
{
  QJsonObject message;
  message[MessageType::TYPE] = QString(MessageType::GET_ROOMS);
  return message;
}

QJsonObject MessageParser::canvasMessage(QByteArray &canvas)
{
  QJsonObject message;
  message[MessageType::TYPE] = MessageType::CANVAS_MESSAGE;
  message[MessageType::CONTENT] = QString(canvas.toBase64());
  return message;
}

MessageReceivedType MessageParser::parseReceivedMessage(const QJsonObject &message, QVector<QString> &ret)
{
  const QJsonValue typeVal = message.value(MessageType::TYPE);
  if (!isFieldValid(typeVal)){
     ret.append("Missing type.");
     return MessageReceivedType::ERROR; // missing type field
  }

//  if (typeVal.toString().compare(MessageType::CANVAS_MESSAGE)!=0)
//    std::cout << "Primljen tip: " << typeVal.toString().toStdString() << std::endl;

  if(typeVal.toString().compare(MessageType::TEXT_MESSAGE) == 0){
      const QJsonValue text = message.value(MessageType::CONTENT);
      if (!isFieldValid(text)){
          ret.append("Message conntent missing!");
          return MessageReceivedType::ERROR; // no text
        }
      const QJsonValue sender = message.value(MessageType::MESSAGE_SENDER);
      if (!isFieldValid(sender)){
          ret.append("Sender missing!");
          return MessageReceivedType::ERROR; // sender missing
        }
      ret.append(sender.toString());
      ret.append(text.toString());
      return MessageReceivedType::TEXT_MESSAGE;
    }

  else if(typeVal.toString().compare(MessageType::USER_JOINED) == 0){
    const QJsonValue username = message.value(MessageType::USERNAME);
    if (!isFieldValid(username)){
        ret.append("Username is missing");
        return MessageReceivedType::ERROR; // username missing or invalid
      }
    ret.append(username.toString());
    return MessageReceivedType::USER_JOINED;
    }

  else if(typeVal.toString().compare(MessageType::USER_LEFT) == 0){
    const QJsonValue username = message.value(MessageType::USERNAME);
    if (!isFieldValid(username)){
        ret.append("Username is missing");
        return MessageReceivedType::ERROR; // username missing or invalid
      }
    ret.append(username.toString());
    return MessageReceivedType::USER_LEFT;
    }

  else if(typeVal.toString().compare(MessageType::JOIN_ROOM) == 0){
    const QJsonValue room = message.value(MessageType::ROOM_NAME);
//    std::cout << room.toString().toStdString() << std::endl;
//    bool b = true;
    if (!isFieldValid(room) || room.toString().isEmpty()){
        ret.append("Failed to join room!");
//        b=false;
        // neuspelo prikljucivanje sobi ako je null ili prazno
      }
    return MessageReceivedType::JOINED_ROOM;
//    std::cout << b << std::endl;
//    imHost = false;
//    emit joinedRoom(b); // TODO proveriti prenos argumenata
    }
  else if(typeVal.toString().compare(MessageType::GET_ROOMS) == 0){
    const QJsonValue rooms = message.value(MessageType::CONTENT);
    if (!isFieldValid(rooms)){
        ret.append("List of rooms is missing");
        return MessageReceivedType::ERROR; // nema liste soba
      }

    // TODO check copy and memory
//    QVector<QString> *room_list = new QVector<QString>;
    auto room_split = rooms.toString().split(",");
    for(QString& r : room_split){
//        room_list->push_back(r);
        ret.append(r);
      }
    return MessageReceivedType::GET_ROOMS;
    }

  else if(typeVal.toString().compare(MessageType::NEW_HOST) == 0){
//    imHost = true;
//      shouldBecomeHost = true;
//    std::cout << "IM NEW HOST" << std::endl;
      return MessageReceivedType::NEW_HOST;
    }

  else if(typeVal.toString().compare(MessageType::GAME_OVER) == 0){
//    std::cout << "I am not host anymore" << std::endl;
//    imHost = false; // if was host i won't be anymore, and next host will get message later
//    emit gameOver();
      return MessageReceivedType::GAME_OVER;
    }

  else if(typeVal.toString().compare(MessageType::START) == 0){
//      if (shouldBecomeHost){
//        imHost = true;
//        shouldBecomeHost = false;
//        }
//    emit startGame();
      return MessageReceivedType::GAME_START;
    }
  // CANVAS
  else if(typeVal.toString().compare(MessageType::CANVAS_MESSAGE)==0){
      const QJsonValue canvas_content = message.value(MessageType::CONTENT);
      if (!isFieldValid(canvas_content)){
        ret.append("Canvas is missing!");
        return MessageReceivedType::ERROR;
        }

//      QByteArray b = QByteArray::fromBase64(canvas_content.toString().toUtf8());
      ret.append(canvas_content.toString().toUtf8());
      return MessageReceivedType::CANVAS_MESSAGE;
//      emit canvasReceived(b);
    }

  ret.append("Unknow type of message!");
  return MessageReceivedType::ERROR;
}

bool MessageParser::isFieldValid(const QJsonValue &value)
{
  return !value.isUndefined() && !value.isNull() && value.isString();
}
