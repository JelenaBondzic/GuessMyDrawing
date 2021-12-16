 #include "existingrooms.h"
#include "ui_existingrooms.h"

ExistingRooms::ExistingRooms(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExistingRooms)
{
    ui->setupUi(this);

    for (int i=0; i<activeRoomsNumber ; i++ ) {
        //add list of existing rooms in existing rooms window

    }
}
ExistingRooms::~ExistingRooms()
{
    delete ui;
}
