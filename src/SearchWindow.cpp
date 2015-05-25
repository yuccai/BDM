#include "SearchWindow.h"

SearchWindow::SearchWindow() : QDialog()
{
  m_button_openFile = new QPushButton("Selection fichier");
  m_searchImg = new Image();
  m_labelImg = new QLabel();
  m_layout = new QHBoxLayout();

  this->setLayout(m_layout);
  m_layout->addWidget(m_labelImg);
  m_layout->addWidget(m_button_openFile);

  QObject::connect(m_button_openFile, &QPushButton::clicked, this, &SearchWindow::openFile);
}

SearchWindow::~SearchWindow()
{
  delete(m_button_openFile);
  delete(m_labelImg);
  delete(m_searchImg);
  delete(m_layout);
}

void SearchWindow::openFile(void)
{
  QString file = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");

  m_searchImg->setName(file.split("/").last());
  m_searchImg->setPath(file);
  m_searchImg->setText(m_searchImg->getName());
  m_searchImg->loadImage(file);
  m_labelImg->setPixmap(QPixmap::fromImage(m_searchImg->getImageOriginal()).scaled(480,360));
  compute();
}

void SearchWindow::compute(void)
{
  Histogram histo = m_searchImg->getHistogram();
  histo.compute(m_searchImg->getImageOriginal());
}
