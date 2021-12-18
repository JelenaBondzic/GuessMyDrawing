#include "chooseword.h"
#include "ui_chooseword.h"

ChooseWord::ChooseWord(QString username, QString roomName, int duration, Client* client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseWord),
    client(client),
    username(username),
    roomName(roomName),
    duration(duration)
{
    ui->setupUi(this);
    connect(ui->pbFirstWord, &QPushButton::clicked, this, &ChooseWord::on_pbFirstWord_clicked);
    connect(ui->pbSecondWord, &QPushButton::clicked, this, &ChooseWord::on_pbSecondWord_clicked);
    connect(ui->pbThirdWord, &QPushButton::clicked, this, &ChooseWord::on_pbThirdWord_clicked);
    connect(ui->myWord, &QPushButton::clicked, this, &ChooseWord::on_myWord_clicked);
    connect(ui->pbCreateGame, &QPushButton::clicked, this, &ChooseWord::on_pbCreateGame_clicked);



}

ChooseWord::~ChooseWord()
{
    delete ui;
}


void ChooseWord::on_pbFirstWord_clicked()
{
    chosenWord = ui->pbFirstWord->text();
   // room->setChosenWord(ui->pbFirstWord->text());
}


void ChooseWord::on_pbSecondWord_clicked()
{
    chosenWord = ui->pbSecondWord->text();

    //room->setChosenWord(ui->pbSecondWord->text());

}


void ChooseWord::on_pbThirdWord_clicked()
{
    chosenWord = ui->pbThirdWord->text();

    //room->setChosenWord(ui->pbSecondWord->text());

}


void ChooseWord::on_myWord_clicked()
{
    chosenWord = ui->lnInsertWord->text();
 //   room->setChosenWord(ui->lnInsertWord->text());

}


void ChooseWord::on_pbCreateGame_clicked()
{
    this->hide();
    client->chooseWord(chosenWord);
   // client->createRoom(username, roomName, duration);
    game = new Game(client, this);
    game->show();
}
