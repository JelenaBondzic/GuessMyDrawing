#include "game.h"
#include "ui_game.h"

Game::Game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    connect(ui->pbFirstWord, &QPushButton::clicked, this, &Game::on_pbFirstWord_clicked);
    connect(ui->pbSecondWord, &QPushButton::clicked, this, &Game::on_pbSecondWord_clicked);


}

Game::~Game()
{
    delete ui;
}

int Game::getDuration() const
{
    return duration;
}

void Game::setDuration(int newDuration)
{
    duration = newDuration;
}


void Game::on_pbFirstWord_clicked()
{
    chosenWord = ui->pbFirstWord->text();
   // room->setChosenWord(ui->pbFirstWord->text());
}


void Game::on_pbSecondWord_clicked()
{
    chosenWord = ui->pbSecondWord->text();

    //room->setChosenWord(ui->pbSecondWord->text());

}


void Game::on_pbThirdWord_clicked()
{
    chosenWord = ui->pbThirdWord->text();

    //room->setChosenWord(ui->pbSecondWord->text());

}


void Game::on_myWord_clicked()
{
    chosenWord = ui->lnInsertWord->text();
 //   room->setChosenWord(ui->lnInsertWord->text());

}


void Game::on_pbCreateGame_clicked()
{

}

