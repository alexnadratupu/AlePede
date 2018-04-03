#include "edgedetector.h"

EdgeDetector::EdgeDetector()
{

}
Image * EdgeDetector::edgeDetectionSobel(Image *img, int position, int umbral)
{
    this->matrixImagenP = static_cast<ImagenPGM*>(img)->getMatrix();
    height=static_cast<ImagenPGM*>(img)->getHeight();
    width=static_cast<ImagenPGM*>(img)->getWidth();
    this->colorDepth=static_cast<ImagenPGM*>(img)->getColorDepth();

    return img;

}

/**
    El detector de bordes basado en Canny:
    * Primero se aplica un filtro gaussiano a la imagen.
    * (No implementado) calculo de los thresholds alto y bajo automaticamente (por ahora se piden estos valores)
    * Luego calculamos los componenetes X y Y del gradiente usando los operadores de Sobel.
      Se calcula la magnitud de dichos componentes y el grado o angulo que forman.
      La magnitud del gradiente deberia ser un double para que no se pierdan valores.
      El grado DEBE de ser un double para que este pueda luego ser discretizado en valores enteros y angulos precisos.
    * Se aplica Non Maximum Suppression a la magnitud del gradiente. Tambien deberia de ser double si la magnitud lo es.
    * Se aplica hysteresis a la matriz con el non maximum Suppression, usando dos thresholds y
      se sigue el borde solo tomando en cuenta el pixel que este 90° en contra de las manecillas del reloj.
      El resultado es 0 si es un borde y 1 si no es un borde;
*/
const double gX [3][3] ={{-1,-2,-1},{0,0,0},{1,2,1}} , gY [3][3]= {{-1,0,1},{-2,0,2},{-1,0,1}};
Image * EdgeDetector::edgeDetectorCanny(Image* img, int thresholdHigh, int thresholdsDown)
{
    this->matrixImagenP=static_cast<ImagenPGM*>(img)->getMatrix();
    height=static_cast<ImagenPGM*>(img)->getHeight();
    width=static_cast<ImagenPGM*>(img)->getWidth();

    //int** dx = new int*[height];
    //int** dy = new int*[height];
    gradientMagnitude = new double*[height];
    //double** gradientDegree = new double*[height];
    gradientDegreeDiscret = new int*[height];
    edgeNonMaximumSuppression = new double*[height];
    edgeHysteresis = new int*[height];
    for (int i = 0; i < height; ++i) {
        //dx[i] = new int[width];
        //dy[i] = new int[width];
        gradientMagnitude[i] = new double[width];
        //gradientDegree[i] = new double[width];
        gradientDegreeDiscret[i] = new int[width];
        edgeNonMaximumSuppression[i] = new double[width];
        edgeHysteresis[i] = new int[width];
        for (int j = 0; j < width; ++j) {
            /*resultMatrix[i][j]= dx[i][j] = dy[i][j]=*/gradientDegreeDiscret[i][j]=
                    *matrixImagenP[i][j];
            edgeNonMaximumSuppression[i][j]=gradientMagnitude[i][j]/*=gradientDegree[i][j]*/=(double)*matrixImagenP[i][j];
            edgeHysteresis[i][j]=1;
        }
    }

    /*********************************************/
    /*//Filtro Gaussiano
    //gaussianaFilter(1,1);
    //gaussianaFilter(1,5);
    //Calculo del Gradiente (magnitud y angulo)

    //Calculo de los componentes usando los operadores de sobel
    //Image *temp1 = this->edgeDetectionSobel(0);

    ImagenPGM* temp = (static_cast<ImagenPGM*>(temp1));
    int *** dx ;
    dx= (temp->getMatrix());
    int ** dx=*((ImagenPGM*)(edgeDetectionSobel(0)))->getMatrix();

    temp = (static_cast<ImagenPGM*>(this->edgeDetectionSobel(1)));
    int *** dy ;
    dy = (temp->getMatrix());
    QTextStream (stdout) <<" mag! " << endl << endl << endl << endl;*/

    //****Calculo de la magnitud y angulo del gradiente a partir de lso componentes
    for(int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if(i==0 || j==0 || i==height-1 || j==width-1){// si son los bordes de la imagen completa
                //dx[i][j]=0;
                //dy[i][j]=0;
                gradientMagnitude[i][j]=0;
                gradientDegreeDiscret[i][j]=0;
                //gradientDegree[i][j]=0;
                edgeNonMaximumSuppression[i][j]=0;
                edgeHysteresis[i][j]=1;
            }else{
                double valueX = 0, valueY = 0, degree;
                valueX += *matrixImagenP[i-1][j-1]*gX[0][0];
                valueY += *matrixImagenP[i-1][j-1]*gY[0][0];


                valueX += *matrixImagenP[i-1][j]*gX[0][1];
                valueY += *matrixImagenP[i-1][j]*gY[0][1];

                valueX += *matrixImagenP[i-1][j+1]*gX[0][2];
                valueY += *matrixImagenP[i-1][j+1]*gY[0][2];

                valueX += *matrixImagenP[i][j-1]*gX[1][0];
                valueY += *matrixImagenP[i][j-1]*gY[1][0];

                valueX += *matrixImagenP[i][j]*gX[1][1];
                valueY += *matrixImagenP[i][j]*gY[1][1];

                valueX += *matrixImagenP[i][j+1]*gX[1][2];
                valueY += *matrixImagenP[i][j+1]*gY[1][2];

                valueX += *matrixImagenP[i+1][j-1]*gX[2][0];
                valueY += *matrixImagenP[i+1][j-1]*gY[2][0];

                valueX += *matrixImagenP[i+1][j]*gX[2][1];
                valueY += *matrixImagenP[i+1][j]*gY[2][1];

                valueX += *matrixImagenP[i+1][j+1]*gX[2][2];
                valueY += *matrixImagenP[i+1][j+1]*gY[2][2];


                if(valueX==0){
                    if(valueY<0){
                        degree = -PI/2;
                    }else{
                        degree = PI/2;
                    }
                }else{
                    degree = atan((double)(valueY/valueX));
                    if(degree==-0){
                        degree= fabs(degree);
                    }
                }
                //dx[i][j]=valueX;
                //dy[i][j]=valueY;
                gradientMagnitude[i][j]=fabs(valueX)+fabs(valueY);
                //gradientDegree[i][j]=degree;//solo para guardar los valores reales
                gradientDegreeDiscret[i][j]=this->discretDegree(degree);

            }
        }
    }

    //Non Maximum Suppression
    nonMaximumSuppression();

    //hysteresis
    hysteresis(thresholdHigh, thresholdsDown);


    /*********************************************/
    ImagenPGM *imageResult = new ImagenPGM (height, width, 1, edgeHysteresis); //OJO SE CAMBIO EL NIVEL DEL COLOR

        for (int i = 0; i < height; ++i) {

            //delete dx[i];
            //dx[i]=0;
            //delete dy[i];
            //dy[i]=0;
            delete gradientMagnitude[i];
            gradientMagnitude[i]=0;
            //delete gradientDegree[i];
            //gradientDegree[i]=0;
            delete gradientDegreeDiscret[i];
            gradientDegreeDiscret[i]=0;
            delete edgeNonMaximumSuppression[i];
            edgeNonMaximumSuppression[i]=0;
            delete edgeHysteresis[i];
            edgeHysteresis[i]=0;

        }
    //delete dx;
    //dx=0;
    //delete dy;
    //dy=0;
    delete gradientMagnitude;
    gradientMagnitude=0;
    //delete gradientDegree;
    //gradientDegree=0;
    delete gradientDegreeDiscret;
    gradientDegreeDiscret=0;

    delete edgeNonMaximumSuppression;
    edgeNonMaximumSuppression=0;
    delete edgeHysteresis;
    edgeHysteresis=0;

    return imageResult;
}

