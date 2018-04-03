#include "basic.h"

Basic::Basic()
{

}
int ** Basic::createKernelFilter(int * vectorKerneli,
                                 int * vectorKernelj,
                                 int   kernelSize)
{
    int ** kernel = new int *[kernelSize];

    for (int i = 0; i < kernelSize; ++i)
    {
        kernel[i] = new int[kernelSize];
    }

    for (int i = 0; i < kernelSize; ++i)
    {
        for (int j = 0; j < kernelSize; ++j)
        {
            kernel[i][j] = vectorKerneli[i] * vectorKernelj[j];
        }
    }

    return kernel;
}

int ** Basic::applyKernel(int     height,
                          int     width,
                          int *** matrixImagenP,
                          int **  kernel,
                          int     kernelSizeX,
                          int     kernelSizeY)
{
    int ** resultMatrix = new int *[height];

    for (int i = 0; i < height; ++i)
    {
        resultMatrix[i] = new int[width];
    }

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            resultMatrix[i][j] = *matrixImagenP[i][j];
        }
    }

    int inicial_position = floor(kernelSizeX / 2);

    for (int i = inicial_position; i < height - inicial_position; ++i)
    {
        for (int j = inicial_position; j < width - inicial_position; ++j)
        {
            applyKerneltoPixel(matrixImagenP, i, j, kernel, kernelSizeX, kernelSizeY, resultMatrix);
        }
    }

    // ImagenPGM *imageResult = new ImagenPGM (height, width, colorDepth, resultMatrix);

    /*
     *       for (int i = 0; i < height; ++i) {
     *           delete resultMatrix[i];
     *           resultMatrix[i]=0;
     *       }
     *
     *   delete resultMatrix;
     *   resultMatrix=0;
     */

    // return imageResult;
    return resultMatrix;
}

void Basic::applyKerneltoPixel(int *** matrixImagenP,
                               int     i,
                               int     j,
                               int **  kernel,
                               int     kernelSizeX,
                               int     kernelSizeY,
                               int **  matrix)
{
    int ii       = 0,
        jj       = 0,
        newPixel = 0,
        div      = 0;

    for (int x = 0; x < kernelSizeX; ++x)
    {
        ii = (floor(kernelSizeX / 2) * -1) + x + i;

        for (int y = 0; y < kernelSizeY; ++y)
        {
            jj       = (floor(kernelSizeY / 2) * -1) + y + j;
            newPixel += *matrixImagenP[ii][jj] * kernel[x][y];
            div      += abs(kernel[x][y]);

            // QTextStream (stdout) <<"newPixel: "<<newPixel;
        }
    }

    int cond = qRound(newPixel / div);

    if ((cond >= 0) && (cond < 256))
    {
        matrix[i][j] = cond;
    }
    else if (cond < 0)
    {
        matrix[i][j] = 0;
    }
    else
    {
        matrix[i][j] = 255;
    }
}
