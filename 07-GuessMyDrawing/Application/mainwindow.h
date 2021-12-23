#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "client.h"
#include "existingrooms.h"
#include "game.h"
#include "settings.h"
#include "chooseword.h"
#include "popup.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QString username, QWidget *parent = nullptr);
  ~MainWindow();

public slots:
  void JoinGameClicked();
  void CreateNewGameClicked();
  void gameWindowClosed();
  void showPopUp();


public:
  void attemptConnection(qint16 port);

//private slots:
//  void messageRecieved(const QString &sender, const QString &text);
//  void sendMessage();
//  void userJoined(const QString &username);
//  void userLeft(const QString &username);
  //  void error(QAbstractSocket::SocketError socketError);
  // ADDED
private:
  Ui::MainWindow *ui;
 // Client* client;
  ExistingRooms* existingRooms = nullptr;
  Settings *settings = nullptr;
  Client *chatClient;
//  QStandardItemModel *mChatModel;
  Game *game;
  ChooseWord *chooseWord;
  PopUp *popUpWindow;

};
#endif // MAINWINDOW_H
