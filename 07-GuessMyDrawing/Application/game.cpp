#include "game.h"
#include "ui_game.h"
#include "canvas.h"
#include "client.h"


Game::Game(QString username, Client* client, QWidget *parent) :
    username(username),
    client(client),
    QDialog(parent),
    ui(new Ui::Game),
    _canvas(new Canvas(this))
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


    connect(ui->pbFirstWord, &QPushButton::clicked, this, &Game::on_pbFirstWord_clicked);
    connect(ui->pbSecondWord, &QPushButton::clicked, this, &Game::on_pbSecondWord_clicked);



}

Game::~Game()
{
//    client->leaveRoom();
//    mainWindow = new MainWindow(username, this);
   // mainWindow->show();
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
    client->chooseWord(chosenWord);
}


//void Game::closeEvent(QCloseEvent* event)
//{
//    emit MySignalToIndicateThatTheWindowIsClosing();
//    event->accept();
//}








