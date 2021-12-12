#ifndef CANVAS_H
#define CANVAS_H


class Canvas
{
public:
    Canvas();
private:
    unsigned height;
    unsigned width;

    void takeSnapshot();
};

#endif // CANVAS_H
