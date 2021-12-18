#include "settings.h"
#include "ui_settings.h"
#include "game.h"
#include "mainwindow.h"

Settings::Settings(Client* client, QWidget *parent) :
    client(client),
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    connect(ui->pbSave, &QPushButton::clicked, this, &Settings::onSaveClicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &Settings::onBackClicked);
    connect(ui->leUsername, &QLineEdit::editingFinished, this,  &Settings::on_leUsername_editingFinished);


    connect(ui->radioButton, &QRadioButton::clicked, this, &Settings::on_radioButton_clicked);
    connect(ui->radioButton_2, &QRadioButton::clicked, this, &Settings::on_radioButton_2_clicked);
    connect(ui->radioButton_3, &QRadioButton::clicked, this, &Settings::on_radioButton_3_clicked);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::onSaveClicked()
{
    hide();
    QWidget *parent = this->parentWidget();
    parent->hide();
    sendSettingsToCLient(username, roomName, duration);
    chooseWordWindow = new ChooseWord(username, roomName, duration, client, this);
    chooseWordWindow->show();
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
    duration = 90;
}

void Settings::on_radioButton_3_clicked()
{
    duration = 120;
}


void Settings::on_lineEdit_editingFinished()
{
    this->roomName = ui->lnRoomName->text();
}


void Settings::sendSettingsToCLient(QString username, QString roomName, int duration){
   // client->createRoom(username, roomName, duration);
}


void Settings::on_leUsername_editingFinished()
{
    username = ui->leUsername->text();
}

