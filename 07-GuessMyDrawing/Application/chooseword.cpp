#include "chooseword.h"
#include "ui_chooseword.h"

#include<iostream>

ChooseWord::ChooseWord(Game* game, QString username, QString roomName, Client* client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseWord),
    client(client),
    username(username),
    roomName(roomName),
    game(game)
{
    ui->setupUi(this);
    connect(ui->pbFirstWord, &QPushButton::clicked, this, &ChooseWord::pbFirstWord_clicked);
    connect(ui->pbSecondWord, &QPushButton::clicked, this, &ChooseWord::pbSecondWord_clicked);
    connect(ui->pbThirdWord, &QPushButton::clicked, this, &ChooseWord::pbThirdWord_clicked);
    connect(ui->myWord, &QPushButton::clicked, this, &ChooseWord::myWord_clicked);
    connect(ui->pbCreateGame, &QPushButton::clicked, this, &ChooseWord::pbCreateGame_clicked);
    connect(game, &Game::IAmHost, this, &ChooseWord::show_Window);

    ui->pbCreateGame->setDisabled(true);

}

ChooseWord::~ChooseWord()
{
    delete ui;
}


void ChooseWord::pbFirstWord_clicked()
{
    chosenWord = ui->pbFirstWord->text();
    ui->pbCreateGame->setDisabled(false);
}


void ChooseWord::pbSecondWord_clicked()
{
    chosenWord = ui->pbSecondWord->text();

    ui->pbCreateGame->setDisabled(false);

}


void ChooseWord::pbThirdWord_clicked()
{
    chosenWord = ui->pbThirdWord->text();

    ui->pbCreateGame->setDisabled(false);

}


void ChooseWord::myWord_clicked()
{
    chosenWord = ui->lnInsertWord->text();
    ui->pbCreateGame->setDisabled(false);

}


void ChooseWord::pbCreateGame_clicked()
{
    this->hide();
    client->chooseWord(chosenWord);
    //std::cout << chosenWord.toStdString() << std::endl;
    //client->createRoom(username, roomName, duration);
   // game = new Game(client, this);
    game->show();
}

void ChooseWord::show_Window()
{
    //std::cout << "Stiglo u window" << std::endl;
    this->show();
}
