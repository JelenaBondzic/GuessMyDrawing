#ifndef ROOM_H
#define ROOM_H

#include<iostream>
#include<string>
#include<map>
#include<unordered_map>
#include<QString>
#include<QMap>
#include<QJsonObject>
#include "thread.h"

class Room
{
private:
    QString name;
    QMap<QString, Thread*> players;
    QString chosenWord;
    int numOfPlayers = players.size();
    int duration;
//    Client* host;
    QString host;
    bool gameIsStarted;


public:
    //server call constructor for room and sends in constructor name of host
    Room(QString name, QString firstHost, int duration);

    void broadcast(const QJsonObject& message);

    void start();
    void setDuration(int newDuration);
    void leaveRoom(QString player);

    bool usernameIsValid(QString username);
    void setWordAndStartGame(const QString &newChosenWord);
    void checkChatWord(QString word, Thread* senderUser);
    bool joinClient(QString username, Thread* thread);
};

#endif // ROOM_H