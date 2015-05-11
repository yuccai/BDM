#include <cmath>
#include <iostream>
#include "Fourier.h"
#include <fftw3.h>
#include <QColor>

Fourier::Fourier()
{
}

Fourier::~Fourier()
{
}

void Fourier::computeForward(QImage img)
{
  int h = img.height(),
      w = img.width();
  m_h = h;
  m_w = w;
  fftw_complex *in;
  fftw_complex *out;
  fftw_plan p;

  in = (fftw_complex*) fftw_malloc(h*w*sizeof(fftw_complex));
  out = (fftw_complex*) fftw_malloc(h*w*sizeof(fftw_complex));
  m_real.resize(h);
  m_imaginary.resize(h);
  m_magnitude.resize(h);


  for(int i=0; i<h; i++)
  {
    m_real[i].resize(w);
    m_imaginary[i].resize(w);
    m_magnitude[i].resize(w);
  }

  for(int y=0; y<h; y++){
    for(int x=0; x<w; x++){
      in[y*w +x][0] = qGray(img.pixel(x,y));
      in[y*w +x][1] = 0;
    }
  }

  p = fftw_plan_dft_2d(w, h, in, out, FFTW_FORWARD, FFTW_MEASURE);
  fftw_execute(p);

  for(int i=0; i<h; i++){
    for(int j=0; j<w; j++){
      m_real[i][j] = out[i*w+j][0];
      m_imaginary[i][j] = out[i*w+j][1];
      m_magnitude[i][j] = sqrt(m_real[i][j]*m_real[i][j] + m_imaginary[i][j]*m_imaginary[i][j]);
    }
  }
  fftw_destroy_plan(p);
  if(in)
    fftw_free(in);
  if(out)
    fftw_free(out);
}

void Fourier::computeMagnitude()
{
  for(int i=0; i<m_h; i++)
    for(int j=0; j<m_w; j++)
      m_magnitude[i][j] = sqrt(m_real[i][j]*m_real[i][j] + m_imaginary[i][j]*m_imaginary[i][j]);
}

void Fourier::computeBackward(QImage *img)
{
  int h = img->height(),
      w = img->width();
  fftw_complex *in;
  fftw_complex *out;
  fftw_plan p;
  QColor col;
  int c;

  in = (fftw_complex*) fftw_malloc(h*w*sizeof(fftw_complex));
  out = (fftw_complex*) fftw_malloc(h*w*sizeof(fftw_complex));
  m_real.resize(h);
  m_imaginary.resize(h);


  for(int i=0; i<h; i++)
  {
    m_real[i].resize(w);
    m_imaginary[i].resize(w);
  }

  for(int y=0; y<h; y++){
    for(int x=0; x<w; x++){
      in[y*w +x][0] = m_real[y][x];
      in[y*w +x][1] = m_imaginary[y][x];
    }
  }

  p = fftw_plan_dft_2d(w, h, in, out, FFTW_BACKWARD, FFTW_MEASURE);
  fftw_execute(p);

  for(int i=0; i<h; i++)
  {
    for(int j=0; j<w; j++)
    {
      c = (out[i*w+j][0]+128)/(h*w);
      if(c>255)
        c=255;
      if(c<0)
        c=0;
      col.setRgb(c,c,c);
      img->setPixel(j,i,col.rgb());
    }
  }

  fftw_destroy_plan(p);
  if(in)
    fftw_free(in);
  if(out)
    fftw_free(out);
}

void Fourier::cut()
{
  int h = m_h,
      w = m_w;
  int x,y,d, D;
  D = sqrt( (w/4)*(w/4) + (h/4)*(h/4) );
  std::cout << "w : " << m_w << ", h : " << m_h << " :  > " << D << std::endl;
  for(int i=0; i<h; i++){
    for(int j=0; j<w; j++){
      x = (i+(w/2))%w - (w/2);
      y = (j+(h/2))%h - (h/2);
      d = sqrt( x*x + y*y );
      if(d > D){
        m_real[i][j] = 0;
        m_imaginary[i][j] = 0;
        m_magnitude[i][j] = 0;
      }
    }
  }
}
