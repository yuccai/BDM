#include <QFont>
#include <vector>
#include <QVector>
#include "Page2.h"

Page2::Page2(void) : QLabel()
{
  m_customPlot = new QCustomPlot();
  m_layout = new QVBoxLayout();

  initCustomPlot();

  this->setLayout(m_layout);
  m_layout->addWidget(m_customPlot);
  QObject::connect(m_customPlot, &QCustomPlot::legendClick, this, &Page2::toggleBarChart);
}

Page2::~Page2(void)
{
  delete(m_customPlot);
  delete(m_layout);
}

void Page2::initCustomPlot(void)
{
  //create empty bar chart objects:
  QCPBars *r_histo = new QCPBars(m_customPlot->xAxis, m_customPlot->yAxis);
  QCPBars *g_histo = new QCPBars(m_customPlot->xAxis, m_customPlot->yAxis);
  QCPBars *b_histo = new QCPBars(m_customPlot->xAxis, m_customPlot->yAxis);
  m_customPlot->addPlottable(r_histo);
  m_customPlot->addPlottable(g_histo);
  m_customPlot->addPlottable(b_histo);
  // set names and colors:
  QPen pen;
  pen.setWidthF(1.2);
  pen.setColor(QColor(255, 131, 0));
  r_histo->setName("Red");
  r_histo->setPen(pen);
  r_histo->setBrush(QColor(255, 131, 0, 50));
  pen.setColor(QColor(150, 222, 0));
  g_histo->setName("Green");
  g_histo->setPen(pen);
  g_histo->setBrush(QColor(150, 222, 0, 70));
  pen.setColor(QColor(1, 92, 191));
  b_histo->setName("Blue");
  b_histo->setPen(pen);
  b_histo->setBrush(QColor(1, 92, 191, 50));

  // prepare x axis with country labels:
  m_customPlot->xAxis->setAutoTicks(true);
  m_customPlot->xAxis->setAutoTickLabels(true);
  m_customPlot->xAxis->setSubTickCount(0);
  m_customPlot->xAxis->setTickLength(0, 2);
  m_customPlot->xAxis->grid()->setVisible(true);

  //prepare y axis:
  m_customPlot->yAxis->setAutoTicks(true);
  m_customPlot->yAxis->setAutoTickLabels(true);
  m_customPlot->yAxis->setSubTickCount(0);
  m_customPlot->yAxis->setTickLength(0, 2);
  m_customPlot->yAxis->grid()->setVisible(true);
  m_customPlot->yAxis->setRange(0, 1);

  //setup legend:
  m_customPlot->legend->setVisible(true);
  m_customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
  m_customPlot->legend->setBrush(QColor(255, 255, 255, 200));
  QPen legendPen;
  legendPen.setColor(QColor(130, 130, 130, 200));
  m_customPlot->legend->setBorderPen(legendPen);
  QFont legendFont = font();
  legendFont.setPointSize(10);
  m_customPlot->legend->setFont(legendFont);
  m_customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void Page2::display(Image img)
{
  //Add data:
  Histogram h = img.getHistogram();
  h.compute(img.getImageOriginal());
  QCPBars* h_histo[3];

  m_customPlot->xAxis->setRange(-1, h.getHistoSize()+1);

  QVector<double>  ticks;
  for(int i=0; i<h.getHistoSize(); i++)
    ticks << i;
  for(int i=0; i<3; i++)
    h_histo[i] = dynamic_cast<QCPBars*>(m_customPlot->plottable(i));

  h_histo[0]->setData(ticks, h.getRedPix());
  h_histo[1]->setData(ticks, h.getGreenPix());
  h_histo[2]->setData(ticks, h.getBluePix());
  m_customPlot->replot();
}

void Page2::toggleBarChart(QCPLegend *l, QCPAbstractLegendItem *i, QMouseEvent *e)
{
  QCPPlottableLegendItem *it;
  QCPBars *b_clicked;

  it = dynamic_cast<QCPPlottableLegendItem*>(i);
  b_clicked = dynamic_cast<QCPBars*> (it->plottable());
  b_clicked->setVisible(!b_clicked->visible());
}
