#include "Image.h"

Image::Image() : QListWidgetItem()
{
}

Image::~Image()
{
}

void Image::setName(const QString str)
{
  m_name = str;
}

void Image::setPath(const QString str)
{
  m_path = str;
}

void Image::loadImage(const QString str)
{
  int c;
  m_img_original.load(str);
  m_img_modified.load(str);
  //if(m_img_modified.height() > 500)
  m_img_modified = m_img_modified.scaledToHeight(400);
  m_img_original = m_img_original.scaledToHeight(400);
  for(int i =0; i< m_img_modified.height(); i++){
    for(int j=0; j< m_img_modified.width(); j++){
      c = qGray(m_img_modified.pixel(j,i));
      m_img_modified.setPixel(j,i,QColor::fromRgb(c,c,c).rgb());
    }
  }
  //m_histogram.compute(m_img_modified);
}

QString Image::getName(void)
{
  return m_name;
}

QString Image::getPath(void)
{
  return m_path;
}

QImage Image::getImageOriginal(void)
{
  return m_img_original;
}

QImage Image::getImageModified(void)
{
  return m_img_modified;
}

Histogram Image::getHistogram()
{
  return m_histogram;
}

void Image::applyFourier()
{
  QVector < QVector <double> > magnitude;
  int h = m_img_modified.height(),
      w = m_img_modified.width();
  QColor col;
  int c;

  m_fourier.computeForward(m_img_modified);
  magnitude = m_fourier.getMagnitude();

  for(int y=0; y<h; y++)
  {
    for(int x=0; x<w; x++)
    {
      c = 255*magnitude[y][x]/((double) (h*w));
      if(c > 255)
        c = 255;
      if(c < 0)
        c = 0;
      col.setRgb(c,c,c);
      //m_img_modified.setPixel((x+w/2)%w,(y+h/2)%h,col.rgb());
      m_img_modified.setPixel((x+w/2)%w,(y+h/2)%h,col.rgb());
    }
  }
}

void Image::applyFourierInverse()
{
  m_fourier.computeBackward(&m_img_modified);
}

void Image::applyFourierCut()
{
  QVector < QVector <double> > magnitude;
  int h = m_img_modified.height(),
      w = m_img_modified.width();
  QColor col;
  int c;

  m_fourier.cut();
  magnitude = m_fourier.getMagnitude();

  for(int y=0; y<h; y++)
  {
    for(int x=0; x<w; x++)
    {
      c = 255*magnitude[y][x]/((double) (h*w));
      if(c > 255)
        c = 255;
      if(c < 0)
        c = 0;
      col.setRgb(c,c,c);
      m_img_modified.setPixel((x+w/2)%w,(y+h/2)%h,col.rgb());
    }
  }
}

void Image::applyAvgFilter()
{
  m_filter.avgFilter(&m_img_modified);
}

void Image::applySobelFilter()
{
  m_filter.sobelFilter(&m_img_modified);
}

void Image::applyThreshold(int a, int b =255)
{
  int g;
  for(int i=0; i<m_img_modified.height(); i++)
  {
    for(int j=0; j<m_img_modified.width(); j++)
    {
      g = qGray(m_img_modified.pixel(j,i));
      if(g < a || g > b)
        m_img_modified.setPixel(j,i,0);
      else
        m_img_modified.setPixel(j,i,QColor::fromRgb(255,255,255).rgb());
    }
  }
}

void Image::applyErosion(int r)
{
  m_filter.erosion(&m_img_modified,r);
}

void Image::applyDilatation(int r)
{
  m_filter.dilatation(&m_img_modified,r);
}

void Image::applyNegative(void)
{
  m_filter.negative(&m_img_modified);
}

QList <QPoint> Image::applyInterestPoints()
{
  //return m_filter.findHoughPoints(m_img_modified);
  return m_filter.findInterestPoints(m_img_modified);
}

