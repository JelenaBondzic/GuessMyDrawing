#include "room.h"


#include<unordered_map>


void Room::setDuration(int newDuration)
{
    duration = newDuration;
}

bool Room::usernameIsValid(QString username)
{
    for(qsizetype i = 0; i<players.size(); ++i){
        if(players.at(i)->name() == username)
            return false;
    }

    return true;
}

void Room::setChosenWord(const QString &newChosenWord)
{
    chosenWord = newChosenWord;
}

Room::Room(QString name, Client* firstHost): name(name), firstHost(firstHost)
{
    start();
}


void Room::start()
{

    //wait until numOfPlayers >= 2
    while(numOfPlayers > 2){
        //create new round + start next round Round.start(timer.duration)
        round = new Round(this->duration, chosenWord);
        //choose new host for next round
        host = round->getHost();
        //setHost

        //round.start(timer.duration) returns winner_id

    }
}
