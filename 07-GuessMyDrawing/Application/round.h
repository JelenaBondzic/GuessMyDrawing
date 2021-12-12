#ifndef ROUND_H
#define ROUND_H

#include<iostream>

class Round
{
public:
    Round(int time);

    std::string start(int time);
    void chooseWord();



    const std::string &getWord() const;
    void setWord(const std::string &newWord);

private:
    std::string word;
    int time;

};

#endif // ROUND_H
