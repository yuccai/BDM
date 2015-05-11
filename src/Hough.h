#ifndef DEF_HOUGH
#define DEF_HOUGH

#include <QDialog>
#include <QVector>
#include <cmath>
#include <lib/qcustomplot/qcustomplot.h>
#include "Image.h"
#include <QList>
#include <QPoint>
#include <QPushButton>
#include <QSpinBox>
#include <QImage>

class Hough : public QDialog
{
  private:
    QCustomPlot                 *m_customPlot;
    QVBoxLayout                 *m_layout;
    QHBoxLayout                 *m_layout_spin_box;
    QPushButton                 *m_button_find_lines;
    QVector< QVector <double> >  m_datas;
    QVector <double>             m_ticks;
    int                          m_nbPoints;
    int                          m_step;
    QList <QPointF>              m_lines;
    QSpinBox                    *m_epsilon_theta;
    QSpinBox                    *m_epsilon_rho;
    QSpinBox                    *m_nbPointsPerLine;

  public:
    Hough();
    ~Hough();
    void compute(Image img);
    void initCustomPlot();
    void plot();
    void findLines();
    void applyHough(QImage *img);
};

#endif
