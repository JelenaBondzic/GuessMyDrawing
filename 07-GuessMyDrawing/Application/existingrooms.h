#ifndef EXISTINGROOMS_H
#define EXISTINGROOMS_H

#include <QDialog>
#include "client.h"
#include <QListWidgetItem>
#include "game.h"

namespace Ui {
class ExistingRooms;
}

class ExistingRooms : public QDialog
{
    Q_OBJECT

public:
    explicit ExistingRooms(Game* game, Client* client, QWidget *parent = nullptr);
    ~ExistingRooms();

private slots:
    void on_listOfRooms_itemClicked(QListWidgetItem *item);
    void getActiveRooms(const QVector<QString>* r);
//    void on_leUsername_editingFinished();
    void on_pbJoin_clicked();
    void on_JoinedRoom(bool p);

    void on_leUsername_textEdited(const QString &arg1);

private:
    Ui::ExistingRooms *ui;
    Client *client;
    const QVector<QString>* activeRooms;
    QString username = "";
    QString selectedRoom;
    Game* game;


};

#endif // EXISTINGROOMS_H
