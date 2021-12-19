#include "game.h"
#include "ui_game.h"
#include "canvas.h"
#include "client.h"
#include<iostream>


Game::Game(Client* client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Game),
    client(client),
    _canvas(new Canvas(this)),
    mChatModel(new QStandardItemModel(this))

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

    connect(client, &Client::youAreNewHost, this, &Game::on_You_Are_Host);
   // connect(client, &Client::startGame, this, &Game::on_Start_Game);

    // FOR CHAT
    mChatModel->insertColumn(0);
    ui->listView->setModel(mChatModel);

    connect(client, &Client::messageReceived, this, &Game::messageRecieved);
    connect(client, &Client::userJoined, this, &Game::userJoined);
    connect(client, &Client::userLeft, this, &Game::userLeft);

    connect(ui->btnSend, &QPushButton::clicked, this, &Game::sendMessage);
    connect(ui->leInput, &QLineEdit::returnPressed, this, &Game::sendMessage); // send on enter


}
Game::~Game()
{

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

void Game::onLoadImage()
{
//    _canvas->loadFromSnapshot(*barr);
    _canvas->loadFromSnapshot(ba);
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

// FOR CHAT
void Game::sendMessage()
{
  client->send(ui->leInput->text());

  int newRow = mChatModel->rowCount();
  mChatModel->insertRow(newRow);
  mChatModel->setData(mChatModel->index(newRow,0), ui->leInput->text());
  mChatModel->setData(mChatModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
  ui->listView->scrollToBottom();
  ui->leInput->setText("");
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
}

void Game::userLeft(const QString &username)
{
  int newRow = mChatModel->rowCount();
  mChatModel->insertRow(newRow);
  mChatModel->setData(mChatModel->index(newRow,0), username + " left");
  mChatModel->setData(mChatModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
  ui->listView->scrollToBottom();
}


