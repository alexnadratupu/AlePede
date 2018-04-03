#ifndef IMAGENPPM_H
#define IMAGENPPM_H



#include "imagenpgm.h"
#include "image.h"
#include <QImage>
#include <QRgb>

using namespace std;

class ImagenPPM:
    public Image
{
    int *** matrixRp, ***matrixGp, ***matrixBp;
    int *   lutR, *lutG, *lutB;

    void generateHistogram();
    void generateQImage();

    public:

        // Constructors
        ImagenPPM(QString filename);

        ImagenPPM(QString id,
                  int     h,
                  int     w,
                  int     depth,
                  int **  matrizR,
                  int **  matrizG,
                  int **  matrizB);

        ImagenPPM(QString id,
                  int     h,
                  int     w,
                  int     colorD,
                  int *** matrizR,
                  int *   lutR,
                  int *** matrizG,
                  int *   lutG,
                  int *** matrizB,
                  int *   lutB);

        ~ImagenPPM();

        // Image processing
        Image * changeSize(int factor);
        Image * changeColorDepth(int bits);
        ImagenPGM * convertToGrayScale(int method);

        // Image *equalizateHistogram(int *newlut);
        // Getters
        int *** getMatrizR();
        int *** getMatrizG();
        int *** getMatrizB();

        // Export
        void saveImage(QString filename);
};
#endif // IMAGENPPM_H
