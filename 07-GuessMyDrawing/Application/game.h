#ifndef GAME_H
#define GAME_H

#include <QDialog>
#include "client.h"
#include <QCloseEvent>
#include <QMainWindow>
#include <QWidget>
//#include "mainwindow.h"

namespace Ui {
class Game;
}

class Game : public QDialog
{
    Q_OBJECT

public:
    explicit Game(Client* client, QWidget *parent = nullptr);
    ~Game();

    int getDuration() const;

    void setDuration(int newDuration);
    //void closeEvent( QCloseEvent* event );

signals:
 //   void MySignalToIndicateThatTheWindowIsClosing();


private slots:

    void on_You_Are_Host();
    void on_Game_finished(int result);
    void on_Start_Game();

private:
    Ui::Game *ui;
    int duration;
    QString chosenWord;
    Client *client;
    QString username;
};

#endif // GAME_H
