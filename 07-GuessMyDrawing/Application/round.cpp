#include "round.h"
#include <QDebug>
#include<QString>

Round::Round(int duration, QString chosenWord): duration(duration), word(chosenWord)
{

   timer = new QTimer();
  // connect(timer, &QTimer::timeout, this, &Round::timerSlot);


   host = start(duration);
}


Client *Round::start(int duration)
{
    //start timer
    timer->start(duration*1000);
    //show canvas
    //draw and recive/send message loop

        //if chosen word is the same like someone's message -> mark winner
        //if time is up -> make random winner

    //return winner_id
    return host;
}


void Round::timerSlot()
{
    qDebug() << "update...";
}


Client *Round::getHost() const
{
    return host;
}

void Round::setWord(const QString &newWord)
{
    word = newWord;
}
