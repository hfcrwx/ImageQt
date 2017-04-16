#include "image.h"
#include <QDebug>

Image::Image(QString path)
{
    pixmap.load(path);
}

Image::~Image()
{
}

void Image::save(QString path)
{
    pixmap.save(path, 0, 60);

}

QPixmap Image::pixmapObject()
{
    return pixmap;
}

int Image::width()
{
    return pixmap.width();
}

int Image::height()
{
    return pixmap.height();
}

void Image::updatePixmap(QPixmap newPixmap)
{
    pixmap = newPixmap;
}
