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
#include "lib/qcustomplot.h"

using namespace std;

class Image : public QListWidgetItem
{
  private:
    QString m_name;
    QString m_path;
    QImage  m_img;
    QImage  m_img1;

  public:
    Image();
    ~Image();
    void setName(const QString str);
    void setPath(const QString str);
    void loadImage(const QString str);
    QString getName(void);
    QString getPath(void);
    QImage getImage(void);
    QImage getImage1(void);
    vector< QVector <double>  > histogramme(void);
    vector< vector <double> > fourier(void);
};

#endif
