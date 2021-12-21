#include "game.h"
#include "ui_game.h"
#include "canvas.h"
#include "client.h"
#include<iostream>


Game::Game(Client* client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Game),
    _canvas(new Canvas(this)),
    client(client),
    mChatModel(new QStandardItemModel(this)),
    timerCanvas(new QTimer(this))
{
    ui->setupUi(this);



    _canvas->resize(600, 600);
    connect(ui->pbClearDrawing, &QPushButton::clicked,
            this, &Game::onClearDrawing);
    connect(ui->cbPenColor, &QComboBox::currentTextChanged,
            this, &Game::onChangePenColor);
    connect(ui->pbIncPenWidth, &QPushButton::clicked,
            this, &Game::onIncPenWidth);
    connect(ui->pbDecPenWidth, &QPushButton::clicked,
            this, &Game::onDecPenWidth);



    // FOR CHAT
    mChatModel->insertColumn(0);
    ui->listView->setModel(mChatModel);

    connect(client, &Client::messageReceived, this, &Game::messageRecieved);
    connect(client, &Client::userJoined, this, &Game::userJoined);
    connect(client, &Client::userLeft, this, &Game::userLeft);
    connect(client, &Client::youAreNewHost, this, &Game::You_Are_Host);
    connect(client, &Client::startGame, this, &Game::Start_Game);
    connect(client, &Client::gameOver, this, &Game::Game_Over);

    connect(ui->btnSend, &QPushButton::clicked, this, &Game::sendMessage);
    connect(ui->btnSend, &QPushButton::clicked, this, &Game::sendMessage);

    connect(timerCanvas, &QTimer::timeout, this, &Game::sendCanvasMessage);


    connect(ui->leInput, &QLineEdit::returnPressed, this, &Game::sendMessage); // send on enter

    // CANVAS
    connect(client, &Client::canvasReceived, this, &Game::onLoadImage); // send on enter
    timerCanvas->start(50);
}
Game::~Game()
{
    client->leaveRoom();
    delete ui;
}


Canvas *Game::getCanvas() const
{
    return _canvas;
}

void Game::onClearDrawing()
{
    _canvas->clearImage();
}

void Game::onChangePenColor()
{
    QColor color = Qt::black;
    if (ui->cbPenColor->currentText().compare("Blue") == 0) {
        color = Qt::blue;
    }
    if (ui->cbPenColor->currentText().compare("Red") == 0) {
        color = Qt::red;
    }
    if (ui->cbPenColor->currentText().compare("Green") == 0) {
        color = Qt::green;
    }
    if (ui->cbPenColor->currentText().compare("Yellow") == 0) {
        color = Qt::yellow;
    }
    if (ui->cbPenColor->currentText().compare("Magenta") == 0) {
        color = Qt::magenta;
    }
    if (ui->cbPenColor->currentText().compare("White") == 0) {
        color = Qt::white;
    }
    _canvas->setPenColor(color);
}

void Game::onIncPenWidth()
{
    int currPenWidth = _canvas->penWidth();
    _canvas->setPenWidth(currPenWidth+1);
}

void Game::onDecPenWidth()
{
    int currPenWidth = _canvas->penWidth();
    _canvas->setPenWidth(currPenWidth-1);
}

void Game::onTakeSnap()
{
//    barr = _canvas->takeSnapshot();
    _canvas->takeSnapshot(ba);

}

void Game::onLoadImage(QByteArray b)
{
 // std::cout << "LOADING" <<std::endl;
//  std::cout << b.toStdString() << std::endl;
//    _canvas->loadFromSnapshot(*barr);
    _canvas->loadFromSnapshot(b);
}

int Game::getDuration() const
{
    return duration;
}

void Game::setDuration(int newDuration)
{
    duration = newDuration;
}

void Game::You_Are_Host()
{
//    QWidget *parent = this->parentWidget();
//    parent->show();
  //  std::cout << "Jesam host" << std::endl;
    ui->leInput->setDisabled(true);


    emit IAmHost();
}

void Game::on_Game_finished(int result)
{
    this->hide();
    QWidget *parent = this->parentWidget();

    parent->show();
    client->leaveRoom();

}

void Game::Start_Game()
{
  std::cout << "START" <<std::endl;
  if (client->isHost())
    ui->leInput->setDisabled(true);
  else
      ui->leInput->setDisabled(false);
}

void Game::Game_Over()
{

   ui->leInput->setDisabled(true);


}

// FOR CHAT
void Game::sendMessage()
{
  client->send(ui->leInput->text());

//  int newRow = mChatModel->rowCount();
//  mChatModel->insertRow(newRow);
//  mChatModel->setData(mChatModel->index(newRow,0), ui->leInput->text());
//  mChatModel->setData(mChatModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
//  ui->listView->scrollToBottom();
  ui->leInput->setText("");

//  std::cout << "SENDING "<<std::endl;
  if (client->isHost()){
   //   std::cout << "SENDING "<<std::endl;
      QByteArray b;
      _canvas->takeSnapshot(b);
//      std::cout << b.toStdString() << std::endl;
      client->sendCanvas(b);
    }
}

void Game::sendCanvasMessage() {
    if (client->isHost()){
     //   std::cout << "SENDING "<<std::endl;
        QByteArray b;
        _canvas->takeSnapshot(b);
  //      std::cout << b.toStdString() << std::endl;
        client->sendCanvas(b);
    }
}

void Game::messageRecieved(const QString &sender, const QString &text)
{
//  std::cout << sender.toStdString() << " " << text.toStdString() << std::endl;
  int newRow = mChatModel->rowCount();
  mChatModel->insertRow(newRow);
  mChatModel->setData(mChatModel->index(newRow,0), sender + " : " + text);
  mChatModel->setData(mChatModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
  ui->listView->scrollToBottom();
}

void Game::userJoined(const QString &username)
{
  int newRow = mChatModel->rowCount();
  mChatModel->insertRow(newRow);
  mChatModel->setData(mChatModel->index(newRow,0), username + " joined");
  mChatModel->setData(mChatModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
  ui->listView->scrollToBottom();
  show();
}

void Game::userLeft(const QString &username)
{
  int newRow = mChatModel->rowCount();
  mChatModel->insertRow(newRow);
  mChatModel->setData(mChatModel->index(newRow,0), username + " left");
  mChatModel->setData(mChatModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
  ui->listView->scrollToBottom();
}


