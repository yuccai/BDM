#include "Window.h"
#include <QFileDialog>
#include <iostream>


Window::Window() : QWidget()
{
  initLayout();
  m_button_addFile = new QPushButton("Add File");
  m_list_path = new QListWidget();
  m_label_img = new QLabel();
  m_tabs = new QTabWidget();
  m_list_path->setMinimumWidth(200);
  initCustomPlot();

  QObject::connect(m_button_addFile, &QPushButton::clicked, this, &Window::openFile);
  QObject::connect(m_list_path, &QListWidget::itemActivated, this, &Window::displayImage);

  QImage img("img/banana.jpg");
  QPixmap pixmap = QPixmap::fromImage(img);
  m_label_img->setPixmap(pixmap);

  m_left_layout->addWidget(m_list_path);
  m_left_layout->addWidget(m_button_addFile);
  m_right_layout->addWidget(m_tabs);

  m_tabs->addTab(m_label_img, "Image de base");
  m_tabs->addTab(m_customPlot, "Histogramme");


  setWindowTitle("Projet Banque de données multimédia");
  show();
}

Window::~Window(void)
{
  delete(m_customPlot);
  delete(m_button_addFile);
  delete(m_list_path);
  delete(m_label_img);
  delete(m_tabs);
  delete(m_left_layout);
  delete(m_right_layout);
  delete(m_main_layout);
}

void Window::initLayout(void)
{
  m_main_layout = new QHBoxLayout();
  m_left_layout = new QVBoxLayout();
  m_right_layout = new QVBoxLayout();
  m_main_layout->addLayout(m_left_layout);
  m_main_layout->addLayout(m_right_layout);
  setLayout(m_main_layout);
}

void Window::initCustomPlot(void)
{
  m_customPlot = new QCustomPlot();

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
  g_histo->setBrush(QColor(1, 92, 191, 50));
  pen.setColor(QColor(1, 92, 191));
  b_histo->setName("Blue");
  b_histo->setPen(pen);
  b_histo->setBrush(QColor(150, 222, 0, 70));

  // prepare x axis with country labels:
  m_customPlot->xAxis->setAutoTicks(true);
  m_customPlot->xAxis->setAutoTickLabels(true);
  m_customPlot->xAxis->setSubTickCount(0);
  m_customPlot->xAxis->setTickLength(0, 2);
  m_customPlot->xAxis->grid()->setVisible(true);
  m_customPlot->xAxis->setRange(0, 255);
  m_customPlot->xAxis->setPadding(10);

  //prepare y axis:
  m_customPlot->yAxis->setRange(0, 1);
  m_customPlot->yAxis->setLabelPadding(0.1);

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

void Window::openFile(void)
{
  QStringList files = QFileDialog::getOpenFileNames(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");

  foreach(QString file, files)
  {
    Image *it = new Image();
    it->setName(file.split("/").last());
    it->setPath(file);
    it->setText(it->getName());
    it->loadImage(file);
    m_list_path->insertItem(0,it);
    if(file == files.first())
      displayImage(it);
  }
}

void Window::displayImage(QListWidgetItem *l)
{
  Image& img = dynamic_cast<Image&>(*l);
  m_label_img->setPixmap(QPixmap::fromImage(img.getImage()).scaled(680,460));
  img.displayHistogramme(m_customPlot);
}

QCustomPlot* Window::getCustomPlot(void)
{
  return m_customPlot;
}
