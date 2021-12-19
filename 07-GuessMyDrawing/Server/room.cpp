#include "room.h"
#include "../Application/MessageType.h"
#include<unordered_map>


void Room::setDuration(int newDuration)
{
    duration = newDuration;
}

void Room::leaveRoom(QString player)
{
    QMap<QString, Thread*>::const_iterator i = players.find(player);
    players.erase(i);

    //broadcast others that player has left the game??
}

bool Room::usernameIsValid(QString username)
{
    if(players.contains(username))
        return false;

    return true;
}

void Room::setWordAndStartGame(const QString &newChosenWord)
{
    chosenWord = newChosenWord;
    //if there is 2 or more players, start game
    if(players.size() >= 2)
        start();
}

void Room::checkChatWord(QString word, Thread* senderUser)
{


    if(word.compare(chosenWord)){

        QJsonObject message1;
        QMapIterator<QString, Thread*> i(players);
        while (i.hasNext()) {
            i.next();
            i.value()->send(message1);
         }

        QJsonObject message;
        message[MessageType::TYPE] = MessageType::NEW_HOST;
        senderUser->send(message);


    }

}

Room::Room(QString name, QString host, int duration): name(name), host(host), duration(duration)
{

}

bool Room::joinClient(QString username, Thread* thread){
    QJsonObject message;


    //ckech if username is taken
    bool check = usernameIsValid(username);

    //if username is taken
    if(!check){
        message[MessageType::ROOM_NAME] = "";
        thread->send(message);
        return false;
    }

    else{
    //if username is not taken
    players.insert(username, thread);
    message[MessageType::TYPE] = QString(MessageType::JOIN_ROOM);
    message[MessageType::ROOM_NAME] = name;
    thread->send(message);


    //if there is 2 or more players, start game
    if(players.size() >= 2 and !gameIsStarted)
        start();

    return true;
    }
}

void Room::start()
{

    QJsonObject message;
   // message[MessageType::TYPE] = MessageType::START;

    QMapIterator<QString, Thread*> i(players);
    while (i.hasNext()) {
         i.next();
         i.value()->send(message);
    }

    gameIsStarted = true;

}

void Room::broadcast(const QJsonObject &message) {
    for (auto i=players.begin(); i!=players.end(); i++) {
        i.value()->send(message);
    }
}
