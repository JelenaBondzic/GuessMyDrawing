#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , chatClient(new Client("milica", this)),
  mChatModel(new QStandardItemModel(this))
{
  ui->setupUi(this);

  mChatModel->insertColumn(0);
  ui->listView->setModel(mChatModel);

  connect(chatClient, &Client::connected, this, &MainWindow::connectToServer);
  connect(chatClient, &Client::messageReacieved, this, &MainWindow::messageRecieved);
  connect(chatClient, &Client::disconnected, this, &MainWindow::disconectedFromServer);
  connect(chatClient, &Client::error, this, &MainWindow::error);
  connect(chatClient, &Client::userJoined, this, &MainWindow::userJoined);
  connect(chatClient, &Client::userLeft, this, &MainWindow::userLeft);

  connect(ui->btnSend, &QPushButton::clicked, this, &MainWindow::sendMessage);
  connect(ui->leInput, &QLineEdit::returnPressed, this, &MainWindow::sendMessage); // send on enter

}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::attemptConnection()
{
  // Update
  // Possibly static adres and port from server?
  chatClient->connectToServer(QHostAddress::LocalHost, 1234);
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

