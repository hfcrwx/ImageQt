#ifndef IMAGE_H
#define IMAGE_H

#include <QPixmap>
#include <QFileInfo>
#include <QImage>

class Image
{
private:
    QPixmap pixmap;

public:
    Image(QString path);
    ~Image();

    void save(QString path);

    void updatePixmap(QPixmap newPixmap);

    QPixmap pixmapObject();


    int width();
    int height();
};

#endif // IMAGE_H
