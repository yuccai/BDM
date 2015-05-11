#include "Filter.h"
#include <QColor>
#include <iostream>
#include <cmath>

Filter::Filter(void)
{
  m_avg.resize(3);
  m_sobelX.resize(3);
  m_sobelY.resize(3);

  for(int i=0; i<3; i++){
    m_avg[i].resize(3);
    m_sobelX[i].resize(3);
    m_sobelY[i].resize(3);
    m_avg[i].fill(1);
  }

  m_sobelX[0][0] = -1;
  m_sobelX[1][0] = 0;
  m_sobelX[2][0] = 1;
  m_sobelX[0][1] = -2;
  m_sobelX[1][1] = 0;
  m_sobelX[2][1] = 2;
  m_sobelX[0][2] = -1;
  m_sobelX[1][2] = 0;
  m_sobelX[2][2] = 1;

  m_sobelY[0][0] = -1;
  m_sobelY[1][0] = -2;
  m_sobelY[2][0] = -1;
  m_sobelY[0][1] = 0;
  m_sobelY[1][1] = 0;
  m_sobelY[2][1] = 0;
  m_sobelY[0][2] = 1;
  m_sobelY[1][2] = 2;
  m_sobelY[2][2] = 1;
}

Filter::~Filter(void)
{
}

void Filter::avgFilter(QImage *dest)
{
  int w = dest->width(),
      h = dest->height(),
      c, p;
  QImage src = *dest;
  QColor col;

  for(int i=0; i<h; i++)
  {
    for(int j=0; j<w; j++)
    {
      c=0;
      p=9;
      for(int k=-1; k<2; k++)
      {
        for(int l=-1; l<2; l++)
        {
          if( (j+l) >= 0 && (j+l) < w && (i+k) >= 0 && (i+k) < h)
            c += qGray(src.pixel(j+l,i+k))*m_avg[l+1][k+1];
          else
            p-=1;
        }
      }
      c = c/p;
      col.setRgb(c,c,c);
      dest->setPixel(j,i,col.rgb());
    }
  }
}

void Filter::sobelFilter(QImage *dest)
{
  int w = dest->width(),
      h = dest->height(),
      c, c1, c2;
  bool inside;
  QImage src = *dest;
  QColor col;

  for(int i=0; i<h; i++)
  {
    for(int j=0; j<w; j++)
    {
      c1=0;
      c2=0;
      inside = true;
      for(int k=-1; k<2; k++)
      {
        for(int l=-1; l<2; l++)
        {
          if( (j+l) >= 0 && (j+l) < w && (i+k) >= 0 && (i+k) < h && inside)
          {
            c1 += qGray(src.pixel(j+l,i+k))*m_sobelX[l+1][k+1];
            c2 += qGray(src.pixel(j+l,i+k))*m_sobelY[l+1][k+1];
          }
          else{
            inside = false;
            c1 = 0;
            c2 = 0;
          }
        }
      }
      c = sqrt(c1*c1+c2*c2);
      if(c>255)
        c=255;
      if(c<0)
        c=0;

      col.setRgb(c,c,c);
      dest->setPixel(j,i,col.rgb());
    }
  }
}

QList <QPoint> Filter::findInterestPoints(QImage src)
{
  int h = src.height(),
      w = src.width(),
      r = 3;
  double ix,iy,s,u,c,a,b,d;
  QList <QPoint> l;
  u=0.05;
  s=1500;

  for(int i=0; i<h; i++)
  {
    for(int j=0; j<w; j++)
    {
      if( (j-2*r) >= 0 && (j+2*r) < w && (i-2*r) >= 0 && (i+2*r) < h)
      {
        a=0;
        b=0;
        c=0;
        d=0;
        for(int k=-1; k<2; k++)
        {
          for(int l=-1; l<2; l++)
          {
            ix = 0;
            iy = 0;
            for(int m=-1; m<2; m++)
            {
              for(int n=-1; n<2; n++)
              {
                ix += qGray(src.pixel(j+l+m,i+k+n))*m_sobelX[n+1][m+1]/255;
                iy += qGray(src.pixel(j+l+m,i+k+n))*m_sobelY[n+1][m+1]/255;
              }
            }
            a+=ix*ix;
            b+=iy*iy;
            d+=ix*iy;
          }
        }
        c = a*b - d*d - u*(a+b)*(a+b);
        if(c>s){
          l.append(QPoint(j,i));
        }
      }
    }
  }
  std::cout << "Interest points found : " << l.count() << std::endl;
  return l;
}

QList <QPoint> Filter::findHoughPoints(QImage src)
{
  int h = src.height(),
      w = src.width(),
      i,j;
  QList <QPoint> l;
  QColor white = QColor::fromRgb(255,255,255),
         col;
  for(i=0;i<h;i++){
    for(j=0;j<w;j++){
      col = src.pixel(j,i);
      if(col==white){
        l.append(QPoint(j,i));
      }
    }
  }
  std::cout << "Hough points found : " << l.count() << std::endl;
  return l;
}

void Filter::erosion(QImage *dest, int r)
{
  int i,j,k,l,w,h;
  QImage src(*dest);
  bool included;
  QColor black, white, col;

  w = src.width();
  h = src.height();

  black = QColor::fromRgb(0,0,0);
  white = QColor::fromRgb(255,255,255);

  for(i=0;i<h;i++)
  {
    for(j=0;j<w;j++)
    {
      if( (i-r)>=0 && (i+r)<h && (j-r)>=0 && (j+r)<w )
      {
        col = src.pixel(j,i);
        if(col == white)
        {
          included = true;
          for(k=-r;k<=r;k++)
          {
            for(l=-r;l<=r;l++)
            {
              if(k*k + l*l <= r*r)
              {
                col = src.pixel(j+l,i+k);
                if(col == black)
                  included = false;
              }
            }
          }
          if(!included)
            dest->setPixel(j,i,black.rgb());
        }
      }
    }
  }
}

void Filter::dilatation(QImage *dest, int r)
{
  negative(dest);
  erosion(dest,r);
  negative(dest);
}

void Filter::negative(QImage *img)
{
  QColor black,white,col;
  black = QColor::fromRgb(0,0,0);
  white = QColor::fromRgb(255,255,255);
  for(int i=0; i<img->height(); i++)
  {
    for(int j=0; j<img->width(); j++)
    {
      col = img->pixel(j,i);
      if(col == black)
        img->setPixel(j,i,white.rgb());
      else
        img->setPixel(j,i,black.rgb());
    }
  }
}
