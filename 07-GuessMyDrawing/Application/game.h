#ifndef GAME_H
#define GAME_H

#include "canvas.h"
#include "client.h"
#include <QDialog>
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

    Canvas *getCanvas() const;

    int getDuration() const;

    void setDuration(int newDuration);
    //void closeEvent( QCloseEvent* event );

signals:
   // void MySignalToIndicateThatTheWindowIsClosing();

public slots:
    void onClearDrawing();
    void onChangePenColor();
    void onIncPenWidth();
    void onDecPenWidth();
    void onTakeSnap();
    void onLoadImage();

private slots:
    void on_pbFirstWord_clicked();

    void on_pbSecondWord_clicked();

    void on_pbThirdWord_clicked();

    void on_myWord_clicked();

    void on_pbCreateGame_clicked();


private:
    Ui::Game *ui;
    Canvas *_canvas;
    QByteArray *barr = nullptr;
    QByteArray ba;

    int duration;
    QString chosenWord;
    Client *client;
   // QMainWindow* mainWindow;
    QString username;


};

#endif // GAME_H
