#include "image.h"
#include <QDebug>

Image::Image(QString path)
{
    pixmap.load(path);
    img.load(path);
    info = new QFileInfo(path);
    qDebug() << sizeof img << sizeof pixmap  << sizeof pixmap.data_ptr();
}

Image::~Image()
{
    if (info)
    {
        delete info;
        info = NULL;
    }
}

void Image::save(QString path)
{
    pixmap.save(path, 0, 60);

}

QPixmap Image::pixmapObject()
{
    return pixmap;
}

QImage Image::imageObject()
{
    return img;
}

QString Image::name()
{
    return info->fileName();
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

void Image::updateImage(const QImage &image)
{
    img = image;
}
