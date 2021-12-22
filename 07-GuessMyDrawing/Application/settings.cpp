#include "settings.h"
#include "ui_settings.h"
#include "game.h"
#include "mainwindow.h"

Settings::Settings(Game* game, Client* client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings),
    client(client),
    game(game)
{
    ui->setupUi(this);
    connect(ui->pbSave, &QPushButton::clicked, this, &Settings::SaveClicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &Settings::BackClicked);

 //   connect(ui->leUsername, &QLineEdit::editingFinished, this,  &Settings::on_leUsername_editingFinished);
    connect(ui->leUsername, &QLineEdit::textChanged, this,  &Settings::leUsername_textChanged);
    connect(ui->lnRoomName, &QLineEdit::textChanged, this, &Settings::lnRoomName_textChanged);
    connect(ui->radioButton, &QRadioButton::clicked, this, &Settings::radioButton_clicked);
    connect(ui->radioButton_2, &QRadioButton::clicked, this, &Settings::radioButton_2_clicked);
    connect(ui->radioButton_3, &QRadioButton::clicked, this, &Settings::radioButton_3_clicked);

    ui->pbSave->setDisabled(true);
    ui->leUsername->setDisabled(true);
    ui->radioButton->setDisabled(true);
    ui->radioButton_2->setDisabled(true);
    ui->radioButton_3->setDisabled(true);

}

Settings::~Settings()
{
    delete ui;
}

void Settings::SaveClicked()
{
    hide();
    QWidget *parent = this->parentWidget();
    parent->hide();
    username = ui->leUsername->text();
    roomName = ui->lnRoomName->text();
  //  chooseWordWindow = new ChooseWord(game, username, roomName, client, this);

    sendSettingsToCLient(username, roomName, duration);
    //chooseWordWindow->show();
}

void Settings::BackClicked(){
    hide();

    QWidget *parent = this->parentWidget();
    parent->show();
}

void Settings::radioButton_clicked()
{
    duration = 60;
    ui->leUsername->setDisabled(false);

}

void Settings::radioButton_2_clicked()
{
    duration = 90;
    ui->leUsername->setDisabled(false);

}

void Settings::radioButton_3_clicked()
{
    duration = 120;
    ui->leUsername->setDisabled(false);

}


//void Settings::on_lineEdit_editingFinished()
//{
//    ui->pbCreateGame->setDisabled(true);
//}


void Settings::sendSettingsToCLient(QString username, QString roomName, int duration){
    client->createRoom(username, roomName, duration);
}


//void Settings::on_leUsername_editingFinished()
//{
//  //   ui->pbSave->setDisabled(false);
//}


void Settings::leUsername_textChanged(const QString &arg1)
{
//    QString roomName1 = ui->lnRoomName->text();
//    if(roomName.compare("") != 0)
        ui->pbSave->setDisabled(false);

}


void Settings::lnRoomName_textChanged(const QString &arg1)
{
    ui->radioButton->setDisabled(false);
    ui->radioButton_2->setDisabled(false);
    ui->radioButton_3->setDisabled(false);
}

