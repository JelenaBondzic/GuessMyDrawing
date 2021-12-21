#ifndef GAME_H
#define GAME_H

#include "canvas.h"
#include "client.h"
#include <QDialog>
#include <QCloseEvent>
#include <QMainWindow>
#include <QWidget>
#include <QStandardItemModel>
#include <QTimer>
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
    void closeEvent( QCloseEvent* event ) override;

private slots:
    void sendMessage();
    void sendCanvasMessage();
    void messageRecieved(const QString &sender, const QString &text);
    void userLeft(const QString &username);
    void userJoined(const QString &username);
    void pbLeaveClicked();


signals:
 //   void MySignalToIndicateThatTheWindowIsClosing();
    void IAmHost();

public slots:
    void onClearDrawing();
    void onChangePenColor();
    void onIncPenWidth();
    void onDecPenWidth();
    void onLoadImage(QByteArray b);

private slots:

    void You_Are_Host();
  //  void on_Game_finished(int result);
    void Start_Game();
    void Game_Over();
private:
    Ui::Game *ui;
    Canvas *_canvas;

    int duration;
    QString chosenWord;
    Client *client;
    QString username;

    QTimer* timerCanvas;
    void enableCanvas(const bool isHost);

    // chat
    QStandardItemModel *mChatModel;

};

#endif // GAME_H
