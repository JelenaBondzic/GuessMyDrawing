#include "mainwindow.h"
#include "server.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  Server s;
  s.startServer();

  w.attemptConnection(1234);
  w.show();

  MainWindow w1;
  w1.attemptConnection(1234);
  w1.show();
  return a.exec();
}
