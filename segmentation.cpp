#include "segmentation.h"

#include <QDebug>

#define eps 1.0E-3
Segmentation::Segmentation()
{
}

Image * Segmentation::kmeansPPM(Image * img,
                                int     clusters)
{
    // Calcular el valor de los centroides iniciales de manera aleatoria
    // Se recorre la imagen y se agrupa en el un cluster(grupo) dependiendo del centroide al que mas cercano esten
    // Se calcula el centroide para cada grupo y se tienen presentes los centroides anteriores
    // Se calcula el error es decir la diferencia existente entre los centroides viejos y los nuevos
    color centroid[clusters];
    color oldCentroid[clusters];

    int width      = static_cast<ImagenPPM *>(img) -> getWidth();
    int height     = static_cast<ImagenPPM *>(img) -> getHeight();
    int colorDepth = static_cast<ImagenPPM *>(img) -> getColorDepth();

    srand(time(NULL));

    for (int i = 0; i < clusters; i++)
    {
        int x = rand() % (height - 1);
        int y = rand() % (width - 1);

        centroid[i]      = getColor(img, x, y);
        oldCentroid[i].r = 0;
        oldCentroid[i].b = 0;
        oldCentroid[i].g = 0;

        qDebug() << centroid[i].r;
    }

    int    label;
    int    temp;
    int    dist = 100000;
    double red[clusters];
    double green[clusters];
    double blue[clusters];
    int    count[clusters];
    int    labeled[height][width];    // matriz de clasificacion
    color  tcolor;
    bool   continuar = true;

    while (continuar)
    {
        for (int i = 0; i < clusters; i++)
        {
            red[i]   = 0;
            green[i] = 0;
            blue[i]  = 0;
            count[i] = 0;
        }

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                tcolor = getColor(img, i, j);
                dist   = distanceColor(centroid[0], tcolor);
                label  = 0;

                for (int k = 1; k < clusters; k++)
                {
                    temp = distanceColor(centroid[k], tcolor);

                    if (temp < dist)
                    {
                        dist  = temp;
                        label = k;
                    }
                }

                count[label]++;

                red[label]   += tcolor.r;
                green[label] += tcolor.g;
                blue[label]  += tcolor.b;

                if (equalsColor(centroid, oldCentroid, clusters))
                {
                    labeled[i][j] = label;
                    continuar     = false;
                }
            }
        }

        // actualizar centroides
        for (int i = 0; i < clusters; i++)
        {
            oldCentroid[i].r = centroid[i].r;
            oldCentroid[i].g = centroid[i].g;
            oldCentroid[i].b = centroid[i].b;

            if (count[i] == 0)
            {
                continue;    // no actualizar centroide si no se hay colores que promediar
            }

            centroid[i].r = (int) (red[i] / count[i]);
            centroid[i].g = (int) (green[i] / count[i]);
            centroid[i].b = (int) (blue[i] / count[i]);
        }
    }

    int ** kmeansMatrixR = new int *[height];
    int ** kmeansMatrixG = new int *[height];
    int ** kmeansMatrixB = new int *[height];

    for (int i = 0; i < height; i++)
    {
        kmeansMatrixR[i] = new int[width];
        kmeansMatrixG[i] = new int[width];
        kmeansMatrixB[i] = new int[width];
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            kmeansMatrixR[i][j] = centroid[labeled[i][j]].r;
            kmeansMatrixG[i][j] = centroid[labeled[i][j]].g;
            kmeansMatrixB[i][j] = centroid[labeled[i][j]].b;
        }
    }

    ImagenPPM * result = new ImagenPPM(QString("P3"), height, width, colorDepth, kmeansMatrixR, kmeansMatrixG,
                                       kmeansMatrixB);

    return result;
}

int Segmentation::distanceGray(int x,
                               int y)
{
    return sqrt((x - y) * (x - y));
}

bool Segmentation::equalsGray(int * centroid,
                              int * oldcentroid,
                              int   size)
{
    double total = 0;
    bool   equal = false;

    for (int i = 0; i < size; i++)
    {
        total += (centroid[i] - oldcentroid[i]) * (centroid[i] - oldcentroid[i]);
    }

    total = sqrt(total);

    if (total < eps)
    {
        equal = true;
    }

    return equal;
}

