#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "client.h"
#include "existingrooms.h"
#include "game.h"
#include "settings.h"

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
  void onJoinGameClicked();
  void onCreateNewGameClicked();

public:
  void attemptConnection(qint16 port);

private slots:
  void messageRecieved(const QString &sender, const QString &text);
  void sendMessage();
  void userJoined(const QString &username);
  void userLeft(const QString &username);
//  void error(QAbstractSocket::SocketError socketError);
  // ADDED
private:
  Ui::MainWindow *ui;
  Client* client;
  Game *game;
  Settings *settings;
  Client *chatClient;
  QStandardItemModel *mChatModel;

};
#endif // MAINWINDOW_H
