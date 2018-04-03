#include "histogram.h"

Histogram::Histogram(int    height,
                     int    width,
                     int    colorD,
                     int ** matrix)
{
    int nColumnas = width;
    int nFilas    = height;

    intensidad     = colorD + 1;
    colorFrequency = new double[intensidad];

    for (int i = 0; i < intensidad; i++)
    {
        colorFrequency[i] = 0;
    }

    for (int i = 0; i < nFilas; i++)
    {
        for (int j = 0; j < nColumnas; j++)
        {
            colorFrequency[matrix[i][j]]++;
        }
    }

    generateMatrix();
}

Histogram::~Histogram()
{
    for (int i = 0; i < intensidad; i++)
    {
        delete matrizHistograma[i];

        matrizHistograma[i] = 0;
    }

    delete matrizHistograma;

    matrizHistograma = 0;

    delete colorFrequency;

    colorFrequency = 0;
}

void Histogram::generateMatrix()
{
    matrizHistograma = new int *[intensidad];

    for (int i = 0; i < intensidad; i++)
    {
        matrizHistograma[i] = new int[intensidad];
    }

    double maxFreq = findMaxFrecuency();

    for (int i = 0; i < intensidad; i++)
    {
        for (int j = 0; j < intensidad; j++)
        {
            if (intensidad - i <= ((colorFrequency[j] * intensidad) / maxFreq))
            {
                matrizHistograma[i][j] = 0;
            }
            else
            {
                matrizHistograma[i][j] = 255;
            }
        }
    }
}

int Histogram::ThresholdingByTwoPeaks()
{
    int max1  = 0;
    int max2  = 0;
    int temp1 = 0;
    int temp2 = 0;

    // look first peak
    for (int i = 1; i < intensidad - 1; ++i)
    {
        if ((colorFrequency[i] > colorFrequency[i - 1]) && (colorFrequency[i] > colorFrequency[i + 1]))
        {
            if (colorFrequency[i] > colorFrequency[max1])
            {
                max1 = i;
            }
        }
    }

    // look second peak
    for (int i = 1; i < intensidad - 1; ++i)
    {
        if ((colorFrequency[i] > colorFrequency[i - 1]) && (colorFrequency[i] > colorFrequency[i + 1]))
        {
            temp1 = pow(max1 - i, 2) * colorFrequency[i];

            if (temp1 > temp2)
            {
                temp2 = temp1;
                max2  = i;
            }
        }
    }

    return (max1 + max2) / 2;
}

void Histogram::calculatePromedio()
{
    int threshold = ThresholdingByTwoPeaks();

    u1 = 0;
    u2 = 0;
    w1 = 0;
    w2 = 0;
    n  = 0;

    for (int i = 0; i < intensidad; ++i)
    {
        if (colorFrequency[i] != 0)
        {
            n += colorFrequency[i];
        }
    }

    for (int i = 0; i < intensidad; ++i)
    {
        if (colorFrequency[i] != 0)
        {
            if (i <= threshold)
            {
                w1 += colorFrequency[i] / n;
            }
            else
            {
                w2 += colorFrequency[i] / n;
            }
        }
    }

    for (int i = 0; i < intensidad; ++i)
    {
        if (colorFrequency[i] != 0)
        {
            if (i <= threshold)
            {
                u1 += (i * (colorFrequency[i] / n)) / w1;
            }
            else
            {
                u2 += (i * (colorFrequency[i] / n)) / w2;
            }
        }
    }
}

int Histogram::ThresholdingByIsodata()
{
    calculatePromedio();

    return ((int) (u1 + u2) / 2);
}

int Histogram::ThresholdingByOtsu()
{
    calculatePromedio();

    double uc = (w1 * u1) + (w2 * u2);

    return ((int) uc);
}

double Histogram::findMaxFrecuency()
{
    QList<double> frequencies;

    for (int i = 0; i < intensidad; i++)
    {
        frequencies.append(colorFrequency[i]);
    }

    qSort(frequencies.begin(), frequencies.end());

    return frequencies.last();
}

int * Histogram::calculateEqualization()
{
    int      a  = 0;
    int *    discretizedFrecuency = new int[intensidad];
    double * relativeEqualization = new double[intensidad];

    for (int i = 0; i < intensidad; i++)
    {
        discretizedFrecuency[i] = 0;
        relativeEqualization[i] = 0;
    }

    relativeEqualization[0] = colorFrequency[0];

    for (int i = 1; i < intensidad; ++i)
    {
        relativeEqualization[i] += relativeEqualization[i - 1] + colorFrequency[i];
    }

    a = relativeEqualization[intensidad - 1];

    for (int i = 0; i < intensidad; ++i)
    {
        discretizedFrecuency[i] = qRound(((intensidad - 1) * relativeEqualization[i]) / a);
    }

    delete relativeEqualization;

    relativeEqualization = 0;

    return discretizedFrecuency;
}

QImage * Histogram::getHistogram()
{
    qImage = new QImage(intensidad, intensidad, QImage::Format_RGB32);

    for (int i = 0; i < intensidad; ++i)
    {
        for (int j = 0; j < intensidad; ++j)
        {
            qImage -> setPixel(j, i, qRgb(matrizHistograma[i][j], matrizHistograma[i][j], matrizHistograma[i][j]));
        }
    }

    return qImage;
}

double * Histogram::getColorFrequency()
{
    return this -> colorFrequency;
}

