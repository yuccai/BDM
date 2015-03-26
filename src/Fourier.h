#ifndef DEF_FOURIER
#define DEF_FOURIER

#include <QVector>
#include <QImage>

class Fourier
{
  private:
    QVector <QVector <double> > m_real;
    QVector <QVector <double> > m_imaginary;

  public:
    Fourier();
    ~Fourier();
    void compute(QImage img);
    QVector <QVector <double> > getReal(void) { return m_real; };
    QVector <QVector <double> > getImaginary(void) { return m_imaginary; };
};

#endif