Image * Segmentation::kmeansPGM(Image * img,
                                int     clusters)
{
    // Calcular el valor de los centroides iniciales de manera aleatoria
    // Se recorre la imagen y se agrupa en el un cluster(grupo) dependiendo del centroide al que mas cercano esten
    // Se calcula el centroide para cada grupo y se tienen presentes los centroides anteriores
    // Se calcula el error es decir la diferencia existente entre los centroides viejos y los nuevos
    int     centroid[clusters];
    int     oldCentroid[clusters];
    int *** matrix     = static_cast<ImagenPGM *>(img) -> getMatrix();
    int     width      = static_cast<ImagenPGM *>(img) -> getWidth();
    int     height     = static_cast<ImagenPGM *>(img) -> getHeight();
    int     colorDepth = static_cast<ImagenPGM *>(img) -> getColorDepth();

    srand(time(NULL));

    for (int i = 0; i < clusters; i++)
    {
        int x = rand() % (height - 1);
        int y = rand() % (width - 1);

        centroid[i]    = *matrix[x][y];
        oldCentroid[i] = 0;
    }

    int    label;
    int    temp;
    int    dist = 100000;
    double grayScale[clusters];
    int    count[clusters];
    int    labeled[height][width];    // matriz de clasificacion
    int    tgray     = 0;
    bool   continuar = true;

    while (continuar)
    {
        for (int i = 0; i < clusters; i++)
        {
            grayScale[i] = 0;
            count[i]     = 0;
        }

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                tgray = *matrix[i][j];
                dist  = distanceGray(centroid[0], tgray);
                label = 0;

                for (int k = 1; k < clusters; k++)
                {
                    temp = distanceGray(centroid[k], tgray);

                    if (temp < dist)
                    {
                        dist  = temp;
                        label = k;
                    }
                }

                count[label]++;

                grayScale[label] += tgray;

                if (equalsGray(centroid, oldCentroid, clusters))
                {
                    labeled[i][j] = label;
                    continuar     = false;
                }
            }
        }

        // actualizar centroides
        for (int i = 0; i < clusters; i++)
        {
            oldCentroid[i] = centroid[i];

            if (count[i] == 0)
            {
                continue;    // no actualizar centroide si no se hay colores que promediar
            }

            centroid[i] = (int) (grayScale[i] / count[i]);
        }
    }

    int ** kmeansMatrix = new int *[height];

    for (int i = 0; i < height; i++)
    {
        kmeansMatrix[i] = new int[width];
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            kmeansMatrix[i][j] = centroid[labeled[i][j]];
        }
    }

    ImagenPGM * result = new ImagenPGM(height, width, colorDepth, kmeansMatrix);

    return result;
}

int Segmentation::distanceColor(color a,
                                color b)
{
    return sqrt((a.r - b.r) * (a.r - b.r) + (a.g - b.g) * (a.g - b.g) + (a.b - b.b) * (a.b - b.b));
}

bool Segmentation::equalsColor(color * centroid,
                               color * oldcentroid,
                               int     size)
{
    double total = 0;
    bool   equal = false;

    for (int i = 0; i < size; i++)
    {
        total += (centroid[i].r - oldcentroid[i].r) * (centroid[i].r - oldcentroid[i].r);
        total += (centroid[i].g - oldcentroid[i].g) * (centroid[i].g - oldcentroid[i].g);
        total += (centroid[i].b - oldcentroid[i].b) * (centroid[i].b - oldcentroid[i].b);
    }

    total = sqrt(total);

    if (total < eps)
    {
        equal = true;
    }

    return equal;
}

color Segmentation::getColor(Image * img,
                             int     x,
                             int     y)
{
    color   out;
    int *** matrixR = static_cast<ImagenPPM *>(img) -> getMatrizR();
    int *** matrixG = static_cast<ImagenPPM *>(img) -> getMatrizG();
    int *** matrixB = static_cast<ImagenPPM *>(img) -> getMatrizB();

    out.r = *matrixR[x][y];
    out.g = *matrixG[x][y];
    out.b = *matrixB[x][y];

    return out;
}

