#ifndef IMAGE_H
#define IMAGE_H

#include <QPixmap>
#include <QFileInfo>
#include <QImage>

class Image
{
private:
    QImage img;
    QPixmap pixmap;
    QFileInfo *info;

public:
    Image(QString path);
    ~Image();

    void save(QString path);

    void updatePixmap(QPixmap newPixmap);
    void updateImage(const QImage &image);

    QPixmap pixmapObject();
    QImage imageObject();

    QString name();         // logo.png

    int width();
    int height();
};

#endif // IMAGE_H
