#include "room.h"
#include "round.h"
//#include "client.h"

#include<unordered_map>


Room::Room(std::string name, std::string host): name(name), host(host)
{
    start();
}

const std::string &Room::getName() const
{
    return name;
}


const std::unordered_map<std::string, Client *> &Room::getPlayers() const
{
    return players;
}

void Room::setPlayers(const std::unordered_map<std::string, Client *> &newPlayers)
{
    players = newPlayers;
}

const std::string &Room::getHost() const
{
    return host;
}

void Room::setHost(const std::string &newHost)
{
    host = newHost;
}

Timer *Room::getTimer() const
{
    return timer;
}

void Room::setTimer(Timer *newTimer)
{
    timer = newTimer;
}

Round *Room::getRound() const
{
    return round;
}

void Room::setRound(Round *newRound)
{
    round = newRound;
}

void Room::start()
{

    //wait until numOfPlayers >= 2
    while(numOfPlayers > 2){
        //create new round + start next round Round.start(timer.duration)

        //choose new host for next round
        //setHost

        //round.start(timer.duration) returns winner_id

    }
}
