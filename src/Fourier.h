#ifndef DEF_FOURIER
#define DEF_FOURIER

#include <QVector>
#include <QImage>

class Fourier
{
  private:
    QVector <QVector <double> > m_real;
    QVector <QVector <double> > m_imaginary;
    QVector <QVector <double> > m_magnitude;
    int                         m_h;
    int                         m_w;

  public:
    Fourier();
    ~Fourier();
    void computeForward(QImage img);
    void computeBackward(QImage *img);
    void computeMagnitude(void);
    void cut(void);
    QVector <QVector <double> > getReal(void) { return m_real; };
    QVector <QVector <double> > getImaginary(void) { return m_imaginary; };
    QVector <QVector <double> > getMagnitude(void) { return m_magnitude; };
};

#endif