/**
    Discretiza los valores del angulo para indicar los angulos posibles que son 8.
*/
int EdgeDetector::discretDegree(double value)
{
    double degree = (value + PI/2.0) * 180 / PI;

    if(degree<0 || degree > 180){
        QTextStream (stdout) <<"error discret degree! \n";

        //degree = 360 + degree;
    }

    if((degree>= 0 && degree <22.5) ||(degree>=157.5 && degree<=180)){
        return 0;
    }else if(degree>= 22.5 && degree <67.5){
        return 1;
    }else if(degree>= 67.5 && degree <112.5){
        return 2;
    }else if(degree>= 112.5 && degree <157.5){
        return 3;
    }

    //cerr << "no entro discret" << endl;
    return -1;
}
/**
    Se suprimen los valores que sean menores a los dos vecinos que indique la dirección del gradiente, de lo contrario se deja el valor de la magnitud
*/
void EdgeDetector::nonMaximumSuppression()
{
    for(int i = 0 ; i< height;i++ ){
        for(int j = 0 ; j< width;j++ ){

            int orientation = gradientDegreeDiscret[i][j];
            double valueGradient = gradientMagnitude[i][j];
            edgeNonMaximumSuppression[i][j]=gradientMagnitude[i][j];
            switch(orientation){
            case 0:
                if(j==0){
                    if(valueGradient <= gradientMagnitude[i][j+1]){
                        edgeNonMaximumSuppression[i][j]=0;
                    }
                }else if(j == width-1){
                    if(valueGradient <= gradientMagnitude[i][j-1]){
                        edgeNonMaximumSuppression[i][j]=0;
                    }
                }else{
                    if(valueGradient <= gradientMagnitude[i][j+1] || valueGradient <= gradientMagnitude[i][j-1]){
                        edgeNonMaximumSuppression[i][j]=0;
                    }
                }
                break;
            case 1:
                if((i == 0 && j!=0) || (j==0 && i!=0)){
                    if(valueGradient <= gradientMagnitude[i-1][j+1]){
                        edgeNonMaximumSuppression[i][j]=0;
                    }

                }else if((i == height-1 && j!=width-1) || (j==width-1 && i!=height-1)){
                    if(valueGradient <= gradientMagnitude[i+1][j-1]){
                        edgeNonMaximumSuppression[i][j]=0;
                    }
                }else if((j !=0 && i!=0) && (i!=height-1 && j!=width-1)){//no sea las esquinas
                    if(valueGradient <= gradientMagnitude[i+1][j-1] || valueGradient <= gradientMagnitude[i-1][j+1]){
                        edgeNonMaximumSuppression[i][j]=0;

                    }
                }
            case 2:
                if(i==0){
                    if(valueGradient <= gradientMagnitude[i+1][j]){
                        edgeNonMaximumSuppression[i][j]=0;
                    }
                }else if(i == height-1){
                    if(valueGradient <= gradientMagnitude[i-1][j]){
                        edgeNonMaximumSuppression[i][j]=0;
                    }
                }else{
                    if(valueGradient <= gradientMagnitude[i+1][j] || valueGradient <= gradientMagnitude[i-1][j]){
                        edgeNonMaximumSuppression[i][j]=0;
                    }
                }
            case 3:
                if((i == 0 && j!=width-1) || (j==0 && i!=height-1)){
                    if(valueGradient <= gradientMagnitude[i+1][j+1]){
                        edgeNonMaximumSuppression[i][j]=0;
                    }

                }else if((i == height-1 && j!=0) || (j==width-1 && i!=0)){
                    if(valueGradient <= gradientMagnitude[i-1][j-1]){
                        edgeNonMaximumSuppression[i][j]=0;
                    }
                }else if((j !=0 && i!=height-1) && (i!=0 && j!=width-1)){//no sea las esquinas
                    if(valueGradient <= gradientMagnitude[i+1][j+1] || valueGradient <= gradientMagnitude[i-1][j-1]){
                        edgeNonMaximumSuppression[i][j]=0;

                    }
                }
                break;
            }


        }
    }
}
/**
    Se aplica para determinar los bordes de la imagen.
    Primero se buscan los valores que esten por encima del thresholdHigh y
    si es asi se empieza a recorrer en busca de los siguientes puntos que esten por encima del thresholdDown.

*/
void EdgeDetector::hysteresis(int thresholdHigh, int thresholdsDown)
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width ; j++){
            //QTextStream (stdout) << (edgeNonMaximumSuppression[i][j]/8)<<" \n";

            if((edgeNonMaximumSuppression[i][j])>=(double)thresholdHigh){//OJO AQUI CON LA DIVISION
                edgeFollow(i,j, thresholdsDown);
            }
        }
    }
    //0 es borde , 1 no es borde
}

