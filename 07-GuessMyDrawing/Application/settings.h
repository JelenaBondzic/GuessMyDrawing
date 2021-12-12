#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include "game.h"
//#include "mainwindow.h"

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

private slots:
    void onSaveClicked();
    void onBackClicked();

private:
    Ui::Settings *ui;
    Game *game;

};

#endif // SETTINGS_H
