#include "tools.h"
#include "medianfilter.h"
#include "common.h"

/*****************************************************************************
 *                           Greyscale
 * **************************************************************************/
QImage Tools::GreyScale(const QImage &origin)
{
    QImage *newImage = new QImage(origin.width(), origin.height(),
                                   QImage::Format_ARGB32);
    QColor oldColor;

    for (int x=0; x<newImage->width(); x++) {
        for (int y=0; y<newImage->height(); y++) {
            oldColor = QColor(origin.pixel(x,y));
            int average = (oldColor.red()*299+oldColor.green()*587+oldColor.blue()*114+500)/1000;
            newImage->setPixel(x,y,qRgb(average,average,average));
        }
    }

    return *newImage;

}

/*****************************************************************************
 *                           Adjust color temperature
 * **************************************************************************/
QImage Tools::Warm(int delta, const QImage &origin)
{
    QImage *newImage = new QImage(origin.width(), origin.height(),
                                  QImage::Format_ARGB32);

    QColor oldColor;
    int r, g, b;

    for (int x=0; x<newImage->width(); x++)
    {
        for (int y=0; y<newImage->height(); y++)
        {
            oldColor = QColor(origin.pixel(x,y));

            r = oldColor.red() + delta;
            g = oldColor.green() + delta;
            b = oldColor.blue();
//            qDebug()<<r<<" "<<g<<""<<b;

            // Check if the new values are between 0 and 255
            r = qBound(0, r, 255);
            g = qBound(0, g, 255);

            newImage->setPixel(x,y, qRgb(r,g,b));
        }
    }
    return *newImage;
}

QImage Tools::Cool(int delta, const QImage& origin)
{
    QImage *newImage = new QImage(origin.width(), origin.height(),
                                  QImage::Format_ARGB32);

    QColor oldColor;
    int r, g, b;

    for (int x=0; x<newImage->width(); x++)
    {
        for (int y=0; y<newImage->height(); y++)
        {
            oldColor = QColor(origin.pixel(x,y));

            r = oldColor.red();
            g = oldColor.green();
            b = oldColor.blue() + delta;

            // Check if the new values are between 0 and 255
            r = qBound(0, r, 255);
            g = qBound(0, g, 255);

            newImage->setPixel(x,y, qRgb(r,g,b));
        }
    }
    return *newImage;
}



/*****************************************************************************
 *                          Adjust image brightness
 * **************************************************************************/
QImage Tools::Brightness(int delta, const QImage& origin)
{
    QImage *newImage = new QImage(origin.width(), origin.height(),
                                  QImage::Format_ARGB32);
    QColor oldColor;
    int r, g, b;

    for (int x=0; x<newImage->width(); x++)
    {
        for (int y=0; y<newImage->height(); y++)
        {
            oldColor = QColor(origin.pixel(x,y));

            r = oldColor.red() + delta;
            g = oldColor.green() + delta;
            b = oldColor.blue() + delta;

            // Check if the new values are between 0 and 255
            r = qBound(0, r, 255);
            g = qBound(0, g, 255);

            newImage->setPixel(x,y, qRgb(r,g,b));
        }
    }
    return *newImage;
}

/*****************************************************************************
 *                                   Flip
 * **************************************************************************/
QImage Tools::Horizontal(const QImage &origin)
{
    QImage *newImage = new QImage(QSize(origin.width(), origin.height()),
                                  QImage::Format_ARGB32);
    QColor tmpColor;
    int r, g, b;
    for (int x=0; x<newImage->width(); x++)
    {
        for (int y=0; y<newImage->height(); y++)
        {
            tmpColor = QColor(origin.pixel(x, y));
            r = tmpColor.red();
            g = tmpColor.green();
            b = tmpColor.blue();

            newImage->setPixel(newImage->width()-x-1,y, qRgb(r,g,b));

        }
    }
    return *newImage;
}

QImage Tools::Vertical(const QImage &origin)
{
    QImage *newImage = new QImage(QSize(origin.width(), origin.height()),
                                  QImage::Format_ARGB32);
    QColor tmpColor;
    int r, g, b;
    for (int x=0; x<newImage->width(); x++)
    {
        for (int y=0; y<newImage->height(); y++)
        {
            tmpColor = QColor(origin.pixel(x, y));
            r = tmpColor.red();
            g = tmpColor.green();
            b = tmpColor.blue();

            newImage->setPixel(x, newImage->height()-y-1, qRgb(r,g,b));

        }
    }
    return *newImage;
}





