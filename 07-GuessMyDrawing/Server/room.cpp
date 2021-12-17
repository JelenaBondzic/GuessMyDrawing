#include "room.h"
#include "../Application/MessageType.h"
#include<QJsonObject>
#include<unordered_map>


void Room::setDuration(int newDuration)
{
    duration = newDuration;
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
    QJsonObject message;
   // message[MessageType::TYPE] = MessageType::START;

    QMapIterator<QString, Thread*> i(players);
    while (i.hasNext()) {
        i.next();
        i.value()->send(message);
    }

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
    message[MessageType::TYPE] = QString(MessageType::JOIN_ROOM);
    message[MessageType::ROOM_NAME] = name;
    thread->send(message);

    //if there is 2 or more players, start game
    if(players.size() >= 2)
        start();

    return true;
    }
}

void Room::start()
{

    //wait until numOfPlayers >= 2
//    while(numOfPlayers > 2){
//        //create new round + start next round Round.start(timer.duration)
//        round = new Round(this->duration, chosenWord);
//        //choose new host for next round
//        host = round->getHost();
//        //setHost

//        //round.start(timer.duration) returns winner_id

//    }


    QJsonObject message;
    message[MessageType::TYPE] = MessageType::NEW_HOST;
    players[host]->send(message);



}
