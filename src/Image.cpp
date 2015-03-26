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
  m_img_original.load(str);
  m_img_modified.load(str);
  //m_img_modified = m_img_modified.scaledToHeight(100);
  m_histogram.compute(m_img_modified);
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
  QVector < QVector <double> > real;
  QColor c;
  m_fourier.compute(m_img_modified);
  int h = m_img_modified.height(),
      w = m_img_modified.width();

  real = m_fourier.getReal();

  for(int y=0; y<h; y++)
  {
    for(int x=0; x<w; x++)
    {
      if(real[y][x] < 255){
        c.setRgb(real[y][x],real[y][x],real[y][x]);
        m_img_modified.setPixel((x+w/2)%w,(y+h/2)%h,c.rgb());
      }
    }
  }
}
