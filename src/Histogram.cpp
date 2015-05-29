#include "Histogram.h"
#include <iostream>
#include <algorithm>
#include <cmath>

Histogram::Histogram()
{
  m_histoSize = 64;
  m_redPix.resize(m_histoSize);
  m_greenPix.resize(m_histoSize);
  m_bluePix.resize(m_histoSize);
  m_colorPix.resize(m_histoSize);
}

Histogram::~Histogram()
{
}

struct sortHisto{
  double val;
  int col;
};

bool moreThan( const struct sortHisto & e1, const struct sortHisto & e2 )
{
  if(e1.val > e2.val)
    return true;
  else
    return false;
}

void Histogram::compute(QImage img)
{
  QRgb p;
  int h = img.height(),
      w = img.width();
  double hw = h*w;

  int jaune = 0;

  m_redPix.fill(0);
  m_greenPix.fill(0);
  m_bluePix.fill(0);
  m_colorPix.fill(0);

  for(int i = 0; i<h; i++)
  {
    for(int j = 0; j<w; j++)
    {
      p = img.pixel(j,i);
      if(abs(qRed(p)-qBlue(p))<33)
        jaune++;
      m_redPix[(int)(((double) qRed(p))/255.0*((double) m_histoSize-1)) ]+=1;
      m_greenPix[(int)(((double) qBlue(p))/255.0*((double) m_histoSize-1)) ]+=1;
      m_bluePix[(int)(((double) qGreen(p))/255.0*((double) m_histoSize-1)) ]+=1;
      m_colorPix[(int) ( (double) ((qRed(p) + qBlue(p)*256 + qGreen(p)*256*256)/(pow(256,3)-1)) * ((double) m_histoSize-1) ) ]+=1;
    }
  }

  QVector <struct sortHisto> col;
  col.resize(m_histoSize);
  bool increasing = true, oldincreasing = true;
  for(int i=0; i<m_histoSize; i++)
  {
    m_redPix[i]/=hw;
    m_greenPix[i]/=hw;
    m_bluePix[i]/=hw;
    m_colorPix[i]/=hw;
    if(i>0){
      if(m_colorPix[i-1] < m_colorPix[i])
        increasing = true;
      else
        increasing = false;
      if(oldincreasing==true && increasing==false && m_colorPix[i] > 0.00)
        m_colors << (i-1);
      oldincreasing = increasing;
    }
    col[i].val = m_colorPix[i];
    col[i].col = i;
  }
  if(increasing)
    m_colors << m_histoSize-1;

  std::sort(col.begin(),col.end(),moreThan);
  /*
  double tmpR=0,tmpG=0,tmpB=0;
  bool bR=true,bG=true,bB=true;
  double rate = 0.6;
  int i=0;
  while(i<m_histoSize && (bR || bG || bB ))
  {
    if(tmpR > rate)
      bR = false;
    else
      m_reds << red[i].col;
    if(tmpG > rate)
      bG = false;
    else
      m_blues << blue[i].col;
    if(tmpB > rate)
      bB = false;
    else
      m_greens << green[i].col;

    tmpR += red[i].val;
    tmpG += green[i].val;
    tmpB += blue[i].val;
    i++;
  }
  std::cout << std::endl << "nb red : " <<  m_reds.count() << std::endl;
  std::cout <<"nb blue : " <<  m_blues.count() << std::endl;
  std::cout << std::endl << "nb peak : " <<  m_colors.count() << std::endl;
  for(int i = 0; i<m_colors.count(); i++)
    std::cout << m_colors.value(i) << " " ;
  for(int i = 0; i<m_histoSize; i++)
  {
    std::cout << col[i].val << "->" << col[i].col << std::endl;
  }
  */
  //std::cout << 100*jaune / hw << std::endl;
}

