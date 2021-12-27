#ifndef MESSAGEPARSER_H
#define MESSAGEPARSER_H

#include<QJsonObject>
#include "../MessageType.h"


class MessageParser
{
public:
    MessageParser();

    QJsonObject startMessage();
    QJsonObject userJoinedMessage(QString &username);
    QJsonObject joinRoomMessage(QString &roomName);
    QJsonObject gameOverMessage();
    QJsonObject newHostMessage();
    QJsonObject userLeftMessage(QString username);


};

#endif // MESSAGEPARSER_H
