#include "mainwindow.h"
#include "server.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  Server s;
  s.startServer();
//  w.attemptConnection();
  w.show();
  return a.exec();
}
