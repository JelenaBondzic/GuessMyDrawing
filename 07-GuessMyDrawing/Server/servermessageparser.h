#ifndef SERVERMESSAGEPARSER_H
#define SERVERMESSAGEPARSER_H

#include<QJsonObject>
#include "../MessageType.h"
#include "ServerMessageEnum.h"


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

    ServerMessageType getTypeFromMessage(const QJsonObject& message);
    QJsonObject toGetRoomsMessage(const QString& rooms);
    QVector<QString> fromJoinRoomMessage(const QJsonObject& message);
    QVector<QString> fromChooseWordMessage(const QJsonObject& message);
    QVector<QString> fromCreateRoomMessage(const QJsonObject& message);
};

#endif // SERVERMESSAGEPARSER_H
