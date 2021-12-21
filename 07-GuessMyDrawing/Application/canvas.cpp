#include "canvas.h"

#include <QMouseEvent>
#include <QPainter>
#include <iostream>
#include <QByteArray>
#include <QBuffer>

Canvas::Canvas(QWidget *parent)
    : QWidget(parent)
{

}


void Canvas::takeSnapshot(QByteArray &barr)
{
    QBuffer buffer(&barr);
    buffer.open(QIODevice::WriteOnly);
    bool imageSaved = _image.save(&buffer, "PNG");
}

void Canvas::loadFromSnapshot(const QByteArray &arr)
{
    bool imageLoaded = _image.loadFromData(arr, "PNG");
    _modified = true;
    update();
}

void Canvas::clearImage()
{
    _image.fill(qRgb(255, 255, 255));
    _modified = true;
    update();
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        _lastPoint = event->pos();
        _drawing = true;
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && _drawing)
        drawLineTo(event->pos());
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && _drawing) {
        drawLineTo(event->pos());
        _drawing = false;
    }
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, _image, dirtyRect);
}

void Canvas::resizeEvent(QResizeEvent *event)
{
    if (width() > _image.width() || height() > _image.height()) {
        int newWidth = qMax(width() + 128, _image.width());
        int newHeight = qMax(height() + 128, _image.height());
        resizeImage(&_image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void Canvas::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&_image);
    painter.setPen(QPen(_myPenColor, _myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(_lastPoint, endPoint);
    _modified = true;

    int rad = (_myPenWidth / 2) + 2;
    update(QRect(_lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    _lastPoint = endPoint;
}

void Canvas::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

int Canvas::penWidth() const {
    return _myPenWidth;
}

void Canvas::setPenWidth(int width)
{
    if (width >= _maxPenWidth) {
        _myPenWidth = _maxPenWidth;
    }
    else if (width <= _minPenWidth) {
        _myPenWidth = _minPenWidth;
    }
    else {
        _myPenWidth = width;
    }
}

void Canvas::setPenColor(QColor color)
{
    _myPenColor = color;
}
