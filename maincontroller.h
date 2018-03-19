#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QImage>

class MainController
{
private:
    Image *newImage;
    Image *oldImage;

public:
    MainController();
    ~MainController();

    bool LoadImage(QString fileName);

    //MyMenuOptionsForImageEditing

    void ChangeColorDepth(int depth);
    void ChangeToGreyscale(int method);

    bool WeightedAverage(QString filename, double alpha);
    bool AddImage(QString filename);
    bool SubstractImage(QString filename);


    void ScaleImage(double factorPerX, double factorPerY);
    void TranslationOfImage(double factorPerX, double factorPerY);
    void RotateImage(double angle);

    //histogram

    bool BimoidalSegmentation(int T);
    void EqualizeHistogram();

    //segmentation

    void OtsuSegmentation();
    void IsoDataSegmentation();

    //Contrast

    void GammaCorrection(double myGamma);
    void ContrastStreching();

    //filer

    void Scaling(double factorX,
                         double factorY);
           void Translation(double factorX,
                            double factorY);
           void Rotation(double angle);
           void Reflection(bool orientationX);    // true X false Y

           // histogram
           bool BimodalSegmentaion(int T);
           void EqualizateHistogram();
           void OtsuSegmentation();
           void IsodataSegmentation();

           // contrast
           void GammaCorrection(double r);
           void ContrastStretching();

           // Filter
           void MeanFilter(int size);
           void ConvolutionFilter(int ** kernel,
                                  int    size);
           void GaussianaFilter(int size);
           void NoiseCleaningPixel(int delta);
           void NoiseCleaningLine(double delta);

           // Edge Detection
           void EdgeDetectionSobel(int position);
           void EdgeDetectorCanny(int thresholdHigh,
                                  int thresholdDown);

           // Morphological Operation
           void DilateOperation(int ** matrixStructuringElement,
                                int    origenX,
                                int    origenY,
                                int    heightS,
                                int    widthS);
           void ErosionOperation(int ** matrixStructuringElement,
                                 int    origenX,
                                 int    origenY,
                                 int    heightS,
                                 int    widthS);
           void OpeningOperation(int ** matrixStructuringElement,
                                 int    origenX,
                                 int    origenY,
                                 int    heightS,
                                 int    widthS);
           void ClosingOperation(int ** matrixStructuringElement,
                                 int    origenX,
                                 int    origenY,
                                 int    heightS,
                                 int    widthS);

           // Segementation
           void SegmentationK_Means(int cluster);
           void SegmentationRemoveCap();
           int GetCountFrameFirstImage();
           void SegmentationWhiteTissue();
           void SegmentationGrayTissue();

           // DICOM
           void ApplyWindowLevel(int window,int level);
           void ChangeFrame(int numFrame);
           QString getDataSet();
           void ConvertDICOMtoPGM();
           // GETTERS:
           Image * getImage();
           QImage * getQImage();
           QImage * getHistogramImage();

           // Others methods:
           bool undo();
           bool isThereAnUploadedImage();
           void saveImage(QString filename,
                          QString id);




};

#endif // MAINCONTROLLER_H
