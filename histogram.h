#ifndef HISTOGRAM_H
#define HISTOGRAM_H


#include <QImage>
#include "math.h"

class Histogram
{
    public:
        Histogram(int    height,
                  int    width,
                  int    colorD,
                  int ** matrix);

        ~Histogram();

        int ThresholdingByIsodata();
        int ThresholdingByOtsu();
        int ThresholdingByTwoPeaks();
        int * calculateEqualization();

        // Getters
        QImage * getHistogram();
        double * getColorFrequency();

    private:
        double * colorFrequency;
        int **   matrizHistograma;
        int      intensidad;
        double   u1, u2, w1, w2, n;
        QImage * qImage;

        void generateMatrix();
        double findMaxFrecuency();
        void calculatePromedio();
};

#endif // HISTOGRAM_H
