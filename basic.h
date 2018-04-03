#ifndef BASIC_H
#define BASIC_H


#include <math.h>
#include <qglobal.h>
#include <stdlib.h>
//using namespace std;


class Basic
{
    public:
        Basic();

        int ** createKernelFilter(int * vectorKerneli,
                                  int * vectorKernelj,
                                  int   kernelSize);
        int ** applyKernel(int     height,
                           int     width,
                           int *** matrixImagenP,
                           int **  kernel,
                           int     kernelSizeX,
                           int     kernelSizeY);
        void applyKerneltoPixel(int *** matrixImagenP,
                                int     i,
                                int     j,
                                int **  kernel,
                                int     kernelSizeX,
                                int     kernelSizeY,
                                int **  matrix);
};

#endif // BASIC_H
