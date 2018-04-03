#ifndef IMAGEFILE_H
#define IMAGEFILE_H


#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;

class ImageFile:
    public QFile
{
    private:
        QList<QString> lectura;
        QList<QString> supportedFormats;
        QString        id;
        int            colorDepth;
        int            height;
        int            width;
        int *          matrix;

        bool readFileImage();

    public:
        ImageFile(QString fileName);

        bool readFile();
        void readingProcess();
        void printImageContents();
        QList<QString> getImageContents();

        // GETTERS
        QString getId();
        int getColorDepth();
        int getHeight();
        int getWidth();
        int * getMatrix();
};

#endif // IMAGEFILE_H
