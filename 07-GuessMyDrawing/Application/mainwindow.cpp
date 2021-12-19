#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "existingrooms.h"
#include "settings.h"
#include <QHostAddress>

MainWindow::MainWindow(QString username, QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  chatClient = new Client(username, this);
  attemptConnection(1234);

  ui->setupUi(this);
  connect(ui->pbJoinGame, &QPushButton::clicked, this, &MainWindow::onJoinGameClicked);
  connect(ui->pbCreateNewGame, &QPushButton::clicked, this, &MainWindow::onCreateNewGameClicked);
  //  connect(game, &Game::MySignalToIndicateThatTheWindowIsClosing, this, &MainWindow::gameWindowClosed);
  game = new Game(chatClient, this);

}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::attemptConnection(qint16 port)
{
  // Update
  // Possibly static adres and port from server?
  chatClient->connectToServer(QHostAddress::LocalHost, port);
}

void MainWindow::onJoinGameClicked()
{
    existingRooms = new ExistingRooms(game, chatClient, this);
    existingRooms->setModal(true);
    //opening the second window
    existingRooms->exec();

}

void MainWindow::onCreateNewGameClicked() {
 //   hide();
    settings = new Settings(game, chatClient, this);
    settings->setModal(true);
 //   settings->show();
    settings->exec();

}



void MainWindow::gameWindowClosed()
{
    std::cout  << "mainnn" << std::endl;
}
