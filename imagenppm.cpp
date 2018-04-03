#include "imagenppm.h"

ImagenPPM::ImagenPPM(QString filename)
{
    ImageFile imageFile(filename);

    if (imageFile.readFile())
    {
        this -> identification = imageFile.getId();
        this -> width          = imageFile.getWidth();
        this -> height         = imageFile.getHeight();
        this -> colorDepth     = imageFile.getColorDepth();
        this -> imageType      = "PPM";

        int * matrix = imageFile.getMatrix();

        matrixRp = new int **[height];
        matrixGp = new int **[height];
        matrixBp = new int **[height];

        for (int i = 0; i < height; i++)
        {
            matrixRp[i] = new int *[width];
            matrixGp[i] = new int *[width];
            matrixBp[i] = new int *[width];
        }

        // Lookup Table
        lutR = new int[colorDepth + 1];
        lutG = new int[colorDepth + 1];
        lutB = new int[colorDepth + 1];

        for (int i = 0; i < colorDepth + 1; ++i)
        {
            lutR[i] = i;
            lutG[i] = i;
            lutB[i] = i;
        }

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                matrixRp[i][j] = &lutR[matrix[(i * width * 3) + (j * 3)]];
                matrixGp[i][j] = &lutG[matrix[(i * width * 3) + (j * 3) + 1]];
                matrixBp[i][j] = &lutB[matrix[(i * width * 3) + (j * 3) + 2]];
            }
        }

        generateHistogram();
        generateQImage();

        status = true;
    }
    else
    {
        status = false;
    }
}

ImagenPPM::ImagenPPM(QString id,
                     int     h,
                     int     w,
                     int     depth,
                     int **  matrizR,
                     int **  matrizG,
                     int **  matrizB)
{
    this -> identification = id;
    this -> height         = h;
    this -> width          = w;
    this -> colorDepth     = depth;
    this -> imageType      = "PPM";
    this -> status         = true;

    // Lookup Table
    lutR = new int[colorDepth + 1];
    lutG = new int[colorDepth + 1];
    lutB = new int[colorDepth + 1];

    for (int i = 0; i < colorDepth + 1; ++i)
    {
        lutR[i] = i;
        lutG[i] = i;
        lutB[i] = i;
    }

    // Matriz Inicialization:
    matrixRp = new int **[height];
    matrixGp = new int **[height];
    matrixBp = new int **[height];

    for (int i = 0; i < height; i++)
    {
        matrixRp[i] = new int *[width];
        matrixGp[i] = new int *[width];
        matrixBp[i] = new int *[width];
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            matrixRp[i][j] = &lutR[matrizR[i][j]];
            matrixGp[i][j] = &lutG[matrizG[i][j]];
            matrixBp[i][j] = &lutB[matrizB[i][j]];
        }
    }

    generateHistogram();
    generateQImage();
}

ImagenPPM::ImagenPPM(QString id,
                     int     h,
                     int     w,
                     int     colorD,
                     int *** matrizR,
                     int *   lutR,
                     int *** matrizG,
                     int *   lutG,
                     int *** matrizB,
                     int *   lutB)
{
    this -> identification = id;
    this -> width          = w;
    this -> height         = h;
    this -> colorDepth     = colorD;
    this -> imageType      = "PPM";
    this -> status         = true;

    // Lookup Table
    this -> lutR = new int[colorDepth + 1];
    this -> lutG = new int[colorDepth + 1];
    this -> lutB = new int[colorDepth + 1];

    for (int i = 0; i < colorDepth + 1; ++i)
    {
        this -> lutR[i] = i;
        this -> lutG[i] = i;
        this -> lutB[i] = i;
    }

    // Matrix of Pointers
    matrixRp = new int **[height];
    matrixGp = new int **[height];
    matrixBp = new int **[height];

    for (int i = 0; i < height; i++)
    {
        matrixRp[i] = new int *[width];
        matrixGp[i] = new int *[width];
        matrixBp[i] = new int *[width];
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            matrixRp[i][j] = &this -> lutR[*matrizR[i][j]];
            matrixGp[i][j] = &this -> lutG[*matrizG[i][j]];
            matrixBp[i][j] = &this -> lutB[*matrizB[i][j]];
        }
    }

    generateHistogram();
    generateQImage();
}

