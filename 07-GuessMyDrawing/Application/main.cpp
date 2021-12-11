#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;

  w.attemptConnection(1234);
  w.show();

  MainWindow w1;
  w1.attemptConnection(1234);
  w1.show();
  return a.exec();
}

