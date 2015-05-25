#include "Histogram.h"
#include <iostream>

Histogram::Histogram()
{
  m_histoSize = 16;
  m_redPix.resize(m_histoSize);
  m_greenPix.resize(m_histoSize);
  m_bluePix.resize(m_histoSize);
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
      m_redPix[(int)(((double) qRed(p))/255.0*((double) m_histoSize)) ]+=1;
      m_bluePix[(int)(((double) qBlue(p))/255.0*((double) m_histoSize)) ]+=1;
      m_greenPix[(int)(((double) qGreen(p))/255.0*((double) m_histoSize)) ]+=1;
      //std::cout << h*w << ": ("<<qRed(p)<<","<<qGreen(p)<<","<<qBlue(p)<<")"<<std::endl;
    }
  }

  for(int i=0; i<m_histoSize; i++)
  {
    m_redPix[i]/=hw;
    m_bluePix[i]/=hw;
    m_greenPix[i]/=hw;
    //std::cout << h*w << ": ("<<m_redPix[i]<<","<<m_greenPix[i]<<","<<m_bluePix[i]<<")"<<std::endl;
  }
}