/**
    Metodo que  sigue un borde. Toma el pixel actual que es mayor al threshold y se toma como un borde.
    Luego se mueve a la posicion siguiente (90° respecto angulo gradiente contra manecillas reloj).
    Determina si es mayor por lo menos al thresholdDown y si es asi llama recursivamente a la función.
    La función para si ya lo hemos visitado o no es mayor al thresholdDown.
*/
int EdgeDetector::edgeFollow(int posX, int posY, int thresholdsDown)
{
    if(edgeHysteresis[posX][posY]==1){//si no lo visite
        edgeHysteresis[posX][posY]=0;
        int degree = gradientDegreeDiscret[posX][posY];
        //cout << degree << endl;
        switch(degree){//mover al siguiente punto 90° respecto angulo gradiente contra manecillas reloj
        case 0:
            posY--;
            posX--;
            break;
        case 1:
            posX-=2;
            break;
        case 2:
            posY++;
            posX--;
            break;
        case 3:
            posY+=2;
            break;
        case 4:
            posY++;
            posY++;
            break;
        case 5:
            posX+=2;
            break;
        case 6:
            posX++;
            posY--;
            break;
        case 7:
            posY-=2;
            break;

        }
        //siguiente punto
                                                                     //OJO CON LA DIVISION
        if(!(posX<0 || posX>=height) && !(posY<0 || posY>=width) && ((edgeNonMaximumSuppression[posX][posY]) >= (double)thresholdsDown)){//puede interesarme
            if(edgeFollow(posX, posY,thresholdsDown)){
                edgeHysteresis[posX][posY]=0;
                return 1;
            }

        }
        return 1;//REVISAR el valor siguiente aun no se ha asignado
    }
    return 0;
}
