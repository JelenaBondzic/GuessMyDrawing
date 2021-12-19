#ifndef GAME_H
#define GAME_H

#include "canvas.h"
#include "client.h"
#include <QDialog>
#include <QCloseEvent>
#include <QMainWindow>
#include <QWidget>
#include <QStandardItemModel>
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

    Canvas *getCanvas() const;

    int getDuration() const;

    void setDuration(int newDuration);
    //void closeEvent( QCloseEvent* event );

private slots:
    void sendMessage();
    void messageRecieved(const QString &sender, const QString &text);
    void userLeft(const QString &username);
    void userJoined(const QString &username);


signals:
 //   void MySignalToIndicateThatTheWindowIsClosing();

public slots:
    void onClearDrawing();
    void onChangePenColor();
    void onIncPenWidth();
    void onDecPenWidth();
    void onTakeSnap();
    void onLoadImage();

private slots:

    void You_Are_Host();
    void on_Game_finished(int result);
    void Start_Game();

private:
    Ui::Game *ui;
    Canvas *_canvas;
    QByteArray *barr = nullptr;
    QByteArray ba;

    int duration;
    QString chosenWord;
    Client *client;
    QString username;

    // chat
    QStandardItemModel *mChatModel;

};

#endif // GAME_H
