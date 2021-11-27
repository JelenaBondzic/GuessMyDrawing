#include "round.h"

Round::Round(int time)
{
    start(time);
}

std::string Round::start(int time)
{
    chooseWord();

    //start timer

    //show canvas
    //draw and recive/send message loop

        //if chosen word is the same like someone's message -> mark winner
        //if time is up -> make random winner

    //return winner_id
}

void Round::chooseWord()
{
    //host is choosing the word
    setWord(word);
}

const std::string &Round::getWord() const
{
    return word;
}

void Round::setWord(const std::string &newWord)
{
    word = newWord;
}
