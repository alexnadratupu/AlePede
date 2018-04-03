#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QFileDialog>
#include <QApplication>
#include <QPixmap>
#include <QPainter>
#include <QMessageBox>
#include <QInputDialog>
#include <QErrorMessage>
#include <QPoint>
#include <QDebug>


// Projec include
#include "maincontroller.h"
#include "colordepthqwidget.h"
#include "thresholdqwidget.h"
#include "windowlevelqwidget.h"
#include "convolutionqwidget.h"
#include "sobelqwidget.h"
#include "structureelementqwidget.h"
#include "cannywidget.h"
#include "changeframewidget.h"

class ColorDepthQwidget;
class ThresholdQwidget;
class ConvolutionQwidget;
class WindowLevelQWidget;
class SobelQwidget;
class StructureElementQwidget;

//namespace Ui {
//class MainWindow;
//}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent=0);
    ~MainWindow();

    void displayResults(QImage *result);
    void ShowHistogram();

private slots:

    // ToolBar Actions
    void on_action_Normal_Size_triggered();
    void on_actionZoom_In_triggered();
    void on_actionZoom_Out_triggered();

    // MenuBar Events

    // File Menu
    void on_actionNew_Job_triggered();
    void on_actionSave_triggered();
    void on_actionExit_triggered();
    void on_action_Load_Image_triggered();
    void enable_triggered();

    // Edit Menu
    void on_actionUndo_triggered();
    void on_actionChange_Color_Depth_triggered();
    void on_actionConver_to_GrayScale_triggered();

    // Global Transformations Menu
    void on_actionWeighted_Average_triggered();
    void on_actionAdd_triggered();
    void on_actionSubstract_triggered();
    void on_actionMultiply_triggered();
    void on_actionDivide_triggered();

    void on_actionMax_triggered();
    void on_actionMin_triggered();

    void on_actionAND_triggered();
    void on_actionOR_triggered();
    void on_actionXOR_triggered();
    void on_actionNOT_triggered();

    // Geometric Operation Menu
    void on_actionTranslation_triggered();
    void on_actionReflection_triggered();
    void on_actionRotation_triggered();
    void on_actionScaling_triggered();

    // Histogram Menu
    void on_actionThreshold_triggered();
    void on_actionEqualization_triggered();
    // Contrast SubMenu
    void on_actionGamma_Correction_triggered();
    void on_actionStretching_triggered();

    //Filters Menu
    void on_actionMean_triggered();
    void on_actionConvolution_triggered();
    void on_actionGaussiana_triggered();
    void on_actionNoise_Cleaning_Line_triggered();
    void on_actionNoise_Cleaning_Pixel_triggered();
    void on_actionMorphological_triggered();

    // Edge Detection Menu
    void on_actionSobel_triggered();
    void on_actionCanny_triggered();

    //Segmentation Menu
    void on_actionK_Means_triggered();
    void on_actionChange_Frame_triggered();


    // DICOM Menu
    void on_actionWindow_Level_triggered();
    void on_actionConvert_to_PGM_triggered();

    // Help Menu
    void on_actionAbout_triggered();

    // Other Methods
    void on_label_Imagen_drawLine(const QPoint start, const QPoint end);
    void on_label_Imagen_eraseLine();
    void on_label_Imagen_mousePosition(const QPoint position);
    void scaleDisplayedImage(double factor);


    void on_actionRemoveCap_triggered();

    void on_actionWhite_Tissue_triggered();

    void on_actionGray_Tissue_triggered();

private:

    MainWindow *ui;
    MainController * mainController;
    QImage *displayedImage, *histogramImage;
    QPixmap pixmapLabelImagen;
    QString lastPath;

    QStringList choiseItemSaveOption();
    QString valueItemSaveOption(QString comparator);
    int indexItemSaveOption(QString comparator);

};

#endif // MAINWINDOW_H