ImagenPPM::~ImagenPPM()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            matrixRp[i][j] = 0;
            matrixGp[i][j] = 0;
            matrixBp[i][j] = 0;
        }

        delete matrixRp[i];

        matrixRp[i] = 0;

        delete matrixGp[i];

        matrixGp[i] = 0;

        delete matrixBp[i];

        matrixBp[i] = 0;
    }

    delete matrixRp;
    this -> matrixRp = 0;

    delete matrixRp;
    this -> matrixRp = 0;

    delete matrixRp;
    this -> matrixRp = 0;

    delete lutR;
    this -> lutR = 0;

    delete lutG;
    this -> lutG = 0;

    delete lutB;
    this -> lutB = 0;
}

// Image processing
Image * ImagenPPM::changeSize(int factor)
{
    int    newwidth  = 0,
           newheight = 0;
    int ** enlargedR, **enlargedG, **enlargedB;

    ImagenPPM * imageResized;

    if (factor > 0)
    {
        newwidth  = this -> width * factor;
        newheight = this -> height * factor;

        // Initialization
        enlargedR = new int *[newheight];
        enlargedG = new int *[newheight];
        enlargedB = new int *[newheight];

        for (int i = 0; i < newheight; i++)
        {
            enlargedR[i] = new int[newwidth];
            enlargedG[i] = new int[newwidth];
            enlargedB[i] = new int[newwidth];
        }

        // Proceso de reduccion
        for (int i = 0; i < newheight; ++i)
        {
            for (int j = 0; j < newwidth; ++j)
            {
                enlargedR[i][j] = *(matrixRp[(int) floor(i / factor)][(int) floor(j / factor)]);
                enlargedG[i][j] = *(matrixGp[(int) floor(i / factor)][(int) floor(j / factor)]);
                enlargedB[i][j] = *(matrixBp[(int) floor(i / factor)][(int) floor(j / factor)]);
            }
        }

        imageResized = new ImagenPPM(identification, newwidth, newheight, colorDepth, enlargedR, enlargedG, enlargedB);

        // Elimination
        for (int i = 0; i < newheight; i++)
        {
            delete enlargedR[i];
            delete enlargedG[i];
            delete enlargedB[i];
        }

        delete enlargedR;
        delete enlargedG;
        delete enlargedB;
    }
    else
    {
        factor    *= -1;
        newwidth  = (int) ceil(this -> width / factor);
        newheight = (int) ceil(this -> height / factor);

        // Initialization
        enlargedR = new int *[newheight];
        enlargedG = new int *[newheight];
        enlargedB = new int *[newheight];

        for (int i = 0; i < newheight; i++)
        {
            enlargedR[i] = new int[newwidth];
            enlargedG[i] = new int[newwidth];
            enlargedB[i] = new int[newwidth];
        }

        // Proceso de reduccion
        for (int i = 0; i < newheight; i++)
        {
            for (int j = 0; j < newwidth; j++)
            {
                enlargedR[i][j] = *(matrixRp[i * factor][j * factor]);
                enlargedG[i][j] = *(matrixGp[i * factor][j * factor]);
                enlargedB[i][j] = *(matrixBp[i * factor][j * factor]);
            }
        }

        imageResized = new ImagenPPM(identification, newwidth, newheight, colorDepth, enlargedR, enlargedG, enlargedB);

        // Elimination
        for (int i = 0; i < newheight; i++)
        {
            delete enlargedR[i];
            delete enlargedG[i];
            delete enlargedB[i];
        }

        delete enlargedR;
        delete enlargedG;
        delete enlargedB;
    }

    return imageResized;
}

Image * ImagenPPM::changeColorDepth(int bits)
{
    double newColorDepth = (int) (pow(2, bits) - 1);
    double auxR, auxG, auxB;

    for (int i = 0; i < colorDepth + 1; i++)
    {
        auxR    = qRound((newColorDepth / colorDepth) * lutR[i]);
        auxG    = qRound((newColorDepth / colorDepth) * lutG[i]);
        auxB    = qRound((newColorDepth / colorDepth) * lutB[i]);
        lutR[i] = auxR;
        lutG[i] = auxG;
        lutB[i] = auxB;
    }

    return new ImagenPPM(identification, height, width, newColorDepth, matrixRp, lutR, matrixGp, lutG, matrixBp, lutB);
}

