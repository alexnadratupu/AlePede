#ifndef IMAGE_H
#define IMAGE_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <QString>
#include <QTextStream>
#include "histogram.h"


class Image
{
    protected:
        QString     identification;
        QString     imageType;
        int         colorDepth;
        int         height;
        int         width;
        bool        status;
        QImage *    qImage;
        Histogram * histogram;

        virtual void generateHistogram() = 0;
        virtual void generateQImage() = 0;

    public:
        Image();

        virtual ~Image();

        // GETTERS:
        QString getIdentification();
        QString getImageType();
        int getColorDepth();
        int getHeight();
        int getWidth();
        bool getStatus();
        Histogram * getHistogram();
        QImage * getQImage();
        QImage * getHistogramImage();

        // SETTERS:
        void setImageIdentification(QString id);

        // Virtual Methods
        // export
        virtual void saveImage(QString filename) = 0;

        // Image transformations
        virtual Image * changeColorDepth(int bits) = 0;

};
#endif // IMAGE_H
