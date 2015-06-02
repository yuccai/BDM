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

  m_redPix.fill(0);
  m_greenPix.fill(0);
  m_bluePix.fill(0);
  m_colorPix.fill(0);

  double l,u,v;
  for(int i = 0; i<h; i++)
  {
    for(int j = 0; j<w; j++)
    {
      p = img.pixel(j,i);
      rgb2luv(p,&l,&u,&v);
      /*
      m_redPix[(int)(((double) qRed(p))/255.0*((double) m_histoSize-1)) ]+=1;
      m_greenPix[(int)(((double) qBlue(p))/255.0*((double) m_histoSize-1)) ]+=1;
      m_bluePix[(int)(((double) qGreen(p))/255.0*((double) m_histoSize-1)) ]+=1;
      //m_colorPix[(int) ( (double) ((qRed(p) + qBlue(p)*256 + qGreen(p)*256*256)/(pow(256,3)-1)) * ((double) m_histoSize-1) ) ]+=1;
      */
      //std::cout << (int) (l/100.0*(m_histoSize-1)) << " " << (int) ((u+134)/354.0*(m_histoSize-1)) << " " <<(int) ((v+140)/263.0*(m_histoSize-1)) << std::endl;
      m_redPix[(int) (l/100.0*(m_histoSize-1))] +=1;
      m_bluePix[(int) ((u+134)/354.0*(m_histoSize-1))] +=1;
      m_greenPix[(int) ((v+140)/263.0*(m_histoSize-1))] +=1;
      m_colorPix[(int) ( (double) ((l + (u+134)*354 + (v+140)*354*354)/(pow(354,3)-1)) * ((double) m_histoSize-1) ) ]+=1;
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
      if(oldincreasing==true && increasing==false && m_colorPix[i-1] > 0.00)
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
  for(int i = 0; i<m_colors.count(); i++)
    std::cout << m_colors.value(i) << " " ;
  std::cout << std::endl;
  */
  /*
  for(int i = 0; i<m_histoSize; i++)
    std::cout << std::endl << col[i].val << "->" << col[i].col << std::endl;
    */
}

double PivotRgb(double n)
{
  return (n > 0.04045 ? pow((n + 0.055) / 1.055, 2.4) : n / 12.92) * 100.0;
}

void Histogram::rgb2luv(QRgb p, double *l, double *u, double *v)
{
  double r = qRed(p),
         g = qGreen(p),
         b = qBlue(p);
  double x=0,y=0,z=0;
  *l=0;
  *u=0;
  *v=0;

  x = 0.412453*PivotRgb(r/255.0) + 0.357580*PivotRgb(g/255.0) + 0.180423*PivotRgb(b/255.0);
  y = 0.212671*PivotRgb(r/255.0) + 0.715160*PivotRgb(g/255.0) + 0.072169*PivotRgb(b/255.0);
  z = 0.019334*PivotRgb(r/255.0) + 0.119193*PivotRgb(g/255.0) + 0.950227*PivotRgb(b/255.0);

  y = y/100;

  if(y>0.008856)
    *l = 116*cbrt(y)-16;
  else
    *l = 903.3*y;


  double targetDenominator    = x+15*100*y+3*z,
         referenceDenominator = 95.047+15*100.000+3*108.883;
  double xTarget = targetDenominator == 0 ? 0 : ((4.0 * x / targetDenominator) - (4.0 * 95.047  / referenceDenominator)),
         yTarget = targetDenominator == 0 ? 0 : ((9.0 * y*100 / targetDenominator) - (9.0 * 100.000 / referenceDenominator));

  *u = (*l)*13.0*xTarget;
  *v = (*l)*13.0*yTarget;


  /*
  std::cout << "(r,g,b) = (" <<r<<","<<g<<","<<b<<")"<<std::endl;
  std::cout << "(x,y,z) = (" <<x<<","<<100*y<<","<<z<<")"<<std::endl;
  std::cout << "(l,u,v) = (" <<*l<<","<<*u<<","<<*v<<")"<<std::endl;
  std::cout << "xTarget : " << xTarget << " | yTarget : " << yTarget << std::endl;
  */
}
