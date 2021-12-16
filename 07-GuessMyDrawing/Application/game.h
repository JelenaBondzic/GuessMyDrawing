#ifndef GAME_H
#define GAME_H

#include <QDialog>
#include "room.h"
//#include "settings.h"

namespace Ui {
class Game;
}

class Game : public QDialog
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();

    int getDuration() const;

    void setDuration(int newDuration);

private slots:
    void on_pbFirstWord_clicked();

    void on_pbSecondWord_clicked();

    void on_pbThirdWord_clicked();

    void on_myWord_clicked();

    void on_pbCreateGame_clicked();

private:
    Ui::Game *ui;
    int duration;
    Room *room;
    //Settings *settings;
    QString chosenWord;
};

#endif // GAME_H
