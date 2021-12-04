#include "existingrooms.h"
#include "ui_existingrooms.h"

ExistingRooms::ExistingRooms(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExistingRooms)
{
    ui->setupUi(this);
   // client.getRooms();
}

ExistingRooms::~ExistingRooms()
{
    delete ui;
}
