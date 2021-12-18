#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "existingrooms.h"
#include "settings.h"

MainWindow::MainWindow(QString username, QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , mChatModel(new QStandardItemModel(this))
{
  ui->setupUi(this);
  connect(ui->pbJoinGame, &QPushButton::clicked, this, &MainWindow::onJoinGameClicked);
  connect(ui->pbCreateNewGame, &QPushButton::clicked, this, &MainWindow::onCreateNewGameClicked);
  chatClient = new Client(username, this);
  mChatModel->insertColumn(0);
  ui->listView->setModel(mChatModel);

  connect(chatClient, &Client::messageReceived, this, &MainWindow::messageRecieved);
  connect(chatClient, &Client::userJoined, this, &MainWindow::userJoined);
  connect(chatClient, &Client::userLeft, this, &MainWindow::userLeft);

  connect(ui->btnSend, &QPushButton::clicked, this, &MainWindow::sendMessage);
  connect(ui->leInput, &QLineEdit::returnPressed, this, &MainWindow::sendMessage); // send on enter

//  connect(game, &Game::MySignalToIndicateThatTheWindowIsClosing, this, &MainWindow::gameWindowClosed);

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

void MainWindow::sendMessage()
{
  chatClient->send(ui->leInput->text());

  int newRow = mChatModel->rowCount();
  mChatModel->insertRow(newRow);
  mChatModel->setData(mChatModel->index(newRow,0), ui->leInput->text());
  mChatModel->setData(mChatModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
  ui->listView->scrollToBottom();
  ui->leInput->setText("");
}


void MainWindow::onJoinGameClicked()
{
    existingRooms = new ExistingRooms(chatClient, this);
    existingRooms->setModal(true);
    //opening the second window
    existingRooms->exec();

}

void MainWindow::messageRecieved(const QString &sender, const QString &text)
{
//  std::cout << sender.toStdString() << " " << text.toStdString() << std::endl;
  int newRow = mChatModel->rowCount();
  mChatModel->insertRow(newRow);
  mChatModel->setData(mChatModel->index(newRow,0), sender + " : " + text);
  mChatModel->setData(mChatModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
  ui->listView->scrollToBottom();
}

void MainWindow::onCreateNewGameClicked() {
 //   hide();
    settings = new Settings(chatClient, this);
    settings->setModal(true);
 //   settings->show();
    settings->exec();

}

void MainWindow::userJoined(const QString &username)
{
  int newRow = mChatModel->rowCount();
  mChatModel->insertRow(newRow);
  mChatModel->setData(mChatModel->index(newRow,0), username + " joined");
  mChatModel->setData(mChatModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
  ui->listView->scrollToBottom();
}

void MainWindow::userLeft(const QString &username)
{
  int newRow = mChatModel->rowCount();
  mChatModel->insertRow(newRow);
  mChatModel->setData(mChatModel->index(newRow,0), username + " left");
  mChatModel->setData(mChatModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
  ui->listView->scrollToBottom();
}

void MainWindow::gameWindowClosed()
{
    std::cout  << "mainnn" << std::endl;
}

