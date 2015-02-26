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

vector< vector<int> > Image::historgramme(void)
{
  vector< vector<int> > h;
  QRgb p;

  for(int i=0; i<3; i++)
    h.push_back(vector<int>(256,0));

  for(int i = 0; i<m_img.height(); i++)
  {
    for(int j = 0; j<m_img.width(); j++)
    {
      p = m_img.pixel(j,i);
      h[0][qRed(p)]++;
      h[1][qGreen(p)]++;
      h[2][qBlue(p)]++;
    }
  }

  for(int i=0; i<3; i++)
    for(int j=0; j<256; j++)
    h[i][j] = (h[i][j]*100)/(m_img.height()*m_img.width());
  return h;
}
