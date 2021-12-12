#ifndef EXISTINGROOMS_H
#define EXISTINGROOMS_H

#include <QDialog>
#include "client.h"

namespace Ui {
class ExistingRooms;
}

class ExistingRooms : public QDialog
{
    Q_OBJECT

public:
    explicit ExistingRooms(QWidget *parent = nullptr);
    ~ExistingRooms();

private:
    Ui::ExistingRooms *ui;
    Client *client;
};

#endif // EXISTINGROOMS_H
