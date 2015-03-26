#include "Page3.h"

Page3::Page3(void) : QLabel()
{
  m_label_img = new QLabel();
  m_layout = new QHBoxLayout();
  m_groupbox = new QGroupBox("Options");
  m_form_layout = new QFormLayout();
  m_box_filter_avg = new QCheckBox("Filtre moyen");
  m_box_fourier = new QCheckBox("Fourier");
  m_box_fourier_cut = new QCheckBox("Fourier restreint");
  m_box_fourier_inverse = new QCheckBox("Fourier inverse");
  m_box_sobel = new QCheckBox("Filtre de Sobel");
  m_box_bounding_box = new QCheckBox("Boîte englobante");
  m_box_interest_points = new QCheckBox("Points d'intérêts");
  m_button_reset = new QPushButton("Reset");

  m_label_img->setMinimumWidth(640);
  m_label_img->setMinimumHeight(480);
  setLayout(m_layout);
  m_layout->addWidget(m_label_img);
  m_layout->addWidget(m_groupbox);
  m_groupbox->setLayout(m_form_layout);

  m_form_layout->addRow("1",m_box_filter_avg);
  m_form_layout->addRow("2",m_box_fourier);
  m_form_layout->addRow("3",m_box_fourier_cut);
  m_form_layout->addRow("4",m_box_fourier_inverse);
  m_form_layout->addRow("5",m_box_sobel);
  m_form_layout->addRow("6",m_box_bounding_box);
  m_form_layout->addRow("7",m_box_interest_points);
  m_form_layout->addRow(m_button_reset);

  QObject::connect(m_box_fourier, &QCheckBox::clicked, this, &Page3::displayFourier);
}

Page3::~Page3(void)
{
  delete(m_box_filter_avg);
  delete(m_box_fourier);
  delete(m_box_fourier_cut);
  delete(m_box_fourier_inverse);
  delete(m_box_sobel);
  delete(m_box_bounding_box);
  delete(m_box_interest_points);
  delete(m_button_reset);
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
