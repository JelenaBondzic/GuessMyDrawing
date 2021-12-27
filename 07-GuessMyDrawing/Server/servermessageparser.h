#ifndef SERVERMESSAGEPARSER_H
#define SERVERMESSAGEPARSER_H

#include<QJsonObject>
#include "../MessageType.h"


class ServerMessageParser
{
public:
    ServerMessageParser();

    QJsonObject startMessage();
    QJsonObject userJoinedMessage(QString &username);
    QJsonObject joinRoomMessage(QString &roomName);
    QJsonObject gameOverMessage();
    QJsonObject newHostMessage();
    QJsonObject userLeftMessage(QString username);


};

#endif // SERVERMESSAGEPARSER_H
