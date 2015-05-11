#ifndef DEF_IMAGE
#define DEF_IMAGE

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLayout>
#include <QListWidget>
#include <QObject>
#include <QRgb>
#include <iostream>
#include <vector>
#include <QVector>
#include <QList>
#include <QPoint>
#include "lib/qcustomplot/qcustomplot.h"
#include "Fourier.h"
#include "Histogram.h"
#include "Filter.h"


using namespace std;

class Image : public QListWidgetItem
{
  private:
    QString          m_name;
    QString          m_path;
    QImage           m_img_original;
    QImage           m_img_modified;
    Histogram        m_histogram;
    Fourier          m_fourier;
    Filter           m_filter;

  public:
    Image();
    ~Image();
    void setName(const QString str);
    void setPath(const QString str);
    Histogram getHistogram(void);
    void loadImage(const QString str);
    QString getName(void);
    QString getPath(void);
    QImage getImageOriginal(void);
    QImage getImageModified(void);
    void setImageOriginal(QImage img){ m_img_original = img;};
    void setImageModified(QImage img){ m_img_modified = img;};
    void applyFourier(void);
    void applyFourierInverse(void);
    void applyFourierCut(void);
    void applyAvgFilter(void);
    void applySobelFilter(void);
    void applyThreshold(int a, int b);
    void applyErosion(int r);
    void applyDilatation(int r);
    void applyNegative(void);
    QList <QPoint> applyInterestPoints(void);
};


#endif
