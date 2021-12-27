#include "messageparser.h"

MessageParser::MessageParser()
{

}


QJsonObject MessageParser::startMessage()
{
    QJsonObject message;
    message[MessageType::TYPE] = MessageType::START;

    return message;
}

QJsonObject MessageParser::userJoinedMessage(QString &username)
{
    QJsonObject message;
    message[MessageType::TYPE] = MessageType::USER_JOINED;
    message[MessageType::USERNAME] = username;

    return message;
}

QJsonObject MessageParser::joinRoomMessage(QString &roomName)
{
    QJsonObject message;
    message[MessageType::TYPE] = MessageType::JOIN_ROOM;
    message[MessageType::ROOM_NAME] =roomName;

    return message;
}

QJsonObject MessageParser::gameOverMessage()
{
    QJsonObject message;
    message[MessageType::TYPE] = MessageType::GAME_OVER;

    return message;
}

QJsonObject MessageParser::newHostMessage()
{
    QJsonObject message;
    message[MessageType::TYPE] = MessageType::NEW_HOST;

    return message;
}

QJsonObject MessageParser::userLeftMessage(QString username)
{
    QJsonObject message;
    message[MessageType::TYPE] = MessageType::USER_LEFT;
    message[MessageType::USERNAME] = username;

    return message;
}
