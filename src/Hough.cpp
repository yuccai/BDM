#include "Hough.h"
#include "Filter.h"

Hough::Hough() : QDialog()
{
  m_customPlot = new QCustomPlot();
  m_button_find_lines = new QPushButton("Trouver les lignes");
  m_layout = new QVBoxLayout();
  m_layout_spin_box = new QHBoxLayout();
  m_epsilon_rho = new QSpinBox();
  m_epsilon_theta = new QSpinBox();
  m_nbPointsPerLine = new QSpinBox();

  this->setLayout(m_layout);
  m_layout->addWidget(m_customPlot);
  m_layout->addItem(m_layout_spin_box);
  m_layout->addWidget(m_button_find_lines);
  m_layout_spin_box->addWidget(m_epsilon_rho);
  m_layout_spin_box->addWidget(m_epsilon_theta);
  m_layout_spin_box->addWidget(m_nbPointsPerLine);
  m_epsilon_theta->setValue(0.1);
  m_epsilon_rho->setValue(1);
  m_nbPointsPerLine->setValue(50);


  initCustomPlot();
  m_step = 100;

  setWindowTitle("Transformée de Hough");

  QObject::connect(m_button_find_lines, &QPushButton::clicked, this, &Hough::findLines);
  resize (500,400);
}

Hough::~Hough()
{
  delete(m_nbPointsPerLine);
  delete(m_epsilon_theta);
  delete(m_epsilon_theta);
  delete(m_customPlot);
  delete(m_button_find_lines);
  delete(m_layout_spin_box);
  delete(m_layout);
}

void Hough::compute(Image img)
{
  Filter f;
  QList <QPoint> points;
  int i;
  double h,w, theta;

  points = f.findHoughPoints(img.getImageModified());
  h = img.getImageModified().height();
  w = img.getImageModified().width();
  m_nbPoints = points.count();

  m_customPlot->yAxis->setRange(max(w,h),-max(w,h));

  m_datas.resize(m_nbPoints);
  m_ticks.resize(m_step);

  for(i=0; i<m_nbPoints; i++){
    m_datas[i].resize(m_step);
  }

  i=0;
  foreach(QPoint p, points)
  {
    theta = -M_PI/2;
    for(int j=0; j<m_step; j++){
      theta += 1/((double) m_step)*M_PI;
      if(i == 0)
        m_ticks[j] = theta;
      m_datas[i][j] = p.x()*cos(theta) + p.y()*sin(theta);
    }
    i++;
  }
}

void Hough::initCustomPlot()
{
  m_customPlot->xAxis->setLabel("theta");
  m_customPlot->xAxis->setAutoTicks(true);
  m_customPlot->xAxis->setAutoTickLabels(true);
  m_customPlot->xAxis->setSubTickCount(0);
  m_customPlot->xAxis->setTickLength(0, 2);
  m_customPlot->xAxis->grid()->setVisible(true);

  m_customPlot->yAxis->setLabel("rho");
  m_customPlot->yAxis->setAutoTicks(true);
  m_customPlot->yAxis->setAutoTickLabels(true);
  m_customPlot->yAxis->setSubTickCount(0);
  m_customPlot->yAxis->setTickLength(0, 2);
  m_customPlot->yAxis->grid()->setVisible(true);

  m_customPlot->xAxis->setRange(-M_PI/2, M_PI/2);

  m_customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void Hough::plot()
{
  m_customPlot->clearGraphs();
  for(int i=0; i<m_nbPoints; i++)
  {
    m_customPlot->addGraph();
    m_customPlot->graph(i)->setData(m_ticks,m_datas[i]);
  }
  m_customPlot->replot();
}

void Hough::findLines()
{
  int i,j,k;
  double epsilon;
  double p0Y, pY, avg, e_rho, e_theta;
  int nbPointsperLine, c;

  i=0;
  /*
  epsilon = m_epsilon_theta->value();
  e_theta = m_epsilon_theta->value();
  e_rho = m_epsilon_rho->value();
  nbPointsperLine = m_nbPointsPerLine->value();
  */
  epsilon = 0.1;
  e_theta = 2;
  e_rho = 2;
  nbPointsperLine = 25;
  m_lines.clear();

  for(i=0; i<m_nbPoints; i++)
  {
    for(j=0; j<m_step; j++)
    {
      p0Y = m_datas[i][j];
      c = 1;
      avg = p0Y;
      for(k=i+1; k<m_nbPoints; k++)
      {
        pY = m_datas[k][j];
        if( abs(pY-p0Y) < epsilon )
        {
          avg += pY;
          c++;
        }
      }
      avg /= c;
      if(c >= nbPointsperLine)
      {
        bool b =true;
        foreach(QPointF p, m_lines)
        {
          if( (abs(p.x()-m_ticks[j]) <= e_theta) && (abs(p.y()-avg) <= e_rho))
            b = false;
        }

        if(b)
        {
          QPointF p;
          p.setX(m_ticks[j]);
          p.setY(avg);
          m_lines.append(p);
        }
      }
    }
  }
  this->close();
  std::cout << "Lines found : " << m_lines.count() << std::endl;
}

void bresenham(QImage *img, int x1, int y1, int x2, int y2, QColor c){
  int dx, dy, e, incx, incy;
  int x,y;
  int i;

  dx = abs(x2-x1);
  dy = abs(y2-y1);

  x = x1;
  y = y1;

  if(x1<x2)
    incx = 1;
  else
    incx = -1;
  if(y1<y2)
    incy = 1;
  else
    incy = -1;

  if(dx>dy){
    e = 2*dy - dx;
    for(i=0;i<dx;i++){
      img->setPixel(x,y,c.rgb());
      if(e>0){
        y += incy;
        e += 2*(dy - dx);
      }
      else
        e += 2*dy;
      x += incx;
    }
  }
  else{
    e = 2*dx - dy;
    for(i=0;i<dy;i++){
      img->setPixel(x,y,c.rgb());
      if(e>0){
        x += incx;
        e += 2*(dx - dy);
      }
      else
        e += 2*dx;
      y += incy;
    }
  }
}

void Hough::applyHough(QImage* img)
{
  int h,w;
  double a,b;

  h = img->height();
  w = img->width();

  foreach(QPointF p, m_lines)
  {
    if(p.x()!=0){
        a = -1/(tan(p.x()));
        b = p.y()*(sin(p.x()) + cos(p.x())*cos(p.x())/sin(p.x()));
    }
    else
    {
      a = 0;
      b = 0;
    }
    int x1,x2,y1,y2;
    //p1
    if( (-b/a>=0) && (-b/a<w) ){
      x1 = -b/a;
      y1 = 0;
    }
    else if( ((h-b)/a>=0) && ((h-b)/a<w) ){
      x1 = (h-b)/a;
      y1 = h;
    }
    else{
      x1 = 0;
      y1 = b;
    }
    //p2
    if( (w*a+b>=0) && (w*a+b<h) ){
      x2 = w;
      y2 = w*a+b;
    }
    else if ( ((h-b)/a >=0) && ((h-b)/a < w) ){
      x2 = (h-b)/a;
      y2 = h;
    }
    else{
      x2 = -b/a;
      y2 = 0;
    }
    std::cout << "rho : " << p.y() << " theta " << p.x()*180/M_PI << "a : " << a << " b : " << b << "("<<x1<<","<<y1<<") ("<<x2<<","<<y2<<")"<<std::endl;
    bresenham(img,x1,y1,x2,y2,QColor::fromRgb(0,0,255));
  }
}