ImagenPGM * ImagenPPM::convertToGrayScale(int method)
{
    ImagenPGM * result;

    int ** grayScaleMatrix = new int *[height];

    for (int i = 0; i < height; i++)
    {
        grayScaleMatrix[i] = new int[width];
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (method == 16384)
            {
                grayScaleMatrix[i][j] = (int) (0.299 * matrixRp[i][j][0] + 0.587 * matrixGp[i][j][0]
                                               + 0.114 * matrixBp[i][j][0]);
            }
            else
            {
                grayScaleMatrix[i][j] = (int) (0.33 * matrixRp[i][j][0] + 0.33 * matrixGp[i][j][0]
                                               + 0.33 * matrixBp[i][j][0]);
            }
        }
    }

    result = new ImagenPGM(height, width, colorDepth, grayScaleMatrix);

    for (int i = 0; i < height; i++)
    {
        delete grayScaleMatrix[i];
    }

    delete grayScaleMatrix;

    return result;
}

// GUI Display
void ImagenPPM::generateQImage()
{
    qImage = new QImage(width, height, QImage::Format_RGB32);

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            qImage -> setPixel(j, i, qRgb(floor((255/colorDepth)*(*matrixRp[i][j])),
                                          floor((255/colorDepth)*(*matrixGp[i][j])),
                                          floor((255/colorDepth)*(*matrixBp[i][j]))));
        }
    }
}

// Histogram
void ImagenPPM::generateHistogram()
{
    int ** matrix = new int *[height];

    for (int i = 0; i < height; i++)
    {
        matrix[i] = new int[width];
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            matrix[i][j] = (int) (0.33 * matrixRp[i][j][0] + 0.33 * matrixGp[i][j][0] + 0.33 * matrixBp[i][j][0]);
        }
    }

    histogram = new Histogram(height, width, colorDepth, matrix);
}

// export
void ImagenPPM::saveImage(QString filename)
{
    if (!filename.contains(".ppm"))
    {
        filename = filename + ".ppm";
    }

    ofstream fSalida(filename.toStdString().c_str(), ios::out | ios::binary);

    if (!identification.compare("P3"))
    {
        fSalida << identification.toStdString() << endl;
        fSalida << "#LEARNING IMAGE PROCESSING AT UNIVALLE" << endl;
        fSalida << width << " " << height << endl;
        fSalida << colorDepth << endl;

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                fSalida << *(matrixRp[i][j]) << " " << *(matrixGp[i][j]) << " " << *(matrixBp[i][j]) << "    ";
            }

            fSalida << endl;
        }
    }
    else if (!identification.compare("P6"))
    {
        fSalida << identification.toStdString() << endl;
        fSalida << "#LEARNING IMAGE PROCESSING AT UNIVALLE" << endl;
        fSalida << width << " " << height << endl;
        fSalida << colorDepth << endl;

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                fSalida.put((unsigned char) *matrixRp[i][j]);
                fSalida.put((unsigned char) *matrixGp[i][j]);
                fSalida.put((unsigned char) *matrixBp[i][j]);
            }
        }
    }

    fSalida.close();

    /*
     * QFile temp(filename);
     * if(temp.open(QFile::WriteOnly)){
     *   QTextStream fSalida(&temp);
     *
     *   fSalida<<identification<<endl;
     *   fSalida<<"#LEARNING IMAGE PROCESSING AT UNIVALLE"<<endl;
     *   fSalida<<width<<" "<<height<<endl;
     *   fSalida<<colorDepth<<endl;
     *
     *   for(int i=0; i<height; i++){
     *       for(int j=0; j<width; j++){
     *           fSalida<<*(matrixRp[i][j])<<" "<<*(matrixGp[i][j])<<" "<<*(matrixBp[i][j])<<"    ";
     *       }
     *       fSalida<<endl;
     *   }
     * }
     */
}

int *** ImagenPPM::getMatrizR()
{
    return matrixRp;
}

int *** ImagenPPM::getMatrizG()
{
    return matrixGp;
}

int *** ImagenPPM::getMatrizB()
{
    return matrixBp;
}
