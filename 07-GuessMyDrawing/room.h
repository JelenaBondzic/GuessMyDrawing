#ifndef ROOM_H
#define ROOM_H

#include<iostream>
#include<string>
#include<map>
#include<unordered_map>
#include "round.h"
//#include "client.h"

class Timer{
public :
    void end();
};

class Room
{
private:
    std::string name;
    //std::map<std::string, Client*> players;
    std::unordered_map<std::string, Client*> players;
    std::string host;
    Timer* timer;
    Round* round;
    int numOfPlayers = players.size();

public:
    //server call constructor for room and sends in constructor name of host
    Room(std::string name, std::string host);


    const std::string &getName() const;
    const std::unordered_map<std::string, Client *> &getPlayers() const;
    void setPlayers(const std::unordered_map<std::string, Client *> &newPlayers);
    const std::string &getHost() const;
    void setHost(const std::string &newHost);
    Timer *getTimer() const;
    void setTimer(Timer *newTimer);
    Round *getRound() const;
    void setRound(Round *newRound);

    void start();
};

#endif // ROOM_H
