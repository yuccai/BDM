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

  public:
    Histogram();
    ~Histogram();
    QVector <double> getRedPix(void) { return m_redPix; };
    QVector <double> getGreenPix(void) { return m_greenPix; };
    QVector <double> getBluePix(void) { return m_bluePix; };
    void compute(QImage img);
};

#endif
