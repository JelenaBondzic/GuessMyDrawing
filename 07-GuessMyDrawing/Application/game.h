#ifndef GAME_H
#define GAME_H

#include "canvas.h"

#include <QDialog>
#include <QMainWindow>

namespace Ui {
class Game;
}

class Game : public QDialog
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();

    Canvas *getCanvas() const;

public slots:
    void onClearDrawing();
    void onChangePenColor();
    void onIncPenWidth();
    void onDecPenWidth();
    void onTakeSnap();
    void onLoadImage();

private:
    Ui::Game *ui;
    Canvas *_canvas;
    QByteArray *barr = nullptr;
    QByteArray ba;

};

#endif // GAME_H
