#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "existingrooms.h"
#include "settings.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  connect(ui->pbJoinGame, &QPushButton::clicked, this, &MainWindow::onJoinGameClicked);
  connect(ui->pbCreateNewGame, &QPushButton::clicked, this, &MainWindow::onCreateNewGameClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onJoinGameClicked()
{
    ExistingRooms rooms;
    rooms.setModal(true);
    //opening the second window
    rooms.exec();

//s      hide();
//    existingRooms = new ExistingRooms(this);
//    existingRooms->show();
}

void MainWindow::onCreateNewGameClicked()
{
    hide();
    settings = new Settings(this);
    settings->show();
}

