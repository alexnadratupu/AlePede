#ifndef IMAGENPGM_H
#define IMAGENPGM_H

#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QImage>
#include <QRgb>
#include <math.h>
#include "imagefile.h"
#include "image.h"

using namespace std;
#define PI 3.14159265

class ImagenPGM : public Image
{
    int ***   matrixImagenP;
    int *     lut;
    int **    resultMatrixI;
    int **    resultMatrixJ;
    double ** resultMatrixGradiente;
    int **    resultMatrixDirection;
    int **    resultMatrixImage;
    int **    memoryposition;
    int       maxGradiente;

    void generateHistogram();
    void generateQImage();


    int ** applyKernel(int ** kernel, int    kernelSizeX, int    kernelSizeY);
    void applyKerneltoPixel(int i,int j, int ** kernel, int kernelSizeX, int kernelSizeY, int ** matrix);
    Image * clasify(int * centroid, int size, int iterations);
    void matrizMagnitud();
    void matrizDirection();
    int ** Umbral();
    int Threshold(int *colorFrequency);

public:

    // Constructors
    ImagenPGM(QString filename);

    ImagenPGM(int    h,
              int    w,
              int    colorD,
              int ** matrix);

    ImagenPGM(int     h,
              int     w,
              int     colorD,
              int *** matrixP,
              int *   lut);

    ~ImagenPGM();

    // Global Transformations
    Image * changeSize(int factor);
    Image * changeColorDepth(int bits);
    Image * bimodalSegmentaion(int T);
    Image * histogramEqualization(int * newlut);

    // Contrast
    Image * gammaCorrection(double r);
    Image * contrastStretching();

    // Segmentation
    Image * kmeans(int clusters,
                   int iterations);

    // Filters
    Image * meanFilter(int kernelSize);
    Image * convolutionFilter(int ** kernel,
                              int    kernelSize);
    int ** createKernelFilter(int * vectorKerneli,
                              int * vectorKernelj,
                              int   kernelSize);
    Image * gaussianaFilter(int kernelSize);
    Image * noiseCleaningPixel(int delta);
    Image * noiseCleaningLine(double delta);

    // Edge Detection
    Image * edgeDetectionSobel(int position);
    Image * edgeDetectorCanny(int thresholdHigh,
                              int thresholdsDown);

    // Morphological Operation
    Image * dilateOperation(int ** matrixStructuringElement,
                            int    origenX,
                            int    origenY,
                            int    heightS,
                            int    widthS);
    Image * erosionOperation(int ** matrixStructuringElement,
                             int    origenX,
                             int    origenY,
                             int    heightS,
                             int    widthS);
    Image * openingOperation(int ** matrixStructuringElement,
                             int    origenX,
                             int    origenY,
                             int    heightS,
                             int    widthS);
    Image * closingOperation(int ** matrixStructuringElement,
                             int    origenX,
                             int    origenY,
                             int    heightS,
                             int    widthS);
    // Getters
    int *** getMatrix();

    // export
    void saveImage(QString filename);

private:

    int discretDegree(double value);
    void nonMaximumSuppression(double ** edgeNonMaximumSuppression,
                               int **    gradientOrientationDiscret,
                               double ** gradientMagnitude);
    void hysteresis(int **    edgeHysteresis,
                    double ** edgeNonMaximumSuppression,
                    int **    gradientDegreeDiscret,
                    int       thresholdHigh,
                    int       thresholdsDown);
    int edgeFollow(int       posX,
                   int       posY,
                   int **    edgeHysteresis,
                   double ** edgeNonMaximumSuppression,
                   int **    gradientDegreeDiscret,
                   int       thresholdsDown);
    int ** matrixMorphological(int ** matrixImagen,
                               int ** matrixStructuringElement,
                               int    origenX,
                               int    origenY,
                               int    heightS,
                               int    widthS,
                               int    option);

};

#endif // IMAGENPGM_H