/*****************************************************************************
 *                            添加相框
 * **************************************************************************/
QImage Tools::DrawFrame(const QImage &origin, const QImage &frame)
{
    QImage *newImage = new QImage(origin);
    QPainter painter;

    int width = origin.width();
    int height = origin.height();

    QImage tmpFrame = frame.scaled(QSize(width, height));

    painter.begin(newImage);
    painter.drawImage(0, 0, tmpFrame);
    painter.end();

    return *newImage;

}

/*****************************************************************************
 *                           线性灰度变换 y = ax + b
 * **************************************************************************/
QImage Tools::LinearLevelTransformation(const QImage &origin, double _a, double _b)
{
    QImage *newImage = new QImage(origin.width(), origin.height(),
                                   QImage::Format_ARGB32);
    QColor oldColor;
    int grayLevel = 0;

    for (int x=0; x<newImage->width(); x++) {
        for (int y=0; y<newImage->height(); y++) {
            oldColor = QColor(origin.pixel(x,y));
            grayLevel = (oldColor.red()*299+oldColor.green()*587+oldColor.blue()*114+500)/1000;
            int _y = _a*grayLevel + _b;
            // Make sure that the new values are between 0 and 255
            _y = qBound(0, _y, 255);

            newImage->setPixel(x,y,qRgb(_y,_y,_y));
        }
    }
//    qDebug()<<"a:"<<_a<<"\tb:"<<_b;

    return *newImage;
}


/*****************************************************************************
 *                           对数灰度变换
 * **************************************************************************/
QImage Tools::LogGreyLevelTransformation(const QImage &origin, double a, double b)
{
    QImage *newImage = new QImage(origin.width(), origin.height(),
                                   QImage::Format_ARGB32);
    QColor oldColor;
    int grayLevel = 0;

    for (int x=0; x<newImage->width(); x++) {
        for (int y=0; y<newImage->height(); y++) {
            oldColor = QColor(origin.pixel(x,y));
            grayLevel = (oldColor.red()*299+oldColor.green()*587+oldColor.blue()*114+500)/1000;
            int _y = qLn(b+grayLevel)/qLn(a);

            // Make sure that the new values are between 0 and 255
            _y = qBound(0, _y, 255);

            newImage->setPixel(x,y,qRgb(_y,_y,_y));
        }
    }

    return *newImage;
}


/*****************************************************************************
 *                           幂次灰度变换 _y=c*_x^r+b
 * **************************************************************************/
QImage Tools::PowerGreyLevelTransformation(const QImage &origin, double c, double r, double b)
{
    QImage *newImage = new QImage(origin.width(), origin.height(),
                                   QImage::Format_ARGB32);
    QColor oldColor;
    int _x = 0;

    for (int x=0; x<newImage->width(); x++) {
        for (int y=0; y<newImage->height(); y++) {
            oldColor = QColor(origin.pixel(x,y));
            _x = (oldColor.red()*299+oldColor.green()*587+oldColor.blue()*114+500)/1000;
            int _y =c*qPow(_x, r)+b;

            // Make sure that the new values are between 0 and 255
            _y = qBound(0, _y, 255);

            newImage->setPixel(x,y,qRgb(_y,_y,_y));
        }
    }

    return *newImage;
}


/*****************************************************************************
 *                                  指数灰度变换
 * **************************************************************************/
QImage Tools::ExpTransform(const QImage &origin, double b, double c, double a)
{
    QImage *newImage = new QImage(origin.width(), origin.height(),
                                   QImage::Format_ARGB32);
    QColor oldColor;
    int _x = 0;

    for (int x=0; x<newImage->width(); x++) {
        for (int y=0; y<newImage->height(); y++) {
            oldColor = QColor(origin.pixel(x,y));
            _x = (oldColor.red()*299+oldColor.green()*587+oldColor.blue()*114+500)/1000;
            int _y =qPow(b, c*(_x-a));

            // Make sure that the new values are between 0 and 255
            _y = qBound(0, _y, 255);

            newImage->setPixel(x,y,qRgb(_y,_y,_y));
        }
    }

    return *newImage;
}

/*****************************************************************************
 *                                  双阈值灰度变换
 * int option:
 *          0   0-255-0
 *          1   255-0-255
 * **************************************************************************/
