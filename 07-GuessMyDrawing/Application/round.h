#ifndef ROUND_H
#define ROUND_H

#include<iostream>
#include<QTimer>
#include<QObject>
#include<QString>
#include "client.h"


class Round
{

public:
    Round(int duration, QString chosenWord);

    Client *start(int duration);
    const std::string &getWord() const;
    int duration;

    void setWord(const QString &newWord);

    Client *getHost() const;

public slots:
    void timerSlot();

private:
    QString word;
    int time;
    QTimer *timer;
    Client* host;

};

#endif // ROUND_H
