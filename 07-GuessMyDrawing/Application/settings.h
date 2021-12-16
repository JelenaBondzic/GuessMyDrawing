#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include "game.h"
#include "client.h"
#include "room.h"
//#include "mainwindow.h"

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

private slots:
    void onSaveClicked();
    void onBackClicked();

    void on_radioButton_3_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_lineEdit_editingFinished();

private:
    Ui::Settings *ui;
    Game *game;
    int duration;
    QString roomName;
    Client *client;
    Room *room ;

};

#endif // SETTINGS_H
