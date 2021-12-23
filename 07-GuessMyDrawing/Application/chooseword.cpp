#include "chooseword.h"
#include "ui_chooseword.h"

#include<iostream>

ChooseWord::ChooseWord(Game* game,Client* client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseWord),
    client(client),
    game(game)
{
    ui->setupUi(this);
    this->hide();

    connect(ui->pbFirstWord, &QPushButton::clicked, this, &ChooseWord::pbFirstWord_clicked);
    connect(ui->pbSecondWord, &QPushButton::clicked, this, &ChooseWord::pbSecondWord_clicked);
    connect(ui->pbThirdWord, &QPushButton::clicked, this, &ChooseWord::pbThirdWord_clicked);
    connect(ui->myWord, &QPushButton::clicked, this, &ChooseWord::myWord_clicked);
    connect(ui->pbCreateGame, &QPushButton::clicked, this, &ChooseWord::pbCreateGame_clicked);
    connect(game, &Game::IAmHost, this, &ChooseWord::show_Window);
    connect(client, &Client::errorConnecting, this, &ChooseWord::showPopUp);


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
    //client->createRoom(username, roomName, duration);
    game->show();
}

void ChooseWord::show_Window()
{
    ui->lnInsertWord->setText("");
    ui->pbCreateGame->setDisabled(true);
    this->show();
}



void ChooseWord::showPopUp()
{
    hide();

}
