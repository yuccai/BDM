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
  m_img.load(str);
}

QString Image::getName(void)
{
  return m_name;
}

QString Image::getPath(void)
{
  return m_path;
}

QImage Image::getImage(void)
{
  return m_img;
}

int* Image::historgramme(void)
{
  int h[3][256]={0};
  for(int i = 0; i<m_img.height(); i++)
  {
    for(int j = 0; j<m_img.width(); j++)
    {
      QRgb p = m_img.pixel(i,j);
      h[0][qRed(p)]++;
      h[1][qGreen(p)]++;
      h[2][qBlue(p)]++;
    }
  }
  return h;
}
