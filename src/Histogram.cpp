#include "Histogram.h"

Histogram::Histogram()
{
  m_redPix.resize(256);
  m_greenPix.resize(256);
  m_bluePix.resize(256);
  m_redPix.fill(0);
  m_greenPix.fill(0);
  m_bluePix.fill(0);
}

Histogram::~Histogram()
{
}

void Histogram::compute(QImage img)
{
  QRgb p;
  int h = img.height(),
      w = img.width();
  int hw = h*w;

  for(int i = 0; i<h; i++)
  {
    for(int j = 0; j<w; j++)
    {
      p = img.pixel(j,i);
      m_redPix[qRed(p)]+=1;
      m_bluePix[qGreen(p)]+=1;
      m_greenPix[qBlue(p)]+=1;
    }
  }

  for(int i=0; i<256; i++)
  {
    m_redPix[i]/=hw;
    m_bluePix[i]/=hw;
    m_greenPix[i]/=hw;
  }
}
