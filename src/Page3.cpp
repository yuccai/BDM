#include "Page3.h"

Page3::Page3(void) : QLabel()
{
  m_label_img = new QLabel();
  m_layout = new QHBoxLayout();
  m_groupbox = new QGroupBox("Options");
  m_layout_threshold = new QHBoxLayout();
  m_layout_morpho = new QHBoxLayout();
  m_form_layout = new QFormLayout();
  m_button_filter_avg = new QPushButton("Filtre moyen");
  m_button_fourier = new QPushButton("Fourier");
  m_button_fourier_cut = new QPushButton("Fourier restreint");
  m_button_fourier_inverse = new QPushButton("Fourier inverse");
  m_button_sobel = new QPushButton("Filtre de Sobel");
  m_button_bounding_box = new QPushButton("Boîte englobante");
  m_button_threshold = new QPushButton("Seuillage");
  m_box_interest_points = new QCheckBox("Points d'intérêts");
  m_hide_options = new QCheckBox("Masquer les options");
  m_button_hough = new QPushButton("Transformée de Hough");
  m_button_reset = new QPushButton("Reset");
  m_button_erosion = new QPushButton("Erosion");
  m_button_dilatation = new QPushButton("Dilatation");
  m_button_negative = new QPushButton("Negatif");
  m_threshold_inf = new QSpinBox();
  m_threshold_inf->setMinimum(0);
  m_threshold_inf->setMaximum(255);
  m_threshold_inf->setValue(128);
  m_threshold_sup = new QSpinBox();
  m_threshold_sup->setMinimum(0);
  m_threshold_sup->setMaximum(255);
  m_threshold_sup->setValue(255);
  m_morpho_r = new QSpinBox();
  m_morpho_r->setMinimum(0);
  m_morpho_r->setValue(4);

  m_label_img->setMinimumWidth(640);
  m_label_img->setMinimumHeight(480);
  setLayout(m_layout);
  m_layout->addWidget(m_label_img);
  m_layout->addWidget(m_hide_options);
  m_layout->setAlignment(m_hide_options, Qt::AlignTop);
  m_layout->addWidget(m_groupbox);
  m_groupbox->setLayout(m_form_layout);
  m_layout_threshold->addWidget(m_threshold_inf);
  m_layout_threshold->addWidget(m_threshold_sup);
  m_layout_threshold->addWidget(m_button_threshold);
  m_layout_morpho->addWidget(m_morpho_r);
  m_layout_morpho->addWidget(m_button_erosion);
  m_layout_morpho->addWidget(m_button_dilatation);

  m_form_layout->addRow("1",m_button_filter_avg);
  m_form_layout->addRow("2",m_button_fourier);
  m_form_layout->addRow("3",m_button_fourier_cut);
  m_form_layout->addRow("4",m_button_fourier_inverse);
  m_form_layout->addRow("5",m_button_sobel);
  m_form_layout->addRow("6",m_button_bounding_box);
  m_form_layout->addRow("7",m_box_interest_points);
  m_form_layout->addRow("8",m_layout_threshold);
  m_form_layout->addRow("9",m_button_hough);
  m_form_layout->addRow("10",m_button_negative);
  m_form_layout->addRow("11",m_layout_morpho);
  m_form_layout->addRow(m_button_reset);

  QObject::connect(m_button_fourier, &QCheckBox::clicked, this, &Page3::displayFourier);
  QObject::connect(m_button_fourier_cut, &QCheckBox::clicked, this, &Page3::displayFourierCut);
  QObject::connect(m_button_fourier_inverse, &QCheckBox::clicked, this, &Page3::displayFourierInverse);
  QObject::connect(m_button_filter_avg, &QCheckBox::clicked, this, &Page3::displayAvgFilter);
  QObject::connect(m_button_sobel, &QCheckBox::clicked, this, &Page3::displaySobelFilter);
  QObject::connect(m_button_threshold, &QCheckBox::clicked, this, &Page3::displayThresold);
  QObject::connect(m_button_reset, &QCheckBox::clicked, this, &Page3::reset);
  QObject::connect(m_button_hough, &QCheckBox::clicked, this, &Page3::displayHoughChart);
  QObject::connect(m_button_erosion, &QCheckBox::clicked, this, &Page3::displayErosion);
  QObject::connect(m_button_dilatation, &QCheckBox::clicked, this, &Page3::displayDilatation);
  QObject::connect(m_button_negative, &QCheckBox::clicked, this, &Page3::displayNegative);
  QObject::connect(m_box_interest_points, &QCheckBox::toggled, this, &Page3::displayInterestPoints);
  QObject::connect(m_hide_options, &QCheckBox::toggled, m_groupbox, &QGroupBox::setHidden);
}

