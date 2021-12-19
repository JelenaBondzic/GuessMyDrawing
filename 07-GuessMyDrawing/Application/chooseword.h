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
    explicit ChooseWord(Game* game, QString username, QString roomName, int duration, Client* client, QWidget *parent = nullptr);
    ~ChooseWord();

private slots:
    void on_pbFirstWord_clicked();

    void on_pbSecondWord_clicked();

    void on_pbThirdWord_clicked();

    void on_myWord_clicked();

    void on_pbCreateGame_clicked();

private:
    Ui::ChooseWord *ui;
    QString chosenWord;
    Client *client;
    QString username;
    QString roomName;
    Game* game;
    int duration;
};

#endif // CHOOSEWORD_H
