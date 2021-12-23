#ifndef CHOOSEWORD_H
#define CHOOSEWORD_H

#include <QDialog>
#include "client.h"
#include "game.h"

namespace Ui {
class ChooseWord;
}

class ChooseWord : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseWord(Game* game, Client* client, QWidget *parent = nullptr);
    ~ChooseWord();

private slots:
    void pbFirstWord_clicked();

    void pbSecondWord_clicked();

    void pbThirdWord_clicked();

    void myWord_clicked();

    void pbCreateGame_clicked();
    void show_Window();
    void leave();
    void showPopUp();

private:
    Ui::ChooseWord *ui;
    QString chosenWord;
    Client *client;
    Game* game;

};

#endif // CHOOSEWORD_H