Page3::~Page3(void)
{
  delete(m_threshold_sup);
  delete(m_threshold_inf);
  delete(m_morpho_r);
  delete(m_hide_options);
  delete(m_button_hough);
  delete(m_button_threshold);
  delete(m_button_erosion);
  delete(m_button_dilatation);
  delete(m_button_filter_avg);
  delete(m_button_negative);
  delete(m_button_fourier);
  delete(m_button_fourier_cut);
  delete(m_button_fourier_inverse);
  delete(m_button_sobel);
  delete(m_button_bounding_box);
  delete(m_box_interest_points);
  delete(m_button_reset);
  delete(m_layout_threshold);
  delete(m_layout_morpho);
  delete(m_form_layout);
  delete(m_groupbox);
  delete(m_layout);
}

void Page3::display(Image img)
{
  m_label_img->setPixmap(QPixmap::fromImage(img.getImageModified()).scaled(640,480));
  m_selected_img = img;
}

void Page3::displayFourier()
{
  m_selected_img.applyFourier();
  display(m_selected_img);
}

void Page3::displayFourierCut()
{
  m_selected_img.applyFourierCut();
  display(m_selected_img);
}

void Page3::displayFourierInverse()
{
  m_selected_img.applyFourierInverse();
  display(m_selected_img);
}

void Page3::displayAvgFilter()
{
  m_selected_img.applyAvgFilter();
  display(m_selected_img);
}

void Page3::displaySobelFilter()
{
  m_selected_img.applySobelFilter();
  display(m_selected_img);
}

void Page3::reset()
{
  int c;
  QImage img = m_selected_img.getImageModified();
  img.load(m_selected_img.getPath());
  if(img.height() > 500)
    img = img.scaledToHeight(500);
  for(int i =0; i< img.height(); i++){
    for(int j=0; j< img.width(); j++){
      c = qGray(img.pixel(j,i));
      img.setPixel(j,i,QColor::fromRgb(c,c,c).rgb());
    }
  }
  m_selected_img.setImageModified(img);
  display(m_selected_img);
}

void Page3::displayThresold()
{
  m_selected_img.applyThreshold(m_threshold_inf->value(),m_threshold_sup->value());
  display(m_selected_img);
}

void Page3::displayInterestPoints(bool b)
{
  QImage img(m_selected_img.getImageModified());;
  if(b)
  {
    QList <QPoint> l = m_selected_img.applyInterestPoints();
    foreach(QPoint p, l)
    {
      /*
      for(int i=-1; i<3; i++)
        for(int j=-1; j<3; j++)
          if( (j+p.x()) >=0 && (j+p.x()) < img.width() && (i+p.y()) >=0 && (i+p.y()) < img.height())
            img.setPixel(j+p.x(),i+p.y(),QColor::fromRgb(255,0,0).rgb());
            */
        img.setPixel(p.x(),p.y(),QColor::fromRgb(255,0,0).rgb());
    }
    m_label_img->setPixmap(QPixmap::fromImage(img.scaled(640,480)));
  }
  else
    display(m_selected_img);
}

void Page3::displayHoughChart()
{
  m_hough.compute(m_selected_img);
  m_hough.plot();
  m_hough.exec();
  displayHough();
}

void Page3::displayHough()
{
  QImage img(m_selected_img.getImageModified());
  m_hough.applyHough(&img);
  //m_selected_img.setImageModified(img);
  //display(m_selected_img);
  /*
  QList <QPoint> l = m_selected_img.applyInterestPoints();
  foreach(QPoint p, l)
  {
    for(int i=-1; i<3; i++)
      for(int j=-1; j<3; j++)
        if( (j+p.x()) >=0 && (j+p.x()) < img.width() && (i+p.y()) >=0 && (i+p.y()) < img.height())
          img.setPixel(j+p.x(),i+p.y(),QColor::fromRgb(255,0,0).rgb());
  }
  */
  m_label_img->setPixmap(QPixmap::fromImage(img.scaled(640,480)));
}

void Page3::displayErosion()
{
  m_selected_img.applyErosion(m_morpho_r->value());
  display(m_selected_img);
}

void Page3::displayDilatation()
{
  m_selected_img.applyDilatation(m_morpho_r->value());
  display(m_selected_img);
}

void Page3::displayNegative()
{
  m_selected_img.applyNegative();
  display(m_selected_img);
}