Image * Segmentation::removeCap(Image * img)
{
    int *** matrix     = static_cast<ImagenPGM *>(img) -> getMatrix();
    int     width      = static_cast<ImagenPGM *>(img) -> getWidth();
    int     height     = static_cast<ImagenPGM *>(img) -> getHeight();
    int     colorDepth = static_cast<ImagenPGM *>(img) -> getColorDepth();
    int     valueInit  = *matrix[0][0];
    int     change     = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int pixel = *matrix[i][j];

            if (pixel != valueInit)
            {
                while (pixel != valueInit)
                {
                    matrix[i][j + change] = &valueInit;

                    change++;

                    pixel = *matrix[i][j + change];
                }

                change = 0;

                break;
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = width - 1; j >= width / 2; j--)
        {
            int pixel = *matrix[i][j];

            if (pixel != valueInit)
            {
                while (pixel != valueInit)
                {
                    matrix[i][j - change] = &valueInit;

                    change++;

                    pixel = *matrix[i][j - change];
                }

                change = 0;

                break;
            }
        }
    }

    int ** removeCapMatrix = new int *[height];

    for (int i = 0; i < height; i++)
    {
        removeCapMatrix[i] = new int[width];
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            removeCapMatrix[i][j] = *matrix[i][j];
        }
    }

    ImagenPGM * result = new ImagenPGM(height, width, colorDepth, removeCapMatrix);

    return result;
}

Image * Segmentation::whiteTissue(Image * img)
{
    int *** matrix             = static_cast<ImagenPGM *>(img) -> getMatrix();
    int     width              = static_cast<ImagenPGM *>(img) -> getWidth();
    int     height             = static_cast<ImagenPGM *>(img) -> getHeight();
    int     colorDepth         = static_cast<ImagenPGM *>(img) -> getColorDepth();
    int     valueInit          = *matrix[0][0];
    int **  whiteTissuepMatrix = new int *[height];

    for (int i = 0; i < height; i++)
    {
        whiteTissuepMatrix[i] = new int[width];
    }

    // Para segmentar materia gris recorremos lo de kmeans y el color de fondo lo volvemos blanco.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (*matrix[i][j] != valueInit)
            {
                matrix[i][j] = &colorDepth;
            }
        }
    }

    valueInit = *matrix[0][0];

    for (int i = 0; i < height; i++)
    {
        for (int j = width - 1; j >= width / 2; j--)
        {
            int pixel = *matrix[i][j];

            if (pixel != valueInit)
            {
                break;
            }

            matrix[i][j] = &colorDepth;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int pixel = *matrix[i][j];

            if (pixel != valueInit)
            {
                break;
            }

            matrix[i][j] = &colorDepth;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            whiteTissuepMatrix[i][j] = *matrix[i][j];
        }
    }

    ImagenPGM * result = new ImagenPGM(height, width, colorDepth, whiteTissuepMatrix);

    return result;
}

Image * Segmentation::grayTissue(Image * img)
{
    int *** matrix           = static_cast<ImagenPGM *>(img) -> getMatrix();
    int     width            = static_cast<ImagenPGM *>(img) -> getWidth();
    int     height           = static_cast<ImagenPGM *>(img) -> getHeight();
    int     colorDepth       = static_cast<ImagenPGM *>(img) -> getColorDepth();
    int     valueInit        = *matrix[0][0];
    int **  grayTissueMatrix = new int *[height];

    for (int i = 0; i < height; i++)
    {
        grayTissueMatrix[i] = new int[width];
    }

    // Para segmentar materia gris recorremos lo de kmeans y el color de fondo lo volvemos blanco.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (*matrix[i][j] == valueInit)
            {
                matrix[i][j] = &colorDepth;
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            grayTissueMatrix[i][j] = *matrix[i][j];
        }
    }

    ImagenPGM * result = new ImagenPGM(height, width, colorDepth, grayTissueMatrix);

    return result;
}
