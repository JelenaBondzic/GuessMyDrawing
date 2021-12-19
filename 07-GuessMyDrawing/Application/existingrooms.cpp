 #include "existingrooms.h"
#include "ui_existingrooms.h"
#include <iostream>

ExistingRooms::ExistingRooms(Client* client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExistingRooms),
    client(client)
{
    ui->setupUi(this);
    connect(client, &Client::roomList, this, &ExistingRooms::getActiveRooms);
    connect(ui->leUsername, &QLineEdit::editingFinished, this, &ExistingRooms::on_leUsername_editingFinished);
    connect(ui->listOfRooms, &QListWidget::itemClicked, this, &ExistingRooms::on_listOfRooms_itemClicked);
    connect(ui->pbJoin, &QPushButton::clicked, this, &ExistingRooms::on_pbJoin_clicked);
    connect(client, &Client::joinedRoom, this, &ExistingRooms::on_JoinedRoom);

    client->getRooms();

//    for (int i=0; i< activeRooms->size() ; ++i) {
//        ui->listOfRooms->addItem(activeRooms->at(i));
//    }


}
ExistingRooms::~ExistingRooms()
{
    delete ui;
}

void ExistingRooms::on_listOfRooms_itemClicked(QListWidgetItem *item)
{
    selectedRoom = ui->listOfRooms->selectedItems()[0]->text();
}

void ExistingRooms::getActiveRooms(const QVector<QString> *r)
{
    activeRooms = r;

    for (int i=0; i< activeRooms->size() ; ++i) {
       ui->listOfRooms->addItem(activeRooms->at(i));
       std::cout << activeRooms << std::endl;
    }
//    std::cout << r;
//    std::cout << activeRooms;
}


void ExistingRooms::on_leUsername_editingFinished()
{
    username = ui->leUsername->text();
}


void ExistingRooms::on_pbJoin_clicked()
{
    hide();
    QWidget *parent = this->parentWidget();
    parent->hide();

    std::cout << &username << std::endl;
    std::cout << &username << std::endl;

    client->joinRoom(username, selectedRoom);
}

void ExistingRooms::on_JoinedRoom(bool p)
{
    if(p){
        game = new Game(client, this);
        game->show();
    }
}

