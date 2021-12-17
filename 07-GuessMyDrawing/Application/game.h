#ifndef GAME_H
#define GAME_H

#include <QDialog>
#include "client.h"
#include <QCloseEvent>
#include <QMainWindow>
//#include "mainwindow.h"

namespace Ui {
class Game;
}

class Game : public QDialog
{
    Q_OBJECT

public:
    explicit Game(QString username, Client* client, QWidget *parent = nullptr);
    ~Game();

    int getDuration() const;

    void setDuration(int newDuration);
    //void closeEvent( QCloseEvent* event );

signals:
   // void MySignalToIndicateThatTheWindowIsClosing();


private slots:
    void on_pbFirstWord_clicked();

    void on_pbSecondWord_clicked();

    void on_pbThirdWord_clicked();

    void on_myWord_clicked();

    void on_pbCreateGame_clicked();


private:
    Ui::Game *ui;
    int duration;
    QString chosenWord;
    Client *client;
   // QMainWindow* mainWindow;
    QString username;
};

#endif // GAME_H
