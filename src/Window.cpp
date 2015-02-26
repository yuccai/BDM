#include "Window.h"
#include <QFileDialog>
#include <iostream>
#include "lib/qcustomplot.h"


Window::Window() : QWidget()
{
  initLayout();
  m_button_addFile = new QPushButton("Add File");
  m_list_path = new QListWidget();
  m_label_img = new QLabel();
  m_tabs = new QTabWidget();
  m_list_path->setMinimumWidth(200);

  QObject::connect(m_button_addFile, &QPushButton::clicked, this, &Window::openFile);
  QObject::connect(m_list_path, &QListWidget::itemActivated, this, &Window::displayImage);

  QImage img("img/banana.jpg");
  QPixmap pixmap = QPixmap::fromImage(img);
  m_label_img->setPixmap(pixmap);

  m_left_layout->addWidget(m_list_path);
  m_left_layout->addWidget(m_button_addFile);
  m_right_layout->addWidget(m_tabs);

  m_tabs->addTab(m_label_img, "Image de base");
  // generate some data:
   QCustomPlot *customPlot = new QCustomPlot();
   QVector<double> x(101), y(101); // initialize with entries 0..100
   for (int i=0; i<101; ++i)
   {
     x[i] = i/50.0 - 1; // x goes from -1 to 1
       y[i] = x[i]*x[i]; // let's plot a quadratic function
       }
       // create graph and assign data to it:
       customPlot->addGraph();
       customPlot->graph(0)->setData(x, y);
       // give the axes some labels:
       customPlot->xAxis->setLabel("x");
       customPlot->yAxis->setLabel("y");
       // set axes ranges, so we see all data:
       customPlot->xAxis->setRange(-1, 1);
       customPlot->yAxis->setRange(0, 1);
       customPlot->replot();
       m_tabs->addTab(customPlot, "Histogramme");

  setWindowTitle("Projet Banque de données multimédia");
  show();
}

Window::~Window()
{
  delete(m_button_addFile);
  delete(m_list_path);
  delete(m_label_img);
  delete(m_left_layout);
  delete(m_right_layout);
  delete(m_main_layout);
}

void Window::initLayout()
{
  m_main_layout = new QHBoxLayout();
  m_left_layout = new QVBoxLayout();
  m_right_layout = new QVBoxLayout();
  m_main_layout->addLayout(m_left_layout);
  m_main_layout->addLayout(m_right_layout);
  setLayout(m_main_layout);
}

void Window::openFile()
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
}
