#ifndef DEF_HISTOGRAM
#define DEF_HISTOGRAM

#include <QImage>
#include <QVector>

class Histogram
{
  private:
    QVector <double> m_redPix;
    QVector <double> m_greenPix;
    QVector <double> m_bluePix;
    QVector <double> m_colorPix;
    QList <int>      m_reds;
    QList <int>      m_greens;
    QList <int>      m_blues;
    QList <int>      m_colors;
    int              m_histoSize;

  public:
    Histogram();
    ~Histogram();
    QVector <double> getRedPix(void) { return m_redPix; };
    QVector <double> getGreenPix(void) { return m_greenPix; };
    QVector <double> getBluePix(void) { return m_bluePix; };
    QVector <double> getColorPix(void) { return m_colorPix; };
    QList <int>      getColors(void) {return m_colors; };
    void compute(QImage img);
    int getHistoSize(void) { return m_histoSize; };
    void rgb2luv(QRgb p, double *l, double *u, double *v);
};

#endif
