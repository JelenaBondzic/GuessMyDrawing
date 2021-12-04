#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "existingrooms.h"
#include "settings.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , chatClient(new Client("milica", this)),
  mChatModel(new QStandardItemModel(this))
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

void MainWindow::attemptConnection()
{
  // Update
  // Possibly static adres and port from server?
  chatClient->connectToServer(QHostAddress::LocalHost, 12345);
}

void MainWindow::connectToServer()
{
  // nothing
  // asking for username generally
}

void MainWindow::messageRecieved(const QString &sender, const QString &text)
{
  std::cout << sender.toStdString() << " " << text.toStdString() << std::endl;
  int newRow = mChatModel->rowCount();
  mChatModel->insertRow(newRow);
  mChatModel->setData(mChatModel->index(newRow,0), sender + " : " + text);
  mChatModel->setData(mChatModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
  ui->listView->scrollToBottom();
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

void MainWindow::disconectedFromServer()
{
  // if client lose connection to server
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

void MainWindow::error(QAbstractSocket::SocketError socketError)
{
  std::cout << "ERROR :( " << std::endl;
}

