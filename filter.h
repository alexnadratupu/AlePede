#ifndef FILTER_H
#define FILTER_H

#include "image.h"
#include "basic.h"
class Filter : public Basic
{
public:
    Filter();

    Image * meanFilter(Image * img,
                       int     kernelSize);
    Image * convolutionFilter(Image * img,
                              int **  kernel,
                              int     kernelSize);
    Image * gaussianaFilter(Image * img,
                            int     kernelSize);
    Image * noiseCleaningPixel(Image * img,
                               int     delta);
    Image * noiseCleaningLine(Image * img,
                              int     delta);


};

#endif // FILTER_H
