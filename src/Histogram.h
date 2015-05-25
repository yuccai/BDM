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
    QList <int>      m_reds;
    QList <int>      m_greens;
    QList <int>      m_blues;
    int              m_histoSize;

  public:
    Histogram();
    ~Histogram();
    QVector <double> getRedPix(void) { return m_redPix; };
    QVector <double> getGreenPix(void) { return m_greenPix; };
    QVector <double> getBluePix(void) { return m_bluePix; };
    void compute(QImage img);
    int getHistoSize(void) { return m_histoSize; };

};

#endif
