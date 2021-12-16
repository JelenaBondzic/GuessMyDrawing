#ifndef ROOM_H
#define ROOM_H

#include<iostream>
#include<string>
#include<map>
#include<unordered_map>
#include "round.h"
#include "client.h"
#include<QString>

class Room
{
private:
    QString name;
    QList<Client*> players;

    Round* round;
    QString chosenWord;
    int numOfPlayers = players.size();
    int duration;
    Client* host;
    Client* firstHost;

public:
    //server call constructor for room and sends in constructor name of host
    Room(QString name, Client* firstHost);

    void start();
    void setDuration(int newDuration);

    bool usernameIsValid(QString username);
    void setChosenWord(const QString &newChosenWord);
};

#endif // ROOM_H
