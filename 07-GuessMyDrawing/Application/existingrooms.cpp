 #include "existingrooms.h"
#include "ui_existingrooms.h"
#include <iostream>

ExistingRooms::ExistingRooms(Game* game, Client* client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExistingRooms),
    client(client),
    game(game)
{
    ui->setupUi(this);
    connect(client, &Client::roomList, this, &ExistingRooms::getActiveRooms);
    connect(ui->leUsername, &QLineEdit::textEdited, this, &ExistingRooms::leUsername_textEdited);

    connect(ui->listOfRooms, &QListWidget::itemClicked, this, &ExistingRooms::listOfRooms_itemClicked);
    connect(ui->pbJoin, &QPushButton::clicked, this, &ExistingRooms::pbJoin_clicked);
    connect(client, &Client::joinedRoom, this, &ExistingRooms::JoinedRoom);
    connect(client, &Client::errorConnecting, this, &ExistingRooms::showPopUp);


    client->getRooms();

    ui->pbJoin->setDisabled(true);
    ui->listOfRooms->setDisabled(true);

 //   chooseWord = new ChooseWord(game, username, selectedRoom, client, this);

}
ExistingRooms::~ExistingRooms()
{
  std::cout << "Existing rooms destrucotr" << std::endl;
    delete ui;
}

void ExistingRooms::listOfRooms_itemClicked(QListWidgetItem *item)
{
    ui->pbJoin->setDisabled(false);
    selectedRoom = ui->listOfRooms->selectedItems()[0]->text();
//    std::cout << selectedRoom.toStdString() << std::endl;
}

void ExistingRooms::getActiveRooms(const QVector<QString> *r)
{
    activeRooms = r;

    for (int i=0; i< activeRooms->size() ; ++i) {
       ui->listOfRooms->addItem(activeRooms->at(i));
      // std::cout << activeRooms << std::endl;
    }
//    delete r; // TODO check
//    std::cout << r;
//    std::cout << activeRooms;
}


//void ExistingRooms::on_leUsername_editingFinished()
//{
//    username = ui->leUsername->text();
//    if(username.compare("") != 0){
//        ui->pbJoin->setDisabled(false);

//    }
//}


void ExistingRooms::pbJoin_clicked()
{
    hide();
    QWidget *parent = this->parentWidget();
    parent->hide();

   // std::cout << username.toStdString() << std::endl;

    client->joinRoom(username, selectedRoom);
}

void ExistingRooms::JoinedRoom(bool p)
{
    if(p){
        //game = new Game(client, this);
        game->show();
    }
}


void ExistingRooms::leUsername_textEdited(const QString &arg1)
{
    username = ui->leUsername->text();

    ui->listOfRooms->setDisabled(false);
}

void ExistingRooms::showPopUp()
{
    hide();
}

