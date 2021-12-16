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


    connect(ui->radioButton, &QRadioButton::clicked, this, &Settings::on_radioButton_clicked);
    connect(ui->radioButton_2, &QRadioButton::clicked, this, &Settings::on_radioButton_2_clicked);
    connect(ui->radioButton_3, &QRadioButton::clicked, this, &Settings::on_radioButton_3_clicked);

//    connect(ui->radioButton, SIGNAL(clicked()), this, SLOT(on_radioButton_1_clicked()));

//    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(on_radioButton_2_clicked()));


}

Settings::~Settings()
{
    delete ui;
}

void Settings::onSaveClicked()
{
    hide();
    room = new Room(roomName, client);
    room->setDuration(this->duration);
    game = new Game(this);
    game->show();
}

void Settings::onBackClicked(){
    hide();

    QWidget *parent = this->parentWidget();
    parent->show();
}

void Settings::on_radioButton_clicked()
{
    duration = 60;

}


void Settings::on_radioButton_2_clicked()
{
    this->duration = 90;

}

void Settings::on_radioButton_3_clicked()
{
    this->duration = 120;


}


void Settings::on_lineEdit_editingFinished()
{
    this->roomName = ui->lnRoomName->text();
}

