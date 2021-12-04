#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

public slots:
  void onJoinGameClicked();
  void onCreateNewGameClicked();

private:
  Ui::MainWindow *ui;
  Client* client;
  Game *game;
  Settings *settings;

};
#endif // MAINWINDOW_H
