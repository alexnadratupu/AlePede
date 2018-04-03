#include "imagefile.h"

ImageFile::ImageFile(QString filename):
    QFile(filename)
{
    supportedFormats << "ppm" << "pgm";
}

bool ImageFile::readFile()
{
    // Se asigna el resultado de leer la imagen PGM o PPM ya sea P2,P5 o P3,P6 respectivamente
    bool state = readFileImage();

    return state;

    /*
     * if(supportedFormats.contains(fileName().section(".",-1))){
     *
     *   if (this->open(QIODevice::ReadOnly)){
     *
     *       QTextStream lector(this);
     *       while (!lector.atEnd())
     *       {
     *           QString line = lector.readLine();
     *           if(!line.startsWith("#")){
     *               lectura<<line;
     *           }
     *       }
     *       readingProcess();
     *       return true; //ojo cambiar ahora
     *   }
     *   else{
     *       return false;
     *   }
     * }else{
     *   return false;
     * }
     */
}

void ImageFile::readingProcess()
{
    this -> id = lectura.at(0);

    // Habia problemas con varios espacios entre los valores de ancho y alto ejemplo: 250    250, generan fallo de segmentacion
    QStringList lineSplit = lectura.at(1).split(QRegExp("\\s+"));
    this -> width         = lineSplit.at(0).toInt();
    this -> height        = lineSplit.at(1).toInt();
    this -> colorDepth    = lectura.at(2).toInt();

    if (id == "P2")
    {
        this -> matrix = new int[width * height];
    }
    else
    {
        this -> matrix = new int[3 * width * height];
    }

    int i = 0;

    for (int z = 3; z < lectura.length(); ++z)
    {
        lineSplit = lectura.at(z).split(QRegExp("\\s+"));

        foreach(QString pixel, lineSplit)
        {
            if (!pixel.isEmpty())
            {
                matrix[i] = (pixel + "     ").toInt();

                i++;
            }
        }
    }
}

void ImageFile::printImageContents()
{
    QTextStream cout(stdout);

    for (int i = 0; i < lectura.size(); i++)
    {
        cout << lectura.at(i) << endl;
    }
}

QList<QString> ImageFile::getImageContents()
{
    return lectura;
}

// GETTERS
QString ImageFile::getId()
{
    return this -> id;
}

int ImageFile::getWidth()
{
    return this -> width;
}

int ImageFile::getHeight()
{
    return this -> height;
}

int ImageFile::getColorDepth()
{
    return this -> colorDepth;
}

int * ImageFile::getMatrix()
{
    return this -> matrix;
}

bool ImageFile::readFileImage()
{
    string path = fileName().toStdString();

    ifstream imageIn(path.c_str(), ios::binary);

    string content;
    int    count = 0;

    if (!imageIn.is_open())
    {
        cerr << "Error: ¡La imagen no existe o no pudo ser cargada!" << endl;

        return false;
    }

    while (count < 4)
    {
        imageIn >> content;

        if (content.substr(0, 1).compare("#"))
        {                                 // Si la linea no es un comentario se guardan los datos
            if (count == 0)
            {
                if (content.compare("P2") && content.compare("P3") && content.compare("P5") && content.compare("P6"))
                {
                    cerr << "Error: ¡La imagen no es de tipo PGM " << content << endl;

                    return false;
                }
                else
                {
                    QString temp(content.c_str());

                    this -> id = temp;
                }
            }

            if (count == 1)
            {
                this -> width = atoi(content.c_str());
            }

            if (count == 2)
            {
                this -> height = atoi(content.c_str());
            }

            if (count == 3)
            {
                this -> colorDepth = atoi(content.c_str());
            }

            count++;
        }
        else
        {
            getline(imageIn, content);    // Si es un comentario se descarta el resto de linea
        }
    }

    if (!this -> id.compare("P2"))
    {    // Si la imagen es en escala de grises
        // Inicializamos el valor para la matrix
        this -> matrix = new int[width * height];

        for (int i = 0; i < this -> height; i++)
        {            // Hasta que se haya llenado la matriz Y
            for (int j = 0; j < this -> width; j++)
            {
                imageIn >> content;

                if (content.substr(0, 1).compare("#"))
                {    // Si la linea no es un comentario se guardan los datos
                    int value = atoi(content.c_str());

                    // Falta validar si es un pixel valido USAR CLASE EXCEPTION IMAGE FALTA***
                    matrix[(i * width) + j] = value;
                }
                else
                {
                    getline(imageIn, content);
                    i--;
                }    // Si es un comentario se descarta el resto de linea
            }
        }

        // cout << "Bien: ¡La imagen se leyo correctamente" << endl;
    }
    else if (!this -> id.compare("P3"))
    {                // Si la imagen es a color
        // Se le dan tamaño a las matrices RGB
        this -> matrix = new int[3 * width * height];

        int count = 0;

        for (int i = 0; i < this -> height; i++)
        {
            for (int j = 0; j < this -> width; j++)
            {
                if (content.substr(0, 1).compare("#"))
                {    // Si la linea no es un comentario se guardan los datos
                    // Falta validar si es un pixel valido USAR CLASE EXCEPTION IMAGE FALTA***
                    int value;

                    imageIn >> content;    // R

                    value         = atoi(content.c_str());
                    matrix[count] = value;

                    count++;

                    imageIn >> content;    // G

                    value         = atoi(content.c_str());
                    matrix[count] = value;

                    count++;

                    imageIn >> content;    // B

                    value         = atoi(content.c_str());
                    matrix[count] = value;

                    count++;
                }
                else
                {
                    getline(imageIn, content);
                    i--;
                }                          // Si es un comentario se descarta el resto de linea
            }
        }

        // cout << "Bien: ¡La imagen se leyo correctamente" << endl;
    }
    else if (!this -> id.compare("P5"))
    {
        // Inicializamos el valor para la matrix
        this -> matrix = new int[width * height];

        int val = 0;

        for (int i = 0; i < this -> height; i++)
        {
            for (int j = 0; j < this -> width; j++)
            {
                val                     = imageIn.get();
                matrix[(i * width) + j] = val;
            }
        }

        // cout << "Bien: ¡La imagen se leyo correctamente " << this->id.toStdString()<< endl;
    }
    else if (!this -> id.compare("P6"))
    {
        // Inicializamos el valor para la matrix
        this -> matrix = new int[3 * width * height];

        int val   = 0;
        int count = 0;

        imageIn.get();

        for (int i = 0; i < this -> height; i++)
        {
            for (int j = 0; j < this -> width; j++)
            {
                val           = imageIn.get();    // (int)charImage[i*this->width+j];
                matrix[count] = val;

                count++;

                val           = imageIn.get();
                matrix[count] = val;

                count++;

                val           = imageIn.get();
                matrix[count] = val;

                count++;
            }
        }

        // cout << "Bien: ¡La imagen se leyo correctamente p6" << this->id.toStdString()<< endl;
    }

    imageIn.close();

    return true;
}
