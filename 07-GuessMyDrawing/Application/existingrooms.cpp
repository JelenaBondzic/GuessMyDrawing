 #include "existingrooms.h"
#include "ui_existingrooms.h"
#include <iostream>

ExistingRooms::ExistingRooms(Client* client, QWidget *parent) :
    client(client),
    QDialog(parent),
    ui(new Ui::ExistingRooms)
{
    ui->setupUi(this);
    connect(client, &Client::roomList, this, &ExistingRooms::getActiveRooms);
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
//    std::cout << r;
//    std::cout << activeRooms;
}


void ExistingRooms::on_leUsername_editingFinished()
{
    username = ui->leUsername->text();
}


void ExistingRooms::on_pbJoin_clicked()
{
    client->joinRoom(username, selectedRoom);
    game = new Game(username, client, this);
    game->show();

}

