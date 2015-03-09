#include "Image.h"
#include <math>

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
  m_img1.load(str);
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

QImage Image::getImage1(void)
{
  return m_img1;
}

vector< QVector<double> > Image::histogramme(void)
{
  vector< QVector <double> > h;
  QRgb p;

  for(int i=0; i<3; i++)
    h.push_back(QVector<double>(256,0));

  for(int i = 0; i<m_img.height(); i++)
  {
    for(int j = 0; j<m_img.width(); j++)
    {
      p = m_img.pixel(j,i);
      h[0][qRed(p)]+=1;
      h[1][qGreen(p)]+=1;
      h[2][qBlue(p)]+=1;
    }
  }

  for(int i=0; i<3; i++){
    for(int j=0; j<256; j++){
      h[i][j] = h[i][j]/(m_img.height()*m_img.width());
    }
  }
  return h;
}

vector<double> Image::fourier(void)
{
  vector< <vector < vector <double> > > f;
  f.push_back(vector<
  for(int i = 0 ; i<m_img.height(); i++)
  {
    f[0].push_back(vector<double>(m_img.width(),0);
    f[1].push_back(vector<double>(m_img.width(),0);
    f[2].push_back(vector<double>(m_img.width(),0);
    for(int j = 0; j<m_img.width(); j++)
    {
    }
  }
  return f;
}