QImage Tools::TwoThreshold(const QImage &origin, double t1, double t2, int option)
{
    QImage *newImage = new QImage(origin.width(), origin.height(),
                                   QImage::Format_ARGB32);
    QColor oldColor;
    int _x = 0;
    int _y = 0;
    if (option == 0)
    {
        for (int x=0; x<newImage->width(); x++) {
            for (int y=0; y<newImage->height(); y++) {
                oldColor = QColor(origin.pixel(x,y));
                _x = (oldColor.red()*299+oldColor.green()*587+oldColor.blue()*114+500)/1000;

                if (_x < t1 || _x > t2)
                    _y = 0;
                else
                    _y = 255;


                // Make sure that the new values are between 0 and 255
                _y = qBound(0, _y, 255);

                newImage->setPixel(x,y,qRgb(_y,_y,_y));
            }
        }
    }
    else
    {
        for (int x=0; x<newImage->width(); x++) {
            for (int y=0; y<newImage->height(); y++) {
                oldColor = QColor(origin.pixel(x,y));
                _x = (oldColor.red()*299+oldColor.green()*587+oldColor.blue()*114+500)/1000;

                if (_x>=t1 && _x<=t2)
                    _y = 0;
                else
                    _y = 255;


                // Make sure that the new values are between 0 and 255
                _y = qBound(0, _y, 255);

                newImage->setPixel(x,y,qRgb(_y,_y,_y));
            }
        }
    }

    return *newImage;
}



/*****************************************************************************
 *                                拉伸灰度变换
 * 拉伸变换使用一个分段函数，三个k值
 * **************************************************************************/
QImage Tools::StretchTransform(const QImage &origin,
                               int x1, int x2,
                               double k1, double k2, double k3,
                               double b2, double b3)
{
    QImage *newImage = new QImage(origin.width(), origin.height(),
                                   QImage::Format_ARGB32);
    QColor oldColor;
    int _x = 0;
    int _y = 0;

    for (int x=0; x<newImage->width(); x++) {
        for (int y=0; y<newImage->height(); y++) {
            oldColor = QColor(origin.pixel(x,y));
            _x = (oldColor.red()*299+oldColor.green()*587+oldColor.blue()*114+500)/1000;

            if ( _x<x1)
                _y = k1*_x;
            else if (_x < x2)
                _y = k2*_x + b2;
            else
                _y = k3*_x + b3;


            // Make sure that the new values are between 0 and 255
            _y = qBound(0, _y, 255);

            newImage->setPixel(x,y,qRgb(_y,_y,_y));
        }
    }

    return *newImage;
}


/*****************************************************************************
 *                               简单平滑处理
 * **************************************************************************/
QImage Tools::SimpleSmooth(const QImage &origin)
{
    QImage *newImage = new QImage(origin);

    int kernel[5][5] = {
        {0,0,1,0,0},
        {0,1,3,1,0},
        {1,3,7,3,1},
        {0,1,3,1,0},
        {0,0,1,0,0}
    };
    int kernelSize = 5;
    int sumKernel=27;
    int r,g,b;
    QColor color;

    for(int x=kernelSize/2; x<newImage->width()-kernelSize/2; x++)
    {
        for (int y=kernelSize/2; y<newImage->height()-kernelSize/2; y++)
        {
            r = g = b = 0;
            for (int i=-kernelSize/2; i<=kernelSize/2; i++)
            {
                for (int j=-kernelSize/2; j<=kernelSize/2; j++)
                {
                    color = QColor(origin.pixel(x+i,y+j));
                    r += color.red()*kernel[kernelSize/2+i][kernelSize/2+j];
                    g += color.green()*kernel[kernelSize/2+i][kernelSize/2+j];
                    b += color.blue()*kernel[kernelSize/2+i][kernelSize/2+j];

                }
            }
            r = qBound(0, r/sumKernel, 255);
            g = qBound(0, g/sumKernel, 255);
            b = qBound(0, b/sumKernel, 255);

            newImage->setPixel(x,y,qRgb(r,g,b));

        }
    }
    return *newImage;
}


/*****************************************************************************
 *                                   中值滤波
 * **************************************************************************/
QImage Tools::MeidaFilter(const QImage &origin, int filterRadius)
{
    int imageHeight = origin.height();
    int imageWidth = origin.width();
    MedianFilter medianFilter;
    int* resImageBits = new int[imageHeight * imageWidth];
    medianFilter.applyMedianFilter((int*)origin.bits(), resImageBits, imageHeight, imageWidth, filterRadius);

    QImage destImage((uchar*)resImageBits, imageWidth, imageHeight, origin.format());
//    QPixmap pixRes;
//    pixRes.convertFromImage(destImage);


    return destImage;
}
