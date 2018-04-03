#ifndef EDGEDETECTOR_H
#define EDGEDETECTOR_H


#include "basic.h"
#include "image.h"
#include "imagenpgm.h"

#define PI 3.14159265
class EdgeDetector:
    public Basic
{
    public:
        EdgeDetector();

        Image * edgeDetectionSobel(Image * img,
                                   int     position,
                                   int     umbral);
        Image * edgeDetectorCanny(Image * img,
                                  int     thresholdHigh,
                                  int     thresholdsDown);

    private:
        int discretDegree(double value);
        void nonMaximumSuppression();
        void hysteresis(int thresholdHigh,
                        int thresholdsDown);
        int edgeFollow(int posX,
                       int posY,
                       int thresholdsDown);

        int       height;
        int       width;
        int       colorDepth;
        int ***   matrixImagenP;
        double ** gradientMagnitude;
        int **    gradientDegreeDiscret;
        double ** edgeNonMaximumSuppression;
        int **    edgeHysteresis;
};

#endif // EDGEDETECTOR_H
