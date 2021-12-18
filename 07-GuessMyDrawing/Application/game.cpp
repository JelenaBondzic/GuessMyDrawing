#include "game.h"
#include "ui_game.h"
#include "client.h"
#include<iostream>

Game::Game(Client* client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Game),
    client(client)
{
    ui->setupUi(this);
    connect(client, &Client::youAreNewHost, this, &Game::on_You_Are_Host);
    connect(client, &Client::startGame, this, &Game::on_Start_Game);
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

void Game::on_You_Are_Host()
{
    QWidget *parent = this->parentWidget();
    parent->show();
}

void Game::on_Game_finished(int result)
{
    this->hide();
    QWidget *parent = this->parentWidget()->parentWidget()->parentWidget();

    std::cout << parent << std::endl;
    if(parent == 0){
        parent = this->parentWidget()->parentWidget();
    }

    parent->show();
    client->leaveRoom();
    std::cout << "game finished" << std::endl;
    std::cout << parent << std::endl;

    //  emit MySignalToIndicateThatTheWindowIsClosing();
}

void Game::on_Start_Game()
{

}

