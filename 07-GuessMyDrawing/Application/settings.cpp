#include "settings.h"
#include "ui_settings.h"
#include "game.h"
#include "mainwindow.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    connect(ui->pbSave, &QPushButton::clicked, this, &Settings::onSaveClicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &Settings::onBackClicked);

}

Settings::~Settings()
{
    delete ui;
}

void Settings::onSaveClicked()
{
    hide();
    game = new Game(this);
    game->show();
}

void Settings::onBackClicked(){
    hide();

    QWidget *parent = this->parentWidget();
    parent->show();
}

