#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include "game.h"
#include "client.h"
#include "client.h"
#include "chooseword.h"

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(Game* game, Client* client, QWidget *parent = nullptr);
    ~Settings();

    void sendSettingsToCLient(QString username, QString roomName, int duration);

signals:
    void signalThatGameWindowIsClosed();

private slots:
    void SaveClicked();
    void BackClicked();

    void radioButton_3_clicked();
    void radioButton_clicked();
    void radioButton_2_clicked();

    void leUsername_textChanged(const QString &arg1);
    void lnRoomName_textChanged(const QString &arg1);
    void showPopUp();

private:
    Ui::Settings *ui;
    Client *client;
    Game *game;
    int duration;
    QString roomName;
    QString username;


};

#endif // SETTINGS_H
