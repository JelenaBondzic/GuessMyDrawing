#ifndef GAME_H
#define GAME_H

#include "canvas.h"

#include <QDialog>
#include <QMainWindow>

namespace Ui {
class Game;
}

class Game : /*public QMainWindow,*/ public QDialog
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();

public slots:
    void onClearDrawing();
    void onChangePenColor();
    void onIncPenWidth();
    void onDecPenWidth();

private:
    Ui::Game *ui;
    Canvas *_canvas;

};

#endif // GAME_H
