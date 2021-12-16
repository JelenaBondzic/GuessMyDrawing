#include "game.h"
#include "ui_game.h"
#include "canvas.h"

Game::Game(QWidget *parent) :
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

}

Game::~Game()
{
    delete ui;
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



