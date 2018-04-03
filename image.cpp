#include "image.h"

Image::Image()
{

}
Image::~Image()
{
}

QString Image::getIdentification()
{
    return this -> identification;
}

QString Image::getImageType()
{
    return this -> imageType;
}

int Image::getHeight()
{
    return this -> height;
}

int Image::getWidth()
{
    return this -> width;
}

int Image::getColorDepth()
{
    return this -> colorDepth;
}

bool Image::getStatus()
{
    return this -> status;
}

Histogram * Image::getHistogram()
{
    return this -> histogram;
}

QImage * Image::getQImage()
{
    return this -> qImage;
}

QImage * Image::getHistogramImage()
{
    return this -> histogram -> getHistogram();
}

void Image::setImageIdentification(QString id)
{
    this -> identification = id;
}
