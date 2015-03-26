#include <cmath>
#include <iostream>
#include "Fourier.h"
#include <fftw3.h>

Fourier::Fourier()
{
}

Fourier::~Fourier()
{
}

void Fourier::compute(QImage img)
{
  int h = img.height(),
      w = img.width();
  double c = 1/((double) h* (double) w);
  fftw_complex *in;
  fftw_complex *out;
  fftw_plan p;

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
      in[y*w +x][0] = qGray(img.pixel(x,y));
      in[y*w +x][1] = 0;
      //std::cout << qGray(img.pixel(x,y)) << std::endl;
    }
  }

  p = fftw_plan_dft_2d(w, h, in, out, FFTW_FORWARD, FFTW_MEASURE);
  fftw_execute(p);
  double max = 0;

  for(int i=0; i<h; i++){
    for(int j=0; j<w; j++){
      m_real[i][j] = sqrt(out[i*w+j][0]*out[i*w+j][0] + out[i*w+j][1]*out[i*w+j][1]);
      if(max < m_real[i][j])
        max = m_real[i][j];
    }
  }
  c = 1/max;
  std::cout << " MAX : " <<  max << std::endl;
  for(int i=0; i<h; i++){
    for(int j=0; j<w; j++){
      m_real[i][j] = m_real[i][j] * 255 * c;
    }
  }
  fftw_destroy_plan(p);
  if(in)
    fftw_free(in);
  if(out)
    fftw_free(out);

  /*
  std::cout << "h : " << h << ", w : " << w << std::endl;


  for(int v=0; v<h; v++)
  {
    for(int u=0; u<w; u++)
    {
      for(int y=0; y<h; y++)
      {
        for(int x=0; x<w; x++)
        {
          p = img.pixel(x,y);
          m_real[v][u]      += qGray(p)*cos(-2*M_PI*((u-w/2)*x/w + (v-h/2)*y/h));
          m_imaginary[v][u] += qGray(p)*sin(-2*M_PI*((u-w/2)*x/w + (v-h/2)*y/h));
        }
      }
      //std::cout << v << " 1 " << m_real[v][u] << std::endl;
      m_real[v][u]      = abs(m_real[v][u]/(h*w));
      m_imaginary[v][u] = abs(m_imaginary[v][u]/(h*w));
      if(m_real[v][u] > 0)
        std::cout << m_real[v][u] << std::endl;
    }
    std::cout << "h : " << v << std::endl;
  }
  */
}
