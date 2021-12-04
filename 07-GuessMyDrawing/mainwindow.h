#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"
#include <QStandardItemModel>
#include <QAbstractSocket>
#include <iostream>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;

  // ADDED

Client *chatClient;
QStandardItemModel *mChatModel;

public:
  void attemptConnection();

private slots:
  void connectToServer();
  void messageRecieved(const QString &sender, const QString &text);
  void sendMessage();
  void disconectedFromServer();
  void userJoined(const QString &username);
  void userLeft(const QString &username);
  void error(QAbstractSocket::SocketError socketError);
  // ADDED
};
#endif // MAINWINDOW_H
