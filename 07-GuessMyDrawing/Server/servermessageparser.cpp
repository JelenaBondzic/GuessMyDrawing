#include "servermessageparser.h"

ServerMessageParser::ServerMessageParser()
{

}

QJsonObject ServerMessageParser::startMessage()
{
    QJsonObject message;
    message[MessageType::TYPE] = MessageType::START;

    return message;
}

QJsonObject ServerMessageParser::userJoinedMessage(QString &username)
{
    QJsonObject message;
    message[MessageType::TYPE] = MessageType::USER_JOINED;
    message[MessageType::USERNAME] = username;

    return message;
}

QJsonObject ServerMessageParser::joinRoomMessage(QString &roomName)
{
    QJsonObject message;
    message[MessageType::TYPE] = MessageType::JOIN_ROOM;
    message[MessageType::ROOM_NAME] =roomName;

    return message;
}

QJsonObject ServerMessageParser::gameOverMessage()
{
    QJsonObject message;
    message[MessageType::TYPE] = MessageType::GAME_OVER;

    return message;
}

QJsonObject ServerMessageParser::newHostMessage()
{
    QJsonObject message;
    message[MessageType::TYPE] = MessageType::NEW_HOST;

    return message;
}

QJsonObject ServerMessageParser::userLeftMessage(QString username)
{
    QJsonObject message;
    message[MessageType::TYPE] = MessageType::USER_LEFT;
    message[MessageType::USERNAME] = username;

    return message;
}
